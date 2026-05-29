package org.acm.nhenehan.interop;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.nio.file.Files;
import java.util.List;
import org.junit.jupiter.api.Test;

final class StandardsGenerationPipelineTest {

    @Test
    void generateArtifactsForManifestCases() throws Exception {
        List<StandardsGenerationPipeline.GeneratedCaseArtifacts> artifacts =
                StandardsGenerationPipeline.generateAllSelectedCases();

        assertFalse(artifacts.isEmpty(), "manifest did not contain concrete schema/xml cases");

        for (StandardsGenerationPipeline.GeneratedCaseArtifacts caseArtifacts : artifacts) {
            assertTrue(Files.exists(caseArtifacts.mainSchemaExi()), "missing schema EXI for " + caseArtifacts.caseId());
            assertTrue(Files.exists(caseArtifacts.staticGrammar()), "missing static grammar for " + caseArtifacts.caseId());
            assertTrue(Files.exists(caseArtifacts.metadataFile()), "missing metadata for " + caseArtifacts.caseId());
        }
    }
}
