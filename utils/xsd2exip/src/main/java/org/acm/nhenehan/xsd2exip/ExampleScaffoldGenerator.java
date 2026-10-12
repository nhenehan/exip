package org.acm.nhenehan.xsd2exip;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Locale;
import java.util.Set;
import javax.xml.parsers.DocumentBuilderFactory;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

final class ExampleScaffoldGenerator {

    private static final String ENCODE_REGISTRY_MARKER = "\t/* GENERATED ENCODE ENTRIES */";
    private static final String DECODE_REGISTRY_MARKER = "\t/* GENERATED DECODE ENTRIES */";

    private ExampleScaffoldGenerator() {
    }

    static void generateFromSchema(String exampleName, String schemaPath, Path examplesRoot, boolean force) throws IOException {
        String slug = slugify(exampleName);
        if (slug.isBlank()) {
            throw new IOException("unable to derive slug from example name: " + exampleName);
        }

        String pascal = toPascal(slug);
        String upper = slug.toUpperCase().replace('-', '_');
        SchemaModel model = deriveModel(Path.of(schemaPath), pascal);

        Path encDir = examplesRoot.resolve("simpleEncoding");
        Path decDir = examplesRoot.resolve("simpleDecoding");

        String modelHeaderName = pascal + "Model.h";

        writeFile(encDir.resolve(modelHeaderName), modelHeaderTemplate(upper, pascal, model), force);
        writeFile(decDir.resolve(modelHeaderName), modelHeaderTemplate(upper, pascal, model), force);

        writeFile(encDir.resolve("encode" + pascal + "EXI.h"), encoderHeaderTemplate(upper, pascal, modelHeaderName), force);
        writeFile(encDir.resolve("encode" + pascal + "EXI.c"), encoderSourceTemplate(pascal, schemaPath), force);
        writeFile(decDir.resolve("decode" + pascal + "EXI.h"), decoderHeaderTemplate(upper, pascal, modelHeaderName), force);
        writeFile(decDir.resolve("decode" + pascal + "EXI.c"), decoderSourceTemplate(pascal, schemaPath), force);

        appendCFileToList(encDir.resolve("CMakeLists.txt"), "set(PROJECT_SOURCE_FILES", "  \"encode" + pascal + "EXI.c\"");
        appendCFileToList(decDir.resolve("CMakeLists.txt"), "set(PROJECT_SOURCE_FILES", "  \"decode" + pascal + "EXI.c\"");

        appendRegistryInclude(encDir.resolve("exampleEncodeRegistry.c"), "#include \"encode" + pascal + "EXI.h\"");
        appendRegistryEntry(encDir.resolve("exampleEncodeRegistry.c"), ENCODE_REGISTRY_MARKER,
                "\t{\"" + slug + "\", encode" + pascal + "},");

        appendRegistryInclude(decDir.resolve("exampleDecodeRegistry.c"), "#include \"decode" + pascal + "EXI.h\"");
        appendRegistryEntry(decDir.resolve("exampleDecodeRegistry.c"), DECODE_REGISTRY_MARKER,
                "\t{\"" + slug + "\", decode" + pascal + "},");
    }

    private static void writeFile(Path path, String content, boolean force) throws IOException {
        Files.createDirectories(path.getParent());
        if (Files.exists(path) && !force) {
            throw new IOException("file exists (use --force to overwrite): " + path);
        }
        Files.writeString(path, content, StandardCharsets.UTF_8);
    }

    private static void appendCFileToList(Path cmakePath, String listHeader, String lineToAdd) throws IOException {
        String existing = Files.readString(cmakePath, StandardCharsets.UTF_8);
        if (existing.contains(lineToAdd)) {
            return;
        }

        int listIndex = existing.indexOf(listHeader);
        if (listIndex < 0) {
            throw new IOException("unable to find CMake source list in " + cmakePath);
        }
        int closeIndex = existing.indexOf(")", listIndex);
        if (closeIndex < 0) {
            throw new IOException("unable to find end of CMake source list in " + cmakePath);
        }

        String updated = existing.substring(0, closeIndex) + lineToAdd + System.lineSeparator() + existing.substring(closeIndex);
        Files.writeString(cmakePath, updated, StandardCharsets.UTF_8);
    }

    private static void appendRegistryInclude(Path filePath, String includeLine) throws IOException {
        String existing = Files.readString(filePath, StandardCharsets.UTF_8);
        if (existing.contains(includeLine)) {
            return;
        }

        int anchor = existing.indexOf("#include <");
        if (anchor < 0) {
            anchor = existing.indexOf("typedef struct");
        }
        if (anchor < 0) {
            throw new IOException("unable to find include insertion point in " + filePath);
        }

        String updated = existing.substring(0, anchor) + includeLine + System.lineSeparator() + existing.substring(anchor);
        Files.writeString(filePath, updated, StandardCharsets.UTF_8);
    }

    private static void appendRegistryEntry(Path filePath, String marker, String entryLine) throws IOException {
        String existing = Files.readString(filePath, StandardCharsets.UTF_8);
        if (existing.contains(entryLine)) {
            return;
        }

        int markerIndex = existing.indexOf(marker);
        if (markerIndex < 0) {
            throw new IOException("unable to find registry marker in " + filePath);
        }

        String updated = existing.substring(0, markerIndex) + entryLine + System.lineSeparator() + existing.substring(markerIndex);
        Files.writeString(filePath, updated, StandardCharsets.UTF_8);
    }

    static String slugify(String input) {
        return input
            .toLowerCase()
            .replaceAll("[^a-z0-9]+", "-")
            .replaceAll("^-+", "")
            .replaceAll("-+$", "");
    }

    static String toPascal(String slug) {
        String[] parts = slug.split("-");
        StringBuilder out = new StringBuilder();
        for (String part : parts) {
            if (part.isBlank()) {
                continue;
            }
            out.append(Character.toUpperCase(part.charAt(0)));
            out.append(part.substring(1));
        }
        return out.toString();
    }

    private static String encoderHeaderTemplate(String upper, String pascal, String modelHeaderName) {
        return """
            /* Auto-generated by xsd2exip --generate-c */
            #ifndef ENCODE___UPPER___EXI_H_
            #define ENCODE___UPPER___EXI_H_

            #include "procTypes.h"
            #include "__MODEL_HEADER__"

            errorCode serialize__PASCAL__(const __PASCAL__Model* input, void* serializerContext);

            errorCode encode__PASCAL__(EXIPSchema* schemaPtr, FILE *outfile, size_t (*outputStream)(void* buf, size_t size, void* stream));

            #endif /* ENCODE___UPPER___EXI_H_ */
            """
            .replace("__UPPER__", upper)
            .replace("__MODEL_HEADER__", modelHeaderName)
            .replace("__PASCAL__", pascal);
    }

    private static String encoderSourceTemplate(String pascal, String schemaPath) {
        return """
            /* Auto-generated by xsd2exip --generate-c */
            #include "encode__PASCAL__EXI.h"
            #include "EXISerializer.h"
            #include "stringManipulate.h"

            errorCode serialize__PASCAL__(const __PASCAL__Model* input, void* serializerContext)
            {
                EXIP_UNUSED(input);
                EXIP_UNUSED(serializerContext);

                /*
                 * TODO: generated starter serializer for __PASCAL__Model.
                 * Fill in element/attribute writes that match __SCHEMA_PATH__.
                 */
                return EXIP_NOT_IMPLEMENTED_YET;
            }

            errorCode encode__PASCAL__(EXIPSchema* schemaPtr, FILE *outfile, size_t (*outputStream)(void* buf, size_t size, void* stream))
            {
                EXIP_UNUSED(schemaPtr);
                EXIP_UNUSED(outfile);
                EXIP_UNUSED(outputStream);

                /*
                 * TODO: implement encode__PASCAL__() for schema:
                 * __SCHEMA_PATH__
                 *
                 * Suggested pattern:
                 *   1. initialize EXIStream and header/options
                 *   2. serialize startDocument/startElement/... using EXISerializer
                 *   3. close stream and return EXIP_OK on success
                 */

                return EXIP_NOT_IMPLEMENTED_YET;
            }
            """
            .replace("__PASCAL__", pascal)
            .replace("__SCHEMA_PATH__", schemaPath);
    }

    private static String decoderHeaderTemplate(String upper, String pascal, String modelHeaderName) {
        return """
            /* Auto-generated by xsd2exip --generate-c */
            #ifndef DECODE___UPPER___EXI_H_
            #define DECODE___UPPER___EXI_H_

            #include "decodeTestEXI.h"
            #include "__MODEL_HEADER__"

            errorCode deserialize__PASCAL__(__PASCAL__Model* output, void* parserContext);

            errorCode decode__PASCAL__(EXIPSchema* schemaPtr, unsigned char outFlag, FILE *infile,
                    boolean outOfBandOpts, EXIOptions* opts,
                    size_t (*inputStream)(void* buf, size_t size, void* stream));

            #endif /* DECODE___UPPER___EXI_H_ */
            """
            .replace("__UPPER__", upper)
            .replace("__MODEL_HEADER__", modelHeaderName)
            .replace("__PASCAL__", pascal);
    }

    private static String decoderSourceTemplate(String pascal, String schemaPath) {
        return """
            /* Auto-generated by xsd2exip --generate-c */
            #include "decode__PASCAL__EXI.h"

            errorCode deserialize__PASCAL__(__PASCAL__Model* output, void* parserContext)
            {
                EXIP_UNUSED(output);
                EXIP_UNUSED(parserContext);

                /*
                 * TODO: generated starter deserializer for __PASCAL__Model.
                 * Read values from parser callbacks for __SCHEMA_PATH__.
                 */
                return EXIP_NOT_IMPLEMENTED_YET;
            }

            errorCode decode__PASCAL__(EXIPSchema* schemaPtr, unsigned char outFlag, FILE *infile,
                    exip_bool outOfBandOpts, EXIOptions* opts,
                    size_t (*inputStream)(void* buf, size_t size, void* stream))
            {
                /*
                 * Generated wrapper for schema:
                 * __SCHEMA_PATH__
                 *
                 * Customize this function if the example needs special decode-time behavior.
                 */
                return decode(schemaPtr, outFlag, infile, outOfBandOpts, opts, inputStream);
            }
            """
            .replace("__PASCAL__", pascal)
            .replace("__SCHEMA_PATH__", schemaPath);
    }

    private static String modelHeaderTemplate(String upper, String pascal, SchemaModel model) {
        return """
            /* Auto-generated by xsd2exip --generate-c */
            #ifndef __PASCAL___MODEL___UPPER___H_
            #define __PASCAL___MODEL___UPPER___H_

            #include "procTypes.h"
            #include <stdint.h>

            typedef struct {
            __FIELDS__
            } __PASCAL__Model;

            #endif /* __PASCAL___MODEL___UPPER___H_ */
            """
            .replace("__UPPER__", upper)
            .replace("__PASCAL__", pascal)
            .replace("__FIELDS__", renderFields(model.fields()));
    }

    private static String renderFields(List<SchemaField> fields) {
        StringBuilder out = new StringBuilder();
        for (SchemaField field : fields) {
            if (field.list()) {
                out.append("    ").append(field.cType()).append("* ").append(field.cName()).append(";")
                    .append(System.lineSeparator());
                out.append("    uint16_t ").append(field.cName()).append("Count;")
                    .append(System.lineSeparator());
            } else {
                out.append("    ").append(field.cType()).append(" ").append(field.cName()).append(";")
                    .append(System.lineSeparator());
            }

            if (field.optional()) {
                out.append("    exip_bool has").append(toPascalCaseWord(field.cName())).append(";")
                    .append(System.lineSeparator());
            }
        }
        return out.toString();
    }

    private static SchemaModel deriveModel(Path schemaPath, String fallbackPascal) {
        try {
            if (!Files.exists(schemaPath)) {
                return fallbackModel(fallbackPascal);
            }

            DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
            factory.setNamespaceAware(true);
            Document document = factory.newDocumentBuilder().parse(schemaPath.toFile());
            Element schema = document.getDocumentElement();

            Element rootElement = findFirstTopLevelElement(schema);
            if (rootElement == null) {
                return fallbackModel(fallbackPascal);
            }

            String rootName = sanitizeIdentifier(rootElement.getAttribute("name"), "document");
            Element complexType = resolveComplexType(schema, rootElement);
            if (complexType == null) {
                return new SchemaModel(rootName, List.of(
                    new SchemaField("value", "char*", false, false)
                ));
            }

            List<SchemaField> fields = extractFields(complexType);
            if (fields.isEmpty()) {
                fields = List.of(new SchemaField("value", "char*", false, false));
            }

            return new SchemaModel(rootName, fields);
        } catch (Exception ex) {
            return fallbackModel(fallbackPascal);
        }
    }

    private static SchemaModel fallbackModel(String fallbackPascal) {
        String cName = sanitizeIdentifier(toCamel(fallbackPascal + "Value"), "value");
        return new SchemaModel(fallbackPascal.toLowerCase(Locale.ROOT), List.of(
            new SchemaField(cName, "char*", false, false)
        ));
    }

    private static List<SchemaField> extractFields(Element complexType) {
        List<SchemaField> fields = new ArrayList<>();
        Set<String> seen = new LinkedHashSet<>();

        for (Element elementField : descendantsByLocalName(complexType, "element")) {
            String fieldName = sanitizeIdentifier(toCamel(elementField.getAttribute("name")), "value");
            if (!seen.add(fieldName)) {
                continue;
            }
            String cType = mapXsdTypeToC(resolveTypeName(elementField));
            boolean list = isListField(elementField);
            boolean optional = "0".equals(elementField.getAttribute("minOccurs"));
            fields.add(new SchemaField(fieldName, cType, list, optional));
        }

        for (Element attributeField : descendantsByLocalName(complexType, "attribute")) {
            String fieldName = sanitizeIdentifier(toCamel(attributeField.getAttribute("name")), "attributeValue");
            if (!seen.add(fieldName)) {
                continue;
            }
            String cType = mapXsdTypeToC(resolveTypeName(attributeField));
            boolean optional = !"required".equals(attributeField.getAttribute("use"));
            fields.add(new SchemaField(fieldName, cType, false, optional));
        }

        return fields;
    }

    private static Element resolveComplexType(Element schema, Element rootElement) {
        Element inline = firstChildByLocalName(rootElement, "complexType");
        if (inline != null) {
            return inline;
        }

        String typeRef = rootElement.getAttribute("type");
        if (typeRef == null || typeRef.isBlank()) {
            return null;
        }

        String localType = stripPrefix(typeRef);
        for (Element complexType : topLevelByLocalName(schema, "complexType")) {
            if (localType.equals(complexType.getAttribute("name"))) {
                return complexType;
            }
        }
        return null;
    }

    private static Element findFirstTopLevelElement(Element schema) {
        List<Element> elements = topLevelByLocalName(schema, "element");
        if (elements.isEmpty()) {
            return null;
        }
        return elements.get(0);
    }

    private static List<Element> topLevelByLocalName(Element parent, String localName) {
        List<Element> result = new ArrayList<>();
        NodeList children = parent.getChildNodes();
        for (int i = 0; i < children.getLength(); i++) {
            Node node = children.item(i);
            if (node instanceof Element element && localName.equals(element.getLocalName())) {
                result.add(element);
            }
        }
        return result;
    }

    private static List<Element> descendantsByLocalName(Element parent, String localName) {
        List<Element> result = new ArrayList<>();
        NodeList nodes = parent.getElementsByTagNameNS("*", localName);
        for (int i = 0; i < nodes.getLength(); i++) {
            Node node = nodes.item(i);
            if (node instanceof Element element) {
                result.add(element);
            }
        }
        return result;
    }

    private static Element firstChildByLocalName(Element parent, String localName) {
        for (Element child : topLevelByLocalName(parent, localName)) {
            return child;
        }
        return null;
    }

    private static String resolveTypeName(Element node) {
        String typeRef = node.getAttribute("type");
        if (typeRef == null || typeRef.isBlank()) {
            return "xs:string";
        }
        return stripPrefix(typeRef).toLowerCase(Locale.ROOT);
    }

    private static String stripPrefix(String qname) {
        int idx = qname.indexOf(':');
        if (idx >= 0 && idx + 1 < qname.length()) {
            return qname.substring(idx + 1);
        }
        return qname;
    }

    private static boolean isListField(Element element) {
        String maxOccurs = element.getAttribute("maxOccurs");
        if ("unbounded".equals(maxOccurs)) {
            return true;
        }
        if (maxOccurs == null || maxOccurs.isBlank()) {
            return false;
        }
        try {
            return Integer.parseInt(maxOccurs) > 1;
        } catch (NumberFormatException ex) {
            return false;
        }
    }

    private static String mapXsdTypeToC(String typeName) {
        return switch (typeName) {
            case "boolean" -> "exip_bool";
            case "byte", "unsignedbyte", "short", "unsignedshort", "int", "unsignedint", "integer" -> "int32_t";
            case "long", "unsignedlong" -> "int64_t";
            case "float", "double", "decimal" -> "double";
            default -> "char*";
        };
    }

    private static String toCamel(String value) {
        String normalized = value.replaceAll("[^A-Za-z0-9]+", " ").trim();
        if (normalized.isEmpty()) {
            return "value";
        }

        String[] parts = normalized.split("\\s+");
        StringBuilder out = new StringBuilder(parts[0].toLowerCase(Locale.ROOT));
        for (int i = 1; i < parts.length; i++) {
            out.append(toPascalCaseWord(parts[i]));
        }
        return out.toString();
    }

    private static String toPascalCaseWord(String value) {
        if (value == null || value.isBlank()) {
            return "Value";
        }
        String cleaned = value.replaceAll("[^A-Za-z0-9]", "");
        if (cleaned.isEmpty()) {
            return "Value";
        }
        return Character.toUpperCase(cleaned.charAt(0)) + cleaned.substring(1);
    }

    private static String sanitizeIdentifier(String value, String fallback) {
        String cleaned = (value == null ? "" : value).replaceAll("[^A-Za-z0-9_]", "");
        if (cleaned.isBlank()) {
            cleaned = fallback;
        }
        if (!Character.isLetter(cleaned.charAt(0)) && cleaned.charAt(0) != '_') {
            cleaned = "f_" + cleaned;
        }

        return switch (cleaned) {
            case "int", "double", "float", "char", "short", "long", "switch", "default", "struct" -> cleaned + "Field";
            default -> cleaned;
        };
    }

    private record SchemaModel(String rootName, List<SchemaField> fields) {
    }

    private record SchemaField(String cName, String cType, boolean list, boolean optional) {
    }
}
