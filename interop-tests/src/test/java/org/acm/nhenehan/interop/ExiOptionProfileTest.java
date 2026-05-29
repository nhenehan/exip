package org.acm.nhenehan.interop;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.util.Arrays;
import java.util.List;
import org.junit.jupiter.api.Test;

final class ExiOptionProfileTest {

    @Test
    void strictSchemaInformedBitPackedProfileIsPresentAndRequired() {
        List<ExiOptionProfile> all = Arrays.asList(ExiOptionProfile.values());
        ExiOptionProfile gate = all.stream()
            .filter(ExiOptionProfile::requiredGate)
            .findFirst()
            .orElseThrow();

        assertEquals("P0", gate.id());
        assertTrue(gate.schemaInformed());
        assertEquals("BIT_PACKED", gate.codingMode());
        assertTrue(gate.strict());
    }

    @Test
    void optionMatrixCoversRequiredDiagnosticCombinations() {
        List<ExiOptionProfile> all = Arrays.asList(ExiOptionProfile.values());

        assertEquals(4, all.size(), "expected P0-P3 option profiles");
        assertTrue(all.stream().allMatch(ExiOptionProfile::schemaInformed));
        assertTrue(
            all.stream().anyMatch(p -> "BIT_PACKED".equals(p.codingMode()) && p.strict()),
            "missing strict bit-packed profile"
        );
        assertTrue(
            all.stream().anyMatch(p -> "BIT_PACKED".equals(p.codingMode()) && !p.strict()),
            "missing non-strict bit-packed profile"
        );
        assertTrue(
            all.stream().anyMatch(p -> "BYTE_PACKED".equals(p.codingMode()) && p.strict()),
            "missing strict byte-packed profile"
        );
        assertTrue(
            all.stream().anyMatch(p -> "COMPRESSION".equals(p.codingMode()) && p.strict()),
            "missing strict compression profile"
        );
    }
}
