package org.acm.nhenehan.xsd2exip;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import org.junit.jupiter.api.Test;

class ExiInteropToolTest {

    // A tank level reading. <level> is a local element, so only a fragment
    // (EXI 8.5.2, https://www.w3.org/TR/exi/#informedFragGrammars) may start with it.
    private static final String XSD = """
            <xs:schema xmlns:xs="http://www.w3.org/2001/XMLSchema"
                targetNamespace="urn:tank" xmlns="urn:tank" elementFormDefault="qualified">
              <xs:element name="tank">
                <xs:complexType>
                  <xs:sequence>
                    <xs:element name="level" type="xs:int"/>
                  </xs:sequence>
                </xs:complexType>
              </xs:element>
            </xs:schema>
            """;

    @Test
    void parseArgs_readsFragmentFlags() {
        assertFalse(ExiInteropTool.parseArgs(new String[] {"encode-xml"}).fragment);
        assertTrue(ExiInteropTool.parseArgs(new String[] {"encode-xml", "--fragment"}).fragment);
        assertFalse(ExiInteropTool.parseArgs(new String[] {"encode-xml", "--fragment", "--no-fragment"}).fragment);
    }

    @Test
    void fragment_encodesALocalElementAsTheRoot() throws Exception {
        Path dir = Files.createTempDirectory("xsd2exip-fragment");
        Path xsd = dir.resolve("tank.xsd");
        Files.writeString(xsd, XSD, StandardCharsets.UTF_8);
        Path xml = dir.resolve("level.xml");
        Files.writeString(xml, "<level xmlns=\"urn:tank\">42</level>", StandardCharsets.UTF_8);
        Path exi = dir.resolve("level.exi");

        ExiInteropTool.Options o = ExiInteropTool.parseArgs(new String[] {
            "encode-xml", "--strict", "--fragment",
            "--xsd", xsd.toString(), "--xml", xml.toString(), "--out", exi.toString()
        });
        ExiInteropTool.encodeXml(o);
        assertTrue(Files.size(exi) > 0);

        o.exi = exi.toString();
        ByteArrayOutputStream buf = new ByteArrayOutputStream();
        try (PrintStream out = new PrintStream(buf, true, StandardCharsets.UTF_8)) {
            ExiInteropTool.dumpEvents(o, out);
        }
        String events = buf.toString(StandardCharsets.UTF_8);
        assertTrue(events.startsWith("SD"), events);
        assertTrue(events.contains("level"), events);
        assertTrue(events.strip().endsWith("ED"), events);
    }

    @Test
    void fragment_changesTheBytesOfAGlobalRoot() throws Exception {
        Path dir = Files.createTempDirectory("xsd2exip-fragment-global");
        Path xsd = dir.resolve("tank.xsd");
        Files.writeString(xsd, XSD, StandardCharsets.UTF_8);
        Path xml = dir.resolve("tank.xml");
        Files.writeString(xml, "<tank xmlns=\"urn:tank\"><level>42</level></tank>", StandardCharsets.UTF_8);

        byte[][] out = new byte[2][];
        String[] flag = {"--no-fragment", "--fragment"};
        for (int i = 0; i < 2; i++) {
            Path exi = dir.resolve("tank" + i + ".exi");
            ExiInteropTool.encodeXml(ExiInteropTool.parseArgs(new String[] {
                "encode-xml", "--strict", flag[i],
                "--xsd", xsd.toString(), "--xml", xml.toString(), "--out", exi.toString()
            }));
            out[i] = Files.readAllBytes(exi);
        }
        assertNotEquals(java.util.Arrays.toString(out[0]), java.util.Arrays.toString(out[1]));
    }
}
