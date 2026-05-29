# interop-tests

Purpose: Java-side interoperability/oracle tests for schema-aware EXI validation.

## Initial Scope

- JAXB round-trip test harness for matrix schemas (S3-S5).
- EXI option profile matrix with mandatory strict gate:
  - P0: schema-informed + BIT_PACKED + strict (required)
  - P1: schema-informed + BIT_PACKED + non-strict
  - P2: schema-informed + BYTE_PACKED + strict
  - P3: schema-informed + COMPRESSION + strict

## Current Status

- Module scaffolded with JUnit 5, EXIficient, JAXB dependencies.
- Option-profile matrix tests in place to lock required combinations.
- JAXB class generation plugin is configured; case-specific schema sources will be wired as S3/S4/S5 fixtures are connected.

## Run

- `mvn -q test`
