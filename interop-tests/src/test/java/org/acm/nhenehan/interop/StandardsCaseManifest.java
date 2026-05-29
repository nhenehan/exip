package org.acm.nhenehan.interop;

import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import java.io.IOException;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;

final class StandardsCaseManifest {

    static final Path MANIFEST_PATH = Path.of("src/test/resources/fixtures/standards/manifests/cases-manifest.json");

    private StandardsCaseManifest() {
    }

    static List<StandardsCase> loadSelectedCases() throws IOException {
        ObjectMapper mapper = new ObjectMapper();
        JsonNode root = mapper.readTree(MANIFEST_PATH.toFile());
        JsonNode selectedCases = root.path("selectedCases");

        if (!selectedCases.isArray()) {
            throw new IOException("invalid manifest: selectedCases must be an array");
        }

        List<StandardsCase> cases = new ArrayList<>();
        for (JsonNode node : selectedCases) {
            JsonNode schemaNode = node.get("schema");
            JsonNode xmlNode = node.get("xml");

            // Non-concrete entries are intentionally ignored until schema/xml paths are provided.
            if (schemaNode == null || xmlNode == null) {
                continue;
            }

            String id = node.path("id").asText();
            String title = node.path("title").asText();
            String category = node.path("category").asText();
            Path schema = Path.of("src/test/resources").resolve(schemaNode.asText()).normalize();
            Path xml = Path.of("src/test/resources").resolve(xmlNode.asText()).normalize();

            List<Path> imports = new ArrayList<>();
            JsonNode importsNode = node.get("imports");
            if (importsNode != null && importsNode.isArray()) {
                for (JsonNode importNode : importsNode) {
                    imports.add(Path.of("src/test/resources").resolve(importNode.asText()).normalize());
                }
            }

            List<String> expectedTokens = new ArrayList<>();
            JsonNode expectedTokensNode = node.get("expectedTokens");
            if (expectedTokensNode != null && expectedTokensNode.isArray()) {
                for (JsonNode tokenNode : expectedTokensNode) {
                    expectedTokens.add(tokenNode.asText());
                }
            }

            List<String> profileIds = new ArrayList<>();
            JsonNode profilesNode = node.get("profiles");
            if (profilesNode != null && profilesNode.isArray()) {
                for (JsonNode profileNode : profilesNode) {
                    profileIds.add(profileNode.asText());
                }
            }

            cases.add(new StandardsCase(id, title, category, schema, xml, imports, expectedTokens, profileIds));
        }

        return cases;
    }

    record StandardsCase(
            String id,
            String title,
            String category,
            Path schema,
            Path xml,
            List<Path> imports,
            List<String> expectedTokens,
            List<String> profileIds) {
    }
}
