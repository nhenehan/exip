package org.acm.nhenehan.xsd2exip;

import com.siemens.ct.exi.core.CodingMode;
import com.siemens.ct.exi.core.EXIBodyDecoder;
import com.siemens.ct.exi.core.EXIFactory;
import com.siemens.ct.exi.core.EncodingOptions;
import com.siemens.ct.exi.core.FidelityOptions;
import com.siemens.ct.exi.core.container.DocType;
import com.siemens.ct.exi.core.container.NamespaceDeclaration;
import com.siemens.ct.exi.core.container.ProcessingInstruction;
import com.siemens.ct.exi.core.context.GrammarContext;
import com.siemens.ct.exi.core.context.GrammarUriContext;
import com.siemens.ct.exi.core.context.QNameContext;
import com.siemens.ct.exi.core.datatype.Datatype;
import com.siemens.ct.exi.core.datatype.EnumDatatype;
import com.siemens.ct.exi.core.datatype.ListDatatype;
import com.siemens.ct.exi.core.datatype.NBitUnsignedIntegerDatatype;
import com.siemens.ct.exi.core.datatype.RestrictedCharacterSetDatatype;
import com.siemens.ct.exi.core.datatype.charset.RestrictedCharacterSet;
import com.siemens.ct.exi.core.exceptions.EXIException;
import com.siemens.ct.exi.core.grammars.Grammars;
import com.siemens.ct.exi.core.grammars.event.Attribute;
import com.siemens.ct.exi.core.grammars.event.AttributeNS;
import com.siemens.ct.exi.core.grammars.event.DatatypeEvent;
import com.siemens.ct.exi.core.grammars.event.Event;
import com.siemens.ct.exi.core.grammars.event.EventType;
import com.siemens.ct.exi.core.grammars.event.StartElement;
import com.siemens.ct.exi.core.grammars.event.StartElementNS;
import com.siemens.ct.exi.core.grammars.grammar.Grammar;
import com.siemens.ct.exi.core.grammars.grammar.SchemaInformedFirstStartTagGrammar;
import com.siemens.ct.exi.core.grammars.grammar.SchemaInformedGrammar;
import com.siemens.ct.exi.core.grammars.production.Production;
import com.siemens.ct.exi.core.helpers.DefaultEXIFactory;
import com.siemens.ct.exi.core.values.QNameValue;
import com.siemens.ct.exi.core.values.Value;
import com.siemens.ct.exi.grammars.GrammarFactory;
import com.siemens.ct.exi.main.api.sax.EXIResult;
import com.siemens.ct.exi.main.api.sax.EXISource;
import java.io.BufferedInputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import java.io.StringWriter;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.IdentityHashMap;
import java.util.List;
import java.util.Map;
import javax.xml.namespace.QName;
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

/**
 * Flag-driven EXIficient oracle CLI used by the rexi interop fixtures.
 *
 * <pre>
 * ExiInteropTool encode-xml    --xsd a.xsd|none --xml in.xml --out out.exi [opts]
 * ExiInteropTool decode-xml    --xsd a.xsd|none --exi in.exi [opts]          (XML on stdout)
 * ExiInteropTool dump-events   --xsd a.xsd|none --exi in.exi [opts]          (one event per line)
 * ExiInteropTool dump-grammars --xsd a.xsd [--out g.txt]                     (grammar dump)
 * ExiInteropTool encode-xsd    --xsd a.xsd --xsd-exi-out a.xsd.exi           (schema EXI for exip)
 * ExiInteropTool xsd2exip      &lt;Main args...&gt;                            (delegates to Main)
 * </pre>
 */
public final class ExiInteropTool {

    private static final String EXIFICIENT_VERSION = "1.0.7";

    private ExiInteropTool() {
    }

    static final class Options {
        String mode;
        String xsd = "none";
        String xml;
        String exi;
        String out;
        String xsdExiOut;
        boolean strict = false;
        CodingMode codingMode = CodingMode.BIT_PACKED;
        boolean includeOptions = false;
        boolean includeCookie = false;
        String schemaId;
        int valueMaxLength = -1;
        int valuePartitionCapacity = -1;
        List<String> preserve = new ArrayList<>();
        List<String> positional = new ArrayList<>();
    }

    public static void main(String[] args) throws Exception {
        if (args.length < 1) {
            printUsage();
            System.exit(1);
        }

        String mode = args[0];
        if ("xsd2exip".equals(mode)) {
            Main.main(Arrays.copyOfRange(args, 1, args.length));
            return;
        }
        if ("--help".equals(mode) || "-h".equals(mode) || "help".equals(mode)) {
            printUsage();
            return;
        }

        Options opts;
        try {
            opts = parseArgs(args);
        } catch (IllegalArgumentException ex) {
            System.err.println("error: " + ex.getMessage());
            printUsage();
            System.exit(2);
            return;
        }

        switch (opts.mode) {
            case "encode-xml" -> {
                require(opts.xml, "--xml");
                require(opts.out, "--out");
                encodeXml(opts);
            }
            case "decode-xml" -> {
                require(opts.exi, "--exi");
                String xml = decodeXml(opts);
                PrintStream out = new PrintStream(System.out, true, StandardCharsets.UTF_8);
                out.print(xml);
                out.flush();
            }
            case "dump-events" -> {
                require(opts.exi, "--exi");
                PrintStream out = new PrintStream(System.out, true, StandardCharsets.UTF_8);
                dumpEvents(opts, out);
                out.flush();
            }
            case "dump-grammars" -> {
                if ("none".equals(opts.xsd)) {
                    throw new IllegalArgumentException("dump-grammars requires --xsd <file>");
                }
                if (opts.out != null) {
                    try (PrintStream out = new PrintStream(new FileOutputStream(opts.out), false, StandardCharsets.UTF_8)) {
                        dumpGrammars(opts, out);
                    }
                } else {
                    PrintStream out = new PrintStream(System.out, true, StandardCharsets.UTF_8);
                    dumpGrammars(opts, out);
                    out.flush();
                }
            }
            case "encode-xsd" -> {
                if ("none".equals(opts.xsd)) {
                    throw new IllegalArgumentException("encode-xsd requires --xsd <file>");
                }
                String target = opts.xsdExiOut != null ? opts.xsdExiOut : opts.out;
                require(target, "--xsd-exi-out");
                // Same encoding exip expects for schema documents: schema-less,
                // Preserve.prefixes, options in header (see Main.generate).
                Main.generate(opts.xsd, target, true);
            }
            default -> {
                System.err.println("error: unknown mode " + opts.mode);
                printUsage();
                System.exit(2);
            }
        }
    }

    private static void require(String value, String flag) {
        if (value == null) {
            throw new IllegalArgumentException("missing " + flag);
        }
    }

    // ------------------------------------------------------------------ args

    static Options parseArgs(String[] args) {
        Options o = new Options();
        o.mode = args[0];
        for (int i = 1; i < args.length; i++) {
            String a = args[i];
            if (!a.startsWith("--")) {
                o.positional.add(a);
                continue;
            }
            String key = a;
            String inlineValue = null;
            int eq = a.indexOf('=');
            if (eq > 0) {
                key = a.substring(0, eq);
                inlineValue = a.substring(eq + 1);
            }
            switch (key) {
                case "--strict" -> o.strict = true;
                case "--no-strict" -> o.strict = false;
                case "--include-options" -> o.includeOptions = true;
                case "--no-options" -> o.includeOptions = false;
                case "--cookie" -> o.includeCookie = true;
                case "--no-cookie" -> o.includeCookie = false;
                case "--xsd" -> o.xsd = value(args, i, inlineValue, key);
                case "--xml" -> o.xml = value(args, i, inlineValue, key);
                case "--exi" -> o.exi = value(args, i, inlineValue, key);
                case "--out" -> o.out = value(args, i, inlineValue, key);
                case "--xsd-exi-out" -> o.xsdExiOut = value(args, i, inlineValue, key);
                case "--schema-id" -> o.schemaId = value(args, i, inlineValue, key);
                case "--alignment" -> o.codingMode = parseAlignment(value(args, i, inlineValue, key));
                case "--value-max-length" -> o.valueMaxLength = Integer.parseInt(value(args, i, inlineValue, key));
                case "--value-partition-capacity" ->
                    o.valuePartitionCapacity = Integer.parseInt(value(args, i, inlineValue, key));
                case "--preserve" -> {
                    for (String p : value(args, i, inlineValue, key).split(",")) {
                        String t = p.trim();
                        if (!t.isEmpty()) {
                            o.preserve.add(t);
                        }
                    }
                }
                default -> throw new IllegalArgumentException("unknown flag " + key);
            }
            if (inlineValue == null && takesValue(key)) {
                i++;
            }
        }

        // Backward-compatible positional forms.
        List<String> p = o.positional;
        switch (o.mode) {
            case "encode-xml" -> {
                if (p.size() >= 1 && o.xsd.equals("none") && !p.isEmpty()) {
                    o.xsd = p.get(0);
                }
                if (p.size() >= 2 && o.xml == null) {
                    o.xml = p.get(1);
                }
                if (p.size() >= 3 && o.out == null) {
                    o.out = p.get(2);
                }
            }
            case "decode-xml", "dump-events" -> {
                if (p.size() >= 1 && o.xsd.equals("none")) {
                    o.xsd = p.get(0);
                }
                if (p.size() >= 2 && o.exi == null) {
                    o.exi = p.get(1);
                }
            }
            case "dump-grammars", "encode-xsd" -> {
                if (p.size() >= 1 && o.xsd.equals("none")) {
                    o.xsd = p.get(0);
                }
                if (p.size() >= 2 && o.out == null) {
                    o.out = p.get(1);
                }
            }
            default -> {
            }
        }

        if (o.strict) {
            for (String pr : o.preserve) {
                if (!"lexicalValues".equals(pr)) {
                    throw new IllegalArgumentException("--preserve " + pr + " is incompatible with --strict");
                }
            }
        }
        return o;
    }

    private static boolean takesValue(String key) {
        return switch (key) {
            case "--xsd", "--xml", "--exi", "--out", "--xsd-exi-out", "--schema-id", "--alignment",
                 "--value-max-length", "--value-partition-capacity", "--preserve" -> true;
            default -> false;
        };
    }

    private static String value(String[] args, int i, String inline, String key) {
        if (inline != null) {
            return inline;
        }
        if (i + 1 >= args.length) {
            throw new IllegalArgumentException(key + " requires a value");
        }
        return args[i + 1];
    }

    private static CodingMode parseAlignment(String s) {
        return switch (s) {
            case "bit-packed", "bit_packed", "BIT_PACKED" -> CodingMode.BIT_PACKED;
            case "byte-aligned", "byte-packed", "BYTE_PACKED" -> CodingMode.BYTE_PACKED;
            case "pre-compression", "PRE_COMPRESSION" -> CodingMode.PRE_COMPRESSION;
            case "compression", "COMPRESSION" -> CodingMode.COMPRESSION;
            default -> throw new IllegalArgumentException("unknown alignment " + s);
        };
    }

    // --------------------------------------------------------------- factory

    static Grammars buildGrammars(Options o) throws EXIException {
        GrammarFactory gf = GrammarFactory.newInstance();
        Grammars grammars = "none".equals(o.xsd) ? gf.createSchemaLessGrammars() : gf.createGrammars(o.xsd);
        if (o.schemaId != null) {
            grammars.setSchemaId(o.schemaId);
        }
        return grammars;
    }

    static EXIFactory buildFactory(Options o) throws EXIException {
        EXIFactory f = DefaultEXIFactory.newInstance();
        final Grammars grammars = buildGrammars(o);
        f.setGrammars(grammars);
        // When the header carries a (non-empty) schemaId, EXIficient asks a
        // resolver for the grammars; answer with the ones configured here.
        f.setSchemaIdResolver(schemaId -> {
            if (o.schemaId != null && !o.schemaId.equals(schemaId)) {
                System.err.println("warning: stream schemaId '" + schemaId + "' differs from --schema-id '"
                        + o.schemaId + "'; using --xsd grammars anyway");
            }
            return grammars;
        });
        f.setCodingMode(o.codingMode);

        FidelityOptions fidelity = o.strict ? FidelityOptions.createStrict() : FidelityOptions.createDefault();
        for (String p : o.preserve) {
            String feature = switch (p) {
                case "comments" -> FidelityOptions.FEATURE_COMMENT;
                case "pis" -> FidelityOptions.FEATURE_PI;
                case "dtd" -> FidelityOptions.FEATURE_DTD;
                case "prefixes" -> FidelityOptions.FEATURE_PREFIX;
                case "lexicalValues" -> FidelityOptions.FEATURE_LEXICAL_VALUE;
                default -> throw new IllegalArgumentException("unknown --preserve item " + p);
            };
            fidelity.setFidelity(feature, true);
        }
        f.setFidelityOptions(fidelity);

        EncodingOptions encoding = EncodingOptions.createDefault();
        if (o.includeOptions) {
            encoding.setOption(EncodingOptions.INCLUDE_OPTIONS);
        }
        if (o.includeCookie) {
            encoding.setOption(EncodingOptions.INCLUDE_COOKIE);
        }
        if (o.schemaId != null) {
            encoding.setOption(EncodingOptions.INCLUDE_SCHEMA_ID);
        }
        f.setEncodingOptions(encoding);

        if (o.valueMaxLength >= 0) {
            f.setValueMaxLength(o.valueMaxLength);
        }
        if (o.valuePartitionCapacity >= 0) {
            f.setValuePartitionCapacity(o.valuePartitionCapacity);
        }
        return f;
    }

    // ---------------------------------------------------------- encode/decode

    static void encodeXml(Options o)
            throws IOException, SAXException, EXIException, ParserConfigurationException {
        EXIFactory exiFactory = buildFactory(o);
        try (OutputStream osEXI = new FileOutputStream(o.out)) {
            EXIResult exiResult = new EXIResult(exiFactory);
            exiResult.setOutputStream(osEXI);
            SAXParserFactory parserFactory = SAXParserFactory.newInstance();
            parserFactory.setNamespaceAware(true);
            XMLReader xmlReader = parserFactory.newSAXParser().getXMLReader();
            xmlReader.setContentHandler(exiResult.getHandler());
            xmlReader.parse(o.xml);
        }
    }

    static String decodeXml(Options o) throws IOException, EXIException, TransformerException {
        EXIFactory exiFactory = buildFactory(o);
        EXISource exiSource = new EXISource(exiFactory);
        try (InputStream exiInput = new BufferedInputStream(new FileInputStream(o.exi))) {
            exiSource.setInputSource(new InputSource(exiInput));
            Transformer transformer = TransformerFactory.newInstance().newTransformer();
            transformer.setOutputProperty(OutputKeys.OMIT_XML_DECLARATION, "yes");
            transformer.setOutputProperty(OutputKeys.INDENT, "no");
            StringWriter xml = new StringWriter();
            transformer.transform(exiSource, new StreamResult(xml));
            return xml.toString();
        }
    }

    // ------------------------------------------------------------ dump-events

    static void dumpEvents(Options o, PrintStream out) throws IOException, EXIException {
        EXIFactory exiFactory = buildFactory(o);
        try (InputStream is = new BufferedInputStream(new FileInputStream(o.exi))) {
            EXIBodyDecoder d = exiFactory.createEXIStreamDecoder().decodeHeader(is);
            EventType et;
            while ((et = d.next()) != null) {
                switch (et) {
                    case START_DOCUMENT -> {
                        d.decodeStartDocument();
                        out.println("SD");
                    }
                    case END_DOCUMENT -> {
                        d.decodeEndDocument();
                        out.println("ED");
                    }
                    case START_ELEMENT, START_ELEMENT_NS, START_ELEMENT_GENERIC, START_ELEMENT_GENERIC_UNDECLARED -> {
                        QNameContext q = d.decodeStartElement();
                        out.println("SE " + clark(q));
                    }
                    case END_ELEMENT, END_ELEMENT_UNDECLARED -> {
                        d.decodeEndElement();
                        out.println("EE");
                    }
                    case ATTRIBUTE, ATTRIBUTE_NS, ATTRIBUTE_GENERIC, ATTRIBUTE_INVALID_VALUE,
                         ATTRIBUTE_ANY_INVALID_VALUE, ATTRIBUTE_GENERIC_UNDECLARED -> {
                        QNameContext q = d.decodeAttribute();
                        out.println("AT " + clark(q) + " " + escape(valueText(d.getAttributeValue())));
                    }
                    case ATTRIBUTE_XSI_TYPE -> {
                        d.decodeAttributeXsiType();
                        Value v = d.getAttributeValue();
                        if (v instanceof QNameValue qv) {
                            out.println("XSI_TYPE {" + qv.getNamespaceUri() + "}" + qv.getLocalName());
                        } else {
                            out.println("XSI_TYPE " + escape(valueText(v)));
                        }
                    }
                    case ATTRIBUTE_XSI_NIL -> {
                        d.decodeAttributeXsiNil();
                        out.println("XSI_NIL " + escape(valueText(d.getAttributeValue())));
                    }
                    case CHARACTERS, CHARACTERS_GENERIC, CHARACTERS_GENERIC_UNDECLARED -> {
                        Value v = d.decodeCharacters();
                        out.println("CH " + escape(valueText(v)));
                    }
                    case NAMESPACE_DECLARATION -> {
                        NamespaceDeclaration ns = d.decodeNamespaceDeclaration();
                        out.println("NAMESPACE_DECLARATION prefix=" + escape(ns.prefix) + " uri=" + escape(ns.namespaceURI));
                    }
                    case COMMENT -> {
                        char[] c = d.decodeComment();
                        out.println("COMMENT " + escape(new String(c)));
                    }
                    case PROCESSING_INSTRUCTION -> {
                        ProcessingInstruction pi = d.decodeProcessingInstruction();
                        out.println("PROCESSING_INSTRUCTION target=" + escape(pi.target) + " data=" + escape(pi.data));
                    }
                    case DOC_TYPE -> {
                        DocType dt = d.decodeDocType();
                        out.println("DOC_TYPE name=" + escape(new String(dt.name))
                                + " publicId=" + escape(new String(dt.publicID))
                                + " systemId=" + escape(new String(dt.systemID))
                                + " text=" + escape(new String(dt.text)));
                    }
                    case ENTITY_REFERENCE -> {
                        char[] er = d.decodeEntityReference();
                        out.println("ENTITY_REFERENCE " + escape(new String(er)));
                    }
                    case SELF_CONTAINED -> {
                        d.decodeStartSelfContainedFragment();
                        out.println("SELF_CONTAINED");
                    }
                    default -> throw new EXIException("unhandled event type " + et);
                }
            }
        }
    }

    private static String valueText(Value v) {
        return v == null ? "" : v.toString();
    }

    private static String clark(QNameContext q) {
        return "{" + q.getNamespaceUri() + "}" + q.getLocalName();
    }

    private static String clark(QName q) {
        return "{" + q.getNamespaceURI() + "}" + q.getLocalPart();
    }

    private static String escape(String s) {
        if (s == null) {
            return "";
        }
        StringBuilder sb = new StringBuilder(s.length());
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            switch (c) {
                case '\\' -> sb.append("\\\\");
                case '\n' -> sb.append("\\n");
                case '\r' -> sb.append("\\r");
                case '\t' -> sb.append("\\t");
                default -> sb.append(c);
            }
        }
        return sb.toString();
    }

    // ---------------------------------------------------------- dump-grammars

    /**
     * Deterministic text dump of the EXIficient grammar set.
     *
     * The exificient-grammars 1.0.7 artifact has no Grammars2X (only
     * Grammars2JavaSourceCode / Grammars2JSON), so the dump is produced by
     * walking the Grammars object graph directly. Grammar ids are assigned on
     * first visit in a fixed order: document grammar, then every uri context /
     * qname in string-table order (global element grammar, type grammar), with
     * productions, SE element grammars and element-content grammars followed
     * depth-first. The runtime-derived xsi:nil "type empty" grammars are not
     * part of the static set and are not dumped.
     */
    static final class GrammarDumper {
        private final Map<Grammar, Integer> ids = new IdentityHashMap<>();
        private final List<Grammar> order = new ArrayList<>();

        int idOf(Grammar g) {
            Integer id = ids.get(g);
            if (id == null) {
                id = order.size();
                ids.put(g, id);
                order.add(g);
                // depth-first assignment of everything reachable
                for (int i = 0; i < g.getNumberOfEvents(); i++) {
                    Production p = g.getProduction(i);
                    Event ev = p.getEvent();
                    if (ev instanceof StartElement se && se.getGrammar() != null) {
                        idOf(se.getGrammar());
                    }
                    if (p.getNextGrammar() != null) {
                        idOf(p.getNextGrammar());
                    }
                }
                // Note: SchemaInformedFirstStartTag.getTypeEmpty() derives a fresh
                // grammar at runtime (USE_RUNTIME_EMPTY_TYPE) on every call, so it
                // is not part of the static grammar set and is deliberately not
                // walked here (it would never terminate).
                Grammar ec = safeElementContent(g);
                if (ec != null) {
                    idOf(ec);
                }
            }
            return id;
        }

        private static Grammar safeElementContent(Grammar g) {
            try {
                return g.getElementContentGrammar();
            } catch (RuntimeException ex) {
                return null;
            }
        }

        List<Grammar> order() {
            return order;
        }
    }

    static void dumpGrammars(Options o, PrintStream out) throws EXIException {
        Grammars grammars = buildGrammars(o);
        GrammarContext gc = grammars.getGrammarContext();
        GrammarDumper dumper = new GrammarDumper();

        out.println("# exificient " + EXIFICIENT_VERSION + " grammar dump");
        out.println("schema-informed " + grammars.isSchemaInformed());
        // Grammars.getSchemaId() defaults to the xsd path passed in, which is
        // not portable; only report an explicitly requested --schema-id.
        out.println("schema-id " + (o.schemaId == null ? "<none>" : o.schemaId));
        out.println("uri-contexts " + gc.getNumberOfGrammarUriContexts());
        out.println("qname-contexts " + gc.getNumberOfGrammarQNameContexts());

        // Assign ids: document grammar first, then string-table order.
        int docId = dumper.idOf(grammars.getDocumentGrammar());
        for (int i = 0; i < gc.getNumberOfGrammarUriContexts(); i++) {
            GrammarUriContext uc = gc.getGrammarUriContext(i);
            for (int j = 0; j < uc.getNumberOfQNames(); j++) {
                QNameContext q = uc.getQNameContext(j);
                if (q.getGlobalStartElement() != null && q.getGlobalStartElement().getGrammar() != null) {
                    dumper.idOf(q.getGlobalStartElement().getGrammar());
                }
                if (q.getTypeGrammar() != null) {
                    dumper.idOf(q.getTypeGrammar());
                }
            }
        }
        int fragId = -1;
        if (grammars.getFragmentGrammar() != null) {
            fragId = dumper.idOf(grammars.getFragmentGrammar());
        }

        out.println();
        out.println("# string table (Appendix D initial uri / prefix / local-name partitions)");
        for (int i = 0; i < gc.getNumberOfGrammarUriContexts(); i++) {
            GrammarUriContext uc = gc.getGrammarUriContext(i);
            StringBuilder sb = new StringBuilder();
            sb.append("uri ").append(i).append(" \"").append(uc.getNamespaceUri()).append("\"");
            sb.append(" prefixes=[");
            for (int k = 0; k < uc.getNumberOfPrefixes(); k++) {
                if (k > 0) {
                    sb.append(',');
                }
                sb.append('"').append(uc.getPrefix(k)).append('"');
            }
            sb.append(']');
            out.println(sb);
            for (int j = 0; j < uc.getNumberOfQNames(); j++) {
                QNameContext q = uc.getQNameContext(j);
                StringBuilder l = new StringBuilder();
                l.append("  local ").append(j).append(" \"").append(q.getLocalName()).append("\"");
                if (q.getGlobalStartElement() != null) {
                    StartElement se = q.getGlobalStartElement();
                    l.append(" global-element");
                    if (se.getGrammar() != null) {
                        l.append("=").append(dumper.idOf(se.getGrammar()));
                    }
                }
                if (q.getGlobalAttribute() != null) {
                    l.append(" global-attribute").append(datatypeText(q.getGlobalAttribute().getDatatype()));
                }
                if (q.getTypeGrammar() != null) {
                    l.append(" type-grammar=").append(dumper.idOf(q.getTypeGrammar()));
                }
                out.println(l);
            }
        }

        out.println();
        out.println("# grammars");
        out.println("document-grammar " + docId);
        if (fragId >= 0) {
            out.println("fragment-grammar " + fragId);
        }
        // Printing may still discover grammars (none expected after the walk
        // above, but idOf is total so the list is appended to, never reordered).
        for (int idx = 0; idx < dumper.order().size(); idx++) {
            Grammar g = dumper.order().get(idx);
            StringBuilder h = new StringBuilder();
            h.append("grammar ").append(idx).append(" type=").append(g.getGrammarType());
            if (g instanceof SchemaInformedFirstStartTagGrammar fst) {
                h.append(" nillable=").append(fst.isNillable());
                h.append(" typecastable=").append(fst.isTypeCastable());
            }
            if (g instanceof SchemaInformedGrammar sig) {
                h.append(" declared-attributes=").append(sig.getNumberOfDeclaredAttributes());
                // Only symbolic labels; EXIficient's default label is
                // ClassName[identityHashCode], which is not stable across runs.
                String label = sig.getLabel();
                if (label != null && !label.isEmpty() && !label.matches(".*\\[-?\\d+\\]$")) {
                    h.append(" label=\"").append(escape(label)).append('"');
                }
            }
            h.append(" has-EE=").append(g.hasEndElement());
            Grammar ec = GrammarDumper.safeElementContent(g);
            if (ec != null && ec != g) {
                h.append(" element-content=").append(dumper.idOf(ec));
            }
            out.println(h);
            for (int i = 0; i < g.getNumberOfEvents(); i++) {
                Production p = g.getProduction(i);
                Event ev = p.getEvent();
                StringBuilder l = new StringBuilder();
                l.append("  ").append(i).append(": ").append(eventText(ev, dumper));
                l.append(" -> ");
                l.append(p.getNextGrammar() == null ? "-" : String.valueOf(dumper.idOf(p.getNextGrammar())));
                out.println(l);
            }
        }
    }

    private static String eventText(Event ev, GrammarDumper dumper) {
        EventType t = ev.getEventType();
        switch (t) {
            case START_DOCUMENT:
                return "SD";
            case END_DOCUMENT:
                return "ED";
            case END_ELEMENT:
                return "EE";
            case START_ELEMENT: {
                StartElement se = (StartElement) ev;
                String s = "SE " + clark(se.getQName());
                if (se.getGrammar() != null) {
                    s += " grammar=" + dumper.idOf(se.getGrammar());
                }
                return s;
            }
            case START_ELEMENT_NS:
                return "SE {" + ((StartElementNS) ev).getNamespaceURI() + "}*";
            case START_ELEMENT_GENERIC:
                return "SE *";
            case ATTRIBUTE: {
                Attribute at = (Attribute) ev;
                return "AT " + clark(at.getQName()) + datatypeText(at.getDatatype());
            }
            case ATTRIBUTE_NS:
                return "AT {" + ((AttributeNS) ev).getNamespaceURI() + "}*";
            case ATTRIBUTE_GENERIC:
                return "AT *";
            case CHARACTERS: {
                String s = "CH";
                if (ev instanceof DatatypeEvent de) {
                    s += datatypeText(de.getDatatype());
                }
                return s;
            }
            case CHARACTERS_GENERIC:
                return "CH *";
            default:
                return t.name();
        }
    }

    private static String datatypeText(Datatype dt) {
        if (dt == null) {
            return " [untyped]";
        }
        StringBuilder sb = new StringBuilder(" [");
        sb.append(dt.getBuiltInType());
        if (dt.getSchemaType() != null) {
            sb.append(" schema-type=").append(clark(dt.getSchemaType()));
        }
        if (dt.getDatatypeID() != null) {
            sb.append(" id=").append(dt.getDatatypeID());
        }
        if (dt instanceof EnumDatatype en) {
            sb.append(" bits=").append(en.getCodingLength());
            sb.append(" values=[");
            for (int i = 0; i < en.getEnumerationSize(); i++) {
                if (i > 0) {
                    sb.append('|');
                }
                sb.append(escape(valueText(en.getEnumValue(i))));
            }
            sb.append(']');
        } else if (dt instanceof NBitUnsignedIntegerDatatype nb) {
            sb.append(" lower=").append(nb.getLowerBound());
            sb.append(" upper=").append(nb.getUpperBound());
            sb.append(" bits=").append(nb.getNumberOfBits());
        } else if (dt instanceof ListDatatype ld) {
            sb.append(" item=").append(datatypeText(ld.getListDatatype()).trim());
        } else if (dt instanceof RestrictedCharacterSetDatatype rd) {
            RestrictedCharacterSet rcs = rd.getRestrictedCharacterSet();
            sb.append(" size=").append(rcs.size()).append(" bits=").append(rcs.getCodingLength());
            sb.append(" chars=[");
            for (int i = 0; i < rcs.size(); i++) {
                if (i > 0) {
                    sb.append(',');
                }
                sb.append(rcs.getCodePoint(i));
            }
            sb.append(']');
        }
        if (dt.getWhiteSpace() != null) {
            sb.append(" ws=").append(dt.getWhiteSpace());
        }
        sb.append(']');
        return sb.toString();
    }

    // ------------------------------------------------------------------ usage

    private static void printUsage() {
        System.out.println("Usage:");
        System.out.println("  ExiInteropTool encode-xml    --xsd <a.xsd>|none --xml in.xml --out out.exi [opts]");
        System.out.println("  ExiInteropTool decode-xml    --xsd <a.xsd>|none --exi in.exi [opts]      (XML to stdout)");
        System.out.println("  ExiInteropTool dump-events   --xsd <a.xsd>|none --exi in.exi [opts]      (one event per line)");
        System.out.println("  ExiInteropTool dump-grammars --xsd <a.xsd> [--out g.txt]");
        System.out.println("  ExiInteropTool encode-xsd    --xsd <a.xsd> --xsd-exi-out a.xsd.exi        (schema EXI for exip -schema=)");
        System.out.println("  ExiInteropTool xsd2exip      <Main args...>                              (delegates to Main)");
        System.out.println("opts:");
        System.out.println("  --strict | --no-strict                        (default no-strict)");
        System.out.println("  --alignment bit-packed|byte-aligned|pre-compression|compression  (default bit-packed)");
        System.out.println("  --include-options | --no-options              (default no-options)");
        System.out.println("  --cookie | --no-cookie                        (default no-cookie)");
        System.out.println("  --schema-id <id>                              (grammars schemaId + INCLUDE_SCHEMA_ID)");
        System.out.println("  --value-max-length N  --value-partition-capacity N");
        System.out.println("  --preserve comments,pis,dtd,prefixes,lexicalValues");
        System.out.println("Positional forms (legacy): encode-xml <xsd|none> <xml> <out>; decode-xml|dump-events <xsd|none> <exi>");
    }
}
