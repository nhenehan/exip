package org.acm.nhenehan.xsd2exip;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import org.junit.jupiter.api.Test;

class ExampleScaffoldGeneratorTest {

    @Test
    void generateFromSchema_writesExpectedFilesAndRegistryEntries() throws IOException {
        Path root = Files.createTempDirectory("xsd2exip-scaffold");
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

        ExampleScaffoldGenerator.generateFromSchema("sep2", schema.toString(), examplesRoot, false);

        assertTrue(Files.exists(encDir.resolve("Sep2Model.h")));
        assertTrue(Files.exists(decDir.resolve("Sep2Model.h")));
        assertTrue(Files.exists(encDir.resolve("encodeSep2EXI.h")));
        assertTrue(Files.exists(encDir.resolve("encodeSep2EXI.c")));
        assertTrue(Files.exists(decDir.resolve("decodeSep2EXI.h")));
        assertTrue(Files.exists(decDir.resolve("decodeSep2EXI.c")));

        String encCmake = Files.readString(encDir.resolve("CMakeLists.txt"), StandardCharsets.UTF_8);
        String decCmake = Files.readString(decDir.resolve("CMakeLists.txt"), StandardCharsets.UTF_8);
        assertTrue(encCmake.contains("\"encodeSep2EXI.c\""));
        assertTrue(decCmake.contains("\"decodeSep2EXI.c\""));

        String encRegistry = Files.readString(encDir.resolve("exampleEncodeRegistry.c"), StandardCharsets.UTF_8);
        String decRegistry = Files.readString(decDir.resolve("exampleDecodeRegistry.c"), StandardCharsets.UTF_8);

        assertTrue(encRegistry.contains("#include \"encodeSep2EXI.h\""));
        assertTrue(encRegistry.contains("{\"sep2\", encodeSep2},"));
        assertTrue(decRegistry.contains("#include \"decodeSep2EXI.h\""));
        assertTrue(decRegistry.contains("{\"sep2\", decodeSep2},"));

        String modelHeader = Files.readString(encDir.resolve("Sep2Model.h"), StandardCharsets.UTF_8);
        assertTrue(modelHeader.contains("double value;"));
        assertTrue(modelHeader.contains("char* note;"));
    }

    @Test
    void generateFromSchema_withoutForce_failsWhenGeneratedFileExists() throws IOException {
        Path root = Files.createTempDirectory("xsd2exip-scaffold-force");
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

        ExampleScaffoldGenerator.generateFromSchema("sep2", schema.toString(), examplesRoot, false);

        IOException ex = assertThrows(IOException.class, () ->
                ExampleScaffoldGenerator.generateFromSchema("sep2", schema.toString(), examplesRoot, false));
        assertTrue(ex.getMessage().contains("file exists"));
    }

    @Test
    void generateFromSchema_withForce_overwritesWithoutDuplicatingRegistryEntries() throws IOException {
        Path root = Files.createTempDirectory("xsd2exip-scaffold-dedupe");
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

        ExampleScaffoldGenerator.generateFromSchema("sep2", schema.toString(), examplesRoot, false);
        ExampleScaffoldGenerator.generateFromSchema("sep2", schema.toString(), examplesRoot, true);

        String encRegistry = Files.readString(encDir.resolve("exampleEncodeRegistry.c"), StandardCharsets.UTF_8);
        String decRegistry = Files.readString(decDir.resolve("exampleDecodeRegistry.c"), StandardCharsets.UTF_8);

        assertEquals(1, countOccurrences(encRegistry, "{\"sep2\", encodeSep2},"));
        assertEquals(1, countOccurrences(decRegistry, "{\"sep2\", decodeSep2},"));

        String encCmake = Files.readString(encDir.resolve("CMakeLists.txt"), StandardCharsets.UTF_8);
        String decCmake = Files.readString(decDir.resolve("CMakeLists.txt"), StandardCharsets.UTF_8);
        assertEquals(1, countOccurrences(encCmake, "\"encodeSep2EXI.c\""));
        assertEquals(1, countOccurrences(decCmake, "\"decodeSep2EXI.c\""));
    }

    @Test
    void generateFromSchema_mapsListOptionalAndAttributeTypesForComplexSchema() throws IOException {
        Path root = Files.createTempDirectory("xsd2exip-scaffold-complex");
        Path examplesRoot = root.resolve("examples");
        Path encDir = examplesRoot.resolve("simpleEncoding");
        Path decDir = examplesRoot.resolve("simpleDecoding");

        Files.createDirectories(encDir);
        Files.createDirectories(decDir);

        Files.writeString(encDir.resolve("CMakeLists.txt"), cmakeTemplate(), StandardCharsets.UTF_8);
        Files.writeString(decDir.resolve("CMakeLists.txt"), cmakeTemplate(), StandardCharsets.UTF_8);
        Files.writeString(encDir.resolve("exampleEncodeRegistry.c"), encodeRegistryTemplate(), StandardCharsets.UTF_8);
        Files.writeString(decDir.resolve("exampleDecodeRegistry.c"), decodeRegistryTemplate(), StandardCharsets.UTF_8);

        Path schema = root.resolve("device.xsd");
        Files.writeString(schema, complexSchema(), StandardCharsets.UTF_8);

        ExampleScaffoldGenerator.generateFromSchema("device-profile", schema.toString(), examplesRoot, false);

        String modelHeader = Files.readString(encDir.resolve("DeviceProfileModel.h"), StandardCharsets.UTF_8);

        assertTrue(modelHeader.contains("int32_t* reading;"));
        assertTrue(modelHeader.contains("uint16_t readingCount;"));
        assertTrue(modelHeader.contains("int32_t quality;"));
        assertTrue(modelHeader.contains("exip_bool hasQuality;"));
        assertTrue(modelHeader.contains("char* serial;"));
        assertTrue(modelHeader.contains("double scale;"));
        assertTrue(modelHeader.contains("exip_bool hasScale;"));
    }

    private static int countOccurrences(String haystack, String needle) {
        int count = 0;
        int idx = 0;
        while (idx >= 0) {
            idx = haystack.indexOf(needle, idx);
            if (idx >= 0) {
                count++;
                idx += needle.length();
            }
        }
        return count;
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
                  <xs:element name=\"note\" type=\"xs:string\" minOccurs=\"0\"/>
                </xs:sequence>
              </xs:complexType>
            </xs:schema>
            """;
    }

        private static String complexSchema() {
                return """
                        <xs:schema xmlns:xs=\"http://www.w3.org/2001/XMLSchema\" elementFormDefault=\"qualified\">
                            <xs:element name=\"Device\" type=\"DeviceType\"/>
                            <xs:complexType name=\"DeviceType\">
                                <xs:sequence>
                                    <xs:element name=\"reading\" type=\"xs:int\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>
                                    <xs:element name=\"quality\" type=\"xs:unsignedShort\" minOccurs=\"0\"/>
                                </xs:sequence>
                                <xs:attribute name=\"serial\" type=\"xs:string\" use=\"required\"/>
                                <xs:attribute name=\"scale\" type=\"xs:decimal\"/>
                            </xs:complexType>
                        </xs:schema>
                        """;
        }
}
