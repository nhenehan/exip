package org.acm.nhenehan.interop;

import static org.junit.jupiter.api.Assertions.assertArrayEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.siemens.ct.exi.core.CodingMode;
import com.siemens.ct.exi.core.EncodingOptions;
import com.siemens.ct.exi.core.EXIFactory;
import com.siemens.ct.exi.core.FidelityOptions;
import com.siemens.ct.exi.core.exceptions.EXIException;
import com.siemens.ct.exi.core.grammars.Grammars;
import com.siemens.ct.exi.core.helpers.DefaultEXIFactory;
import com.siemens.ct.exi.grammars.GrammarFactory;
import com.siemens.ct.exi.main.api.sax.EXIResult;
import com.siemens.ct.exi.main.api.sax.EXISource;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.StringReader;
import java.io.StringWriter;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Stream;
import javax.xml.parsers.SAXParserFactory;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.stream.StreamResult;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;
import org.xml.sax.InputSource;
import org.xml.sax.XMLReader;

final class StandardsConformanceProfileTest {

    private static final Path REPO_ROOT = Path.of("..").toAbsolutePath().normalize();
    private static final Path EXIPD_BIN = REPO_ROOT.resolve("build/examples/simpleDecoding/exipd");

    private static final Map<String, StandardsGenerationPipeline.GeneratedCaseArtifacts> ARTIFACTS_BY_CASE_ID = new HashMap<>();
    private static boolean EXIP_COMPRESSION_SUPPORTED = false;
    private static String EXIP_COMPRESSION_PROBE_SUMMARY = "not-evaluated";

    @BeforeAll
    static void prepareArtifacts() throws Exception {
        ensureExipdBinary();
        for (StandardsGenerationPipeline.GeneratedCaseArtifacts artifacts : StandardsGenerationPipeline.generateAllSelectedCases()) {
            ARTIFACTS_BY_CASE_ID.put(artifacts.caseId(), artifacts);
        }
        evaluateCompressionSupport();
    }

    static Stream<Arguments> profileAndCase() throws IOException {
        List<StandardsCaseManifest.StandardsCase> cases = StandardsCaseManifest.loadSelectedCases();
        return cases.stream().flatMap(c -> Arrays.stream(ExiOptionProfile.values())
                .filter(p -> c.profileIds().isEmpty() || c.profileIds().contains(p.id()))
                .map(p -> Arguments.of(p, c)));
    }

    @ParameterizedTest(name = "{0} / {1}")
    @MethodSource("profileAndCase")
    void manifestDrivenConformanceAndBinaryEquivalence(ExiOptionProfile profile, StandardsCaseManifest.StandardsCase standardsCase)
            throws Exception {
        StandardsGenerationPipeline.GeneratedCaseArtifacts artifacts = ARTIFACTS_BY_CASE_ID.get(standardsCase.id());
        assertTrue(artifacts != null, "missing generated artifacts for case: " + standardsCase.id());

        String xml = Files.readString(standardsCase.xml(), StandardCharsets.UTF_8);

        byte[] encodedFirst = encodeXml(xml, profile, standardsCase.schema());
        byte[] encodedSecond = encodeXml(xml, profile, standardsCase.schema());

        // Binary equivalence check for deterministic encoding with aligned profile/settings.
        assertArrayEquals(encodedFirst, encodedSecond,
                "non-deterministic EXIficient encoding for case/profile: " + standardsCase.id() + "/" + profile.id());

        String decodedExificient = normalizeXml(decodeXml(encodedFirst, profile, standardsCase.schema()));
        for (String token : standardsCase.expectedTokens()) {
            assertTrue(decodedExificient.contains(normalizeToken(token)),
                    "EXIficient decoded XML missing token " + token + " for case/profile " + standardsCase.id() + "/" + profile.id());
        }

        ExipResult exipResult = decodeWithExipd(encodedFirst, profile, artifacts.mainSchemaExi(), artifacts.importSchemaExis());

        if (isCompressionProfile(profile) && !EXIP_COMPRESSION_SUPPORTED) {
            assertTrue(!exipResult.success(),
                    "expected exipd compression decode to be unsupported, but it succeeded; probe="
                            + EXIP_COMPRESSION_PROBE_SUMMARY);
            assertTrue(
                exipResult.output().contains("EXIP_NOT_IMPLEMENTED_YET")
                        || exipResult.output().contains("EXIP_INCONSISTENT_PROC_STATE")
                    || exipResult.output().contains("Assertion `vxTable' failed")
                    || exipResult.output().contains("Error (code: 1)"),
                    "unexpected compression failure signature: " + summarizeFailure(exipResult.output()));
            return;
        }

        assertTrue(exipResult.success(), "exipd decode failed for case/profile " + standardsCase.id() + "/" + profile.id()
                + ": " + summarizeFailure(exipResult.output()));

        String decodedExip = normalizeXml(exipResult.output());
        for (String token : standardsCase.expectedTokens()) {
            assertTrue(decodedExip.contains(normalizeToken(token)),
                    "EXIP decoded output missing token " + token + " for case/profile " + standardsCase.id() + "/" + profile.id());
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

        EncodingOptions encodingOptions = EncodingOptions.createDefault();
        encodingOptions.setOption(EncodingOptions.INCLUDE_OPTIONS);
        factory.setEncodingOptions(encodingOptions);

        FidelityOptions fidelity = FidelityOptions.createDefault();
        if (profile.strict()) {
            fidelity.setFidelity(FidelityOptions.FEATURE_STRICT, true);
        }
        factory.setFidelityOptions(fidelity);

        return factory;
    }

    private static ExipResult decodeWithExipd(byte[] exi, ExiOptionProfile profile, Path mainSchemaExi, List<Path> importSchemaExis)
            throws IOException, InterruptedException {
        Path exiPath = Files.createTempFile("standards-conformance-", ".exi");
        Files.write(exiPath, exi);

        List<String> schemaList = new java.util.ArrayList<>();
        schemaList.add(mainSchemaExi.toAbsolutePath().normalize().toString());
        for (Path importSchemaExi : importSchemaExis) {
            schemaList.add(importSchemaExi.toAbsolutePath().normalize().toString());
        }

        String schemaArg = "-schema=" + String.join(",", schemaList);
        String opsArg = "-ops=" + outOfBandOpsMask(profile);
        ProcessBuilder pb = new ProcessBuilder(EXIPD_BIN.toString(), opsArg, schemaArg, exiPath.toString());
        Process p = pb.start();
        int code = p.waitFor();

        String output = new String(p.getInputStream().readAllBytes(), StandardCharsets.UTF_8)
                + new String(p.getErrorStream().readAllBytes(), StandardCharsets.UTF_8);

        Files.deleteIfExists(exiPath);
        return new ExipResult(code == 0, output);
    }

    private static String outOfBandOpsMask(ExiOptionProfile profile) {
        if ("COMPRESSION".equals(profile.codingMode())) {
            return "-%vc%-%-%-";
        }
        if ("BYTE_PACKED".equals(profile.codingMode()) && profile.strict()) {
            return "-%va%-%-%-";
        }
        if (profile.strict()) {
            return "-%v%-%-%-";
        }
        return "-%-%-%-%-";
    }

    private static void evaluateCompressionSupport() throws Exception {
        StandardsCaseManifest.StandardsCase probeCase = StandardsCaseManifest.loadSelectedCases().stream()
                .filter(c -> !c.schema().toString().isEmpty() && !c.xml().toString().isEmpty())
                .findFirst()
                .orElse(null);
        if (probeCase == null) {
            EXIP_COMPRESSION_SUPPORTED = false;
            EXIP_COMPRESSION_PROBE_SUMMARY = "no-concrete-case";
            return;
        }

        StandardsGenerationPipeline.GeneratedCaseArtifacts artifacts = ARTIFACTS_BY_CASE_ID.get(probeCase.id());
        if (artifacts == null) {
            EXIP_COMPRESSION_SUPPORTED = false;
            EXIP_COMPRESSION_PROBE_SUMMARY = "missing-artifacts";
            return;
        }

        String xml = Files.readString(probeCase.xml(), StandardCharsets.UTF_8);
        byte[] compressed = encodeXml(xml, ExiOptionProfile.STRICT_SCHEMA_INFORMED_COMPRESSION, probeCase.schema());
        ExipResult exipResult = decodeWithExipd(
                compressed,
                ExiOptionProfile.STRICT_SCHEMA_INFORMED_COMPRESSION,
                artifacts.mainSchemaExi(),
                artifacts.importSchemaExis());

        EXIP_COMPRESSION_SUPPORTED = exipResult.success();
        EXIP_COMPRESSION_PROBE_SUMMARY = summarizeFailure(exipResult.output());
    }

    private static void ensureExipdBinary() throws IOException, InterruptedException {
        if (Files.exists(EXIPD_BIN)) {
            return;
        }

        ProcessBuilder configure = new ProcessBuilder(
                "cmake",
                "-S", ".",
                "-B", "build",
                "-G", "Ninja",
                "-DEXIP_PLATFORM_PROFILE=pc");
        configure.directory(REPO_ROOT.toFile());
        Process c = configure.start();
        int ccode = c.waitFor();
        if (ccode != 0) {
            String err = new String(c.getErrorStream().readAllBytes(), StandardCharsets.UTF_8);
            throw new IOException("failed to configure build for exipd: " + err);
        }

        ProcessBuilder build = new ProcessBuilder("cmake", "--build", "build", "--target", "exipd", "-j4");
        build.directory(REPO_ROOT.toFile());
        Process b = build.start();
        int bcode = b.waitFor();
        if (bcode != 0 || !Files.exists(EXIPD_BIN)) {
            String err = new String(b.getErrorStream().readAllBytes(), StandardCharsets.UTF_8);
            throw new IOException("failed to build exipd binary: " + err);
        }
    }

    private static String normalizeXml(String in) {
        return in.replaceAll("\\s+", "").toLowerCase();
    }

    private static String normalizeToken(String token) {
        return token.replaceAll("\\s+", "").toLowerCase();
    }

    private static String summarizeFailure(String output) {
        String compact = output.replace('\n', ' ').replace('\r', ' ').trim();
        if (compact.length() > 240) {
            return compact.substring(0, 240) + "...";
        }
        return compact;
    }

    private static boolean isCompressionProfile(ExiOptionProfile profile) {
        return "COMPRESSION".equals(profile.codingMode());
    }

    private record ExipResult(boolean success, String output) {
    }
}
