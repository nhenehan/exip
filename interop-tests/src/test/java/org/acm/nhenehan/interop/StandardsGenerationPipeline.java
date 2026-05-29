package org.acm.nhenehan.interop;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Locale;

final class StandardsGenerationPipeline {

    private static final Path INTEROP_DIR = Path.of(".").toAbsolutePath().normalize();
    private static final Path REPO_ROOT = INTEROP_DIR.getParent();
    private static final Path XSD2EXIP_DIR = REPO_ROOT.resolve("utils/xsd2exip");
    private static final Path EXAMPLES_DIR = REPO_ROOT.resolve("examples");
    private static final Path BUILD_DIR = REPO_ROOT.resolve("build");
    private static final Path EXIPG_BIN = BUILD_DIR.resolve("utils/schemaHandling/exipg");

    static final Path ARTIFACT_ROOT = Path.of("target/standards-artifacts").toAbsolutePath().normalize();

    private StandardsGenerationPipeline() {
    }

    static List<GeneratedCaseArtifacts> generateAllSelectedCases() throws IOException, InterruptedException {
        ensureExipgBinary();
        List<StandardsCaseManifest.StandardsCase> cases = StandardsCaseManifest.loadSelectedCases();

        List<GeneratedCaseArtifacts> artifacts = new ArrayList<>();
        for (StandardsCaseManifest.StandardsCase standardsCase : cases) {
            artifacts.add(generateCaseArtifacts(standardsCase));
        }
        return artifacts;
    }

    static GeneratedCaseArtifacts generateCaseArtifacts(StandardsCaseManifest.StandardsCase standardsCase)
            throws IOException, InterruptedException {
        Path caseRoot = ARTIFACT_ROOT.resolve(standardsCase.id());
        Path schemaExiDir = caseRoot.resolve("schema-exi");
        Path grammarDir = caseRoot.resolve("grammar");
        Path wrappersDir = caseRoot.resolve("wrappers");

        Files.createDirectories(schemaExiDir);
        Files.createDirectories(grammarDir);
        Files.createDirectories(wrappersDir);

        Path mainSchemaAbs = standardsCase.schema().toAbsolutePath().normalize();
        Path mainSchemaExi = schemaExiDir.resolve(stripExt(mainSchemaAbs.getFileName().toString()) + ".exi");
        generateSchemaExi(mainSchemaAbs, mainSchemaExi);

        List<Path> importExis = new ArrayList<>();
        for (Path importSchema : standardsCase.imports()) {
            Path importSchemaAbs = importSchema.toAbsolutePath().normalize();
            Path importExi = schemaExiDir.resolve(stripExt(importSchemaAbs.getFileName().toString()) + ".exi");
            generateSchemaExi(importSchemaAbs, importExi);
            importExis.add(importExi);
        }

        String prefix = toPrefix(standardsCase.id());
        Path staticGrammar = grammarDir.resolve(standardsCase.id() + "-static-grammar.c");
        generateStaticGrammar(mainSchemaExi, importExis, staticGrammar, prefix);

        Path examplesCopy = wrappersDir.resolve("examples");
        copyDirectory(EXAMPLES_DIR, examplesCopy);
        Path wrapperSchemaExi = wrappersDir.resolve(standardsCase.id() + "-wrapper-schema.exi");
        generateWrapperScaffold(mainSchemaAbs, wrapperSchemaExi, standardsCase.id(), examplesCopy);

        Path metadata = caseRoot.resolve("metadata.txt");
        Files.writeString(metadata, metadataText(standardsCase, mainSchemaExi, importExis, staticGrammar, examplesCopy),
                StandardCharsets.UTF_8);

        return new GeneratedCaseArtifacts(standardsCase.id(), caseRoot, mainSchemaExi, importExis, staticGrammar, examplesCopy, metadata);
    }

    static void generateSchemaExi(Path schemaXsd, Path schemaExiOut) throws IOException, InterruptedException {
        Files.createDirectories(schemaExiOut.getParent());
        runCommand(XSD2EXIP_DIR,
                List.of(
                        "mvn",
                        "-q",
                        "-DskipTests",
                        "exec:java",
                        "-Dexec.mainClass=org.acm.nhenehan.xsd2exip.Main",
                        "-Dexec.args=" + schemaXsd.toAbsolutePath().normalize() + " " + schemaExiOut.toAbsolutePath().normalize()));

        if (!Files.exists(schemaExiOut) || Files.size(schemaExiOut) == 0L) {
            throw new IOException("xsd2exip produced missing/empty schema EXI: " + schemaExiOut);
        }
    }

    static void generateStaticGrammar(Path mainSchemaExi, List<Path> importExis, Path outFile, String prefix)
            throws IOException, InterruptedException {
        Files.createDirectories(outFile.getParent());

        List<String> schemaList = new ArrayList<>();
        schemaList.add(mainSchemaExi.toAbsolutePath().normalize().toString());
        for (Path importExi : importExis) {
            schemaList.add(importExi.toAbsolutePath().normalize().toString());
        }

        runCommand(REPO_ROOT,
                List.of(
                        EXIPG_BIN.toAbsolutePath().normalize().toString(),
                        "-static",
                        "-pfx=" + prefix,
                        "-schema=" + String.join(",", schemaList),
                        outFile.toAbsolutePath().normalize().toString()));

        if (!Files.exists(outFile) || Files.size(outFile) == 0L) {
            throw new IOException("exipg produced missing/empty static grammar: " + outFile);
        }
    }

    static void generateWrapperScaffold(Path schemaXsd, Path schemaExiOut, String caseId, Path examplesRoot)
            throws IOException, InterruptedException {
        Files.createDirectories(schemaExiOut.getParent());

        String generateName = "phase7-" + caseId.toLowerCase(Locale.ROOT);
        runCommand(XSD2EXIP_DIR,
                List.of(
                        "mvn",
                        "-q",
                        "-DskipTests",
                        "exec:java",
                        "-Dexec.mainClass=org.acm.nhenehan.xsd2exip.Main",
                        "-Dexec.args="
                                + schemaXsd.toAbsolutePath().normalize() + " "
                                + schemaExiOut.toAbsolutePath().normalize()
                                + " --generate-c=" + generateName
                                + " --examples-root=" + examplesRoot.toAbsolutePath().normalize()
                                + " --force"));
    }

    static void ensureExipgBinary() throws IOException, InterruptedException {
        if (Files.exists(EXIPG_BIN)) {
            return;
        }

        runCommand(REPO_ROOT,
                List.of(
                        "cmake",
                        "-S",
                        ".",
                        "-B",
                        "build",
                        "-G",
                        "Ninja",
                        "-DEXIP_PLATFORM_PROFILE=pc"));

        runCommand(REPO_ROOT,
                List.of(
                        "cmake",
                        "--build",
                        "build",
                        "--target",
                        "exipg",
                        "-j4"));

        if (!Files.exists(EXIPG_BIN)) {
            throw new IOException("failed to produce exipg binary at " + EXIPG_BIN);
        }
    }

    private static void copyDirectory(Path from, Path to) throws IOException {
        if (Files.exists(to)) {
            Files.walk(to)
                    .sorted(Comparator.reverseOrder())
                    .forEach(path -> {
                        try {
                            Files.delete(path);
                        } catch (IOException ex) {
                            throw new RuntimeException(ex);
                        }
                    });
        }

        Files.walk(from).forEach(source -> {
            try {
                Path relative = from.relativize(source);
                Path destination = to.resolve(relative);
                if (Files.isDirectory(source)) {
                    Files.createDirectories(destination);
                } else {
                    Files.createDirectories(destination.getParent());
                    Files.copy(source, destination, StandardCopyOption.REPLACE_EXISTING, StandardCopyOption.COPY_ATTRIBUTES);
                }
            } catch (IOException ex) {
                throw new RuntimeException(ex);
            }
        });
    }

    private static void runCommand(Path workDir, List<String> command) throws IOException, InterruptedException {
        ProcessBuilder pb = new ProcessBuilder(command);
        pb.directory(workDir.toFile());

        Process process = pb.start();
        int code = process.waitFor();
        if (code != 0) {
            String stderr = new String(process.getErrorStream().readAllBytes(), StandardCharsets.UTF_8);
            throw new IOException("command failed (" + code + "): " + String.join(" ", command) + "\n" + stderr);
        }
    }

    private static String stripExt(String name) {
        int dot = name.lastIndexOf('.');
        return dot > 0 ? name.substring(0, dot) : name;
    }

    private static String toPrefix(String caseId) {
        String normalized = caseId.toLowerCase(Locale.ROOT).replaceAll("[^a-z0-9]+", "_");
        if (!normalized.endsWith("_")) {
            normalized = normalized + "_";
        }
        return normalized;
    }

    private static String metadataText(
            StandardsCaseManifest.StandardsCase standardsCase,
            Path mainSchemaExi,
            List<Path> importExis,
            Path staticGrammar,
            Path examplesCopy) {
        StringBuilder out = new StringBuilder();
        out.append("caseId=").append(standardsCase.id()).append('\n');
        out.append("title=").append(standardsCase.title()).append('\n');
        out.append("category=").append(standardsCase.category()).append('\n');
        out.append("schema=").append(standardsCase.schema().toAbsolutePath().normalize()).append('\n');
        out.append("xml=").append(standardsCase.xml().toAbsolutePath().normalize()).append('\n');
        out.append("schemaExi=").append(mainSchemaExi.toAbsolutePath().normalize()).append('\n');
        out.append("importSchemaExi=").append(importExis.stream().map(p -> p.toAbsolutePath().normalize().toString()).toList()).append('\n');
        out.append("staticGrammar=").append(staticGrammar.toAbsolutePath().normalize()).append('\n');
        out.append("wrapperExamplesRoot=").append(examplesCopy.toAbsolutePath().normalize()).append('\n');
        return out.toString();
    }

    record GeneratedCaseArtifacts(
            String caseId,
            Path caseRoot,
            Path mainSchemaExi,
            List<Path> importSchemaExis,
            Path staticGrammar,
            Path wrapperExamplesRoot,
            Path metadataFile) {
    }
}
