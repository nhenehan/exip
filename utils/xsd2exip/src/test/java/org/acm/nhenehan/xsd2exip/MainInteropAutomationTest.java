package org.acm.nhenehan.xsd2exip;

import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.assertFalse;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import org.junit.jupiter.api.Test;

class MainInteropAutomationTest {

    @Test
    void main_runsGenerateCAndExipgAutomationInSingleInvocation() throws IOException {
        Path root = Files.createTempDirectory("xsd2exip-main-interop");
        Path examplesRoot = root.resolve("examples");
        Path encDir = examplesRoot.resolve("simpleEncoding");
        Path decDir = examplesRoot.resolve("simpleDecoding");

        Files.createDirectories(encDir);
        Files.createDirectories(decDir);

        Files.writeString(encDir.resolve("CMakeLists.txt"), cmakeTemplate(), StandardCharsets.UTF_8);
        Files.writeString(decDir.resolve("CMakeLists.txt"), cmakeTemplate(), StandardCharsets.UTF_8);
        Files.writeString(encDir.resolve("exampleEncodeRegistry.c"), encodeRegistryTemplate(), StandardCharsets.UTF_8);
        Files.writeString(decDir.resolve("exampleDecodeRegistry.c"), decodeRegistryTemplate(), StandardCharsets.UTF_8);

        Path schema = root.resolve("sep2.xsd");
        Files.writeString(schema, simpleSchema(), StandardCharsets.UTF_8);

        Path exiOutput = root.resolve("sep2-xsd.exi");
        Path exipgOut = root.resolve("sep2-grammar.out");
        Path exipgLog = root.resolve("exipg-args.log");
        Path fakeExipg = root.resolve("fake-exipg.sh");

        Files.writeString(fakeExipg, fakeExipgScript(exipgLog), StandardCharsets.UTF_8);
        fakeExipg.toFile().setExecutable(true);

        Main.main(new String[] {
            schema.toString(),
            exiOutput.toString(),
            "--generate-c=sep2",
            "--examples-root=" + examplesRoot,
            "--exipg-bin=" + fakeExipg,
            "--exipg-mode=text",
            "--exipg-out=" + exipgOut
        });

        assertTrue(Files.exists(exiOutput), "schema EXI output should be generated");

        assertTrue(Files.exists(encDir.resolve("Sep2Model.h")));
        assertTrue(Files.exists(encDir.resolve("encodeSep2EXI.c")));
        assertTrue(Files.exists(decDir.resolve("decodeSep2EXI.c")));

        String exipgArgs = Files.readString(exipgLog, StandardCharsets.UTF_8);
        assertTrue(exipgArgs.contains("-text"), "exipg should receive text mode argument");
        assertTrue(exipgArgs.contains("-schema=" + exiOutput), "exipg should receive schema list argument");
        assertTrue(exipgArgs.contains(exipgOut.toString()), "exipg should receive output path argument");
    }

    @Test
    void main_runsExipgStaticModeWithPrefixOpsAndSchemaList() throws IOException {
        Path root = Files.createTempDirectory("xsd2exip-main-static");
        Path examplesRoot = root.resolve("examples");
        Path encDir = examplesRoot.resolve("simpleEncoding");
        Path decDir = examplesRoot.resolve("simpleDecoding");

        Files.createDirectories(encDir);
        Files.createDirectories(decDir);

        Files.writeString(encDir.resolve("CMakeLists.txt"), cmakeTemplate(), StandardCharsets.UTF_8);
        Files.writeString(decDir.resolve("CMakeLists.txt"), cmakeTemplate(), StandardCharsets.UTF_8);
        Files.writeString(encDir.resolve("exampleEncodeRegistry.c"), encodeRegistryTemplate(), StandardCharsets.UTF_8);
        Files.writeString(decDir.resolve("exampleDecodeRegistry.c"), decodeRegistryTemplate(), StandardCharsets.UTF_8);

        Path schema = root.resolve("sep2.xsd");
        Files.writeString(schema, simpleSchema(), StandardCharsets.UTF_8);

        Path exiOutput = root.resolve("sep2-xsd.exi");
        Path exipgOut = root.resolve("sep2-grammar-static.out");
        Path exipgLog = root.resolve("exipg-static-args.log");
        Path fakeExipg = root.resolve("fake-exipg.sh");

        Files.writeString(fakeExipg, fakeExipgScript(exipgLog), StandardCharsets.UTF_8);
        fakeExipg.toFile().setExecutable(true);

        String schemaList = exiOutput + "," + root.resolve("sep2-types.exi");

        Main.main(new String[] {
            schema.toString(),
            exiOutput.toString(),
            "--examples-root=" + examplesRoot,
            "--exipg-bin=" + fakeExipg,
            "--exipg-mode=static",
            "--exipg-prefix=sep_",
            "--exipg-ops=0100",
            "--exipg-schema-list=" + schemaList,
            "--exipg-out=" + exipgOut
        });

        assertTrue(Files.exists(exiOutput), "schema EXI output should be generated");

        String exipgArgs = Files.readString(exipgLog, StandardCharsets.UTF_8);
        assertTrue(exipgArgs.contains("-static"), "exipg should receive static mode argument");
        assertTrue(exipgArgs.contains("-pfx=sep_"), "exipg should receive custom prefix");
        assertTrue(exipgArgs.contains("-ops=0100"), "exipg should receive ops mask");
        assertTrue(exipgArgs.contains("-schema=" + schemaList), "exipg should receive explicit schema list");
        assertTrue(exipgArgs.contains(exipgOut.toString()), "exipg should receive output path argument");
    }

    @Test
    void main_runsExipgDynamicModeWithPrefixAndDefaultSchemaList() throws IOException {
        Path root = Files.createTempDirectory("xsd2exip-main-dynamic");
        Path examplesRoot = root.resolve("examples");
        Path encDir = examplesRoot.resolve("simpleEncoding");
        Path decDir = examplesRoot.resolve("simpleDecoding");

        Files.createDirectories(encDir);
        Files.createDirectories(decDir);

        Files.writeString(encDir.resolve("CMakeLists.txt"), cmakeTemplate(), StandardCharsets.UTF_8);
        Files.writeString(decDir.resolve("CMakeLists.txt"), cmakeTemplate(), StandardCharsets.UTF_8);
        Files.writeString(encDir.resolve("exampleEncodeRegistry.c"), encodeRegistryTemplate(), StandardCharsets.UTF_8);
        Files.writeString(decDir.resolve("exampleDecodeRegistry.c"), decodeRegistryTemplate(), StandardCharsets.UTF_8);

        Path schema = root.resolve("sep2.xsd");
        Files.writeString(schema, simpleSchema(), StandardCharsets.UTF_8);

        Path exiOutput = root.resolve("sep2-xsd.exi");
        Path exipgOut = root.resolve("sep2-grammar-dynamic.out");
        Path exipgLog = root.resolve("exipg-dynamic-args.log");
        Path fakeExipg = root.resolve("fake-exipg.sh");

        Files.writeString(fakeExipg, fakeExipgScript(exipgLog), StandardCharsets.UTF_8);
        fakeExipg.toFile().setExecutable(true);

        Main.main(new String[] {
            schema.toString(),
            exiOutput.toString(),
            "--examples-root=" + examplesRoot,
            "--exipg-bin=" + fakeExipg,
            "--exipg-mode=dynamic",
            "--exipg-prefix=dyn_",
            "--exipg-out=" + exipgOut
        });

        String exipgArgs = Files.readString(exipgLog, StandardCharsets.UTF_8);
        assertTrue(exipgArgs.contains("-dynamic"), "exipg should receive dynamic mode argument");
        assertTrue(exipgArgs.contains("-pfx=dyn_"), "exipg should receive custom prefix");
        assertTrue(exipgArgs.contains("-schema=" + exiOutput), "exipg should default schema list to generated EXI");
        assertTrue(exipgArgs.contains(exipgOut.toString()), "exipg should receive output path argument");
    }

    @Test
    void main_runsExipgExipModeWithoutPrefixAndWithOps() throws IOException {
        Path root = Files.createTempDirectory("xsd2exip-main-exip");
        Path examplesRoot = root.resolve("examples");
        Path encDir = examplesRoot.resolve("simpleEncoding");
        Path decDir = examplesRoot.resolve("simpleDecoding");

        Files.createDirectories(encDir);
        Files.createDirectories(decDir);

        Files.writeString(encDir.resolve("CMakeLists.txt"), cmakeTemplate(), StandardCharsets.UTF_8);
        Files.writeString(decDir.resolve("CMakeLists.txt"), cmakeTemplate(), StandardCharsets.UTF_8);
        Files.writeString(encDir.resolve("exampleEncodeRegistry.c"), encodeRegistryTemplate(), StandardCharsets.UTF_8);
        Files.writeString(decDir.resolve("exampleDecodeRegistry.c"), decodeRegistryTemplate(), StandardCharsets.UTF_8);

        Path schema = root.resolve("sep2.xsd");
        Files.writeString(schema, simpleSchema(), StandardCharsets.UTF_8);

        Path exiOutput = root.resolve("sep2-xsd.exi");
        Path exipgOut = root.resolve("sep2-grammar-exip.out");
        Path exipgLog = root.resolve("exipg-exip-args.log");
        Path fakeExipg = root.resolve("fake-exipg.sh");

        Files.writeString(fakeExipg, fakeExipgScript(exipgLog), StandardCharsets.UTF_8);
        fakeExipg.toFile().setExecutable(true);

        Main.main(new String[] {
            schema.toString(),
            exiOutput.toString(),
            "--examples-root=" + examplesRoot,
            "--exipg-bin=" + fakeExipg,
            "--exipg-mode=exip",
            "--exipg-ops=1110",
            "--exipg-out=" + exipgOut
        });

        String exipgArgs = Files.readString(exipgLog, StandardCharsets.UTF_8);
        assertTrue(exipgArgs.contains("-exip"), "exipg should receive exip mode argument");
        assertTrue(exipgArgs.contains("-ops=1110"), "exipg should receive ops mask");
        assertFalse(exipgArgs.contains("-pfx="), "exip mode should not include prefix argument");
        assertTrue(exipgArgs.contains("-schema=" + exiOutput), "exipg should default schema list to generated EXI");
        assertTrue(exipgArgs.contains(exipgOut.toString()), "exipg should receive output path argument");
    }

    private static String fakeExipgScript(Path logPath) {
        return "#!/usr/bin/env sh\n"
            + "set -e\n"
            + "printf '%s\\n' \"$@\" > '" + logPath.toString() + "'\n"
            + "exit 0\n";
    }

    private static String cmakeTemplate() {
        return """
            set(PROJECT_SOURCE_FILES
              \"example.c\"
            )
            """;
    }

    private static String encodeRegistryTemplate() {
        return """
            #include <stdio.h>
            typedef struct {
                const char* name;
                int (*fn)(void);
            } entry_t;

            static entry_t entries[] = {
            \t/* GENERATED ENCODE ENTRIES */
            };
            """;
    }

    private static String decodeRegistryTemplate() {
        return """
            #include <stdio.h>
            typedef struct {
                const char* name;
                int (*fn)(void);
            } entry_t;

            static entry_t entries[] = {
            \t/* GENERATED DECODE ENTRIES */
            };
            """;
    }

    private static String simpleSchema() {
        return """
            <xs:schema xmlns:xs=\"http://www.w3.org/2001/XMLSchema\" elementFormDefault=\"qualified\">
              <xs:element name=\"Telemetry\" type=\"TelemetryType\"/>
              <xs:complexType name=\"TelemetryType\">
                <xs:sequence>
                  <xs:element name=\"value\" type=\"xs:double\"/>
                </xs:sequence>
              </xs:complexType>
            </xs:schema>
            """;
    }
}
