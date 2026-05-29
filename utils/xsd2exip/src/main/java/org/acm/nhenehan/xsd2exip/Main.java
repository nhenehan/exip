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
import java.nio.file.Path;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParserFactory;
import org.xml.sax.SAXException;
import org.xml.sax.XMLReader;

/**
 *
 * @author Nathan Henehan <nhenehan@acm.org>
 */
public class Main {
    
    protected static void generate(String xsdin, String exiout, boolean includeOptions){

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

            if (includeOptions) {
                EncodingOptions encodingOptions = EncodingOptions.createDefault();
                encodingOptions.setOption(EncodingOptions.INCLUDE_OPTIONS);
                exiFactory.setEncodingOptions(encodingOptions);
            }

            String fileEXI = exiout; // EXI output
            try ( OutputStream osEXI = new FileOutputStream(fileEXI)) {
                EXIResult exiResult = new EXIResult(exiFactory);
                exiResult.setOutputStream(osEXI);
                SAXParserFactory parserFactory = SAXParserFactory.newInstance();
                parserFactory.setNamespaceAware(true);
                XMLReader xmlReader = parserFactory.newSAXParser().getXMLReader();
                xmlReader.setContentHandler(exiResult.getHandler());
                xmlReader.parse(xsdin); // parse XML input
            }
        } catch (IOException | SAXException | EXIException | ParserConfigurationException ex) {
            Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    public static void main(String[] args) {
        MainOptions options;

        try {
            options = parseOptions(args);
        } catch (IllegalArgumentException ex) {
            System.out.println("Invalid arguments: " + ex.getMessage());
            printUsage();
            System.exit(-1);
            return;
        }

        generate(options.xsdInput, options.exiOutput, options.includeHeaderOptions);

        if (options.exipgOutPath != null) {
            try {
                runExipg(options);
            } catch (IOException ex) {
                Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
                System.exit(-1);
            }
        }

        if (options.generateCExampleName != null) {
            try {
                ExampleScaffoldGenerator.generateFromSchema(
                        options.generateCExampleName,
                        options.xsdInput,
                        options.examplesRoot,
                        options.forceOverwrite);
            } catch (IOException ex) {
                Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
                System.exit(-1);
            }
        }
    }

    private static MainOptions parseOptions(String[] args) {
        if (args.length < 2) {
            throw new IllegalArgumentException("expected at least <path-to-xsd> <exi-output-path>");
        }

        MainOptions options = new MainOptions();
        options.xsdInput = args[0];
        options.exiOutput = args[1];
        options.examplesRoot = Path.of("..", "..", "examples").normalize().toAbsolutePath();
        options.includeHeaderOptions = true;
        options.exipgMode = "static";
        options.exipgPrefix = "prfx_";

        for (int i = 2; i < args.length; i++) {
            String arg = args[i];
            if (arg.startsWith("--generate-c=")) {
                options.generateCExampleName = arg.substring("--generate-c=".length());
            } else if (arg.equals("--generate-c")) {
                if (i + 1 >= args.length) {
                    throw new IllegalArgumentException("--generate-c requires a value");
                }
                options.generateCExampleName = args[++i];
            } else if (arg.startsWith("--examples-root=")) {
                options.examplesRoot = Path.of(arg.substring("--examples-root=".length())).toAbsolutePath().normalize();
            } else if (arg.equals("--examples-root")) {
                if (i + 1 >= args.length) {
                    throw new IllegalArgumentException("--examples-root requires a value");
                }
                options.examplesRoot = Path.of(args[++i]).toAbsolutePath().normalize();
            } else if (arg.equals("--force")) {
                options.forceOverwrite = true;
            } else if (arg.equals("--omit-header-options")) {
                options.includeHeaderOptions = false;
            } else if (arg.startsWith("--exipg-bin=")) {
                options.exipgBinPath = arg.substring("--exipg-bin=".length());
            } else if (arg.equals("--exipg-bin")) {
                if (i + 1 >= args.length) {
                    throw new IllegalArgumentException("--exipg-bin requires a value");
                }
                options.exipgBinPath = args[++i];
            } else if (arg.startsWith("--exipg-mode=")) {
                options.exipgMode = arg.substring("--exipg-mode=".length());
            } else if (arg.equals("--exipg-mode")) {
                if (i + 1 >= args.length) {
                    throw new IllegalArgumentException("--exipg-mode requires a value");
                }
                options.exipgMode = args[++i];
            } else if (arg.startsWith("--exipg-prefix=")) {
                options.exipgPrefix = arg.substring("--exipg-prefix=".length());
            } else if (arg.equals("--exipg-prefix")) {
                if (i + 1 >= args.length) {
                    throw new IllegalArgumentException("--exipg-prefix requires a value");
                }
                options.exipgPrefix = args[++i];
            } else if (arg.startsWith("--exipg-ops=")) {
                options.exipgOpsMask = arg.substring("--exipg-ops=".length());
            } else if (arg.equals("--exipg-ops")) {
                if (i + 1 >= args.length) {
                    throw new IllegalArgumentException("--exipg-ops requires a value");
                }
                options.exipgOpsMask = args[++i];
            } else if (arg.startsWith("--exipg-out=")) {
                options.exipgOutPath = arg.substring("--exipg-out=".length());
            } else if (arg.equals("--exipg-out")) {
                if (i + 1 >= args.length) {
                    throw new IllegalArgumentException("--exipg-out requires a value");
                }
                options.exipgOutPath = args[++i];
            } else if (arg.startsWith("--exipg-schema-list=")) {
                options.exipgSchemaList = arg.substring("--exipg-schema-list=".length());
            } else if (arg.equals("--exipg-schema-list")) {
                if (i + 1 >= args.length) {
                    throw new IllegalArgumentException("--exipg-schema-list requires a value");
                }
                options.exipgSchemaList = args[++i];
            } else {
                throw new IllegalArgumentException("unknown argument: " + arg);
            }
        }

        if (options.exipgOutPath != null && (options.exipgBinPath == null || options.exipgBinPath.isBlank())) {
            throw new IllegalArgumentException("--exipg-out requires --exipg-bin");
        }

        return options;
    }

    private static void runExipg(MainOptions options) throws IOException {
        ProcessBuilder pb = new ProcessBuilder();
        java.util.ArrayList<String> command = new java.util.ArrayList<>();
        command.add(options.exipgBinPath);

        String mode = options.exipgMode == null ? "static" : options.exipgMode;
        switch (mode) {
            case "static" -> {
                command.add("-static");
                command.add("-pfx=" + options.exipgPrefix);
            }
            case "dynamic" -> {
                command.add("-dynamic");
                command.add("-pfx=" + options.exipgPrefix);
            }
            case "text" -> command.add("-text");
            case "exip" -> command.add("-exip");
            default -> throw new IOException("unsupported exipg mode: " + mode);
        }

        if (options.exipgOpsMask != null && !options.exipgOpsMask.isBlank()) {
            command.add("-ops=" + options.exipgOpsMask);
        }

        String schemaList = options.exipgSchemaList;
        if (schemaList == null || schemaList.isBlank()) {
            schemaList = options.exiOutput;
        }
        command.add("-schema=" + schemaList);
        command.add(options.exipgOutPath);

        pb.command(command);
        pb.inheritIO();

        try {
            int exit = pb.start().waitFor();
            if (exit != 0) {
                throw new IOException("exipg exited with code " + exit);
            }
        } catch (InterruptedException ex) {
            Thread.currentThread().interrupt();
            throw new IOException("exipg invocation interrupted", ex);
        }
    }

    private static void printUsage() {
        System.out.println("Usage:");
        System.out.println("xsd2exip <path-to-xsd> <exi-output-path> [--generate-c=<name>] [--examples-root=<path>] [--force] [--omit-header-options]");
        System.out.println("        [--exipg-bin=<path>] [--exipg-mode=<static|dynamic|text|exip>] [--exipg-prefix=<prefix>] [--exipg-ops=<mask>] [--exipg-schema-list=<main.exi,import1.exi,...>] [--exipg-out=<path>]");
    }

    private static final class MainOptions {
        private String xsdInput;
        private String exiOutput;
        private String generateCExampleName;
        private Path examplesRoot;
        private boolean forceOverwrite;
        private boolean includeHeaderOptions;
        private String exipgBinPath;
        private String exipgMode;
        private String exipgPrefix;
        private String exipgOpsMask;
        private String exipgSchemaList;
        private String exipgOutPath;
    }
}
