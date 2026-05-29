package org.acm.nhenehan.interop;

import static org.junit.jupiter.api.Assertions.assertTrue;

import com.siemens.ct.exi.core.CodingMode;
import com.siemens.ct.exi.core.EXIFactory;
import com.siemens.ct.exi.core.FidelityOptions;
import com.siemens.ct.exi.core.exceptions.EXIException;
import com.siemens.ct.exi.core.grammars.Grammars;
import com.siemens.ct.exi.core.helpers.DefaultEXIFactory;
import com.siemens.ct.exi.grammars.GrammarFactory;
import com.siemens.ct.exi.main.api.sax.EXIResult;
import com.siemens.ct.exi.main.api.sax.EXISource;
import jakarta.xml.bind.JAXBContext;
import jakarta.xml.bind.JAXBElement;
import jakarta.xml.bind.Unmarshaller;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.StringReader;
import java.io.StringWriter;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.List;
import java.util.stream.Stream;
import javax.xml.parsers.SAXParserFactory;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.sax.SAXSource;
import javax.xml.transform.stream.StreamResult;
import javax.xml.transform.stream.StreamSource;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.MethodSource;
import org.xml.sax.InputSource;
import org.xml.sax.XMLReader;

final class JaxbExiRoundTripProfileTest {

    private static final Path ROOT = Path.of("src/test/resources/fixtures/standards/cases").normalize();
    private static final Path S3_XSD = ROOT.resolve("inheritance-extension.xsd");
    private static final Path S3_XML = ROOT.resolve("inheritance-extension.xml");
    private static final Path S4_XSD = ROOT.resolve("cross-schema-main.xsd");
    private static final Path S4_XML = ROOT.resolve("cross-schema-main.xml");
    private static final Path S5_XSD = ROOT.resolve("polymorphic-choice.xsd");
    private static final Path S5_XML = ROOT.resolve("polymorphic-choice.xml");
    private static final String GENERATED_PACKAGE = "org.acm.nhenehan.interop.generated";

    static Stream<ExiOptionProfile> profiles() {
        return Stream.of(ExiOptionProfile.values());
    }

    static Stream<RoundTripCase> roundTripCases() {
        return Stream.of(
            new RoundTripCase(
                "S3 inheritance",
                S3_XSD,
                S3_XML,
                List.of("ReadingEvent", "evt-2026-04-15-001", "sensor-17", "temperature")
            ),
            new RoundTripCase(
                "S4 cross-schema import",
                S4_XSD,
                S4_XML,
                List.of("IncidentReport", "INC-2026-0109", "plant-7", "operator-12", "high")
            ),
            new RoundTripCase(
                "S5 polymorphic choice",
                S5_XSD,
                S5_XML,
                List.of("Envelope", "batch-2026-04-15", "operational", "OVERHEAT", "3entriesprocessed")
            )
        );
    }

    static Stream<ProfileCase> profileAndCase() {
        return profiles().flatMap(profile -> roundTripCases().map(rc -> new ProfileCase(profile, rc)));
    }

    @ParameterizedTest(name = "{0} / {1}")
    @MethodSource("profileAndCase")
    void jaxbRoundTripAcrossProfilesIncludesStrictGate(ProfileCase input) throws Exception {
        ExiOptionProfile profile = input.profile();
        RoundTripCase roundTripCase = input.roundTripCase();

        String xmlInput = Files.readString(roundTripCase.xml(), StandardCharsets.UTF_8);

        JAXBContext context = JAXBContext.newInstance(GENERATED_PACKAGE);
        Unmarshaller unmarshaller = context.createUnmarshaller();
        JAXBElement<Object> original = (JAXBElement<Object>) unmarshaller.unmarshal(new StreamSource(new StringReader(xmlInput)), Object.class);

        String canonicalOriginal = normalizeXml(xmlInput);
        byte[] exi = encodeXml(xmlInput, profile, roundTripCase.xsd());
        String decodedXml = decodeXml(exi, profile, roundTripCase.xsd());
        String canonicalDecoded = normalizeXml(decodedXml);

        JAXBElement<Object> roundTripped = (JAXBElement<Object>) unmarshaller.unmarshal(new StreamSource(new StringReader(decodedXml)), Object.class);

        // Strict gate: schema-informed + bit-packed + strict must preserve semantics.
        if (profile.requiredGate()) {
            assertTrue(profile.strict());
            assertTrue("BIT_PACKED".equals(profile.codingMode()));
            assertTrue(profile.schemaInformed());
        }

        for (String token : roundTripCase.expectedTokens()) {
            assertTrue(canonicalDecoded.contains(token), "decoded XML is missing token: " + token);
        }

        String origObjectXml = normalizeXml(marshalElement(context, original));
        String roundObjectXml = normalizeXml(marshalElement(context, roundTripped));
        for (String token : roundTripCase.expectedTokens()) {
            assertTrue(origObjectXml.contains(token), "original object XML is missing token: " + token);
            assertTrue(roundObjectXml.contains(token), "round-tripped object XML is missing token: " + token);
            assertTrue(canonicalOriginal.contains(token), "original XML is missing token: " + token);
        }
    }

    private static byte[] encodeXml(String xml, ExiOptionProfile profile, Path xsd) throws Exception {
        EXIFactory factory = buildFactory(profile, xsd);
        ByteArrayOutputStream out = new ByteArrayOutputStream();

        EXIResult exiResult = new EXIResult(factory);
        exiResult.setOutputStream(out);

        SAXParserFactory parserFactory = SAXParserFactory.newInstance();
        parserFactory.setNamespaceAware(true);
        XMLReader reader = parserFactory.newSAXParser().getXMLReader();
        reader.setContentHandler(exiResult.getHandler());
        reader.parse(new InputSource(new StringReader(xml)));

        return out.toByteArray();
    }

    private static String decodeXml(byte[] exi, ExiOptionProfile profile, Path xsd) throws Exception {
        EXIFactory factory = buildFactory(profile, xsd);
        EXISource exiSource = new EXISource(factory);
        exiSource.setInputSource(new InputSource(new ByteArrayInputStream(exi)));

        Transformer transformer = TransformerFactory.newInstance().newTransformer();
        transformer.setOutputProperty(OutputKeys.OMIT_XML_DECLARATION, "yes");
        transformer.setOutputProperty(OutputKeys.INDENT, "no");

        StringWriter out = new StringWriter();
        transformer.transform(exiSource, new StreamResult(out));
        return out.toString();
    }

    private static EXIFactory buildFactory(ExiOptionProfile profile, Path xsd) throws EXIException {
        EXIFactory factory = DefaultEXIFactory.newInstance();
        Grammars grammars = GrammarFactory.newInstance().createGrammars(xsd.toString());
        factory.setGrammars(grammars);

        CodingMode mode = switch (profile.codingMode()) {
            case "BIT_PACKED" -> CodingMode.BIT_PACKED;
            case "BYTE_PACKED" -> CodingMode.BYTE_PACKED;
            case "COMPRESSION" -> CodingMode.COMPRESSION;
            default -> CodingMode.BIT_PACKED;
        };
        factory.setCodingMode(mode);

        FidelityOptions fidelity = FidelityOptions.createDefault();
        if (profile.strict()) {
            fidelity.setFidelity(FidelityOptions.FEATURE_STRICT, true);
        }
        factory.setFidelityOptions(fidelity);

        return factory;
    }

    private static String marshalElement(JAXBContext context, JAXBElement<Object> element) throws Exception {
        StringWriter out = new StringWriter();
        context.createMarshaller().marshal(element, out);
        return out.toString();
    }

    private static String normalizeXml(String xml) throws Exception {
        Transformer transformer = TransformerFactory.newInstance().newTransformer();
        transformer.setOutputProperty(OutputKeys.OMIT_XML_DECLARATION, "yes");
        transformer.setOutputProperty(OutputKeys.INDENT, "no");

        StringWriter writer = new StringWriter();
        transformer.transform(new SAXSource(new InputSource(new StringReader(xml))), new StreamResult(writer));
        return writer.toString().replaceAll("\\s+", "");
    }

    private record RoundTripCase(String name, Path xsd, Path xml, List<String> expectedTokens) {
        @Override
        public String toString() {
            return name;
        }
    }

    private record ProfileCase(ExiOptionProfile profile, RoundTripCase roundTripCase) {
        @Override
        public String toString() {
            return profile + " / " + roundTripCase;
        }
    }
}
