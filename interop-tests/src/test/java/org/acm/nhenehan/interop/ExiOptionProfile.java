package org.acm.nhenehan.interop;

enum ExiOptionProfile {
    STRICT_SCHEMA_INFORMED_BIT_PACKED(
        "P0",
        true,
        "BIT_PACKED",
        true,
        true
    ),
    SCHEMA_INFORMED_BIT_PACKED_NON_STRICT(
        "P1",
        true,
        "BIT_PACKED",
        false,
        false
    ),
    STRICT_SCHEMA_INFORMED_BYTE_PACKED(
        "P2",
        true,
        "BYTE_PACKED",
        true,
        false
    ),
    STRICT_SCHEMA_INFORMED_COMPRESSION(
        "P3",
        true,
        "COMPRESSION",
        true,
        false
    );

    private final String id;
    private final boolean schemaInformed;
    private final String codingMode;
    private final boolean strict;
    private final boolean requiredGate;

    ExiOptionProfile(String id, boolean schemaInformed, String codingMode, boolean strict, boolean requiredGate) {
        this.id = id;
        this.schemaInformed = schemaInformed;
        this.codingMode = codingMode;
        this.strict = strict;
        this.requiredGate = requiredGate;
    }

    String id() {
        return id;
    }

    boolean schemaInformed() {
        return schemaInformed;
    }

    String codingMode() {
        return codingMode;
    }

    boolean strict() {
        return strict;
    }

    boolean requiredGate() {
        return requiredGate;
    }
}
