#!/usr/bin/env bash
# Regenerates the compression fixtures with the EXIficient-based oracle,
# utils/xsd2exip/target/xsd2exip-cli.jar (cd utils/xsd2exip && mvn -q -DskipTests package).
#   catalog.xml   generated: 300 items, four channels over 100 values, repeated values, small
#                 channels before and after the large ones
#   telemetry-complex.*, readings.*, order-complex.* from rexi-interop fixtures (seed S2, xsi
#                 X2, seed S1); order-complex in blocks of 9 (its value count): an empty last block
# Each document is encoded bit-packed (the reference) and in channels; the test decodes both
# and compares the events.
set -euo pipefail
cd "$(dirname "$0")"
J=../../../utils/xsd2exip/target/xsd2exip-cli.jar
enc() { java -jar "$J" encode-xml "$@" >/dev/null 2>&1; }

python3 - <<'PY'
out = ['<?xml version="1.0" encoding="UTF-8"?>', '<catalog xmlns="urn:test:big" version="7">',
       '  <meta author="ann" note="first"/>']
for n in range(300):
    out.append('  <item id="i%d" kind="k%d">value %d<sub>s%d</sub></item>' % (n % 50, n % 3, n % 120, n))
# a small channel first seen after the large ones: decoded before them (spec 9.3)
out += ['  <meta author="bob" note="last"/>', '  <trailer by="carol">end</trailer>', '</catalog>']
open('catalog.xml', 'w').write('\n'.join(out) + '\n')
PY

# schema-less, options in the header
enc --xsd none --xml catalog.xml --include-options --out catalog.bit-packed.exi
enc --xsd none --xml catalog.xml --include-options --alignment compression --out catalog.compression.exi
enc --xsd none --xml catalog.xml --include-options --alignment compression --block-size 64 --out catalog.compression.64.exi
enc --xsd none --xml catalog.xml --include-options --alignment compression --block-size 1 --out catalog.compression.1.exi
enc --xsd none --xml catalog.xml --include-options --alignment pre-compression --block-size 64 --out catalog.pre-compression.64.exi
enc --xsd none --xml catalog.xml --include-options --alignment pre-compression --out catalog.pre-compression.exi
enc --xsd none --xml catalog.xml --include-options --alignment pre-compression --block-size 1 --out catalog.pre-compression.1.exi

# schema-informed, strict, options out of band (the test sets them)
for doc in telemetry-complex readings order-complex; do
    java -jar "$J" encode-xsd --xsd $doc.xsd --xsd-exi-out $doc-xsd.exi >/dev/null 2>&1
    enc --xsd $doc.xsd --xml $doc.xml --strict --out $doc.bit-packed.exi
    enc --xsd $doc.xsd --xml $doc.xml --strict --alignment compression --out $doc.compression.exi
    enc --xsd $doc.xsd --xml $doc.xml --strict --alignment compression --block-size 3 --out $doc.compression.3.exi
    enc --xsd $doc.xsd --xml $doc.xml --strict --alignment pre-compression --out $doc.pre-compression.exi
    enc --xsd $doc.xsd --xml $doc.xml --strict --alignment pre-compression --block-size 3 --out $doc.pre-compression.3.exi
done
enc --xsd order-complex.xsd --xml order-complex.xml --strict --alignment compression --block-size 9 --out order-complex.compression.9.exi
