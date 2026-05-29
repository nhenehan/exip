package org.acm.nhenehan.xsd2exip;

import com.siemens.ct.exi.core.EXIFactory;
import com.siemens.ct.exi.core.EncodingOptions;
import com.siemens.ct.exi.core.exceptions.EXIException;
import com.siemens.ct.exi.core.grammars.Grammars;
import com.siemens.ct.exi.core.helpers.DefaultEXIFactory;
import com.siemens.ct.exi.grammars.GrammarFactory;
import com.siemens.ct.exi.main.api.sax.EXIResult;
import com.siemens.ct.exi.main.api.sax.EXISource;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.StringWriter;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParserFactory;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.stream.StreamResult;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;
import org.xml.sax.XMLReader;

public final class ExiInteropTool {

    private ExiInteropTool() {
    }

    public static void main(String[] args) throws Exception {
        if (args.length < 3) {
            printUsage();
            System.exit(1);
        }

        String mode = args[0];
        switch (mode) {
            case "decode-xml" -> {
                if (args.length != 3) {
                    printUsage();
                    System.exit(1);
                }
                System.out.print(decodeXml(args[1], args[2]));
            }
            case "encode-xml" -> {
                if (args.length != 4) {
                    printUsage();
                    System.exit(1);
                }
                encodeXml(args[1], args[2], args[3]);
            }
            default -> {
                printUsage();
                System.exit(1);
            }
        }
    }

    static void encodeXml(String xsdPath, String xmlPath, String exiPath)
            throws IOException, SAXException, EXIException, ParserConfigurationException {
        EXIFactory exiFactory = buildFactory(xsdPath);

        try (OutputStream osEXI = new FileOutputStream(exiPath)) {
            EXIResult exiResult = new EXIResult(exiFactory);
            exiResult.setOutputStream(osEXI);
            SAXParserFactory parserFactory = SAXParserFactory.newInstance();
            parserFactory.setNamespaceAware(true);
            XMLReader xmlReader = parserFactory.newSAXParser().getXMLReader();
            xmlReader.setContentHandler(exiResult.getHandler());
            xmlReader.parse(xmlPath);
        }
    }

    static String decodeXml(String xsdPath, String exiPath)
            throws IOException, EXIException, TransformerException {
        EXIFactory exiFactory = buildFactory(xsdPath);
        EXISource exiSource = new EXISource(exiFactory);

        try (InputStream exiInput = new FileInputStream(exiPath)) {
            exiSource.setInputSource(new InputSource(exiInput));

            Transformer transformer = TransformerFactory.newInstance().newTransformer();
            transformer.setOutputProperty(OutputKeys.OMIT_XML_DECLARATION, "yes");
            transformer.setOutputProperty(OutputKeys.INDENT, "no");

            StringWriter xml = new StringWriter();
            transformer.transform(exiSource, new StreamResult(xml));
            return xml.toString();
        }
    }

    static EXIFactory buildFactory(String xsdPath) throws EXIException {
        EXIFactory exiFactory = DefaultEXIFactory.newInstance();
        EncodingOptions encodingOptions = EncodingOptions.createDefault();
        encodingOptions.setOption(EncodingOptions.INCLUDE_OPTIONS);
        exiFactory.setEncodingOptions(encodingOptions);

        if (!"none".equals(xsdPath)) {
            Grammars grammars = GrammarFactory.newInstance().createGrammars(xsdPath);
            exiFactory.setGrammars(grammars);
        }

        return exiFactory;
    }

    private static void printUsage() {
        System.out.println("Usage:");
        System.out.println("  ExiInteropTool decode-xml <xsd-path|none> <input.exi>");
        System.out.println("  ExiInteropTool encode-xml <xsd-path|none> <input.xml> <output.exi>");
    }
}