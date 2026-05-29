package org.acm.nhenehan.interop;

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
import java.util.ArrayList;
import java.util.List;
import java.util.Locale;
import javax.xml.parsers.SAXParserFactory;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.stream.StreamResult;
import org.junit.jupiter.api.Test;
import org.xml.sax.InputSource;
import org.xml.sax.XMLReader;

final class InteropBenchmarkTest {

    private static final Path ROOT = Path.of("src/test/resources/fixtures/standards/cases").normalize();
    private static final Path XSD2EXIP_DIR = Path.of("../utils/xsd2exip").normalize();
    private static final Path EXIPD_BIN = Path.of("../build/examples/simpleDecoding/exipd").normalize();
    private static final Path REPORT_MD = Path.of("target/interop-benchmark-latest.md").normalize();

    private static final int WARMUP_ITERS = 1;
    private static final int MEASURE_ITERS = 3;

    @Test
    void benchmarkOptionProfilesAndInteropDecodeTimes() throws Exception {
        List<CaseDef> cases = List.of(
            new CaseDef("S1-order", ROOT.resolve("order-complex.xsd"), ROOT.resolve("order-complex.xml"), List.of()),
            new CaseDef("S2-telemetry", ROOT.resolve("telemetry-complex.xsd"), ROOT.resolve("telemetry-complex.xml"), List.of()),
            new CaseDef("S3-inheritance", ROOT.resolve("inheritance-extension.xsd"), ROOT.resolve("inheritance-extension.xml"), List.of()),
            new CaseDef("S4-cross-schema", ROOT.resolve("cross-schema-main.xsd"), ROOT.resolve("cross-schema-main.xml"), List.of(ROOT.resolve("cross-schema-common.xsd"))),
            new CaseDef("S5-polymorphic", ROOT.resolve("polymorphic-choice.xsd"), ROOT.resolve("polymorphic-choice.xml"), List.of())
        );

        List<ResultRow> rows = new ArrayList<>();

        for (CaseDef caseDef : cases) {
            String xml = Files.readString(caseDef.xml(), StandardCharsets.UTF_8);
            long xmlBytes = xml.getBytes(StandardCharsets.UTF_8).length;

            List<Path> schemaExis = new ArrayList<>();
            schemaExis.add(generateStandardSchema(caseDef.xsd()));
            for (Path imported : caseDef.importedXsds()) {
                schemaExis.add(generateStandardSchema(imported));
            }

            try {
                for (ExiOptionProfile profile : ExiOptionProfile.values()) {
                    long encodeNs = 0;
                    long decodeNs = 0;
                    long exipDecodeNs = 0;
                    int exiBytes = 0;
                    int exipSuccessCount = 0;
                    String exipStatus = "ok";

                    for (int i = 0; i < WARMUP_ITERS + MEASURE_ITERS; i++) {
                        long startEncode = System.nanoTime();
                        byte[] exi = encodeXml(xml, profile, caseDef.xsd());
                        long endEncode = System.nanoTime();

                        long startDecode = System.nanoTime();
                        String decoded = decodeXml(exi, profile, caseDef.xsd());
                        long endDecode = System.nanoTime();

                        long startExip = System.nanoTime();
                        ExipResult exip = decodeWithExipd(exi, schemaExis);
                        long endExip = System.nanoTime();

                        if (!decoded.contains("<")) {
                            throw new IOException("EXIficient decode returned non-XML payload for " + caseDef.name() + " / " + profile.id());
                        }

                        if (i >= WARMUP_ITERS) {
                            encodeNs += (endEncode - startEncode);
                            decodeNs += (endDecode - startDecode);
                            exipDecodeNs += (endExip - startExip);
                            exiBytes = exi.length;
                            if (exip.success()) {
                                exipSuccessCount++;
                            } else if ("ok".equals(exipStatus)) {
                                exipStatus = summarizeExipFailure(exip.output());
                            }
                        }
                    }

                    if (exipSuccessCount == MEASURE_ITERS) {
                        exipStatus = "ok";
                    } else {
                        exipStatus = exipStatus + " (" + exipSuccessCount + "/" + MEASURE_ITERS + " successful)";
                    }

                    rows.add(new ResultRow(
                        caseDef.name(),
                        profile.id(),
                        profile.codingMode(),
                        profile.strict(),
                        xmlBytes,
                        exiBytes,
                        meanMs(encodeNs),
                        meanMs(decodeNs),
                        meanMs(exipDecodeNs),
                        exipStatus
                    ));
                }
            } finally {
                for (Path schemaExi : schemaExis) {
                    Files.deleteIfExists(schemaExi);
                }
            }
        }

        writeMarkdownReport(rows);
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

    private static ExipResult decodeWithExipd(byte[] exi, List<Path> schemaExis) throws IOException, InterruptedException {
        Path exiPath = Files.createTempFile("interop-bench-", ".exi");
        Files.write(exiPath, exi);

        String schemaArg = "-schema=" + String.join(",", schemaExis.stream().map(Path::toString).toList());
        ProcessBuilder pb = new ProcessBuilder(EXIPD_BIN.toString(), schemaArg, exiPath.toString());
        Process p = pb.start();
        int code = p.waitFor();

        String output = new String(p.getInputStream().readAllBytes(), StandardCharsets.UTF_8)
            + new String(p.getErrorStream().readAllBytes(), StandardCharsets.UTF_8);

        Files.deleteIfExists(exiPath);
        return new ExipResult(code == 0, output);
    }

    private static Path generateStandardSchema(Path xsd) throws IOException, InterruptedException {
        Path out = Files.createTempFile("interop-schema-", ".exi").toAbsolutePath();
        Path absXsd = xsd.toAbsolutePath();

        String args = String.format(Locale.ROOT, "%s %s", absXsd, out);
        ProcessBuilder pb = new ProcessBuilder(
            "mvn",
            "-q",
            "-DskipTests",
            "exec:java",
            "-Dexec.mainClass=org.acm.nhenehan.xsd2exip.Main",
            "-Dexec.args=" + args
        );
        pb.directory(XSD2EXIP_DIR.toFile());

        Process p = pb.start();
        int code = p.waitFor();
        if (code != 0) {
            String err = new String(p.getErrorStream().readAllBytes(), StandardCharsets.UTF_8);
            throw new IOException("xsd2exip schema generation failed: " + err);
        }

        if (!Files.exists(out) || Files.size(out) == 0L) {
            throw new IOException("xsd2exip generated an empty schema EXI for " + absXsd);
        }

        return out;
    }

    private static double meanMs(long totalNs) {
        return totalNs / 1_000_000.0 / MEASURE_ITERS;
    }

    private static String summarizeExipFailure(String output) {
        String compact = output.replace("\r", " ").replace("\n", " ").trim();
        if (compact.length() > 160) {
            return compact.substring(0, 160) + "...";
        }
        return compact;
    }

    private static void writeMarkdownReport(List<ResultRow> rows) throws IOException {
        StringBuilder md = new StringBuilder();
        md.append("# Interop Benchmark Report\n\n");
        md.append("Generated by `InteropBenchmarkTest` in `exip/interop-tests`.\n\n");
        md.append("- Warmup iterations: ").append(WARMUP_ITERS).append("\n");
        md.append("- Measured iterations: ").append(MEASURE_ITERS).append("\n");
        md.append("\n");
        md.append("| Case | Profile | Coding | Strict | XML Bytes | EXI Bytes | Encode ms | EXIficient Decode ms | exipd Decode ms | exipd status |\n");
        md.append("|---|---|---|---:|---:|---:|---:|---:|---:|---|\n");

        for (ResultRow row : rows) {
            md.append("| ")
                .append(row.caseName()).append(" | ")
                .append(row.profileId()).append(" | ")
                .append(row.codingMode()).append(" | ")
                .append(row.strict()).append(" | ")
                .append(row.xmlBytes()).append(" | ")
                .append(row.exiBytes()).append(" | ")
                .append(String.format(Locale.ROOT, "%.3f", row.encodeMs())).append(" | ")
                .append(String.format(Locale.ROOT, "%.3f", row.decodeMs())).append(" | ")
                .append(String.format(Locale.ROOT, "%.3f", row.exipDecodeMs())).append(" | ")
                .append(row.exipStatus())
                .append(" |\n");
        }

        Files.createDirectories(REPORT_MD.getParent());
        Files.writeString(REPORT_MD, md.toString(), StandardCharsets.UTF_8);
    }

    private record CaseDef(String name, Path xsd, Path xml, List<Path> importedXsds) {
    }

    private record ExipResult(boolean success, String output) {
    }

    private record ResultRow(
        String caseName,
        String profileId,
        String codingMode,
        boolean strict,
        long xmlBytes,
        int exiBytes,
        double encodeMs,
        double decodeMs,
        double exipDecodeMs,
        String exipStatus
    ) {
    }
}
