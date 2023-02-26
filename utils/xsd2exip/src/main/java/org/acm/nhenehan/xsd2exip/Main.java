/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Project/Maven2/JavaApp/src/main/java/${packagePath}/${mainClassName}.java to edit this template
 */
package org.acm.nhenehan.xsd2exip;

import com.siemens.ct.exi.core.EXIFactory;
import com.siemens.ct.exi.core.EncodingOptions;
import com.siemens.ct.exi.core.FidelityOptions;
import com.siemens.ct.exi.core.exceptions.EXIException;
import com.siemens.ct.exi.core.helpers.DefaultEXIFactory;
import com.siemens.ct.exi.main.api.sax.EXIResult;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.xml.sax.SAXException;
import org.xml.sax.XMLReader;
import org.xml.sax.helpers.XMLReaderFactory;

/**
 *
 * @author Nathan Henehan <nhenehan@acm.org>
 */
public class Main {
    
    protected static void generate(String xsdin, String exiout){

        /**
         * From EXIP Manual: When encoding the XML Schema file you should use
         * schema-less mode indicated by “Use Schema: None” and also set the
         * Preserve.prefixes option by checking the “Preserve Namespace
         * Declarations” checkbox. It is recommended to encode these options in
         * the header by setting “Include options” checkbox. If you leave the
         * “Include options” unchecked, you need to use the -ops= argument of
         * the exipg utility to specify the out-of-band options.
         */
        try {
            EXIFactory exiFactory = DefaultEXIFactory.newInstance();

            FidelityOptions fidelityOptions = FidelityOptions.createDefault();
            fidelityOptions.setFidelity(FidelityOptions.FEATURE_PREFIX, true);
            exiFactory.setFidelityOptions(fidelityOptions);

            EncodingOptions encodingOptions = EncodingOptions.createDefault();
            encodingOptions.setOption(EncodingOptions.INCLUDE_OPTIONS);
            exiFactory.setEncodingOptions(encodingOptions);

            String fileEXI = exiout; // EXI output
            try ( OutputStream osEXI = new FileOutputStream(fileEXI)) {
                EXIResult exiResult = new EXIResult(exiFactory);
                exiResult.setOutputStream(osEXI);
                XMLReader xmlReader = XMLReaderFactory.createXMLReader();
                xmlReader.setContentHandler(exiResult.getHandler());
                xmlReader.parse(xsdin); // parse XML input
            }
        } catch (IOException | SAXException | EXIException ex) {
            Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Ussage:");
            System.out.println("xsd2exip <path-to-xsd> <exi-output-path>");
            System.exit(-1);
        }
        
        generate(args[0], args[1]);
    }
}
