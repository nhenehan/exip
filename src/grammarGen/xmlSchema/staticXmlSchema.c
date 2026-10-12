/** AUTO-GENERATED: Tue Nov 25 17:49:15 2014
  * Copyright (c) 2010 - 2011, Rumen Kyusakov, EISLAB, LTU
  * $Id$ */

/** Compilation parameters:
  * Compiled for possible deviations from the schema:
  * URLs: 10
  * Local names: 0
  * Prefixes: 1
  * Built-in grammars: 5 */

#include "procTypes.h"

#define CONST

/** START_STRINGS_DEFINITONS */

const CharType xmlscm_LN_0_0[] = {0x61, 0x62, 0x73, 0x74, 0x72, 0x61, 0x63, 0x74}; /* abstract */
const CharType xmlscm_LN_0_1[] = {0x61, 0x74, 0x74, 0x72, 0x69, 0x62, 0x75, 0x74, 0x65, 0x46, 0x6f, 0x72, 0x6d, 0x44, 0x65, 0x66, 0x61, 0x75, 0x6c, 0x74}; /* attributeFormDefault */
const CharType xmlscm_LN_0_2[] = {0x62, 0x61, 0x73, 0x65}; /* base */
const CharType xmlscm_LN_0_3[] = {0x62, 0x6c, 0x6f, 0x63, 0x6b}; /* block */
const CharType xmlscm_LN_0_4[] = {0x62, 0x6c, 0x6f, 0x63, 0x6b, 0x44, 0x65, 0x66, 0x61, 0x75, 0x6c, 0x74}; /* blockDefault */
const CharType xmlscm_LN_0_5[] = {0x64, 0x65, 0x66, 0x61, 0x75, 0x6c, 0x74}; /* default */
const CharType xmlscm_LN_0_6[] = {0x65, 0x6c, 0x65, 0x6d, 0x65, 0x6e, 0x74, 0x46, 0x6f, 0x72, 0x6d, 0x44, 0x65, 0x66, 0x61, 0x75, 0x6c, 0x74}; /* elementFormDefault */
const CharType xmlscm_LN_0_7[] = {0x66, 0x69, 0x6e, 0x61, 0x6c}; /* final */
const CharType xmlscm_LN_0_8[] = {0x66, 0x69, 0x6e, 0x61, 0x6c, 0x44, 0x65, 0x66, 0x61, 0x75, 0x6c, 0x74}; /* finalDefault */
const CharType xmlscm_LN_0_9[] = {0x66, 0x69, 0x78, 0x65, 0x64}; /* fixed */
const CharType xmlscm_LN_0_10[] = {0x66, 0x6f, 0x72, 0x6d}; /* form */
const CharType xmlscm_LN_0_11[] = {0x69, 0x64}; /* id */
const CharType xmlscm_LN_0_12[] = {0x69, 0x74, 0x65, 0x6d, 0x54, 0x79, 0x70, 0x65}; /* itemType */
const CharType xmlscm_LN_0_13[] = {0x6d, 0x61, 0x78, 0x4f, 0x63, 0x63, 0x75, 0x72, 0x73}; /* maxOccurs */
const CharType xmlscm_LN_0_14[] = {0x6d, 0x65, 0x6d, 0x62, 0x65, 0x72, 0x54, 0x79, 0x70, 0x65, 0x73}; /* memberTypes */
const CharType xmlscm_LN_0_15[] = {0x6d, 0x69, 0x6e, 0x4f, 0x63, 0x63, 0x75, 0x72, 0x73}; /* minOccurs */
const CharType xmlscm_LN_0_16[] = {0x6d, 0x69, 0x78, 0x65, 0x64}; /* mixed */
const CharType xmlscm_LN_0_17[] = {0x6e, 0x61, 0x6d, 0x65}; /* name */
const CharType xmlscm_LN_0_18[] = {0x6e, 0x61, 0x6d, 0x65, 0x73, 0x70, 0x61, 0x63, 0x65}; /* namespace */
const CharType xmlscm_LN_0_19[] = {0x6e, 0x69, 0x6c, 0x6c, 0x61, 0x62, 0x6c, 0x65}; /* nillable */
const CharType xmlscm_LN_0_20[] = {0x70, 0x72, 0x6f, 0x63, 0x65, 0x73, 0x73, 0x43, 0x6f, 0x6e, 0x74, 0x65, 0x6e, 0x74, 0x73}; /* processContents */
const CharType xmlscm_LN_0_21[] = {0x70, 0x75, 0x62, 0x6c, 0x69, 0x63}; /* public */
const CharType xmlscm_LN_0_22[] = {0x72, 0x65, 0x66}; /* ref */
const CharType xmlscm_LN_0_23[] = {0x72, 0x65, 0x66, 0x65, 0x72}; /* refer */
const CharType xmlscm_LN_0_24[] = {0x73, 0x63, 0x68, 0x65, 0x6d, 0x61, 0x4c, 0x6f, 0x63, 0x61, 0x74, 0x69, 0x6f, 0x6e}; /* schemaLocation */
const CharType xmlscm_LN_0_25[] = {0x73, 0x6f, 0x75, 0x72, 0x63, 0x65}; /* source */
const CharType xmlscm_LN_0_26[] = {0x73, 0x75, 0x62, 0x73, 0x74, 0x69, 0x74, 0x75, 0x74, 0x69, 0x6f, 0x6e, 0x47, 0x72, 0x6f, 0x75, 0x70}; /* substitutionGroup */
const CharType xmlscm_LN_0_27[] = {0x73, 0x79, 0x73, 0x74, 0x65, 0x6d}; /* system */
const CharType xmlscm_LN_0_28[] = {0x74, 0x61, 0x72, 0x67, 0x65, 0x74, 0x4e, 0x61, 0x6d, 0x65, 0x73, 0x70, 0x61, 0x63, 0x65}; /* targetNamespace */
const CharType xmlscm_LN_0_29[] = {0x74, 0x79, 0x70, 0x65}; /* type */
const CharType xmlscm_LN_0_30[] = {0x75, 0x73, 0x65}; /* use */
const CharType xmlscm_LN_0_31[] = {0x76, 0x61, 0x6c, 0x75, 0x65}; /* value */
const CharType xmlscm_LN_0_32[] = {0x76, 0x65, 0x72, 0x73, 0x69, 0x6f, 0x6e}; /* version */
const CharType xmlscm_LN_0_33[] = {0x78, 0x70, 0x61, 0x74, 0x68}; /* xpath */
const CharType xmlscm_URI_1[] = {0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x77, 0x77, 0x77, 0x2e, 0x77, 0x33, 0x2e, 0x6f, 0x72, 0x67, 0x2f, 0x58, 0x4d, 0x4c, 0x2f, 0x31, 0x39, 0x39, 0x38, 0x2f, 0x6e, 0x61, 0x6d, 0x65, 0x73, 0x70, 0x61, 0x63, 0x65}; /* http://www.w3.org/XML/1998/namespace */
const CharType xmlscm_PFX_1_0[] = {0x78, 0x6d, 0x6c}; /* xml */
const CharType xmlscm_LN_1_0[] = {0x62, 0x61, 0x73, 0x65}; /* base */
const CharType xmlscm_LN_1_1[] = {0x69, 0x64}; /* id */
const CharType xmlscm_LN_1_2[] = {0x6c, 0x61, 0x6e, 0x67}; /* lang */
const CharType xmlscm_LN_1_3[] = {0x73, 0x70, 0x61, 0x63, 0x65}; /* space */
const CharType xmlscm_LN_1_4[] = {0x73, 0x70, 0x65, 0x63, 0x69, 0x61, 0x6c, 0x41, 0x74, 0x74, 0x72, 0x73}; /* specialAttrs */
const CharType xmlscm_URI_2[] = {0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x77, 0x77, 0x77, 0x2e, 0x77, 0x33, 0x2e, 0x6f, 0x72, 0x67, 0x2f, 0x32, 0x30, 0x30, 0x31, 0x2f, 0x58, 0x4d, 0x4c, 0x53, 0x63, 0x68, 0x65, 0x6d, 0x61, 0x2d, 0x69, 0x6e, 0x73, 0x74, 0x61, 0x6e, 0x63, 0x65}; /* http://www.w3.org/2001/XMLSchema-instance */
const CharType xmlscm_PFX_2_0[] = {0x78, 0x73, 0x69}; /* xsi */
const CharType xmlscm_LN_2_0[] = {0x6e, 0x69, 0x6c}; /* nil */
const CharType xmlscm_LN_2_1[] = {0x74, 0x79, 0x70, 0x65}; /* type */
const CharType xmlscm_URI_3[] = {0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x77, 0x77, 0x77, 0x2e, 0x77, 0x33, 0x2e, 0x6f, 0x72, 0x67, 0x2f, 0x32, 0x30, 0x30, 0x31, 0x2f, 0x58, 0x4d, 0x4c, 0x53, 0x63, 0x68, 0x65, 0x6d, 0x61}; /* http://www.w3.org/2001/XMLSchema */
const CharType xmlscm_LN_3_0[] = {0x45, 0x4e, 0x54, 0x49, 0x54, 0x49, 0x45, 0x53}; /* ENTITIES */
const CharType xmlscm_LN_3_1[] = {0x45, 0x4e, 0x54, 0x49, 0x54, 0x59}; /* ENTITY */
const CharType xmlscm_LN_3_2[] = {0x49, 0x44}; /* ID */
const CharType xmlscm_LN_3_3[] = {0x49, 0x44, 0x52, 0x45, 0x46}; /* IDREF */
const CharType xmlscm_LN_3_4[] = {0x49, 0x44, 0x52, 0x45, 0x46, 0x53}; /* IDREFS */
const CharType xmlscm_LN_3_5[] = {0x4e, 0x43, 0x4e, 0x61, 0x6d, 0x65}; /* NCName */
const CharType xmlscm_LN_3_6[] = {0x4e, 0x4d, 0x54, 0x4f, 0x4b, 0x45, 0x4e}; /* NMTOKEN */
const CharType xmlscm_LN_3_7[] = {0x4e, 0x4d, 0x54, 0x4f, 0x4b, 0x45, 0x4e, 0x53}; /* NMTOKENS */
const CharType xmlscm_LN_3_8[] = {0x4e, 0x4f, 0x54, 0x41, 0x54, 0x49, 0x4f, 0x4e}; /* NOTATION */
const CharType xmlscm_LN_3_9[] = {0x4e, 0x61, 0x6d, 0x65}; /* Name */
const CharType xmlscm_LN_3_10[] = {0x51, 0x4e, 0x61, 0x6d, 0x65}; /* QName */
const CharType xmlscm_LN_3_11[] = {0x61, 0x6e, 0x79, 0x53, 0x69, 0x6d, 0x70, 0x6c, 0x65, 0x54, 0x79, 0x70, 0x65}; /* anySimpleType */
const CharType xmlscm_LN_3_12[] = {0x61, 0x6e, 0x79, 0x54, 0x79, 0x70, 0x65}; /* anyType */
const CharType xmlscm_LN_3_13[] = {0x61, 0x6e, 0x79, 0x55, 0x52, 0x49}; /* anyURI */
const CharType xmlscm_LN_3_14[] = {0x62, 0x61, 0x73, 0x65, 0x36, 0x34, 0x42, 0x69, 0x6e, 0x61, 0x72, 0x79}; /* base64Binary */
const CharType xmlscm_LN_3_15[] = {0x62, 0x6f, 0x6f, 0x6c, 0x65, 0x61, 0x6e}; /* boolean */
const CharType xmlscm_LN_3_16[] = {0x62, 0x79, 0x74, 0x65}; /* byte */
const CharType xmlscm_LN_3_17[] = {0x64, 0x61, 0x74, 0x65}; /* date */
const CharType xmlscm_LN_3_18[] = {0x64, 0x61, 0x74, 0x65, 0x54, 0x69, 0x6d, 0x65}; /* dateTime */
const CharType xmlscm_LN_3_19[] = {0x64, 0x65, 0x63, 0x69, 0x6d, 0x61, 0x6c}; /* decimal */
const CharType xmlscm_LN_3_20[] = {0x64, 0x6f, 0x75, 0x62, 0x6c, 0x65}; /* double */
const CharType xmlscm_LN_3_21[] = {0x64, 0x75, 0x72, 0x61, 0x74, 0x69, 0x6f, 0x6e}; /* duration */
const CharType xmlscm_LN_3_22[] = {0x66, 0x6c, 0x6f, 0x61, 0x74}; /* float */
const CharType xmlscm_LN_3_23[] = {0x67, 0x44, 0x61, 0x79}; /* gDay */
const CharType xmlscm_LN_3_24[] = {0x67, 0x4d, 0x6f, 0x6e, 0x74, 0x68}; /* gMonth */
const CharType xmlscm_LN_3_25[] = {0x67, 0x4d, 0x6f, 0x6e, 0x74, 0x68, 0x44, 0x61, 0x79}; /* gMonthDay */
const CharType xmlscm_LN_3_26[] = {0x67, 0x59, 0x65, 0x61, 0x72}; /* gYear */
const CharType xmlscm_LN_3_27[] = {0x67, 0x59, 0x65, 0x61, 0x72, 0x4d, 0x6f, 0x6e, 0x74, 0x68}; /* gYearMonth */
const CharType xmlscm_LN_3_28[] = {0x68, 0x65, 0x78, 0x42, 0x69, 0x6e, 0x61, 0x72, 0x79}; /* hexBinary */
const CharType xmlscm_LN_3_29[] = {0x69, 0x6e, 0x74}; /* int */
const CharType xmlscm_LN_3_30[] = {0x69, 0x6e, 0x74, 0x65, 0x67, 0x65, 0x72}; /* integer */
const CharType xmlscm_LN_3_31[] = {0x6c, 0x61, 0x6e, 0x67, 0x75, 0x61, 0x67, 0x65}; /* language */
const CharType xmlscm_LN_3_32[] = {0x6c, 0x6f, 0x6e, 0x67}; /* long */
const CharType xmlscm_LN_3_33[] = {0x6e, 0x65, 0x67, 0x61, 0x74, 0x69, 0x76, 0x65, 0x49, 0x6e, 0x74, 0x65, 0x67, 0x65, 0x72}; /* negativeInteger */
const CharType xmlscm_LN_3_34[] = {0x6e, 0x6f, 0x6e, 0x4e, 0x65, 0x67, 0x61, 0x74, 0x69, 0x76, 0x65, 0x49, 0x6e, 0x74, 0x65, 0x67, 0x65, 0x72}; /* nonNegativeInteger */
const CharType xmlscm_LN_3_35[] = {0x6e, 0x6f, 0x6e, 0x50, 0x6f, 0x73, 0x69, 0x74, 0x69, 0x76, 0x65, 0x49, 0x6e, 0x74, 0x65, 0x67, 0x65, 0x72}; /* nonPositiveInteger */
const CharType xmlscm_LN_3_36[] = {0x6e, 0x6f, 0x72, 0x6d, 0x61, 0x6c, 0x69, 0x7a, 0x65, 0x64, 0x53, 0x74, 0x72, 0x69, 0x6e, 0x67}; /* normalizedString */
const CharType xmlscm_LN_3_37[] = {0x70, 0x6f, 0x73, 0x69, 0x74, 0x69, 0x76, 0x65, 0x49, 0x6e, 0x74, 0x65, 0x67, 0x65, 0x72}; /* positiveInteger */
const CharType xmlscm_LN_3_38[] = {0x73, 0x68, 0x6f, 0x72, 0x74}; /* short */
const CharType xmlscm_LN_3_39[] = {0x73, 0x74, 0x72, 0x69, 0x6e, 0x67}; /* string */
const CharType xmlscm_LN_3_40[] = {0x74, 0x69, 0x6d, 0x65}; /* time */
const CharType xmlscm_LN_3_41[] = {0x74, 0x6f, 0x6b, 0x65, 0x6e}; /* token */
const CharType xmlscm_LN_3_42[] = {0x75, 0x6e, 0x73, 0x69, 0x67, 0x6e, 0x65, 0x64, 0x42, 0x79, 0x74, 0x65}; /* unsignedByte */
const CharType xmlscm_LN_3_43[] = {0x75, 0x6e, 0x73, 0x69, 0x67, 0x6e, 0x65, 0x64, 0x49, 0x6e, 0x74}; /* unsignedInt */
const CharType xmlscm_LN_3_44[] = {0x75, 0x6e, 0x73, 0x69, 0x67, 0x6e, 0x65, 0x64, 0x4c, 0x6f, 0x6e, 0x67}; /* unsignedLong */
const CharType xmlscm_LN_3_45[] = {0x75, 0x6e, 0x73, 0x69, 0x67, 0x6e, 0x65, 0x64, 0x53, 0x68, 0x6f, 0x72, 0x74}; /* unsignedShort */
const CharType xmlscm_LN_3_46[] = {0x61, 0x6c, 0x6c}; /* all */
const CharType xmlscm_LN_3_47[] = {0x61, 0x6c, 0x6c, 0x4d, 0x6f, 0x64, 0x65, 0x6c}; /* allModel */
const CharType xmlscm_LN_3_48[] = {0x61, 0x6c, 0x6c, 0x4e, 0x4e, 0x49}; /* allNNI */
const CharType xmlscm_LN_3_49[] = {0x61, 0x6e, 0x6e, 0x6f, 0x74, 0x61, 0x74, 0x65, 0x64}; /* annotated */
const CharType xmlscm_LN_3_50[] = {0x61, 0x6e, 0x6e, 0x6f, 0x74, 0x61, 0x74, 0x69, 0x6f, 0x6e}; /* annotation */
const CharType xmlscm_LN_3_51[] = {0x61, 0x6e, 0x79}; /* any */
const CharType xmlscm_LN_3_52[] = {0x61, 0x6e, 0x79, 0x41, 0x74, 0x74, 0x72, 0x69, 0x62, 0x75, 0x74, 0x65}; /* anyAttribute */
const CharType xmlscm_LN_3_53[] = {0x61, 0x70, 0x70, 0x69, 0x6e, 0x66, 0x6f}; /* appinfo */
const CharType xmlscm_LN_3_54[] = {0x61, 0x74, 0x74, 0x72, 0x44, 0x65, 0x63, 0x6c, 0x73}; /* attrDecls */
const CharType xmlscm_LN_3_55[] = {0x61, 0x74, 0x74, 0x72, 0x69, 0x62, 0x75, 0x74, 0x65}; /* attribute */
const CharType xmlscm_LN_3_56[] = {0x61, 0x74, 0x74, 0x72, 0x69, 0x62, 0x75, 0x74, 0x65, 0x47, 0x72, 0x6f, 0x75, 0x70}; /* attributeGroup */
const CharType xmlscm_LN_3_57[] = {0x61, 0x74, 0x74, 0x72, 0x69, 0x62, 0x75, 0x74, 0x65, 0x47, 0x72, 0x6f, 0x75, 0x70, 0x52, 0x65, 0x66}; /* attributeGroupRef */
const CharType xmlscm_LN_3_58[] = {0x62, 0x6c, 0x6f, 0x63, 0x6b, 0x53, 0x65, 0x74}; /* blockSet */
const CharType xmlscm_LN_3_59[] = {0x63, 0x68, 0x6f, 0x69, 0x63, 0x65}; /* choice */
const CharType xmlscm_LN_3_60[] = {0x63, 0x6f, 0x6d, 0x70, 0x6c, 0x65, 0x78, 0x43, 0x6f, 0x6e, 0x74, 0x65, 0x6e, 0x74}; /* complexContent */
const CharType xmlscm_LN_3_61[] = {0x63, 0x6f, 0x6d, 0x70, 0x6c, 0x65, 0x78, 0x52, 0x65, 0x73, 0x74, 0x72, 0x69, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x54, 0x79, 0x70, 0x65}; /* complexRestrictionType */
const CharType xmlscm_LN_3_62[] = {0x63, 0x6f, 0x6d, 0x70, 0x6c, 0x65, 0x78, 0x54, 0x79, 0x70, 0x65}; /* complexType */
const CharType xmlscm_LN_3_63[] = {0x63, 0x6f, 0x6d, 0x70, 0x6c, 0x65, 0x78, 0x54, 0x79, 0x70, 0x65, 0x4d, 0x6f, 0x64, 0x65, 0x6c}; /* complexTypeModel */
const CharType xmlscm_LN_3_64[] = {0x64, 0x65, 0x66, 0x52, 0x65, 0x66}; /* defRef */
const CharType xmlscm_LN_3_65[] = {0x64, 0x65, 0x72, 0x69, 0x76, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x43, 0x6f, 0x6e, 0x74, 0x72, 0x6f, 0x6c}; /* derivationControl */
const CharType xmlscm_LN_3_66[] = {0x64, 0x65, 0x72, 0x69, 0x76, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x53, 0x65, 0x74}; /* derivationSet */
const CharType xmlscm_LN_3_67[] = {0x64, 0x6f, 0x63, 0x75, 0x6d, 0x65, 0x6e, 0x74, 0x61, 0x74, 0x69, 0x6f, 0x6e}; /* documentation */
const CharType xmlscm_LN_3_68[] = {0x65, 0x6c, 0x65, 0x6d, 0x65, 0x6e, 0x74}; /* element */
const CharType xmlscm_LN_3_69[] = {0x65, 0x6e, 0x75, 0x6d, 0x65, 0x72, 0x61, 0x74, 0x69, 0x6f, 0x6e}; /* enumeration */
const CharType xmlscm_LN_3_70[] = {0x65, 0x78, 0x70, 0x6c, 0x69, 0x63, 0x69, 0x74, 0x47, 0x72, 0x6f, 0x75, 0x70}; /* explicitGroup */
const CharType xmlscm_LN_3_71[] = {0x65, 0x78, 0x74, 0x65, 0x6e, 0x73, 0x69, 0x6f, 0x6e}; /* extension */
const CharType xmlscm_LN_3_72[] = {0x65, 0x78, 0x74, 0x65, 0x6e, 0x73, 0x69, 0x6f, 0x6e, 0x54, 0x79, 0x70, 0x65}; /* extensionType */
const CharType xmlscm_LN_3_73[] = {0x66, 0x61, 0x63, 0x65, 0x74}; /* facet */
const CharType xmlscm_LN_3_74[] = {0x66, 0x61, 0x63, 0x65, 0x74, 0x73}; /* facets */
const CharType xmlscm_LN_3_75[] = {0x66, 0x69, 0x65, 0x6c, 0x64}; /* field */
const CharType xmlscm_LN_3_76[] = {0x66, 0x6f, 0x72, 0x6d, 0x43, 0x68, 0x6f, 0x69, 0x63, 0x65}; /* formChoice */
const CharType xmlscm_LN_3_77[] = {0x66, 0x72, 0x61, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x44, 0x69, 0x67, 0x69, 0x74, 0x73}; /* fractionDigits */
const CharType xmlscm_LN_3_78[] = {0x66, 0x75, 0x6c, 0x6c, 0x44, 0x65, 0x72, 0x69, 0x76, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x53, 0x65, 0x74}; /* fullDerivationSet */
const CharType xmlscm_LN_3_79[] = {0x67, 0x72, 0x6f, 0x75, 0x70}; /* group */
const CharType xmlscm_LN_3_80[] = {0x67, 0x72, 0x6f, 0x75, 0x70, 0x52, 0x65, 0x66}; /* groupRef */
const CharType xmlscm_LN_3_81[] = {0x69, 0x64, 0x65, 0x6e, 0x74, 0x69, 0x74, 0x79, 0x43, 0x6f, 0x6e, 0x73, 0x74, 0x72, 0x61, 0x69, 0x6e, 0x74}; /* identityConstraint */
const CharType xmlscm_LN_3_82[] = {0x69, 0x6d, 0x70, 0x6f, 0x72, 0x74}; /* import */
const CharType xmlscm_LN_3_83[] = {0x69, 0x6e, 0x63, 0x6c, 0x75, 0x64, 0x65}; /* include */
const CharType xmlscm_LN_3_84[] = {0x6b, 0x65, 0x79}; /* key */
const CharType xmlscm_LN_3_85[] = {0x6b, 0x65, 0x79, 0x62, 0x61, 0x73, 0x65}; /* keybase */
const CharType xmlscm_LN_3_86[] = {0x6b, 0x65, 0x79, 0x72, 0x65, 0x66}; /* keyref */
const CharType xmlscm_LN_3_87[] = {0x6c, 0x65, 0x6e, 0x67, 0x74, 0x68}; /* length */
const CharType xmlscm_LN_3_88[] = {0x6c, 0x69, 0x73, 0x74}; /* list */
const CharType xmlscm_LN_3_89[] = {0x6c, 0x6f, 0x63, 0x61, 0x6c, 0x43, 0x6f, 0x6d, 0x70, 0x6c, 0x65, 0x78, 0x54, 0x79, 0x70, 0x65}; /* localComplexType */
const CharType xmlscm_LN_3_90[] = {0x6c, 0x6f, 0x63, 0x61, 0x6c, 0x45, 0x6c, 0x65, 0x6d, 0x65, 0x6e, 0x74}; /* localElement */
const CharType xmlscm_LN_3_91[] = {0x6c, 0x6f, 0x63, 0x61, 0x6c, 0x53, 0x69, 0x6d, 0x70, 0x6c, 0x65, 0x54, 0x79, 0x70, 0x65}; /* localSimpleType */
const CharType xmlscm_LN_3_92[] = {0x6d, 0x61, 0x78, 0x45, 0x78, 0x63, 0x6c, 0x75, 0x73, 0x69, 0x76, 0x65}; /* maxExclusive */
const CharType xmlscm_LN_3_93[] = {0x6d, 0x61, 0x78, 0x49, 0x6e, 0x63, 0x6c, 0x75, 0x73, 0x69, 0x76, 0x65}; /* maxInclusive */
const CharType xmlscm_LN_3_94[] = {0x6d, 0x61, 0x78, 0x4c, 0x65, 0x6e, 0x67, 0x74, 0x68}; /* maxLength */
const CharType xmlscm_LN_3_95[] = {0x6d, 0x69, 0x6e, 0x45, 0x78, 0x63, 0x6c, 0x75, 0x73, 0x69, 0x76, 0x65}; /* minExclusive */
const CharType xmlscm_LN_3_96[] = {0x6d, 0x69, 0x6e, 0x49, 0x6e, 0x63, 0x6c, 0x75, 0x73, 0x69, 0x76, 0x65}; /* minInclusive */
const CharType xmlscm_LN_3_97[] = {0x6d, 0x69, 0x6e, 0x4c, 0x65, 0x6e, 0x67, 0x74, 0x68}; /* minLength */
const CharType xmlscm_LN_3_98[] = {0x6e, 0x61, 0x6d, 0x65, 0x64, 0x41, 0x74, 0x74, 0x72, 0x69, 0x62, 0x75, 0x74, 0x65, 0x47, 0x72, 0x6f, 0x75, 0x70}; /* namedAttributeGroup */
const CharType xmlscm_LN_3_99[] = {0x6e, 0x61, 0x6d, 0x65, 0x64, 0x47, 0x72, 0x6f, 0x75, 0x70}; /* namedGroup */
const CharType xmlscm_LN_3_100[] = {0x6e, 0x61, 0x6d, 0x65, 0x73, 0x70, 0x61, 0x63, 0x65, 0x4c, 0x69, 0x73, 0x74}; /* namespaceList */
const CharType xmlscm_LN_3_101[] = {0x6e, 0x61, 0x72, 0x72, 0x6f, 0x77, 0x4d, 0x61, 0x78, 0x4d, 0x69, 0x6e}; /* narrowMaxMin */
const CharType xmlscm_LN_3_102[] = {0x6e, 0x65, 0x73, 0x74, 0x65, 0x64, 0x50, 0x61, 0x72, 0x74, 0x69, 0x63, 0x6c, 0x65}; /* nestedParticle */
const CharType xmlscm_LN_3_103[] = {0x6e, 0x6f, 0x46, 0x69, 0x78, 0x65, 0x64, 0x46, 0x61, 0x63, 0x65, 0x74}; /* noFixedFacet */
const CharType xmlscm_LN_3_104[] = {0x6e, 0x6f, 0x74, 0x61, 0x74, 0x69, 0x6f, 0x6e}; /* notation */
const CharType xmlscm_LN_3_105[] = {0x6e, 0x75, 0x6d, 0x46, 0x61, 0x63, 0x65, 0x74}; /* numFacet */
const CharType xmlscm_LN_3_106[] = {0x6f, 0x63, 0x63, 0x75, 0x72, 0x73}; /* occurs */
const CharType xmlscm_LN_3_107[] = {0x6f, 0x70, 0x65, 0x6e, 0x41, 0x74, 0x74, 0x72, 0x73}; /* openAttrs */
const CharType xmlscm_LN_3_108[] = {0x70, 0x61, 0x72, 0x74, 0x69, 0x63, 0x6c, 0x65}; /* particle */
const CharType xmlscm_LN_3_109[] = {0x70, 0x61, 0x74, 0x74, 0x65, 0x72, 0x6e}; /* pattern */
const CharType xmlscm_LN_3_110[] = {0x70, 0x75, 0x62, 0x6c, 0x69, 0x63}; /* public */
const CharType xmlscm_LN_3_111[] = {0x72, 0x65, 0x61, 0x6c, 0x47, 0x72, 0x6f, 0x75, 0x70}; /* realGroup */
const CharType xmlscm_LN_3_112[] = {0x72, 0x65, 0x64, 0x65, 0x66, 0x69, 0x6e, 0x61, 0x62, 0x6c, 0x65}; /* redefinable */
const CharType xmlscm_LN_3_113[] = {0x72, 0x65, 0x64, 0x65, 0x66, 0x69, 0x6e, 0x65}; /* redefine */
const CharType xmlscm_LN_3_114[] = {0x72, 0x65, 0x64, 0x75, 0x63, 0x65, 0x64, 0x44, 0x65, 0x72, 0x69, 0x76, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x43, 0x6f, 0x6e, 0x74, 0x72, 0x6f, 0x6c}; /* reducedDerivationControl */
const CharType xmlscm_LN_3_115[] = {0x72, 0x65, 0x73, 0x74, 0x72, 0x69, 0x63, 0x74, 0x69, 0x6f, 0x6e}; /* restriction */
const CharType xmlscm_LN_3_116[] = {0x72, 0x65, 0x73, 0x74, 0x72, 0x69, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x54, 0x79, 0x70, 0x65}; /* restrictionType */
const CharType xmlscm_LN_3_117[] = {0x73, 0x63, 0x68, 0x65, 0x6d, 0x61}; /* schema */
const CharType xmlscm_LN_3_118[] = {0x73, 0x63, 0x68, 0x65, 0x6d, 0x61, 0x54, 0x6f, 0x70}; /* schemaTop */
const CharType xmlscm_LN_3_119[] = {0x73, 0x65, 0x6c, 0x65, 0x63, 0x74, 0x6f, 0x72}; /* selector */
const CharType xmlscm_LN_3_120[] = {0x73, 0x65, 0x71, 0x75, 0x65, 0x6e, 0x63, 0x65}; /* sequence */
const CharType xmlscm_LN_3_121[] = {0x73, 0x69, 0x6d, 0x70, 0x6c, 0x65, 0x43, 0x6f, 0x6e, 0x74, 0x65, 0x6e, 0x74}; /* simpleContent */
const CharType xmlscm_LN_3_122[] = {0x73, 0x69, 0x6d, 0x70, 0x6c, 0x65, 0x44, 0x65, 0x72, 0x69, 0x76, 0x61, 0x74, 0x69, 0x6f, 0x6e}; /* simpleDerivation */
const CharType xmlscm_LN_3_123[] = {0x73, 0x69, 0x6d, 0x70, 0x6c, 0x65, 0x44, 0x65, 0x72, 0x69, 0x76, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x53, 0x65, 0x74}; /* simpleDerivationSet */
const CharType xmlscm_LN_3_124[] = {0x73, 0x69, 0x6d, 0x70, 0x6c, 0x65, 0x45, 0x78, 0x70, 0x6c, 0x69, 0x63, 0x69, 0x74, 0x47, 0x72, 0x6f, 0x75, 0x70}; /* simpleExplicitGroup */
const CharType xmlscm_LN_3_125[] = {0x73, 0x69, 0x6d, 0x70, 0x6c, 0x65, 0x45, 0x78, 0x74, 0x65, 0x6e, 0x73, 0x69, 0x6f, 0x6e, 0x54, 0x79, 0x70, 0x65}; /* simpleExtensionType */
const CharType xmlscm_LN_3_126[] = {0x73, 0x69, 0x6d, 0x70, 0x6c, 0x65, 0x52, 0x65, 0x73, 0x74, 0x72, 0x69, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x4d, 0x6f, 0x64, 0x65, 0x6c}; /* simpleRestrictionModel */
const CharType xmlscm_LN_3_127[] = {0x73, 0x69, 0x6d, 0x70, 0x6c, 0x65, 0x52, 0x65, 0x73, 0x74, 0x72, 0x69, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x54, 0x79, 0x70, 0x65}; /* simpleRestrictionType */
const CharType xmlscm_LN_3_128[] = {0x73, 0x69, 0x6d, 0x70, 0x6c, 0x65, 0x54, 0x79, 0x70, 0x65}; /* simpleType */
const CharType xmlscm_LN_3_129[] = {0x74, 0x6f, 0x70, 0x4c, 0x65, 0x76, 0x65, 0x6c, 0x41, 0x74, 0x74, 0x72, 0x69, 0x62, 0x75, 0x74, 0x65}; /* topLevelAttribute */
const CharType xmlscm_LN_3_130[] = {0x74, 0x6f, 0x70, 0x4c, 0x65, 0x76, 0x65, 0x6c, 0x43, 0x6f, 0x6d, 0x70, 0x6c, 0x65, 0x78, 0x54, 0x79, 0x70, 0x65}; /* topLevelComplexType */
const CharType xmlscm_LN_3_131[] = {0x74, 0x6f, 0x70, 0x4c, 0x65, 0x76, 0x65, 0x6c, 0x45, 0x6c, 0x65, 0x6d, 0x65, 0x6e, 0x74}; /* topLevelElement */
const CharType xmlscm_LN_3_132[] = {0x74, 0x6f, 0x70, 0x4c, 0x65, 0x76, 0x65, 0x6c, 0x53, 0x69, 0x6d, 0x70, 0x6c, 0x65, 0x54, 0x79, 0x70, 0x65}; /* topLevelSimpleType */
const CharType xmlscm_LN_3_133[] = {0x74, 0x6f, 0x74, 0x61, 0x6c, 0x44, 0x69, 0x67, 0x69, 0x74, 0x73}; /* totalDigits */
const CharType xmlscm_LN_3_134[] = {0x74, 0x79, 0x70, 0x65, 0x44, 0x65, 0x66, 0x50, 0x61, 0x72, 0x74, 0x69, 0x63, 0x6c, 0x65}; /* typeDefParticle */
const CharType xmlscm_LN_3_135[] = {0x74, 0x79, 0x70, 0x65, 0x44, 0x65, 0x72, 0x69, 0x76, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x43, 0x6f, 0x6e, 0x74, 0x72, 0x6f, 0x6c}; /* typeDerivationControl */
const CharType xmlscm_LN_3_136[] = {0x75, 0x6e, 0x69, 0x6f, 0x6e}; /* union */
const CharType xmlscm_LN_3_137[] = {0x75, 0x6e, 0x69, 0x71, 0x75, 0x65}; /* unique */
const CharType xmlscm_LN_3_138[] = {0x77, 0x68, 0x69, 0x74, 0x65, 0x53, 0x70, 0x61, 0x63, 0x65}; /* whiteSpace */
const CharType xmlscm_LN_3_139[] = {0x77, 0x69, 0x6c, 0x64, 0x63, 0x61, 0x72, 0x64}; /* wildcard */

/** END_STRINGS_DEFINITONS */

static const Production xmlscm_prod_0_0[1] =
{
    {
        838860801, 0,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_0_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_0[2] =
{
    {(Production*) xmlscm_prod_0_0, 1, 0},
    {(Production*) xmlscm_prod_0_1, 1, 1}
};

static const Production xmlscm_prod_1_0[1] =
{
    {
        838860801, 1,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_1_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_1[2] =
{
    {(Production*) xmlscm_prod_1_0, 1, 0},
    {(Production*) xmlscm_prod_1_1, 1, 1}
};

static const Production xmlscm_prod_2_0[1] =
{
    {
        838860801, 2,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_2_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_2[2] =
{
    {(Production*) xmlscm_prod_2_0, 1, 0},
    {(Production*) xmlscm_prod_2_1, 1, 1}
};

static const Production xmlscm_prod_3_0[1] =
{
    {
        838860801, 3,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_3_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_3[2] =
{
    {(Production*) xmlscm_prod_3_0, 1, 0},
    {(Production*) xmlscm_prod_3_1, 1, 1}
};

static const Production xmlscm_prod_4_0[1] =
{
    {
        838860801, 4,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_4_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_4[2] =
{
    {(Production*) xmlscm_prod_4_0, 1, 0},
    {(Production*) xmlscm_prod_4_1, 1, 1}
};

static const Production xmlscm_prod_5_0[1] =
{
    {
        838860801, 5,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_5_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_5[2] =
{
    {(Production*) xmlscm_prod_5_0, 1, 0},
    {(Production*) xmlscm_prod_5_1, 1, 1}
};

static const Production xmlscm_prod_6_0[1] =
{
    {
        838860801, 6,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_6_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_6[2] =
{
    {(Production*) xmlscm_prod_6_0, 1, 0},
    {(Production*) xmlscm_prod_6_1, 1, 1}
};

static const Production xmlscm_prod_7_0[1] =
{
    {
        838860801, 7,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_7_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_7[2] =
{
    {(Production*) xmlscm_prod_7_0, 1, 0},
    {(Production*) xmlscm_prod_7_1, 1, 1}
};

static const Production xmlscm_prod_8_0[1] =
{
    {
        838860801, 8,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_8_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_8[2] =
{
    {(Production*) xmlscm_prod_8_0, 1, 0},
    {(Production*) xmlscm_prod_8_1, 1, 1}
};

static const Production xmlscm_prod_9_0[1] =
{
    {
        838860801, 9,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_9_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_9[2] =
{
    {(Production*) xmlscm_prod_9_0, 1, 0},
    {(Production*) xmlscm_prod_9_1, 1, 1}
};

static const Production xmlscm_prod_10_0[1] =
{
    {
        838860801, 10,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_10_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_10[2] =
{
    {(Production*) xmlscm_prod_10_0, 1, 0},
    {(Production*) xmlscm_prod_10_1, 1, 1}
};

static const Production xmlscm_prod_11_0[1] =
{
    {
        838860801, 11,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_11_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_11[2] =
{
    {(Production*) xmlscm_prod_11_0, 1, 0},
    {(Production*) xmlscm_prod_11_1, 1, 1}
};

static const Production xmlscm_prod_12_0[4] =
{
    {
        838860801, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        536870913, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_12_1[3] =
{
    {
        838860801, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        536870913, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_12[2] =
{
    {(Production*) xmlscm_prod_12_0, 4, 3},
    {(Production*) xmlscm_prod_12_1, 3, 1}
};

static const Production xmlscm_prod_13_0[1] =
{
    {
        838860801, 13,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_13_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_13[2] =
{
    {(Production*) xmlscm_prod_13_0, 1, 0},
    {(Production*) xmlscm_prod_13_1, 1, 1}
};

static const Production xmlscm_prod_14_0[1] =
{
    {
        838860801, 14,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_14_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_14[2] =
{
    {(Production*) xmlscm_prod_14_0, 1, 0},
    {(Production*) xmlscm_prod_14_1, 1, 1}
};

static const Production xmlscm_prod_15_0[1] =
{
    {
        838860801, 15,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_15_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_15[2] =
{
    {(Production*) xmlscm_prod_15_0, 1, 0},
    {(Production*) xmlscm_prod_15_1, 1, 1}
};

static const Production xmlscm_prod_16_0[1] =
{
    {
        838860801, 16,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_16_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_16[2] =
{
    {(Production*) xmlscm_prod_16_0, 1, 0},
    {(Production*) xmlscm_prod_16_1, 1, 1}
};

static const Production xmlscm_prod_17_0[1] =
{
    {
        838860801, 17,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_17_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_17[2] =
{
    {(Production*) xmlscm_prod_17_0, 1, 0},
    {(Production*) xmlscm_prod_17_1, 1, 1}
};

static const Production xmlscm_prod_18_0[1] =
{
    {
        838860801, 18,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_18_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_18[2] =
{
    {(Production*) xmlscm_prod_18_0, 1, 0},
    {(Production*) xmlscm_prod_18_1, 1, 1}
};

static const Production xmlscm_prod_19_0[1] =
{
    {
        838860801, 19,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_19_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_19[2] =
{
    {(Production*) xmlscm_prod_19_0, 1, 0},
    {(Production*) xmlscm_prod_19_1, 1, 1}
};

static const Production xmlscm_prod_20_0[1] =
{
    {
        838860801, 20,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_20_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_20[2] =
{
    {(Production*) xmlscm_prod_20_0, 1, 0},
    {(Production*) xmlscm_prod_20_1, 1, 1}
};

static const Production xmlscm_prod_21_0[1] =
{
    {
        838860801, 21,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_21_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_21[2] =
{
    {(Production*) xmlscm_prod_21_0, 1, 0},
    {(Production*) xmlscm_prod_21_1, 1, 1}
};

static const Production xmlscm_prod_22_0[1] =
{
    {
        838860801, 22,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_22_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_22[2] =
{
    {(Production*) xmlscm_prod_22_0, 1, 0},
    {(Production*) xmlscm_prod_22_1, 1, 1}
};

static const Production xmlscm_prod_23_0[1] =
{
    {
        838860801, 23,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_23_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_23[2] =
{
    {(Production*) xmlscm_prod_23_0, 1, 0},
    {(Production*) xmlscm_prod_23_1, 1, 1}
};

static const Production xmlscm_prod_24_0[1] =
{
    {
        838860801, 24,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_24_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_24[2] =
{
    {(Production*) xmlscm_prod_24_0, 1, 0},
    {(Production*) xmlscm_prod_24_1, 1, 1}
};

static const Production xmlscm_prod_25_0[1] =
{
    {
        838860801, 25,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_25_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_25[2] =
{
    {(Production*) xmlscm_prod_25_0, 1, 0},
    {(Production*) xmlscm_prod_25_1, 1, 1}
};

static const Production xmlscm_prod_26_0[1] =
{
    {
        838860801, 26,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_26_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_26[2] =
{
    {(Production*) xmlscm_prod_26_0, 1, 0},
    {(Production*) xmlscm_prod_26_1, 1, 1}
};

static const Production xmlscm_prod_27_0[1] =
{
    {
        838860801, 27,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_27_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_27[2] =
{
    {(Production*) xmlscm_prod_27_0, 1, 0},
    {(Production*) xmlscm_prod_27_1, 1, 1}
};

static const Production xmlscm_prod_28_0[1] =
{
    {
        838860801, 28,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_28_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_28[2] =
{
    {(Production*) xmlscm_prod_28_0, 1, 0},
    {(Production*) xmlscm_prod_28_1, 1, 1}
};

static const Production xmlscm_prod_29_0[1] =
{
    {
        838860801, 29,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_29_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_29[2] =
{
    {(Production*) xmlscm_prod_29_0, 1, 0},
    {(Production*) xmlscm_prod_29_1, 1, 1}
};

static const Production xmlscm_prod_30_0[1] =
{
    {
        838860801, 30,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_30_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_30[2] =
{
    {(Production*) xmlscm_prod_30_0, 1, 0},
    {(Production*) xmlscm_prod_30_1, 1, 1}
};

static const Production xmlscm_prod_31_0[1] =
{
    {
        838860801, 31,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_31_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_31[2] =
{
    {(Production*) xmlscm_prod_31_0, 1, 0},
    {(Production*) xmlscm_prod_31_1, 1, 1}
};

static const Production xmlscm_prod_32_0[1] =
{
    {
        838860801, 32,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_32_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_32[2] =
{
    {(Production*) xmlscm_prod_32_0, 1, 0},
    {(Production*) xmlscm_prod_32_1, 1, 1}
};

static const Production xmlscm_prod_33_0[1] =
{
    {
        838860801, 33,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_33_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_33[2] =
{
    {(Production*) xmlscm_prod_33_0, 1, 0},
    {(Production*) xmlscm_prod_33_1, 1, 1}
};

static const Production xmlscm_prod_34_0[1] =
{
    {
        838860801, 34,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_34_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_34[2] =
{
    {(Production*) xmlscm_prod_34_0, 1, 0},
    {(Production*) xmlscm_prod_34_1, 1, 1}
};

static const Production xmlscm_prod_35_0[1] =
{
    {
        838860801, 35,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_35_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_35[2] =
{
    {(Production*) xmlscm_prod_35_0, 1, 0},
    {(Production*) xmlscm_prod_35_1, 1, 1}
};

static const Production xmlscm_prod_36_0[1] =
{
    {
        838860801, 36,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_36_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_36[2] =
{
    {(Production*) xmlscm_prod_36_0, 1, 0},
    {(Production*) xmlscm_prod_36_1, 1, 1}
};

static const Production xmlscm_prod_37_0[1] =
{
    {
        838860801, 37,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_37_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_37[2] =
{
    {(Production*) xmlscm_prod_37_0, 1, 0},
    {(Production*) xmlscm_prod_37_1, 1, 1}
};

static const Production xmlscm_prod_38_0[1] =
{
    {
        838860801, 38,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_38_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_38[2] =
{
    {(Production*) xmlscm_prod_38_0, 1, 0},
    {(Production*) xmlscm_prod_38_1, 1, 1}
};

static const Production xmlscm_prod_39_0[1] =
{
    {
        838860801, 39,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_39_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_39[2] =
{
    {(Production*) xmlscm_prod_39_0, 1, 0},
    {(Production*) xmlscm_prod_39_1, 1, 1}
};

static const Production xmlscm_prod_40_0[1] =
{
    {
        838860801, 40,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_40_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_40[2] =
{
    {(Production*) xmlscm_prod_40_0, 1, 0},
    {(Production*) xmlscm_prod_40_1, 1, 1}
};

static const Production xmlscm_prod_41_0[1] =
{
    {
        838860801, 41,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_41_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_41[2] =
{
    {(Production*) xmlscm_prod_41_0, 1, 0},
    {(Production*) xmlscm_prod_41_1, 1, 1}
};

static const Production xmlscm_prod_42_0[1] =
{
    {
        838860801, 42,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_42_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_42[2] =
{
    {(Production*) xmlscm_prod_42_0, 1, 0},
    {(Production*) xmlscm_prod_42_1, 1, 1}
};

static const Production xmlscm_prod_43_0[1] =
{
    {
        838860801, 43,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_43_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_43[2] =
{
    {(Production*) xmlscm_prod_43_0, 1, 0},
    {(Production*) xmlscm_prod_43_1, 1, 1}
};

static const Production xmlscm_prod_44_0[1] =
{
    {
        838860801, 44,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_44_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_44[2] =
{
    {(Production*) xmlscm_prod_44_0, 1, 0},
    {(Production*) xmlscm_prod_44_1, 1, 1}
};

static const Production xmlscm_prod_45_0[1] =
{
    {
        838860801, 45,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_45_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_45[2] =
{
    {(Production*) xmlscm_prod_45_0, 1, 0},
    {(Production*) xmlscm_prod_45_1, 1, 1}
};

static const Production xmlscm_prod_46_0[2] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_46[1] =
{
    {(Production*) xmlscm_prod_46_0, 2, 3}
};

static const Production xmlscm_prod_47_0[5] =
{
    {
        838860802, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        536870914, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544321, 13,
        {0, 25}}
};

static const Production xmlscm_prod_47_1[4] =
{
    {
        838860802, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        536870914, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_47_2[3] =
{
    {
        838860802, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        536870914, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_47[3] =
{
    {(Production*) xmlscm_prod_47_0, 5, 5},
    {(Production*) xmlscm_prod_47_1, 4, 3},
    {(Production*) xmlscm_prod_47_2, 3, 1}
};

static const Production xmlscm_prod_48_0[6] =
{
    {
        838860803, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        536870915, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544322, 13,
        {0, 25}},
    {
        335544321, 39,
        {1, 2}}
};

static const Production xmlscm_prod_48_1[5] =
{
    {
        838860803, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        536870915, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544322, 13,
        {0, 25}}
};

static const Production xmlscm_prod_48_2[4] =
{
    {
        838860803, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        536870915, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_48_3[3] =
{
    {
        838860803, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        536870915, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_48[4] =
{
    {(Production*) xmlscm_prod_48_0, 6, 7},
    {(Production*) xmlscm_prod_48_1, 5, 5},
    {(Production*) xmlscm_prod_48_2, 4, 3},
    {(Production*) xmlscm_prod_48_3, 3, 1}
};

static const Production xmlscm_prod_49_0[5] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316483, 48,
        {3, 67}},
    {
        503316482, 47,
        {3, 53}},
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544321, 2,
        {0, 11}}
};

static const Production xmlscm_prod_49_1[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316483, 48,
        {3, 67}},
    {
        503316482, 47,
        {3, 53}},
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_49_2[3] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316483, 48,
        {3, 67}},
    {
        503316482, 47,
        {3, 53}}
};

static const Production xmlscm_prod_49_3[3] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316483, 48,
        {3, 67}},
    {
        503316482, 47,
        {3, 53}}
};

static const GrammarRule xmlscm_rule_49[4] =
{
    {(Production*) xmlscm_prod_49_0, 5, 5},
    {(Production*) xmlscm_prod_49_1, 4, 3},
    {(Production*) xmlscm_prod_49_2, 3, 1},
    {(Production*) xmlscm_prod_49_3, 3, 1}
};

static const Production xmlscm_prod_50_0[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316482, 49,
        {3, 50}},
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544321, 2,
        {0, 11}}
};

static const Production xmlscm_prod_50_1[3] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316482, 49,
        {3, 50}},
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_50_2[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_50[3] =
{
    {(Production*) xmlscm_prod_50_0, 4, 5},
    {(Production*) xmlscm_prod_50_1, 3, 3},
    {(Production*) xmlscm_prod_50_2, 1, 1}
};

static const Production xmlscm_prod_51_0[1] =
{
    {
        838860801, 46,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_51_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_51[2] =
{
    {(Production*) xmlscm_prod_51_0, 1, 0},
    {(Production*) xmlscm_prod_51_1, 1, 1}
};

static const Production xmlscm_prod_52_0[1] =
{
    {
        838860801, 47,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_52_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_52[2] =
{
    {(Production*) xmlscm_prod_52_0, 1, 0},
    {(Production*) xmlscm_prod_52_1, 1, 1}
};

static const Production xmlscm_prod_53_0[1] =
{
    {
        838860801, 48,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_53_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_53[2] =
{
    {(Production*) xmlscm_prod_53_0, 1, 0},
    {(Production*) xmlscm_prod_53_1, 1, 1}
};

static const Production xmlscm_prod_54_0[1] =
{
    {
        838860801, 39,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_54_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_54[2] =
{
    {(Production*) xmlscm_prod_54_0, 1, 0},
    {(Production*) xmlscm_prod_54_1, 1, 1}
};

static const Production xmlscm_prod_55_0[1] =
{
    {
        838860801, 49,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_55_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_55[2] =
{
    {(Production*) xmlscm_prod_55_0, 1, 0},
    {(Production*) xmlscm_prod_55_1, 1, 1}
};

static const Production xmlscm_prod_56_0[1] =
{
    {
        838860801, 39,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_56_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_56[2] =
{
    {(Production*) xmlscm_prod_56_0, 1, 0},
    {(Production*) xmlscm_prod_56_1, 1, 1}
};

static const Production xmlscm_prod_57_0[3] =
{
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544322, 13,
        {0, 24}},
    {
        335544321, 2,
        {0, 11}}
};

static const Production xmlscm_prod_57_1[2] =
{
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544322, 13,
        {0, 24}}
};

static const Production xmlscm_prod_57_2[3] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316483, 49,
        {3, 50}},
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_57_3[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_57[4] =
{
    {(Production*) xmlscm_prod_57_0, 3, 6},
    {(Production*) xmlscm_prod_57_1, 2, 4},
    {(Production*) xmlscm_prod_57_2, 3, 3},
    {(Production*) xmlscm_prod_57_3, 1, 1}
};

static const Production xmlscm_prod_58_0[6] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316484, 49,
        {3, 50}},
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544323, 13,
        {0, 24}},
    {
        335544322, 13,
        {0, 18}},
    {
        335544321, 2,
        {0, 11}}
};

static const Production xmlscm_prod_58_1[5] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316484, 49,
        {3, 50}},
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544323, 13,
        {0, 24}},
    {
        335544322, 13,
        {0, 18}}
};

static const Production xmlscm_prod_58_2[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316484, 49,
        {3, 50}},
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544323, 13,
        {0, 24}}
};

static const Production xmlscm_prod_58_3[3] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316484, 49,
        {3, 50}},
    {
        369098755, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_58_4[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_58[5] =
{
    {(Production*) xmlscm_prod_58_0, 6, 9},
    {(Production*) xmlscm_prod_58_1, 5, 7},
    {(Production*) xmlscm_prod_58_2, 4, 5},
    {(Production*) xmlscm_prod_58_3, 3, 3},
    {(Production*) xmlscm_prod_58_4, 1, 1}
};

static const Production xmlscm_prod_59_0[18] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 68,
        {3, 109}},
    {
        503316495, 67,
        {3, 138}},
    {
        503316494, 66,
        {3, 69}},
    {
        503316493, 65,
        {3, 94}},
    {
        503316492, 65,
        {3, 97}},
    {
        503316491, 65,
        {3, 87}},
    {
        503316490, 65,
        {3, 77}},
    {
        503316489, 64,
        {3, 133}},
    {
        503316488, 63,
        {3, 93}},
    {
        503316487, 63,
        {3, 92}},
    {
        503316486, 63,
        {3, 96}},
    {
        503316485, 63,
        {3, 95}},
    {
        503316484, 60,
        {3, 128}},
    {
        503316483, 49,
        {3, 50}},
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544322, 2,
        {0, 11}},
    {
        335544321, 10,
        {0, 2}}
};

static const Production xmlscm_prod_59_1[17] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 68,
        {3, 109}},
    {
        503316495, 67,
        {3, 138}},
    {
        503316494, 66,
        {3, 69}},
    {
        503316493, 65,
        {3, 94}},
    {
        503316492, 65,
        {3, 97}},
    {
        503316491, 65,
        {3, 87}},
    {
        503316490, 65,
        {3, 77}},
    {
        503316489, 64,
        {3, 133}},
    {
        503316488, 63,
        {3, 93}},
    {
        503316487, 63,
        {3, 92}},
    {
        503316486, 63,
        {3, 96}},
    {
        503316485, 63,
        {3, 95}},
    {
        503316484, 60,
        {3, 128}},
    {
        503316483, 49,
        {3, 50}},
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544322, 2,
        {0, 11}}
};

static const Production xmlscm_prod_59_2[16] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 68,
        {3, 109}},
    {
        503316495, 67,
        {3, 138}},
    {
        503316494, 66,
        {3, 69}},
    {
        503316493, 65,
        {3, 94}},
    {
        503316492, 65,
        {3, 97}},
    {
        503316491, 65,
        {3, 87}},
    {
        503316490, 65,
        {3, 77}},
    {
        503316489, 64,
        {3, 133}},
    {
        503316488, 63,
        {3, 93}},
    {
        503316487, 63,
        {3, 92}},
    {
        503316486, 63,
        {3, 96}},
    {
        503316485, 63,
        {3, 95}},
    {
        503316484, 60,
        {3, 128}},
    {
        503316483, 49,
        {3, 50}},
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_59_3[14] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 68,
        {3, 109}},
    {
        503316495, 67,
        {3, 138}},
    {
        503316494, 66,
        {3, 69}},
    {
        503316493, 65,
        {3, 94}},
    {
        503316492, 65,
        {3, 97}},
    {
        503316491, 65,
        {3, 87}},
    {
        503316490, 65,
        {3, 77}},
    {
        503316489, 64,
        {3, 133}},
    {
        503316488, 63,
        {3, 93}},
    {
        503316487, 63,
        {3, 92}},
    {
        503316486, 63,
        {3, 96}},
    {
        503316485, 63,
        {3, 95}},
    {
        503316484, 60,
        {3, 128}}
};

static const Production xmlscm_prod_59_4[13] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 68,
        {3, 109}},
    {
        503316495, 67,
        {3, 138}},
    {
        503316494, 66,
        {3, 69}},
    {
        503316493, 65,
        {3, 94}},
    {
        503316492, 65,
        {3, 97}},
    {
        503316491, 65,
        {3, 87}},
    {
        503316490, 65,
        {3, 77}},
    {
        503316489, 64,
        {3, 133}},
    {
        503316488, 63,
        {3, 93}},
    {
        503316487, 63,
        {3, 92}},
    {
        503316486, 63,
        {3, 96}},
    {
        503316485, 63,
        {3, 95}}
};

static const Production xmlscm_prod_59_5[13] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 68,
        {3, 109}},
    {
        503316495, 67,
        {3, 138}},
    {
        503316494, 66,
        {3, 69}},
    {
        503316493, 65,
        {3, 94}},
    {
        503316492, 65,
        {3, 97}},
    {
        503316491, 65,
        {3, 87}},
    {
        503316490, 65,
        {3, 77}},
    {
        503316489, 64,
        {3, 133}},
    {
        503316488, 63,
        {3, 93}},
    {
        503316487, 63,
        {3, 92}},
    {
        503316486, 63,
        {3, 96}},
    {
        503316485, 63,
        {3, 95}}
};

static const Production xmlscm_prod_59_6[13] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 68,
        {3, 109}},
    {
        503316495, 67,
        {3, 138}},
    {
        503316494, 66,
        {3, 69}},
    {
        503316493, 65,
        {3, 94}},
    {
        503316492, 65,
        {3, 97}},
    {
        503316491, 65,
        {3, 87}},
    {
        503316490, 65,
        {3, 77}},
    {
        503316489, 64,
        {3, 133}},
    {
        503316488, 63,
        {3, 93}},
    {
        503316487, 63,
        {3, 92}},
    {
        503316486, 63,
        {3, 96}},
    {
        503316485, 63,
        {3, 95}}
};

static const Production xmlscm_prod_59_7[13] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 68,
        {3, 109}},
    {
        503316495, 67,
        {3, 138}},
    {
        503316494, 66,
        {3, 69}},
    {
        503316493, 65,
        {3, 94}},
    {
        503316492, 65,
        {3, 97}},
    {
        503316491, 65,
        {3, 87}},
    {
        503316490, 65,
        {3, 77}},
    {
        503316489, 64,
        {3, 133}},
    {
        503316488, 63,
        {3, 93}},
    {
        503316487, 63,
        {3, 92}},
    {
        503316486, 63,
        {3, 96}},
    {
        503316485, 63,
        {3, 95}}
};

static const Production xmlscm_prod_59_8[13] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 68,
        {3, 109}},
    {
        503316495, 67,
        {3, 138}},
    {
        503316494, 66,
        {3, 69}},
    {
        503316493, 65,
        {3, 94}},
    {
        503316492, 65,
        {3, 97}},
    {
        503316491, 65,
        {3, 87}},
    {
        503316490, 65,
        {3, 77}},
    {
        503316489, 64,
        {3, 133}},
    {
        503316488, 63,
        {3, 93}},
    {
        503316487, 63,
        {3, 92}},
    {
        503316486, 63,
        {3, 96}},
    {
        503316485, 63,
        {3, 95}}
};

static const Production xmlscm_prod_59_9[13] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 68,
        {3, 109}},
    {
        503316495, 67,
        {3, 138}},
    {
        503316494, 66,
        {3, 69}},
    {
        503316493, 65,
        {3, 94}},
    {
        503316492, 65,
        {3, 97}},
    {
        503316491, 65,
        {3, 87}},
    {
        503316490, 65,
        {3, 77}},
    {
        503316489, 64,
        {3, 133}},
    {
        503316488, 63,
        {3, 93}},
    {
        503316487, 63,
        {3, 92}},
    {
        503316486, 63,
        {3, 96}},
    {
        503316485, 63,
        {3, 95}}
};

static const Production xmlscm_prod_59_10[13] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 68,
        {3, 109}},
    {
        503316495, 67,
        {3, 138}},
    {
        503316494, 66,
        {3, 69}},
    {
        503316493, 65,
        {3, 94}},
    {
        503316492, 65,
        {3, 97}},
    {
        503316491, 65,
        {3, 87}},
    {
        503316490, 65,
        {3, 77}},
    {
        503316489, 64,
        {3, 133}},
    {
        503316488, 63,
        {3, 93}},
    {
        503316487, 63,
        {3, 92}},
    {
        503316486, 63,
        {3, 96}},
    {
        503316485, 63,
        {3, 95}}
};

static const Production xmlscm_prod_59_11[13] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 68,
        {3, 109}},
    {
        503316495, 67,
        {3, 138}},
    {
        503316494, 66,
        {3, 69}},
    {
        503316493, 65,
        {3, 94}},
    {
        503316492, 65,
        {3, 97}},
    {
        503316491, 65,
        {3, 87}},
    {
        503316490, 65,
        {3, 77}},
    {
        503316489, 64,
        {3, 133}},
    {
        503316488, 63,
        {3, 93}},
    {
        503316487, 63,
        {3, 92}},
    {
        503316486, 63,
        {3, 96}},
    {
        503316485, 63,
        {3, 95}}
};

static const Production xmlscm_prod_59_12[13] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 68,
        {3, 109}},
    {
        503316495, 67,
        {3, 138}},
    {
        503316494, 66,
        {3, 69}},
    {
        503316493, 65,
        {3, 94}},
    {
        503316492, 65,
        {3, 97}},
    {
        503316491, 65,
        {3, 87}},
    {
        503316490, 65,
        {3, 77}},
    {
        503316489, 64,
        {3, 133}},
    {
        503316488, 63,
        {3, 93}},
    {
        503316487, 63,
        {3, 92}},
    {
        503316486, 63,
        {3, 96}},
    {
        503316485, 63,
        {3, 95}}
};

static const Production xmlscm_prod_59_13[13] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 68,
        {3, 109}},
    {
        503316495, 67,
        {3, 138}},
    {
        503316494, 66,
        {3, 69}},
    {
        503316493, 65,
        {3, 94}},
    {
        503316492, 65,
        {3, 97}},
    {
        503316491, 65,
        {3, 87}},
    {
        503316490, 65,
        {3, 77}},
    {
        503316489, 64,
        {3, 133}},
    {
        503316488, 63,
        {3, 93}},
    {
        503316487, 63,
        {3, 92}},
    {
        503316486, 63,
        {3, 96}},
    {
        503316485, 63,
        {3, 95}}
};

static const Production xmlscm_prod_59_14[13] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 68,
        {3, 109}},
    {
        503316495, 67,
        {3, 138}},
    {
        503316494, 66,
        {3, 69}},
    {
        503316493, 65,
        {3, 94}},
    {
        503316492, 65,
        {3, 97}},
    {
        503316491, 65,
        {3, 87}},
    {
        503316490, 65,
        {3, 77}},
    {
        503316489, 64,
        {3, 133}},
    {
        503316488, 63,
        {3, 93}},
    {
        503316487, 63,
        {3, 92}},
    {
        503316486, 63,
        {3, 96}},
    {
        503316485, 63,
        {3, 95}}
};

static const Production xmlscm_prod_59_15[13] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 68,
        {3, 109}},
    {
        503316495, 67,
        {3, 138}},
    {
        503316494, 66,
        {3, 69}},
    {
        503316493, 65,
        {3, 94}},
    {
        503316492, 65,
        {3, 97}},
    {
        503316491, 65,
        {3, 87}},
    {
        503316490, 65,
        {3, 77}},
    {
        503316489, 64,
        {3, 133}},
    {
        503316488, 63,
        {3, 93}},
    {
        503316487, 63,
        {3, 92}},
    {
        503316486, 63,
        {3, 96}},
    {
        503316485, 63,
        {3, 95}}
};

static const Production xmlscm_prod_59_16[13] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 68,
        {3, 109}},
    {
        503316495, 67,
        {3, 138}},
    {
        503316494, 66,
        {3, 69}},
    {
        503316493, 65,
        {3, 94}},
    {
        503316492, 65,
        {3, 97}},
    {
        503316491, 65,
        {3, 87}},
    {
        503316490, 65,
        {3, 77}},
    {
        503316489, 64,
        {3, 133}},
    {
        503316488, 63,
        {3, 93}},
    {
        503316487, 63,
        {3, 92}},
    {
        503316486, 63,
        {3, 96}},
    {
        503316485, 63,
        {3, 95}}
};

static const GrammarRule xmlscm_rule_59[17] =
{
    {(Production*) xmlscm_prod_59_0, 18, 7},
    {(Production*) xmlscm_prod_59_1, 17, 5},
    {(Production*) xmlscm_prod_59_2, 16, 3},
    {(Production*) xmlscm_prod_59_3, 14, 1},
    {(Production*) xmlscm_prod_59_4, 13, 1},
    {(Production*) xmlscm_prod_59_5, 13, 1},
    {(Production*) xmlscm_prod_59_6, 13, 1},
    {(Production*) xmlscm_prod_59_7, 13, 1},
    {(Production*) xmlscm_prod_59_8, 13, 1},
    {(Production*) xmlscm_prod_59_9, 13, 1},
    {(Production*) xmlscm_prod_59_10, 13, 1},
    {(Production*) xmlscm_prod_59_11, 13, 1},
    {(Production*) xmlscm_prod_59_12, 13, 1},
    {(Production*) xmlscm_prod_59_13, 13, 1},
    {(Production*) xmlscm_prod_59_14, 13, 1},
    {(Production*) xmlscm_prod_59_15, 13, 1},
    {(Production*) xmlscm_prod_59_16, 13, 1}
};

static const Production xmlscm_prod_60_0[6] =
{
    {
        503316485, 62,
        {3, 136}},
    {
        503316484, 61,
        {3, 88}},
    {
        503316483, 59,
        {3, 115}},
    {
        503316482, 49,
        {3, 50}},
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544321, 2,
        {0, 11}}
};

static const Production xmlscm_prod_60_1[5] =
{
    {
        503316485, 62,
        {3, 136}},
    {
        503316484, 61,
        {3, 88}},
    {
        503316483, 59,
        {3, 115}},
    {
        503316482, 49,
        {3, 50}},
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_60_2[3] =
{
    {
        503316485, 62,
        {3, 136}},
    {
        503316484, 61,
        {3, 88}},
    {
        503316483, 59,
        {3, 115}}
};

static const Production xmlscm_prod_60_3[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_60_4[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_60_5[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_60[6] =
{
    {(Production*) xmlscm_prod_60_0, 6, 4},
    {(Production*) xmlscm_prod_60_1, 5, 2},
    {(Production*) xmlscm_prod_60_2, 3, 0},
    {(Production*) xmlscm_prod_60_3, 1, 1},
    {(Production*) xmlscm_prod_60_4, 1, 1},
    {(Production*) xmlscm_prod_60_5, 1, 1}
};

static const Production xmlscm_prod_61_0[6] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316484, 60,
        {3, 128}},
    {
        503316483, 49,
        {3, 50}},
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544322, 10,
        {0, 12}},
    {
        335544321, 2,
        {0, 11}}
};

static const Production xmlscm_prod_61_1[5] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316484, 60,
        {3, 128}},
    {
        503316483, 49,
        {3, 50}},
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544322, 10,
        {0, 12}}
};

static const Production xmlscm_prod_61_2[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316484, 60,
        {3, 128}},
    {
        503316483, 49,
        {3, 50}},
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_61_3[2] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316484, 60,
        {3, 128}}
};

static const Production xmlscm_prod_61_4[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_61[5] =
{
    {(Production*) xmlscm_prod_61_0, 6, 7},
    {(Production*) xmlscm_prod_61_1, 5, 5},
    {(Production*) xmlscm_prod_61_2, 4, 3},
    {(Production*) xmlscm_prod_61_3, 2, 1},
    {(Production*) xmlscm_prod_61_4, 1, 1}
};

static const Production xmlscm_prod_62_0[6] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316484, 60,
        {3, 128}},
    {
        503316483, 49,
        {3, 50}},
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544322, 50,
        {0, 14}},
    {
        335544321, 2,
        {0, 11}}
};

static const Production xmlscm_prod_62_1[5] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316484, 60,
        {3, 128}},
    {
        503316483, 49,
        {3, 50}},
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544322, 50,
        {0, 14}}
};

static const Production xmlscm_prod_62_2[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316484, 60,
        {3, 128}},
    {
        503316483, 49,
        {3, 50}},
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_62_3[2] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316484, 60,
        {3, 128}}
};

static const Production xmlscm_prod_62_4[2] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316484, 60,
        {3, 128}}
};

static const GrammarRule xmlscm_rule_62[5] =
{
    {(Production*) xmlscm_prod_62_0, 6, 7},
    {(Production*) xmlscm_prod_62_1, 5, 5},
    {(Production*) xmlscm_prod_62_2, 4, 3},
    {(Production*) xmlscm_prod_62_3, 2, 1},
    {(Production*) xmlscm_prod_62_4, 2, 1}
};

static const Production xmlscm_prod_63_0[4] =
{
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544323, 11,
        {0, 31}},
    {
        335544322, 2,
        {0, 11}},
    {
        335544321, 15,
        {0, 9}}
};

static const Production xmlscm_prod_63_1[3] =
{
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544323, 11,
        {0, 31}},
    {
        335544322, 2,
        {0, 11}}
};

static const Production xmlscm_prod_63_2[2] =
{
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544323, 11,
        {0, 31}}
};

static const Production xmlscm_prod_63_3[3] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316484, 49,
        {3, 50}},
    {
        369098755, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_63_4[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_63[5] =
{
    {(Production*) xmlscm_prod_63_0, 4, 8},
    {(Production*) xmlscm_prod_63_1, 3, 6},
    {(Production*) xmlscm_prod_63_2, 2, 4},
    {(Production*) xmlscm_prod_63_3, 3, 3},
    {(Production*) xmlscm_prod_63_4, 1, 1}
};

static const Production xmlscm_prod_64_0[4] =
{
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544323, 37,
        {0, 31}},
    {
        335544322, 2,
        {0, 11}},
    {
        335544321, 15,
        {0, 9}}
};

static const Production xmlscm_prod_64_1[3] =
{
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544323, 37,
        {0, 31}},
    {
        335544322, 2,
        {0, 11}}
};

static const Production xmlscm_prod_64_2[2] =
{
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544323, 37,
        {0, 31}}
};

static const Production xmlscm_prod_64_3[3] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316484, 49,
        {3, 50}},
    {
        369098755, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_64_4[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_64[5] =
{
    {(Production*) xmlscm_prod_64_0, 4, 8},
    {(Production*) xmlscm_prod_64_1, 3, 6},
    {(Production*) xmlscm_prod_64_2, 2, 4},
    {(Production*) xmlscm_prod_64_3, 3, 3},
    {(Production*) xmlscm_prod_64_4, 1, 1}
};

static const Production xmlscm_prod_65_0[4] =
{
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544323, 34,
        {0, 31}},
    {
        335544322, 2,
        {0, 11}},
    {
        335544321, 15,
        {0, 9}}
};

static const Production xmlscm_prod_65_1[3] =
{
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544323, 34,
        {0, 31}},
    {
        335544322, 2,
        {0, 11}}
};

static const Production xmlscm_prod_65_2[2] =
{
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544323, 34,
        {0, 31}}
};

static const Production xmlscm_prod_65_3[3] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316484, 49,
        {3, 50}},
    {
        369098755, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_65_4[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_65[5] =
{
    {(Production*) xmlscm_prod_65_0, 4, 8},
    {(Production*) xmlscm_prod_65_1, 3, 6},
    {(Production*) xmlscm_prod_65_2, 2, 4},
    {(Production*) xmlscm_prod_65_3, 3, 3},
    {(Production*) xmlscm_prod_65_4, 1, 1}
};

static const Production xmlscm_prod_66_0[3] =
{
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544322, 11,
        {0, 31}},
    {
        335544321, 2,
        {0, 11}}
};

static const Production xmlscm_prod_66_1[2] =
{
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544322, 11,
        {0, 31}}
};

static const Production xmlscm_prod_66_2[3] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316483, 49,
        {3, 50}},
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_66_3[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_66[4] =
{
    {(Production*) xmlscm_prod_66_0, 3, 6},
    {(Production*) xmlscm_prod_66_1, 2, 4},
    {(Production*) xmlscm_prod_66_2, 3, 3},
    {(Production*) xmlscm_prod_66_3, 1, 1}
};

static const Production xmlscm_prod_67_0[4] =
{
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544323, 51,
        {0, 31}},
    {
        335544322, 2,
        {0, 11}},
    {
        335544321, 15,
        {0, 9}}
};

static const Production xmlscm_prod_67_1[3] =
{
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544323, 51,
        {0, 31}},
    {
        335544322, 2,
        {0, 11}}
};

static const Production xmlscm_prod_67_2[2] =
{
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544323, 51,
        {0, 31}}
};

static const Production xmlscm_prod_67_3[3] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316484, 49,
        {3, 50}},
    {
        369098755, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_67_4[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_67[5] =
{
    {(Production*) xmlscm_prod_67_0, 4, 8},
    {(Production*) xmlscm_prod_67_1, 3, 6},
    {(Production*) xmlscm_prod_67_2, 2, 4},
    {(Production*) xmlscm_prod_67_3, 3, 3},
    {(Production*) xmlscm_prod_67_4, 1, 1}
};

static const Production xmlscm_prod_68_0[3] =
{
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544322, 39,
        {0, 31}},
    {
        335544321, 2,
        {0, 11}}
};

static const Production xmlscm_prod_68_1[2] =
{
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544322, 39,
        {0, 31}}
};

static const Production xmlscm_prod_68_2[3] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316483, 49,
        {3, 50}},
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_68_3[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_68[4] =
{
    {(Production*) xmlscm_prod_68_0, 3, 6},
    {(Production*) xmlscm_prod_68_1, 2, 4},
    {(Production*) xmlscm_prod_68_2, 3, 3},
    {(Production*) xmlscm_prod_68_3, 1, 1}
};

static const Production xmlscm_prod_69_0[1] =
{
    {
        838860801, 39,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_69_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_69[2] =
{
    {(Production*) xmlscm_prod_69_0, 1, 0},
    {(Production*) xmlscm_prod_69_1, 1, 1}
};

static const Production xmlscm_prod_70_0[4] =
{
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544323, 5,
        {0, 17}},
    {
        335544322, 2,
        {0, 11}},
    {
        335544321, 39,
        {0, 7}}
};

static const Production xmlscm_prod_70_1[3] =
{
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544323, 5,
        {0, 17}},
    {
        335544322, 2,
        {0, 11}}
};

static const Production xmlscm_prod_70_2[2] =
{
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544323, 5,
        {0, 17}}
};

static const Production xmlscm_prod_70_3[5] =
{
    {
        503316487, 62,
        {3, 136}},
    {
        503316486, 61,
        {3, 88}},
    {
        503316485, 59,
        {3, 115}},
    {
        503316484, 49,
        {3, 50}},
    {
        369098755, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_70_4[3] =
{
    {
        503316487, 62,
        {3, 136}},
    {
        503316486, 61,
        {3, 88}},
    {
        503316485, 59,
        {3, 115}}
};

static const Production xmlscm_prod_70_5[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_70_6[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_70_7[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_70[8] =
{
    {(Production*) xmlscm_prod_70_0, 4, 8},
    {(Production*) xmlscm_prod_70_1, 3, 6},
    {(Production*) xmlscm_prod_70_2, 2, 4},
    {(Production*) xmlscm_prod_70_3, 5, 2},
    {(Production*) xmlscm_prod_70_4, 3, 0},
    {(Production*) xmlscm_prod_70_5, 1, 1},
    {(Production*) xmlscm_prod_70_6, 1, 1},
    {(Production*) xmlscm_prod_70_7, 1, 1}
};

static const Production xmlscm_prod_71_0[12] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316490, 60,
        {3, 128}},
    {
        503316489, 49,
        {3, 50}},
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544328, 52,
        {0, 30}},
    {
        335544327, 10,
        {0, 29}},
    {
        335544326, 10,
        {0, 22}},
    {
        335544325, 5,
        {0, 17}},
    {
        335544324, 2,
        {0, 11}},
    {
        335544323, 46,
        {0, 10}},
    {
        335544322, 39,
        {0, 9}},
    {
        335544321, 39,
        {0, 5}}
};

static const Production xmlscm_prod_71_1[11] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316490, 60,
        {3, 128}},
    {
        503316489, 49,
        {3, 50}},
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544328, 52,
        {0, 30}},
    {
        335544327, 10,
        {0, 29}},
    {
        335544326, 10,
        {0, 22}},
    {
        335544325, 5,
        {0, 17}},
    {
        335544324, 2,
        {0, 11}},
    {
        335544323, 46,
        {0, 10}},
    {
        335544322, 39,
        {0, 9}}
};

static const Production xmlscm_prod_71_2[10] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316490, 60,
        {3, 128}},
    {
        503316489, 49,
        {3, 50}},
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544328, 52,
        {0, 30}},
    {
        335544327, 10,
        {0, 29}},
    {
        335544326, 10,
        {0, 22}},
    {
        335544325, 5,
        {0, 17}},
    {
        335544324, 2,
        {0, 11}},
    {
        335544323, 46,
        {0, 10}}
};

static const Production xmlscm_prod_71_3[9] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316490, 60,
        {3, 128}},
    {
        503316489, 49,
        {3, 50}},
    {
        369098755, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544328, 52,
        {0, 30}},
    {
        335544327, 10,
        {0, 29}},
    {
        335544326, 10,
        {0, 22}},
    {
        335544325, 5,
        {0, 17}},
    {
        335544324, 2,
        {0, 11}}
};

static const Production xmlscm_prod_71_4[8] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316490, 60,
        {3, 128}},
    {
        503316489, 49,
        {3, 50}},
    {
        369098756, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544328, 52,
        {0, 30}},
    {
        335544327, 10,
        {0, 29}},
    {
        335544326, 10,
        {0, 22}},
    {
        335544325, 5,
        {0, 17}}
};

static const Production xmlscm_prod_71_5[7] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316490, 60,
        {3, 128}},
    {
        503316489, 49,
        {3, 50}},
    {
        369098757, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544328, 52,
        {0, 30}},
    {
        335544327, 10,
        {0, 29}},
    {
        335544326, 10,
        {0, 22}}
};

static const Production xmlscm_prod_71_6[6] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316490, 60,
        {3, 128}},
    {
        503316489, 49,
        {3, 50}},
    {
        369098758, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544328, 52,
        {0, 30}},
    {
        335544327, 10,
        {0, 29}}
};

static const Production xmlscm_prod_71_7[5] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316490, 60,
        {3, 128}},
    {
        503316489, 49,
        {3, 50}},
    {
        369098759, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544328, 52,
        {0, 30}}
};

static const Production xmlscm_prod_71_8[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316490, 60,
        {3, 128}},
    {
        503316489, 49,
        {3, 50}},
    {
        369098760, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_71_9[2] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316490, 60,
        {3, 128}}
};

static const Production xmlscm_prod_71_10[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_71[11] =
{
    {(Production*) xmlscm_prod_71_0, 12, 19},
    {(Production*) xmlscm_prod_71_1, 11, 17},
    {(Production*) xmlscm_prod_71_2, 10, 15},
    {(Production*) xmlscm_prod_71_3, 9, 13},
    {(Production*) xmlscm_prod_71_4, 8, 11},
    {(Production*) xmlscm_prod_71_5, 7, 9},
    {(Production*) xmlscm_prod_71_6, 6, 7},
    {(Production*) xmlscm_prod_71_7, 5, 5},
    {(Production*) xmlscm_prod_71_8, 4, 3},
    {(Production*) xmlscm_prod_71_9, 2, 1},
    {(Production*) xmlscm_prod_71_10, 1, 1}
};

static const Production xmlscm_prod_72_0[3] =
{
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544322, 10,
        {0, 22}},
    {
        335544321, 2,
        {0, 11}}
};

static const Production xmlscm_prod_72_1[2] =
{
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544322, 10,
        {0, 22}}
};

static const Production xmlscm_prod_72_2[3] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316483, 49,
        {3, 50}},
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_72_3[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_72[4] =
{
    {(Production*) xmlscm_prod_72_0, 3, 6},
    {(Production*) xmlscm_prod_72_1, 2, 4},
    {(Production*) xmlscm_prod_72_2, 3, 3},
    {(Production*) xmlscm_prod_72_3, 1, 1}
};

static const Production xmlscm_prod_73_0[1] =
{
    {
        838860801, 39,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_73_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_73[2] =
{
    {(Production*) xmlscm_prod_73_0, 1, 0},
    {(Production*) xmlscm_prod_73_1, 1, 1}
};

static const Production xmlscm_prod_74_0[6] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316484, 49,
        {3, 50}},
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544323, 53,
        {0, 20}},
    {
        335544322, 39,
        {0, 18}},
    {
        335544321, 2,
        {0, 11}}
};

static const Production xmlscm_prod_74_1[5] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316484, 49,
        {3, 50}},
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544323, 53,
        {0, 20}},
    {
        335544322, 39,
        {0, 18}}
};

static const Production xmlscm_prod_74_2[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316484, 49,
        {3, 50}},
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544323, 53,
        {0, 20}}
};

static const Production xmlscm_prod_74_3[3] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316484, 49,
        {3, 50}},
    {
        369098755, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_74_4[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_74[5] =
{
    {(Production*) xmlscm_prod_74_0, 6, 9},
    {(Production*) xmlscm_prod_74_1, 5, 7},
    {(Production*) xmlscm_prod_74_2, 4, 5},
    {(Production*) xmlscm_prod_74_3, 3, 3},
    {(Production*) xmlscm_prod_74_4, 1, 1}
};

static const Production xmlscm_prod_75_0[2] =
{
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544321, 10,
        {0, 2}}
};

static const Production xmlscm_prod_75_1[20] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316499, 74,
        {3, 52}},
    {
        503316498, 72,
        {3, 56}},
    {
        503316497, 71,
        {3, 55}},
    {
        503316496, 68,
        {3, 109}},
    {
        503316495, 67,
        {3, 138}},
    {
        503316494, 66,
        {3, 69}},
    {
        503316493, 65,
        {3, 94}},
    {
        503316492, 65,
        {3, 97}},
    {
        503316491, 65,
        {3, 87}},
    {
        503316490, 65,
        {3, 77}},
    {
        503316489, 64,
        {3, 133}},
    {
        503316488, 63,
        {3, 93}},
    {
        503316487, 63,
        {3, 92}},
    {
        503316486, 63,
        {3, 96}},
    {
        503316485, 63,
        {3, 95}},
    {
        503316484, 60,
        {3, 128}},
    {
        503316483, 49,
        {3, 50}},
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544322, 2,
        {0, 11}}
};

static const Production xmlscm_prod_75_2[19] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316499, 74,
        {3, 52}},
    {
        503316498, 72,
        {3, 56}},
    {
        503316497, 71,
        {3, 55}},
    {
        503316496, 68,
        {3, 109}},
    {
        503316495, 67,
        {3, 138}},
    {
        503316494, 66,
        {3, 69}},
    {
        503316493, 65,
        {3, 94}},
    {
        503316492, 65,
        {3, 97}},
    {
        503316491, 65,
        {3, 87}},
    {
        503316490, 65,
        {3, 77}},
    {
        503316489, 64,
        {3, 133}},
    {
        503316488, 63,
        {3, 93}},
    {
        503316487, 63,
        {3, 92}},
    {
        503316486, 63,
        {3, 96}},
    {
        503316485, 63,
        {3, 95}},
    {
        503316484, 60,
        {3, 128}},
    {
        503316483, 49,
        {3, 50}},
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_75_3[17] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316499, 74,
        {3, 52}},
    {
        503316498, 72,
        {3, 56}},
    {
        503316497, 71,
        {3, 55}},
    {
        503316496, 68,
        {3, 109}},
    {
        503316495, 67,
        {3, 138}},
    {
        503316494, 66,
        {3, 69}},
    {
        503316493, 65,
        {3, 94}},
    {
        503316492, 65,
        {3, 97}},
    {
        503316491, 65,
        {3, 87}},
    {
        503316490, 65,
        {3, 77}},
    {
        503316489, 64,
        {3, 133}},
    {
        503316488, 63,
        {3, 93}},
    {
        503316487, 63,
        {3, 92}},
    {
        503316486, 63,
        {3, 96}},
    {
        503316485, 63,
        {3, 95}},
    {
        503316484, 60,
        {3, 128}}
};

static const Production xmlscm_prod_75_4[16] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316499, 74,
        {3, 52}},
    {
        503316498, 72,
        {3, 56}},
    {
        503316497, 71,
        {3, 55}},
    {
        503316496, 68,
        {3, 109}},
    {
        503316495, 67,
        {3, 138}},
    {
        503316494, 66,
        {3, 69}},
    {
        503316493, 65,
        {3, 94}},
    {
        503316492, 65,
        {3, 97}},
    {
        503316491, 65,
        {3, 87}},
    {
        503316490, 65,
        {3, 77}},
    {
        503316489, 64,
        {3, 133}},
    {
        503316488, 63,
        {3, 93}},
    {
        503316487, 63,
        {3, 92}},
    {
        503316486, 63,
        {3, 96}},
    {
        503316485, 63,
        {3, 95}}
};

static const Production xmlscm_prod_75_5[16] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316499, 74,
        {3, 52}},
    {
        503316498, 72,
        {3, 56}},
    {
        503316497, 71,
        {3, 55}},
    {
        503316496, 68,
        {3, 109}},
    {
        503316495, 67,
        {3, 138}},
    {
        503316494, 66,
        {3, 69}},
    {
        503316493, 65,
        {3, 94}},
    {
        503316492, 65,
        {3, 97}},
    {
        503316491, 65,
        {3, 87}},
    {
        503316490, 65,
        {3, 77}},
    {
        503316489, 64,
        {3, 133}},
    {
        503316488, 63,
        {3, 93}},
    {
        503316487, 63,
        {3, 92}},
    {
        503316486, 63,
        {3, 96}},
    {
        503316485, 63,
        {3, 95}}
};

static const Production xmlscm_prod_75_6[16] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316499, 74,
        {3, 52}},
    {
        503316498, 72,
        {3, 56}},
    {
        503316497, 71,
        {3, 55}},
    {
        503316496, 68,
        {3, 109}},
    {
        503316495, 67,
        {3, 138}},
    {
        503316494, 66,
        {3, 69}},
    {
        503316493, 65,
        {3, 94}},
    {
        503316492, 65,
        {3, 97}},
    {
        503316491, 65,
        {3, 87}},
    {
        503316490, 65,
        {3, 77}},
    {
        503316489, 64,
        {3, 133}},
    {
        503316488, 63,
        {3, 93}},
    {
        503316487, 63,
        {3, 92}},
    {
        503316486, 63,
        {3, 96}},
    {
        503316485, 63,
        {3, 95}}
};

static const Production xmlscm_prod_75_7[16] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316499, 74,
        {3, 52}},
    {
        503316498, 72,
        {3, 56}},
    {
        503316497, 71,
        {3, 55}},
    {
        503316496, 68,
        {3, 109}},
    {
        503316495, 67,
        {3, 138}},
    {
        503316494, 66,
        {3, 69}},
    {
        503316493, 65,
        {3, 94}},
    {
        503316492, 65,
        {3, 97}},
    {
        503316491, 65,
        {3, 87}},
    {
        503316490, 65,
        {3, 77}},
    {
        503316489, 64,
        {3, 133}},
    {
        503316488, 63,
        {3, 93}},
    {
        503316487, 63,
        {3, 92}},
    {
        503316486, 63,
        {3, 96}},
    {
        503316485, 63,
        {3, 95}}
};

static const Production xmlscm_prod_75_8[16] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316499, 74,
        {3, 52}},
    {
        503316498, 72,
        {3, 56}},
    {
        503316497, 71,
        {3, 55}},
    {
        503316496, 68,
        {3, 109}},
    {
        503316495, 67,
        {3, 138}},
    {
        503316494, 66,
        {3, 69}},
    {
        503316493, 65,
        {3, 94}},
    {
        503316492, 65,
        {3, 97}},
    {
        503316491, 65,
        {3, 87}},
    {
        503316490, 65,
        {3, 77}},
    {
        503316489, 64,
        {3, 133}},
    {
        503316488, 63,
        {3, 93}},
    {
        503316487, 63,
        {3, 92}},
    {
        503316486, 63,
        {3, 96}},
    {
        503316485, 63,
        {3, 95}}
};

static const Production xmlscm_prod_75_9[16] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316499, 74,
        {3, 52}},
    {
        503316498, 72,
        {3, 56}},
    {
        503316497, 71,
        {3, 55}},
    {
        503316496, 68,
        {3, 109}},
    {
        503316495, 67,
        {3, 138}},
    {
        503316494, 66,
        {3, 69}},
    {
        503316493, 65,
        {3, 94}},
    {
        503316492, 65,
        {3, 97}},
    {
        503316491, 65,
        {3, 87}},
    {
        503316490, 65,
        {3, 77}},
    {
        503316489, 64,
        {3, 133}},
    {
        503316488, 63,
        {3, 93}},
    {
        503316487, 63,
        {3, 92}},
    {
        503316486, 63,
        {3, 96}},
    {
        503316485, 63,
        {3, 95}}
};

static const Production xmlscm_prod_75_10[16] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316499, 74,
        {3, 52}},
    {
        503316498, 72,
        {3, 56}},
    {
        503316497, 71,
        {3, 55}},
    {
        503316496, 68,
        {3, 109}},
    {
        503316495, 67,
        {3, 138}},
    {
        503316494, 66,
        {3, 69}},
    {
        503316493, 65,
        {3, 94}},
    {
        503316492, 65,
        {3, 97}},
    {
        503316491, 65,
        {3, 87}},
    {
        503316490, 65,
        {3, 77}},
    {
        503316489, 64,
        {3, 133}},
    {
        503316488, 63,
        {3, 93}},
    {
        503316487, 63,
        {3, 92}},
    {
        503316486, 63,
        {3, 96}},
    {
        503316485, 63,
        {3, 95}}
};

static const Production xmlscm_prod_75_11[16] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316499, 74,
        {3, 52}},
    {
        503316498, 72,
        {3, 56}},
    {
        503316497, 71,
        {3, 55}},
    {
        503316496, 68,
        {3, 109}},
    {
        503316495, 67,
        {3, 138}},
    {
        503316494, 66,
        {3, 69}},
    {
        503316493, 65,
        {3, 94}},
    {
        503316492, 65,
        {3, 97}},
    {
        503316491, 65,
        {3, 87}},
    {
        503316490, 65,
        {3, 77}},
    {
        503316489, 64,
        {3, 133}},
    {
        503316488, 63,
        {3, 93}},
    {
        503316487, 63,
        {3, 92}},
    {
        503316486, 63,
        {3, 96}},
    {
        503316485, 63,
        {3, 95}}
};

static const Production xmlscm_prod_75_12[16] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316499, 74,
        {3, 52}},
    {
        503316498, 72,
        {3, 56}},
    {
        503316497, 71,
        {3, 55}},
    {
        503316496, 68,
        {3, 109}},
    {
        503316495, 67,
        {3, 138}},
    {
        503316494, 66,
        {3, 69}},
    {
        503316493, 65,
        {3, 94}},
    {
        503316492, 65,
        {3, 97}},
    {
        503316491, 65,
        {3, 87}},
    {
        503316490, 65,
        {3, 77}},
    {
        503316489, 64,
        {3, 133}},
    {
        503316488, 63,
        {3, 93}},
    {
        503316487, 63,
        {3, 92}},
    {
        503316486, 63,
        {3, 96}},
    {
        503316485, 63,
        {3, 95}}
};

static const Production xmlscm_prod_75_13[16] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316499, 74,
        {3, 52}},
    {
        503316498, 72,
        {3, 56}},
    {
        503316497, 71,
        {3, 55}},
    {
        503316496, 68,
        {3, 109}},
    {
        503316495, 67,
        {3, 138}},
    {
        503316494, 66,
        {3, 69}},
    {
        503316493, 65,
        {3, 94}},
    {
        503316492, 65,
        {3, 97}},
    {
        503316491, 65,
        {3, 87}},
    {
        503316490, 65,
        {3, 77}},
    {
        503316489, 64,
        {3, 133}},
    {
        503316488, 63,
        {3, 93}},
    {
        503316487, 63,
        {3, 92}},
    {
        503316486, 63,
        {3, 96}},
    {
        503316485, 63,
        {3, 95}}
};

static const Production xmlscm_prod_75_14[16] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316499, 74,
        {3, 52}},
    {
        503316498, 72,
        {3, 56}},
    {
        503316497, 71,
        {3, 55}},
    {
        503316496, 68,
        {3, 109}},
    {
        503316495, 67,
        {3, 138}},
    {
        503316494, 66,
        {3, 69}},
    {
        503316493, 65,
        {3, 94}},
    {
        503316492, 65,
        {3, 97}},
    {
        503316491, 65,
        {3, 87}},
    {
        503316490, 65,
        {3, 77}},
    {
        503316489, 64,
        {3, 133}},
    {
        503316488, 63,
        {3, 93}},
    {
        503316487, 63,
        {3, 92}},
    {
        503316486, 63,
        {3, 96}},
    {
        503316485, 63,
        {3, 95}}
};

static const Production xmlscm_prod_75_15[16] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316499, 74,
        {3, 52}},
    {
        503316498, 72,
        {3, 56}},
    {
        503316497, 71,
        {3, 55}},
    {
        503316496, 68,
        {3, 109}},
    {
        503316495, 67,
        {3, 138}},
    {
        503316494, 66,
        {3, 69}},
    {
        503316493, 65,
        {3, 94}},
    {
        503316492, 65,
        {3, 97}},
    {
        503316491, 65,
        {3, 87}},
    {
        503316490, 65,
        {3, 77}},
    {
        503316489, 64,
        {3, 133}},
    {
        503316488, 63,
        {3, 93}},
    {
        503316487, 63,
        {3, 92}},
    {
        503316486, 63,
        {3, 96}},
    {
        503316485, 63,
        {3, 95}}
};

static const Production xmlscm_prod_75_16[16] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316499, 74,
        {3, 52}},
    {
        503316498, 72,
        {3, 56}},
    {
        503316497, 71,
        {3, 55}},
    {
        503316496, 68,
        {3, 109}},
    {
        503316495, 67,
        {3, 138}},
    {
        503316494, 66,
        {3, 69}},
    {
        503316493, 65,
        {3, 94}},
    {
        503316492, 65,
        {3, 97}},
    {
        503316491, 65,
        {3, 87}},
    {
        503316490, 65,
        {3, 77}},
    {
        503316489, 64,
        {3, 133}},
    {
        503316488, 63,
        {3, 93}},
    {
        503316487, 63,
        {3, 92}},
    {
        503316486, 63,
        {3, 96}},
    {
        503316485, 63,
        {3, 95}}
};

static const Production xmlscm_prod_75_17[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316499, 74,
        {3, 52}},
    {
        503316498, 72,
        {3, 56}},
    {
        503316497, 71,
        {3, 55}}
};

static const Production xmlscm_prod_75_18[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316499, 74,
        {3, 52}},
    {
        503316498, 72,
        {3, 56}},
    {
        503316497, 71,
        {3, 55}}
};

static const Production xmlscm_prod_75_19[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_75[20] =
{
    {(Production*) xmlscm_prod_75_0, 2, 4},
    {(Production*) xmlscm_prod_75_1, 20, 5},
    {(Production*) xmlscm_prod_75_2, 19, 3},
    {(Production*) xmlscm_prod_75_3, 17, 1},
    {(Production*) xmlscm_prod_75_4, 16, 1},
    {(Production*) xmlscm_prod_75_5, 16, 1},
    {(Production*) xmlscm_prod_75_6, 16, 1},
    {(Production*) xmlscm_prod_75_7, 16, 1},
    {(Production*) xmlscm_prod_75_8, 16, 1},
    {(Production*) xmlscm_prod_75_9, 16, 1},
    {(Production*) xmlscm_prod_75_10, 16, 1},
    {(Production*) xmlscm_prod_75_11, 16, 1},
    {(Production*) xmlscm_prod_75_12, 16, 1},
    {(Production*) xmlscm_prod_75_13, 16, 1},
    {(Production*) xmlscm_prod_75_14, 16, 1},
    {(Production*) xmlscm_prod_75_15, 16, 1},
    {(Production*) xmlscm_prod_75_16, 16, 1},
    {(Production*) xmlscm_prod_75_17, 4, 1},
    {(Production*) xmlscm_prod_75_18, 4, 1},
    {(Production*) xmlscm_prod_75_19, 1, 1}
};

static const Production xmlscm_prod_76_0[2] =
{
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544321, 10,
        {0, 2}}
};

static const Production xmlscm_prod_76_1[7] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316486, 74,
        {3, 52}},
    {
        503316485, 72,
        {3, 56}},
    {
        503316484, 71,
        {3, 55}},
    {
        503316483, 49,
        {3, 50}},
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544322, 2,
        {0, 11}}
};

static const Production xmlscm_prod_76_2[6] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316486, 74,
        {3, 52}},
    {
        503316485, 72,
        {3, 56}},
    {
        503316484, 71,
        {3, 55}},
    {
        503316483, 49,
        {3, 50}},
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_76_3[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316486, 74,
        {3, 52}},
    {
        503316485, 72,
        {3, 56}},
    {
        503316484, 71,
        {3, 55}}
};

static const Production xmlscm_prod_76_4[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316486, 74,
        {3, 52}},
    {
        503316485, 72,
        {3, 56}},
    {
        503316484, 71,
        {3, 55}}
};

static const Production xmlscm_prod_76_5[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316486, 74,
        {3, 52}},
    {
        503316485, 72,
        {3, 56}},
    {
        503316484, 71,
        {3, 55}}
};

static const Production xmlscm_prod_76_6[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_76[7] =
{
    {(Production*) xmlscm_prod_76_0, 2, 4},
    {(Production*) xmlscm_prod_76_1, 7, 5},
    {(Production*) xmlscm_prod_76_2, 6, 3},
    {(Production*) xmlscm_prod_76_3, 4, 1},
    {(Production*) xmlscm_prod_76_4, 4, 1},
    {(Production*) xmlscm_prod_76_5, 4, 1},
    {(Production*) xmlscm_prod_76_6, 1, 1}
};

static const Production xmlscm_prod_77_0[5] =
{
    {
        503316484, 76,
        {3, 71}},
    {
        503316483, 75,
        {3, 115}},
    {
        503316482, 49,
        {3, 50}},
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544321, 2,
        {0, 11}}
};

static const Production xmlscm_prod_77_1[4] =
{
    {
        503316484, 76,
        {3, 71}},
    {
        503316483, 75,
        {3, 115}},
    {
        503316482, 49,
        {3, 50}},
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_77_2[2] =
{
    {
        503316484, 76,
        {3, 71}},
    {
        503316483, 75,
        {3, 115}}
};

static const Production xmlscm_prod_77_3[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_77_4[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_77[5] =
{
    {(Production*) xmlscm_prod_77_0, 5, 4},
    {(Production*) xmlscm_prod_77_1, 4, 2},
    {(Production*) xmlscm_prod_77_2, 2, 0},
    {(Production*) xmlscm_prod_77_3, 1, 1},
    {(Production*) xmlscm_prod_77_4, 1, 1}
};

static const Production xmlscm_prod_78_0[1] =
{
    {
        838860801, 39,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_78_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_78[2] =
{
    {(Production*) xmlscm_prod_78_0, 1, 0},
    {(Production*) xmlscm_prod_78_1, 1, 1}
};

static const Production xmlscm_prod_79_0[5] =
{
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544324, 10,
        {0, 22}},
    {
        335544323, 34,
        {0, 15}},
    {
        335544322, 39,
        {0, 13}},
    {
        335544321, 2,
        {0, 11}}
};

static const Production xmlscm_prod_79_1[4] =
{
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544324, 10,
        {0, 22}},
    {
        335544323, 34,
        {0, 15}},
    {
        335544322, 39,
        {0, 13}}
};

static const Production xmlscm_prod_79_2[3] =
{
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544324, 10,
        {0, 22}},
    {
        335544323, 34,
        {0, 15}}
};

static const Production xmlscm_prod_79_3[2] =
{
    {
        369098755, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544324, 10,
        {0, 22}}
};

static const Production xmlscm_prod_79_4[3] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316485, 49,
        {3, 50}},
    {
        369098756, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_79_5[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_79[6] =
{
    {(Production*) xmlscm_prod_79_0, 5, 10},
    {(Production*) xmlscm_prod_79_1, 4, 8},
    {(Production*) xmlscm_prod_79_2, 3, 6},
    {(Production*) xmlscm_prod_79_3, 2, 4},
    {(Production*) xmlscm_prod_79_4, 3, 3},
    {(Production*) xmlscm_prod_79_5, 1, 1}
};

static const Production xmlscm_prod_80_0[6] =
{
    {
        503316485, 93,
        {3, 71}},
    {
        503316484, 92,
        {3, 115}},
    {
        503316483, 49,
        {3, 50}},
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544322, 15,
        {0, 16}},
    {
        335544321, 2,
        {0, 11}}
};

static const Production xmlscm_prod_80_1[5] =
{
    {
        503316485, 93,
        {3, 71}},
    {
        503316484, 92,
        {3, 115}},
    {
        503316483, 49,
        {3, 50}},
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544322, 15,
        {0, 16}}
};

static const Production xmlscm_prod_80_2[4] =
{
    {
        503316485, 93,
        {3, 71}},
    {
        503316484, 92,
        {3, 115}},
    {
        503316483, 49,
        {3, 50}},
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_80_3[2] =
{
    {
        503316485, 93,
        {3, 71}},
    {
        503316484, 92,
        {3, 115}}
};

static const Production xmlscm_prod_80_4[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_80_5[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_80[6] =
{
    {(Production*) xmlscm_prod_80_0, 6, 6},
    {(Production*) xmlscm_prod_80_1, 5, 4},
    {(Production*) xmlscm_prod_80_2, 4, 2},
    {(Production*) xmlscm_prod_80_3, 2, 0},
    {(Production*) xmlscm_prod_80_4, 1, 1},
    {(Production*) xmlscm_prod_80_5, 1, 1}
};

static const Production xmlscm_prod_81_0[7] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316485, 91,
        {3, 68}},
    {
        503316484, 49,
        {3, 50}},
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544323, 59,
        {0, 15}},
    {
        335544322, 60,
        {0, 13}},
    {
        335544321, 2,
        {0, 11}}
};

static const Production xmlscm_prod_81_1[6] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316485, 91,
        {3, 68}},
    {
        503316484, 49,
        {3, 50}},
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544323, 59,
        {0, 15}},
    {
        335544322, 60,
        {0, 13}}
};

static const Production xmlscm_prod_81_2[5] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316485, 91,
        {3, 68}},
    {
        503316484, 49,
        {3, 50}},
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544323, 59,
        {0, 15}}
};

static const Production xmlscm_prod_81_3[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316485, 91,
        {3, 68}},
    {
        503316484, 49,
        {3, 50}},
    {
        369098755, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_81_4[2] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316485, 91,
        {3, 68}}
};

static const Production xmlscm_prod_81_5[2] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316485, 91,
        {3, 68}}
};

static const GrammarRule xmlscm_rule_81[6] =
{
    {(Production*) xmlscm_prod_81_0, 7, 9},
    {(Production*) xmlscm_prod_81_1, 6, 7},
    {(Production*) xmlscm_prod_81_2, 5, 5},
    {(Production*) xmlscm_prod_81_3, 4, 3},
    {(Production*) xmlscm_prod_81_4, 2, 1},
    {(Production*) xmlscm_prod_81_5, 2, 1}
};

static const Production xmlscm_prod_82_0[14] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316492, 74,
        {3, 52}},
    {
        503316491, 72,
        {3, 56}},
    {
        503316490, 71,
        {3, 55}},
    {
        503316489, 89,
        {3, 120}},
    {
        503316488, 89,
        {3, 59}},
    {
        503316487, 81,
        {3, 46}},
    {
        503316486, 79,
        {3, 79}},
    {
        503316485, 80,
        {3, 60}},
    {
        503316484, 77,
        {3, 121}},
    {
        503316483, 49,
        {3, 50}},
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544322, 15,
        {0, 16}},
    {
        335544321, 2,
        {0, 11}}
};

static const Production xmlscm_prod_82_1[13] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316492, 74,
        {3, 52}},
    {
        503316491, 72,
        {3, 56}},
    {
        503316490, 71,
        {3, 55}},
    {
        503316489, 89,
        {3, 120}},
    {
        503316488, 89,
        {3, 59}},
    {
        503316487, 81,
        {3, 46}},
    {
        503316486, 79,
        {3, 79}},
    {
        503316485, 80,
        {3, 60}},
    {
        503316484, 77,
        {3, 121}},
    {
        503316483, 49,
        {3, 50}},
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544322, 15,
        {0, 16}}
};

static const Production xmlscm_prod_82_2[12] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316492, 74,
        {3, 52}},
    {
        503316491, 72,
        {3, 56}},
    {
        503316490, 71,
        {3, 55}},
    {
        503316489, 89,
        {3, 120}},
    {
        503316488, 89,
        {3, 59}},
    {
        503316487, 81,
        {3, 46}},
    {
        503316486, 79,
        {3, 79}},
    {
        503316485, 80,
        {3, 60}},
    {
        503316484, 77,
        {3, 121}},
    {
        503316483, 49,
        {3, 50}},
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_82_3[10] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316492, 74,
        {3, 52}},
    {
        503316491, 72,
        {3, 56}},
    {
        503316490, 71,
        {3, 55}},
    {
        503316489, 89,
        {3, 120}},
    {
        503316488, 89,
        {3, 59}},
    {
        503316487, 81,
        {3, 46}},
    {
        503316486, 79,
        {3, 79}},
    {
        503316485, 80,
        {3, 60}},
    {
        503316484, 77,
        {3, 121}}
};

static const Production xmlscm_prod_82_4[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_82_5[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_82_6[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316492, 74,
        {3, 52}},
    {
        503316491, 72,
        {3, 56}},
    {
        503316490, 71,
        {3, 55}}
};

static const Production xmlscm_prod_82_7[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316492, 74,
        {3, 52}},
    {
        503316491, 72,
        {3, 56}},
    {
        503316490, 71,
        {3, 55}}
};

static const Production xmlscm_prod_82_8[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316492, 74,
        {3, 52}},
    {
        503316491, 72,
        {3, 56}},
    {
        503316490, 71,
        {3, 55}}
};

static const Production xmlscm_prod_82_9[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316492, 74,
        {3, 52}},
    {
        503316491, 72,
        {3, 56}},
    {
        503316490, 71,
        {3, 55}}
};

static const Production xmlscm_prod_82_10[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316492, 74,
        {3, 52}},
    {
        503316491, 72,
        {3, 56}},
    {
        503316490, 71,
        {3, 55}}
};

static const Production xmlscm_prod_82_11[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316492, 74,
        {3, 52}},
    {
        503316491, 72,
        {3, 56}},
    {
        503316490, 71,
        {3, 55}}
};

static const Production xmlscm_prod_82_12[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_82[13] =
{
    {(Production*) xmlscm_prod_82_0, 14, 7},
    {(Production*) xmlscm_prod_82_1, 13, 5},
    {(Production*) xmlscm_prod_82_2, 12, 3},
    {(Production*) xmlscm_prod_82_3, 10, 1},
    {(Production*) xmlscm_prod_82_4, 1, 1},
    {(Production*) xmlscm_prod_82_5, 1, 1},
    {(Production*) xmlscm_prod_82_6, 4, 1},
    {(Production*) xmlscm_prod_82_7, 4, 1},
    {(Production*) xmlscm_prod_82_8, 4, 1},
    {(Production*) xmlscm_prod_82_9, 4, 1},
    {(Production*) xmlscm_prod_82_10, 4, 1},
    {(Production*) xmlscm_prod_82_11, 4, 1},
    {(Production*) xmlscm_prod_82_12, 1, 1}
};

static const Production xmlscm_prod_83_0[3] =
{
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544322, 54,
        {0, 33}},
    {
        335544321, 2,
        {0, 11}}
};

static const Production xmlscm_prod_83_1[2] =
{
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544322, 54,
        {0, 33}}
};

static const Production xmlscm_prod_83_2[3] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316483, 49,
        {3, 50}},
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_83_3[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_83[4] =
{
    {(Production*) xmlscm_prod_83_0, 3, 6},
    {(Production*) xmlscm_prod_83_1, 2, 4},
    {(Production*) xmlscm_prod_83_2, 3, 3},
    {(Production*) xmlscm_prod_83_3, 1, 1}
};

static const Production xmlscm_prod_84_0[3] =
{
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544322, 55,
        {0, 33}},
    {
        335544321, 2,
        {0, 11}}
};

static const Production xmlscm_prod_84_1[2] =
{
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544322, 55,
        {0, 33}}
};

static const Production xmlscm_prod_84_2[3] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316483, 49,
        {3, 50}},
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_84_3[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_84[4] =
{
    {(Production*) xmlscm_prod_84_0, 3, 6},
    {(Production*) xmlscm_prod_84_1, 2, 4},
    {(Production*) xmlscm_prod_84_2, 3, 3},
    {(Production*) xmlscm_prod_84_3, 1, 1}
};

static const Production xmlscm_prod_85_0[3] =
{
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544322, 5,
        {0, 17}},
    {
        335544321, 2,
        {0, 11}}
};

static const Production xmlscm_prod_85_1[2] =
{
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544322, 5,
        {0, 17}}
};

static const Production xmlscm_prod_85_2[3] =
{
    {
        503316484, 83,
        {3, 119}},
    {
        503316483, 49,
        {3, 50}},
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_85_3[1] =
{
    {
        503316484, 83,
        {3, 119}}
};

static const Production xmlscm_prod_85_4[1] =
{
    {
        503316485, 84,
        {3, 75}}
};

static const Production xmlscm_prod_85_5[2] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316486, 84,
        {3, 75}}
};

static const Production xmlscm_prod_85_6[2] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316486, 84,
        {3, 75}}
};

static const GrammarRule xmlscm_rule_85[7] =
{
    {(Production*) xmlscm_prod_85_0, 3, 6},
    {(Production*) xmlscm_prod_85_1, 2, 4},
    {(Production*) xmlscm_prod_85_2, 3, 2},
    {(Production*) xmlscm_prod_85_3, 1, 0},
    {(Production*) xmlscm_prod_85_4, 1, 0},
    {(Production*) xmlscm_prod_85_5, 2, 1},
    {(Production*) xmlscm_prod_85_6, 2, 1}
};

static const Production xmlscm_prod_86_0[3] =
{
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544322, 5,
        {0, 17}},
    {
        335544321, 2,
        {0, 11}}
};

static const Production xmlscm_prod_86_1[2] =
{
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544322, 5,
        {0, 17}}
};

static const Production xmlscm_prod_86_2[2] =
{
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544323, 10,
        {0, 23}}
};

static const Production xmlscm_prod_86_3[3] =
{
    {
        503316485, 83,
        {3, 119}},
    {
        503316484, 49,
        {3, 50}},
    {
        369098755, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_86_4[1] =
{
    {
        503316485, 83,
        {3, 119}}
};

static const Production xmlscm_prod_86_5[1] =
{
    {
        503316486, 84,
        {3, 75}}
};

static const Production xmlscm_prod_86_6[2] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316487, 84,
        {3, 75}}
};

static const Production xmlscm_prod_86_7[2] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316487, 84,
        {3, 75}}
};

static const GrammarRule xmlscm_rule_86[8] =
{
    {(Production*) xmlscm_prod_86_0, 3, 6},
    {(Production*) xmlscm_prod_86_1, 2, 4},
    {(Production*) xmlscm_prod_86_2, 2, 4},
    {(Production*) xmlscm_prod_86_3, 3, 2},
    {(Production*) xmlscm_prod_86_4, 1, 0},
    {(Production*) xmlscm_prod_86_5, 1, 0},
    {(Production*) xmlscm_prod_86_6, 2, 1},
    {(Production*) xmlscm_prod_86_7, 2, 1}
};

static const Production xmlscm_prod_87_0[1] =
{
    {
        838860801, 39,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_87_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_87[2] =
{
    {(Production*) xmlscm_prod_87_0, 1, 0},
    {(Production*) xmlscm_prod_87_1, 1, 1}
};

static const Production xmlscm_prod_88_0[19] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316497, 86,
        {3, 86}},
    {
        503316496, 85,
        {3, 84}},
    {
        503316495, 85,
        {3, 137}},
    {
        503316494, 82,
        {3, 62}},
    {
        503316493, 60,
        {3, 128}},
    {
        503316492, 49,
        {3, 50}},
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544331, 10,
        {0, 29}},
    {
        335544330, 10,
        {0, 22}},
    {
        335544329, 15,
        {0, 19}},
    {
        335544328, 5,
        {0, 17}},
    {
        335544327, 34,
        {0, 15}},
    {
        335544326, 39,
        {0, 13}},
    {
        335544325, 2,
        {0, 11}},
    {
        335544324, 46,
        {0, 10}},
    {
        335544323, 39,
        {0, 9}},
    {
        335544322, 39,
        {0, 5}},
    {
        335544321, 39,
        {0, 3}}
};

static const Production xmlscm_prod_88_1[18] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316497, 86,
        {3, 86}},
    {
        503316496, 85,
        {3, 84}},
    {
        503316495, 85,
        {3, 137}},
    {
        503316494, 82,
        {3, 62}},
    {
        503316493, 60,
        {3, 128}},
    {
        503316492, 49,
        {3, 50}},
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544331, 10,
        {0, 29}},
    {
        335544330, 10,
        {0, 22}},
    {
        335544329, 15,
        {0, 19}},
    {
        335544328, 5,
        {0, 17}},
    {
        335544327, 34,
        {0, 15}},
    {
        335544326, 39,
        {0, 13}},
    {
        335544325, 2,
        {0, 11}},
    {
        335544324, 46,
        {0, 10}},
    {
        335544323, 39,
        {0, 9}},
    {
        335544322, 39,
        {0, 5}}
};

static const Production xmlscm_prod_88_2[17] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316497, 86,
        {3, 86}},
    {
        503316496, 85,
        {3, 84}},
    {
        503316495, 85,
        {3, 137}},
    {
        503316494, 82,
        {3, 62}},
    {
        503316493, 60,
        {3, 128}},
    {
        503316492, 49,
        {3, 50}},
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544331, 10,
        {0, 29}},
    {
        335544330, 10,
        {0, 22}},
    {
        335544329, 15,
        {0, 19}},
    {
        335544328, 5,
        {0, 17}},
    {
        335544327, 34,
        {0, 15}},
    {
        335544326, 39,
        {0, 13}},
    {
        335544325, 2,
        {0, 11}},
    {
        335544324, 46,
        {0, 10}},
    {
        335544323, 39,
        {0, 9}}
};

static const Production xmlscm_prod_88_3[16] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316497, 86,
        {3, 86}},
    {
        503316496, 85,
        {3, 84}},
    {
        503316495, 85,
        {3, 137}},
    {
        503316494, 82,
        {3, 62}},
    {
        503316493, 60,
        {3, 128}},
    {
        503316492, 49,
        {3, 50}},
    {
        369098755, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544331, 10,
        {0, 29}},
    {
        335544330, 10,
        {0, 22}},
    {
        335544329, 15,
        {0, 19}},
    {
        335544328, 5,
        {0, 17}},
    {
        335544327, 34,
        {0, 15}},
    {
        335544326, 39,
        {0, 13}},
    {
        335544325, 2,
        {0, 11}},
    {
        335544324, 46,
        {0, 10}}
};

static const Production xmlscm_prod_88_4[15] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316497, 86,
        {3, 86}},
    {
        503316496, 85,
        {3, 84}},
    {
        503316495, 85,
        {3, 137}},
    {
        503316494, 82,
        {3, 62}},
    {
        503316493, 60,
        {3, 128}},
    {
        503316492, 49,
        {3, 50}},
    {
        369098756, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544331, 10,
        {0, 29}},
    {
        335544330, 10,
        {0, 22}},
    {
        335544329, 15,
        {0, 19}},
    {
        335544328, 5,
        {0, 17}},
    {
        335544327, 34,
        {0, 15}},
    {
        335544326, 39,
        {0, 13}},
    {
        335544325, 2,
        {0, 11}}
};

static const Production xmlscm_prod_88_5[14] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316497, 86,
        {3, 86}},
    {
        503316496, 85,
        {3, 84}},
    {
        503316495, 85,
        {3, 137}},
    {
        503316494, 82,
        {3, 62}},
    {
        503316493, 60,
        {3, 128}},
    {
        503316492, 49,
        {3, 50}},
    {
        369098757, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544331, 10,
        {0, 29}},
    {
        335544330, 10,
        {0, 22}},
    {
        335544329, 15,
        {0, 19}},
    {
        335544328, 5,
        {0, 17}},
    {
        335544327, 34,
        {0, 15}},
    {
        335544326, 39,
        {0, 13}}
};

static const Production xmlscm_prod_88_6[13] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316497, 86,
        {3, 86}},
    {
        503316496, 85,
        {3, 84}},
    {
        503316495, 85,
        {3, 137}},
    {
        503316494, 82,
        {3, 62}},
    {
        503316493, 60,
        {3, 128}},
    {
        503316492, 49,
        {3, 50}},
    {
        369098758, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544331, 10,
        {0, 29}},
    {
        335544330, 10,
        {0, 22}},
    {
        335544329, 15,
        {0, 19}},
    {
        335544328, 5,
        {0, 17}},
    {
        335544327, 34,
        {0, 15}}
};

static const Production xmlscm_prod_88_7[12] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316497, 86,
        {3, 86}},
    {
        503316496, 85,
        {3, 84}},
    {
        503316495, 85,
        {3, 137}},
    {
        503316494, 82,
        {3, 62}},
    {
        503316493, 60,
        {3, 128}},
    {
        503316492, 49,
        {3, 50}},
    {
        369098759, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544331, 10,
        {0, 29}},
    {
        335544330, 10,
        {0, 22}},
    {
        335544329, 15,
        {0, 19}},
    {
        335544328, 5,
        {0, 17}}
};

static const Production xmlscm_prod_88_8[11] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316497, 86,
        {3, 86}},
    {
        503316496, 85,
        {3, 84}},
    {
        503316495, 85,
        {3, 137}},
    {
        503316494, 82,
        {3, 62}},
    {
        503316493, 60,
        {3, 128}},
    {
        503316492, 49,
        {3, 50}},
    {
        369098760, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544331, 10,
        {0, 29}},
    {
        335544330, 10,
        {0, 22}},
    {
        335544329, 15,
        {0, 19}}
};

static const Production xmlscm_prod_88_9[10] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316497, 86,
        {3, 86}},
    {
        503316496, 85,
        {3, 84}},
    {
        503316495, 85,
        {3, 137}},
    {
        503316494, 82,
        {3, 62}},
    {
        503316493, 60,
        {3, 128}},
    {
        503316492, 49,
        {3, 50}},
    {
        369098761, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544331, 10,
        {0, 29}},
    {
        335544330, 10,
        {0, 22}}
};

static const Production xmlscm_prod_88_10[9] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316497, 86,
        {3, 86}},
    {
        503316496, 85,
        {3, 84}},
    {
        503316495, 85,
        {3, 137}},
    {
        503316494, 82,
        {3, 62}},
    {
        503316493, 60,
        {3, 128}},
    {
        503316492, 49,
        {3, 50}},
    {
        369098762, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544331, 10,
        {0, 29}}
};

static const Production xmlscm_prod_88_11[8] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316497, 86,
        {3, 86}},
    {
        503316496, 85,
        {3, 84}},
    {
        503316495, 85,
        {3, 137}},
    {
        503316494, 82,
        {3, 62}},
    {
        503316493, 60,
        {3, 128}},
    {
        503316492, 49,
        {3, 50}},
    {
        369098763, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_88_12[6] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316497, 86,
        {3, 86}},
    {
        503316496, 85,
        {3, 84}},
    {
        503316495, 85,
        {3, 137}},
    {
        503316494, 82,
        {3, 62}},
    {
        503316493, 60,
        {3, 128}}
};

static const Production xmlscm_prod_88_13[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316497, 86,
        {3, 86}},
    {
        503316496, 85,
        {3, 84}},
    {
        503316495, 85,
        {3, 137}}
};

static const Production xmlscm_prod_88_14[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316497, 86,
        {3, 86}},
    {
        503316496, 85,
        {3, 84}},
    {
        503316495, 85,
        {3, 137}}
};

static const Production xmlscm_prod_88_15[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316497, 86,
        {3, 86}},
    {
        503316496, 85,
        {3, 84}},
    {
        503316495, 85,
        {3, 137}}
};

static const Production xmlscm_prod_88_16[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316497, 86,
        {3, 86}},
    {
        503316496, 85,
        {3, 84}},
    {
        503316495, 85,
        {3, 137}}
};

static const Production xmlscm_prod_88_17[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316497, 86,
        {3, 86}},
    {
        503316496, 85,
        {3, 84}},
    {
        503316495, 85,
        {3, 137}}
};

static const GrammarRule xmlscm_rule_88[18] =
{
    {(Production*) xmlscm_prod_88_0, 19, 25},
    {(Production*) xmlscm_prod_88_1, 18, 23},
    {(Production*) xmlscm_prod_88_2, 17, 21},
    {(Production*) xmlscm_prod_88_3, 16, 19},
    {(Production*) xmlscm_prod_88_4, 15, 17},
    {(Production*) xmlscm_prod_88_5, 14, 15},
    {(Production*) xmlscm_prod_88_6, 13, 13},
    {(Production*) xmlscm_prod_88_7, 12, 11},
    {(Production*) xmlscm_prod_88_8, 11, 9},
    {(Production*) xmlscm_prod_88_9, 10, 7},
    {(Production*) xmlscm_prod_88_10, 9, 5},
    {(Production*) xmlscm_prod_88_11, 8, 3},
    {(Production*) xmlscm_prod_88_12, 6, 1},
    {(Production*) xmlscm_prod_88_13, 4, 1},
    {(Production*) xmlscm_prod_88_14, 4, 1},
    {(Production*) xmlscm_prod_88_15, 4, 1},
    {(Production*) xmlscm_prod_88_16, 4, 1},
    {(Production*) xmlscm_prod_88_17, 4, 1}
};

static const Production xmlscm_prod_89_0[11] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316489, 90,
        {3, 51}},
    {
        503316488, 89,
        {3, 120}},
    {
        503316487, 89,
        {3, 59}},
    {
        503316486, 79,
        {3, 79}},
    {
        503316485, 88,
        {3, 68}},
    {
        503316484, 49,
        {3, 50}},
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544323, 34,
        {0, 15}},
    {
        335544322, 39,
        {0, 13}},
    {
        335544321, 2,
        {0, 11}}
};

static const Production xmlscm_prod_89_1[10] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316489, 90,
        {3, 51}},
    {
        503316488, 89,
        {3, 120}},
    {
        503316487, 89,
        {3, 59}},
    {
        503316486, 79,
        {3, 79}},
    {
        503316485, 88,
        {3, 68}},
    {
        503316484, 49,
        {3, 50}},
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544323, 34,
        {0, 15}},
    {
        335544322, 39,
        {0, 13}}
};

static const Production xmlscm_prod_89_2[9] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316489, 90,
        {3, 51}},
    {
        503316488, 89,
        {3, 120}},
    {
        503316487, 89,
        {3, 59}},
    {
        503316486, 79,
        {3, 79}},
    {
        503316485, 88,
        {3, 68}},
    {
        503316484, 49,
        {3, 50}},
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544323, 34,
        {0, 15}}
};

static const Production xmlscm_prod_89_3[8] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316489, 90,
        {3, 51}},
    {
        503316488, 89,
        {3, 120}},
    {
        503316487, 89,
        {3, 59}},
    {
        503316486, 79,
        {3, 79}},
    {
        503316485, 88,
        {3, 68}},
    {
        503316484, 49,
        {3, 50}},
    {
        369098755, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_89_4[6] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316489, 90,
        {3, 51}},
    {
        503316488, 89,
        {3, 120}},
    {
        503316487, 89,
        {3, 59}},
    {
        503316486, 79,
        {3, 79}},
    {
        503316485, 88,
        {3, 68}}
};

static const Production xmlscm_prod_89_5[6] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316489, 90,
        {3, 51}},
    {
        503316488, 89,
        {3, 120}},
    {
        503316487, 89,
        {3, 59}},
    {
        503316486, 79,
        {3, 79}},
    {
        503316485, 88,
        {3, 68}}
};

static const Production xmlscm_prod_89_6[6] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316489, 90,
        {3, 51}},
    {
        503316488, 89,
        {3, 120}},
    {
        503316487, 89,
        {3, 59}},
    {
        503316486, 79,
        {3, 79}},
    {
        503316485, 88,
        {3, 68}}
};

static const Production xmlscm_prod_89_7[6] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316489, 90,
        {3, 51}},
    {
        503316488, 89,
        {3, 120}},
    {
        503316487, 89,
        {3, 59}},
    {
        503316486, 79,
        {3, 79}},
    {
        503316485, 88,
        {3, 68}}
};

static const Production xmlscm_prod_89_8[6] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316489, 90,
        {3, 51}},
    {
        503316488, 89,
        {3, 120}},
    {
        503316487, 89,
        {3, 59}},
    {
        503316486, 79,
        {3, 79}},
    {
        503316485, 88,
        {3, 68}}
};

static const Production xmlscm_prod_89_9[6] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316489, 90,
        {3, 51}},
    {
        503316488, 89,
        {3, 120}},
    {
        503316487, 89,
        {3, 59}},
    {
        503316486, 79,
        {3, 79}},
    {
        503316485, 88,
        {3, 68}}
};

static const GrammarRule xmlscm_rule_89[10] =
{
    {(Production*) xmlscm_prod_89_0, 11, 9},
    {(Production*) xmlscm_prod_89_1, 10, 7},
    {(Production*) xmlscm_prod_89_2, 9, 5},
    {(Production*) xmlscm_prod_89_3, 8, 3},
    {(Production*) xmlscm_prod_89_4, 6, 1},
    {(Production*) xmlscm_prod_89_5, 6, 1},
    {(Production*) xmlscm_prod_89_6, 6, 1},
    {(Production*) xmlscm_prod_89_7, 6, 1},
    {(Production*) xmlscm_prod_89_8, 6, 1},
    {(Production*) xmlscm_prod_89_9, 6, 1}
};

static const Production xmlscm_prod_90_0[8] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316486, 49,
        {3, 50}},
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544325, 56,
        {0, 20}},
    {
        335544324, 39,
        {0, 18}},
    {
        335544323, 34,
        {0, 15}},
    {
        335544322, 39,
        {0, 13}},
    {
        335544321, 2,
        {0, 11}}
};

static const Production xmlscm_prod_90_1[7] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316486, 49,
        {3, 50}},
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544325, 56,
        {0, 20}},
    {
        335544324, 39,
        {0, 18}},
    {
        335544323, 34,
        {0, 15}},
    {
        335544322, 39,
        {0, 13}}
};

static const Production xmlscm_prod_90_2[6] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316486, 49,
        {3, 50}},
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544325, 56,
        {0, 20}},
    {
        335544324, 39,
        {0, 18}},
    {
        335544323, 34,
        {0, 15}}
};

static const Production xmlscm_prod_90_3[5] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316486, 49,
        {3, 50}},
    {
        369098755, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544325, 56,
        {0, 20}},
    {
        335544324, 39,
        {0, 18}}
};

static const Production xmlscm_prod_90_4[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316486, 49,
        {3, 50}},
    {
        369098756, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544325, 56,
        {0, 20}}
};

static const Production xmlscm_prod_90_5[3] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316486, 49,
        {3, 50}},
    {
        369098757, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_90_6[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_90[7] =
{
    {(Production*) xmlscm_prod_90_0, 8, 13},
    {(Production*) xmlscm_prod_90_1, 7, 11},
    {(Production*) xmlscm_prod_90_2, 6, 9},
    {(Production*) xmlscm_prod_90_3, 5, 7},
    {(Production*) xmlscm_prod_90_4, 4, 5},
    {(Production*) xmlscm_prod_90_5, 3, 3},
    {(Production*) xmlscm_prod_90_6, 1, 1}
};

static const Production xmlscm_prod_91_0[19] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316497, 86,
        {3, 86}},
    {
        503316496, 85,
        {3, 84}},
    {
        503316495, 85,
        {3, 137}},
    {
        503316494, 82,
        {3, 62}},
    {
        503316493, 60,
        {3, 128}},
    {
        503316492, 49,
        {3, 50}},
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544331, 10,
        {0, 29}},
    {
        335544330, 10,
        {0, 22}},
    {
        335544329, 15,
        {0, 19}},
    {
        335544328, 5,
        {0, 17}},
    {
        335544327, 57,
        {0, 15}},
    {
        335544326, 58,
        {0, 13}},
    {
        335544325, 2,
        {0, 11}},
    {
        335544324, 46,
        {0, 10}},
    {
        335544323, 39,
        {0, 9}},
    {
        335544322, 39,
        {0, 5}},
    {
        335544321, 39,
        {0, 3}}
};

static const Production xmlscm_prod_91_1[18] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316497, 86,
        {3, 86}},
    {
        503316496, 85,
        {3, 84}},
    {
        503316495, 85,
        {3, 137}},
    {
        503316494, 82,
        {3, 62}},
    {
        503316493, 60,
        {3, 128}},
    {
        503316492, 49,
        {3, 50}},
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544331, 10,
        {0, 29}},
    {
        335544330, 10,
        {0, 22}},
    {
        335544329, 15,
        {0, 19}},
    {
        335544328, 5,
        {0, 17}},
    {
        335544327, 57,
        {0, 15}},
    {
        335544326, 58,
        {0, 13}},
    {
        335544325, 2,
        {0, 11}},
    {
        335544324, 46,
        {0, 10}},
    {
        335544323, 39,
        {0, 9}},
    {
        335544322, 39,
        {0, 5}}
};

static const Production xmlscm_prod_91_2[17] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316497, 86,
        {3, 86}},
    {
        503316496, 85,
        {3, 84}},
    {
        503316495, 85,
        {3, 137}},
    {
        503316494, 82,
        {3, 62}},
    {
        503316493, 60,
        {3, 128}},
    {
        503316492, 49,
        {3, 50}},
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544331, 10,
        {0, 29}},
    {
        335544330, 10,
        {0, 22}},
    {
        335544329, 15,
        {0, 19}},
    {
        335544328, 5,
        {0, 17}},
    {
        335544327, 57,
        {0, 15}},
    {
        335544326, 58,
        {0, 13}},
    {
        335544325, 2,
        {0, 11}},
    {
        335544324, 46,
        {0, 10}},
    {
        335544323, 39,
        {0, 9}}
};

static const Production xmlscm_prod_91_3[16] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316497, 86,
        {3, 86}},
    {
        503316496, 85,
        {3, 84}},
    {
        503316495, 85,
        {3, 137}},
    {
        503316494, 82,
        {3, 62}},
    {
        503316493, 60,
        {3, 128}},
    {
        503316492, 49,
        {3, 50}},
    {
        369098755, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544331, 10,
        {0, 29}},
    {
        335544330, 10,
        {0, 22}},
    {
        335544329, 15,
        {0, 19}},
    {
        335544328, 5,
        {0, 17}},
    {
        335544327, 57,
        {0, 15}},
    {
        335544326, 58,
        {0, 13}},
    {
        335544325, 2,
        {0, 11}},
    {
        335544324, 46,
        {0, 10}}
};

static const Production xmlscm_prod_91_4[15] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316497, 86,
        {3, 86}},
    {
        503316496, 85,
        {3, 84}},
    {
        503316495, 85,
        {3, 137}},
    {
        503316494, 82,
        {3, 62}},
    {
        503316493, 60,
        {3, 128}},
    {
        503316492, 49,
        {3, 50}},
    {
        369098756, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544331, 10,
        {0, 29}},
    {
        335544330, 10,
        {0, 22}},
    {
        335544329, 15,
        {0, 19}},
    {
        335544328, 5,
        {0, 17}},
    {
        335544327, 57,
        {0, 15}},
    {
        335544326, 58,
        {0, 13}},
    {
        335544325, 2,
        {0, 11}}
};

static const Production xmlscm_prod_91_5[14] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316497, 86,
        {3, 86}},
    {
        503316496, 85,
        {3, 84}},
    {
        503316495, 85,
        {3, 137}},
    {
        503316494, 82,
        {3, 62}},
    {
        503316493, 60,
        {3, 128}},
    {
        503316492, 49,
        {3, 50}},
    {
        369098757, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544331, 10,
        {0, 29}},
    {
        335544330, 10,
        {0, 22}},
    {
        335544329, 15,
        {0, 19}},
    {
        335544328, 5,
        {0, 17}},
    {
        335544327, 57,
        {0, 15}},
    {
        335544326, 58,
        {0, 13}}
};

static const Production xmlscm_prod_91_6[13] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316497, 86,
        {3, 86}},
    {
        503316496, 85,
        {3, 84}},
    {
        503316495, 85,
        {3, 137}},
    {
        503316494, 82,
        {3, 62}},
    {
        503316493, 60,
        {3, 128}},
    {
        503316492, 49,
        {3, 50}},
    {
        369098758, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544331, 10,
        {0, 29}},
    {
        335544330, 10,
        {0, 22}},
    {
        335544329, 15,
        {0, 19}},
    {
        335544328, 5,
        {0, 17}},
    {
        335544327, 57,
        {0, 15}}
};

static const Production xmlscm_prod_91_7[12] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316497, 86,
        {3, 86}},
    {
        503316496, 85,
        {3, 84}},
    {
        503316495, 85,
        {3, 137}},
    {
        503316494, 82,
        {3, 62}},
    {
        503316493, 60,
        {3, 128}},
    {
        503316492, 49,
        {3, 50}},
    {
        369098759, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544331, 10,
        {0, 29}},
    {
        335544330, 10,
        {0, 22}},
    {
        335544329, 15,
        {0, 19}},
    {
        335544328, 5,
        {0, 17}}
};

static const Production xmlscm_prod_91_8[11] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316497, 86,
        {3, 86}},
    {
        503316496, 85,
        {3, 84}},
    {
        503316495, 85,
        {3, 137}},
    {
        503316494, 82,
        {3, 62}},
    {
        503316493, 60,
        {3, 128}},
    {
        503316492, 49,
        {3, 50}},
    {
        369098760, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544331, 10,
        {0, 29}},
    {
        335544330, 10,
        {0, 22}},
    {
        335544329, 15,
        {0, 19}}
};

static const Production xmlscm_prod_91_9[10] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316497, 86,
        {3, 86}},
    {
        503316496, 85,
        {3, 84}},
    {
        503316495, 85,
        {3, 137}},
    {
        503316494, 82,
        {3, 62}},
    {
        503316493, 60,
        {3, 128}},
    {
        503316492, 49,
        {3, 50}},
    {
        369098761, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544331, 10,
        {0, 29}},
    {
        335544330, 10,
        {0, 22}}
};

static const Production xmlscm_prod_91_10[9] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316497, 86,
        {3, 86}},
    {
        503316496, 85,
        {3, 84}},
    {
        503316495, 85,
        {3, 137}},
    {
        503316494, 82,
        {3, 62}},
    {
        503316493, 60,
        {3, 128}},
    {
        503316492, 49,
        {3, 50}},
    {
        369098762, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544331, 10,
        {0, 29}}
};

static const Production xmlscm_prod_91_11[8] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316497, 86,
        {3, 86}},
    {
        503316496, 85,
        {3, 84}},
    {
        503316495, 85,
        {3, 137}},
    {
        503316494, 82,
        {3, 62}},
    {
        503316493, 60,
        {3, 128}},
    {
        503316492, 49,
        {3, 50}},
    {
        369098763, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_91_12[6] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316497, 86,
        {3, 86}},
    {
        503316496, 85,
        {3, 84}},
    {
        503316495, 85,
        {3, 137}},
    {
        503316494, 82,
        {3, 62}},
    {
        503316493, 60,
        {3, 128}}
};

static const Production xmlscm_prod_91_13[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316497, 86,
        {3, 86}},
    {
        503316496, 85,
        {3, 84}},
    {
        503316495, 85,
        {3, 137}}
};

static const Production xmlscm_prod_91_14[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316497, 86,
        {3, 86}},
    {
        503316496, 85,
        {3, 84}},
    {
        503316495, 85,
        {3, 137}}
};

static const Production xmlscm_prod_91_15[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316497, 86,
        {3, 86}},
    {
        503316496, 85,
        {3, 84}},
    {
        503316495, 85,
        {3, 137}}
};

static const Production xmlscm_prod_91_16[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316497, 86,
        {3, 86}},
    {
        503316496, 85,
        {3, 84}},
    {
        503316495, 85,
        {3, 137}}
};

static const Production xmlscm_prod_91_17[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316497, 86,
        {3, 86}},
    {
        503316496, 85,
        {3, 84}},
    {
        503316495, 85,
        {3, 137}}
};

static const GrammarRule xmlscm_rule_91[18] =
{
    {(Production*) xmlscm_prod_91_0, 19, 25},
    {(Production*) xmlscm_prod_91_1, 18, 23},
    {(Production*) xmlscm_prod_91_2, 17, 21},
    {(Production*) xmlscm_prod_91_3, 16, 19},
    {(Production*) xmlscm_prod_91_4, 15, 17},
    {(Production*) xmlscm_prod_91_5, 14, 15},
    {(Production*) xmlscm_prod_91_6, 13, 13},
    {(Production*) xmlscm_prod_91_7, 12, 11},
    {(Production*) xmlscm_prod_91_8, 11, 9},
    {(Production*) xmlscm_prod_91_9, 10, 7},
    {(Production*) xmlscm_prod_91_10, 9, 5},
    {(Production*) xmlscm_prod_91_11, 8, 3},
    {(Production*) xmlscm_prod_91_12, 6, 1},
    {(Production*) xmlscm_prod_91_13, 4, 1},
    {(Production*) xmlscm_prod_91_14, 4, 1},
    {(Production*) xmlscm_prod_91_15, 4, 1},
    {(Production*) xmlscm_prod_91_16, 4, 1},
    {(Production*) xmlscm_prod_91_17, 4, 1}
};

static const Production xmlscm_prod_92_0[2] =
{
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544321, 10,
        {0, 2}}
};

static const Production xmlscm_prod_92_1[11] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316490, 74,
        {3, 52}},
    {
        503316489, 72,
        {3, 56}},
    {
        503316488, 71,
        {3, 55}},
    {
        503316487, 89,
        {3, 120}},
    {
        503316486, 89,
        {3, 59}},
    {
        503316485, 81,
        {3, 46}},
    {
        503316484, 79,
        {3, 79}},
    {
        503316483, 49,
        {3, 50}},
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544322, 2,
        {0, 11}}
};

static const Production xmlscm_prod_92_2[10] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316490, 74,
        {3, 52}},
    {
        503316489, 72,
        {3, 56}},
    {
        503316488, 71,
        {3, 55}},
    {
        503316487, 89,
        {3, 120}},
    {
        503316486, 89,
        {3, 59}},
    {
        503316485, 81,
        {3, 46}},
    {
        503316484, 79,
        {3, 79}},
    {
        503316483, 49,
        {3, 50}},
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_92_3[8] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316490, 74,
        {3, 52}},
    {
        503316489, 72,
        {3, 56}},
    {
        503316488, 71,
        {3, 55}},
    {
        503316487, 89,
        {3, 120}},
    {
        503316486, 89,
        {3, 59}},
    {
        503316485, 81,
        {3, 46}},
    {
        503316484, 79,
        {3, 79}}
};

static const Production xmlscm_prod_92_4[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316490, 74,
        {3, 52}},
    {
        503316489, 72,
        {3, 56}},
    {
        503316488, 71,
        {3, 55}}
};

static const Production xmlscm_prod_92_5[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316490, 74,
        {3, 52}},
    {
        503316489, 72,
        {3, 56}},
    {
        503316488, 71,
        {3, 55}}
};

static const Production xmlscm_prod_92_6[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316490, 74,
        {3, 52}},
    {
        503316489, 72,
        {3, 56}},
    {
        503316488, 71,
        {3, 55}}
};

static const Production xmlscm_prod_92_7[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316490, 74,
        {3, 52}},
    {
        503316489, 72,
        {3, 56}},
    {
        503316488, 71,
        {3, 55}}
};

static const Production xmlscm_prod_92_8[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316490, 74,
        {3, 52}},
    {
        503316489, 72,
        {3, 56}},
    {
        503316488, 71,
        {3, 55}}
};

static const Production xmlscm_prod_92_9[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316490, 74,
        {3, 52}},
    {
        503316489, 72,
        {3, 56}},
    {
        503316488, 71,
        {3, 55}}
};

static const Production xmlscm_prod_92_10[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_92[11] =
{
    {(Production*) xmlscm_prod_92_0, 2, 4},
    {(Production*) xmlscm_prod_92_1, 11, 5},
    {(Production*) xmlscm_prod_92_2, 10, 3},
    {(Production*) xmlscm_prod_92_3, 8, 1},
    {(Production*) xmlscm_prod_92_4, 4, 1},
    {(Production*) xmlscm_prod_92_5, 4, 1},
    {(Production*) xmlscm_prod_92_6, 4, 1},
    {(Production*) xmlscm_prod_92_7, 4, 1},
    {(Production*) xmlscm_prod_92_8, 4, 1},
    {(Production*) xmlscm_prod_92_9, 4, 1},
    {(Production*) xmlscm_prod_92_10, 1, 1}
};

static const Production xmlscm_prod_93_0[2] =
{
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544321, 10,
        {0, 2}}
};

static const Production xmlscm_prod_93_1[11] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316490, 74,
        {3, 52}},
    {
        503316489, 72,
        {3, 56}},
    {
        503316488, 71,
        {3, 55}},
    {
        503316487, 89,
        {3, 120}},
    {
        503316486, 89,
        {3, 59}},
    {
        503316485, 81,
        {3, 46}},
    {
        503316484, 79,
        {3, 79}},
    {
        503316483, 49,
        {3, 50}},
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544322, 2,
        {0, 11}}
};

static const Production xmlscm_prod_93_2[10] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316490, 74,
        {3, 52}},
    {
        503316489, 72,
        {3, 56}},
    {
        503316488, 71,
        {3, 55}},
    {
        503316487, 89,
        {3, 120}},
    {
        503316486, 89,
        {3, 59}},
    {
        503316485, 81,
        {3, 46}},
    {
        503316484, 79,
        {3, 79}},
    {
        503316483, 49,
        {3, 50}},
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_93_3[8] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316490, 74,
        {3, 52}},
    {
        503316489, 72,
        {3, 56}},
    {
        503316488, 71,
        {3, 55}},
    {
        503316487, 89,
        {3, 120}},
    {
        503316486, 89,
        {3, 59}},
    {
        503316485, 81,
        {3, 46}},
    {
        503316484, 79,
        {3, 79}}
};

static const Production xmlscm_prod_93_4[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316490, 74,
        {3, 52}},
    {
        503316489, 72,
        {3, 56}},
    {
        503316488, 71,
        {3, 55}}
};

static const Production xmlscm_prod_93_5[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316490, 74,
        {3, 52}},
    {
        503316489, 72,
        {3, 56}},
    {
        503316488, 71,
        {3, 55}}
};

static const Production xmlscm_prod_93_6[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316490, 74,
        {3, 52}},
    {
        503316489, 72,
        {3, 56}},
    {
        503316488, 71,
        {3, 55}}
};

static const Production xmlscm_prod_93_7[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316490, 74,
        {3, 52}},
    {
        503316489, 72,
        {3, 56}},
    {
        503316488, 71,
        {3, 55}}
};

static const Production xmlscm_prod_93_8[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316490, 74,
        {3, 52}},
    {
        503316489, 72,
        {3, 56}},
    {
        503316488, 71,
        {3, 55}}
};

static const Production xmlscm_prod_93_9[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316490, 74,
        {3, 52}},
    {
        503316489, 72,
        {3, 56}},
    {
        503316488, 71,
        {3, 55}}
};

static const Production xmlscm_prod_93_10[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_93[11] =
{
    {(Production*) xmlscm_prod_93_0, 2, 4},
    {(Production*) xmlscm_prod_93_1, 11, 5},
    {(Production*) xmlscm_prod_93_2, 10, 3},
    {(Production*) xmlscm_prod_93_3, 8, 1},
    {(Production*) xmlscm_prod_93_4, 4, 1},
    {(Production*) xmlscm_prod_93_5, 4, 1},
    {(Production*) xmlscm_prod_93_6, 4, 1},
    {(Production*) xmlscm_prod_93_7, 4, 1},
    {(Production*) xmlscm_prod_93_8, 4, 1},
    {(Production*) xmlscm_prod_93_9, 4, 1},
    {(Production*) xmlscm_prod_93_10, 1, 1}
};

static const Production xmlscm_prod_94_0[7] =
{
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544326, 5,
        {0, 17}},
    {
        335544325, 15,
        {0, 16}},
    {
        335544324, 2,
        {0, 11}},
    {
        335544323, 39,
        {0, 7}},
    {
        335544322, 39,
        {0, 3}},
    {
        335544321, 15,
        {0, 0}}
};

static const Production xmlscm_prod_94_1[6] =
{
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544326, 5,
        {0, 17}},
    {
        335544325, 15,
        {0, 16}},
    {
        335544324, 2,
        {0, 11}},
    {
        335544323, 39,
        {0, 7}},
    {
        335544322, 39,
        {0, 3}}
};

static const Production xmlscm_prod_94_2[5] =
{
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544326, 5,
        {0, 17}},
    {
        335544325, 15,
        {0, 16}},
    {
        335544324, 2,
        {0, 11}},
    {
        335544323, 39,
        {0, 7}}
};

static const Production xmlscm_prod_94_3[4] =
{
    {
        369098755, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544326, 5,
        {0, 17}},
    {
        335544325, 15,
        {0, 16}},
    {
        335544324, 2,
        {0, 11}}
};

static const Production xmlscm_prod_94_4[3] =
{
    {
        369098756, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544326, 5,
        {0, 17}},
    {
        335544325, 15,
        {0, 16}}
};

static const Production xmlscm_prod_94_5[2] =
{
    {
        369098757, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544326, 5,
        {0, 17}}
};

static const Production xmlscm_prod_94_6[12] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 74,
        {3, 52}},
    {
        503316495, 72,
        {3, 56}},
    {
        503316494, 71,
        {3, 55}},
    {
        503316493, 89,
        {3, 120}},
    {
        503316492, 89,
        {3, 59}},
    {
        503316491, 81,
        {3, 46}},
    {
        503316490, 79,
        {3, 79}},
    {
        503316489, 80,
        {3, 60}},
    {
        503316488, 77,
        {3, 121}},
    {
        503316487, 49,
        {3, 50}},
    {
        369098758, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_94_7[10] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 74,
        {3, 52}},
    {
        503316495, 72,
        {3, 56}},
    {
        503316494, 71,
        {3, 55}},
    {
        503316493, 89,
        {3, 120}},
    {
        503316492, 89,
        {3, 59}},
    {
        503316491, 81,
        {3, 46}},
    {
        503316490, 79,
        {3, 79}},
    {
        503316489, 80,
        {3, 60}},
    {
        503316488, 77,
        {3, 121}}
};

static const Production xmlscm_prod_94_8[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_94_9[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_94_10[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 74,
        {3, 52}},
    {
        503316495, 72,
        {3, 56}},
    {
        503316494, 71,
        {3, 55}}
};

static const Production xmlscm_prod_94_11[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 74,
        {3, 52}},
    {
        503316495, 72,
        {3, 56}},
    {
        503316494, 71,
        {3, 55}}
};

static const Production xmlscm_prod_94_12[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 74,
        {3, 52}},
    {
        503316495, 72,
        {3, 56}},
    {
        503316494, 71,
        {3, 55}}
};

static const Production xmlscm_prod_94_13[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 74,
        {3, 52}},
    {
        503316495, 72,
        {3, 56}},
    {
        503316494, 71,
        {3, 55}}
};

static const Production xmlscm_prod_94_14[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 74,
        {3, 52}},
    {
        503316495, 72,
        {3, 56}},
    {
        503316494, 71,
        {3, 55}}
};

static const Production xmlscm_prod_94_15[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 74,
        {3, 52}},
    {
        503316495, 72,
        {3, 56}},
    {
        503316494, 71,
        {3, 55}}
};

static const Production xmlscm_prod_94_16[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_94[17] =
{
    {(Production*) xmlscm_prod_94_0, 7, 14},
    {(Production*) xmlscm_prod_94_1, 6, 12},
    {(Production*) xmlscm_prod_94_2, 5, 10},
    {(Production*) xmlscm_prod_94_3, 4, 8},
    {(Production*) xmlscm_prod_94_4, 3, 6},
    {(Production*) xmlscm_prod_94_5, 2, 4},
    {(Production*) xmlscm_prod_94_6, 12, 3},
    {(Production*) xmlscm_prod_94_7, 10, 1},
    {(Production*) xmlscm_prod_94_8, 1, 1},
    {(Production*) xmlscm_prod_94_9, 1, 1},
    {(Production*) xmlscm_prod_94_10, 4, 1},
    {(Production*) xmlscm_prod_94_11, 4, 1},
    {(Production*) xmlscm_prod_94_12, 4, 1},
    {(Production*) xmlscm_prod_94_13, 4, 1},
    {(Production*) xmlscm_prod_94_14, 4, 1},
    {(Production*) xmlscm_prod_94_15, 4, 1},
    {(Production*) xmlscm_prod_94_16, 1, 1}
};

static const Production xmlscm_prod_95_0[5] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316483, 91,
        {3, 68}},
    {
        503316482, 49,
        {3, 50}},
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544321, 2,
        {0, 11}}
};

static const Production xmlscm_prod_95_1[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316483, 91,
        {3, 68}},
    {
        503316482, 49,
        {3, 50}},
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_95_2[2] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316483, 91,
        {3, 68}}
};

static const Production xmlscm_prod_95_3[2] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316483, 91,
        {3, 68}}
};

static const GrammarRule xmlscm_rule_95[4] =
{
    {(Production*) xmlscm_prod_95_0, 5, 5},
    {(Production*) xmlscm_prod_95_1, 4, 3},
    {(Production*) xmlscm_prod_95_2, 2, 1},
    {(Production*) xmlscm_prod_95_3, 2, 1}
};

static const Production xmlscm_prod_96_0[9] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316487, 90,
        {3, 51}},
    {
        503316486, 89,
        {3, 120}},
    {
        503316485, 89,
        {3, 59}},
    {
        503316484, 79,
        {3, 79}},
    {
        503316483, 88,
        {3, 68}},
    {
        503316482, 49,
        {3, 50}},
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544321, 2,
        {0, 11}}
};

static const Production xmlscm_prod_96_1[8] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316487, 90,
        {3, 51}},
    {
        503316486, 89,
        {3, 120}},
    {
        503316485, 89,
        {3, 59}},
    {
        503316484, 79,
        {3, 79}},
    {
        503316483, 88,
        {3, 68}},
    {
        503316482, 49,
        {3, 50}},
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_96_2[6] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316487, 90,
        {3, 51}},
    {
        503316486, 89,
        {3, 120}},
    {
        503316485, 89,
        {3, 59}},
    {
        503316484, 79,
        {3, 79}},
    {
        503316483, 88,
        {3, 68}}
};

static const Production xmlscm_prod_96_3[6] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316487, 90,
        {3, 51}},
    {
        503316486, 89,
        {3, 120}},
    {
        503316485, 89,
        {3, 59}},
    {
        503316484, 79,
        {3, 79}},
    {
        503316483, 88,
        {3, 68}}
};

static const Production xmlscm_prod_96_4[6] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316487, 90,
        {3, 51}},
    {
        503316486, 89,
        {3, 120}},
    {
        503316485, 89,
        {3, 59}},
    {
        503316484, 79,
        {3, 79}},
    {
        503316483, 88,
        {3, 68}}
};

static const Production xmlscm_prod_96_5[6] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316487, 90,
        {3, 51}},
    {
        503316486, 89,
        {3, 120}},
    {
        503316485, 89,
        {3, 59}},
    {
        503316484, 79,
        {3, 79}},
    {
        503316483, 88,
        {3, 68}}
};

static const Production xmlscm_prod_96_6[6] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316487, 90,
        {3, 51}},
    {
        503316486, 89,
        {3, 120}},
    {
        503316485, 89,
        {3, 59}},
    {
        503316484, 79,
        {3, 79}},
    {
        503316483, 88,
        {3, 68}}
};

static const Production xmlscm_prod_96_7[6] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316487, 90,
        {3, 51}},
    {
        503316486, 89,
        {3, 120}},
    {
        503316485, 89,
        {3, 59}},
    {
        503316484, 79,
        {3, 79}},
    {
        503316483, 88,
        {3, 68}}
};

static const GrammarRule xmlscm_rule_96[8] =
{
    {(Production*) xmlscm_prod_96_0, 9, 5},
    {(Production*) xmlscm_prod_96_1, 8, 3},
    {(Production*) xmlscm_prod_96_2, 6, 1},
    {(Production*) xmlscm_prod_96_3, 6, 1},
    {(Production*) xmlscm_prod_96_4, 6, 1},
    {(Production*) xmlscm_prod_96_5, 6, 1},
    {(Production*) xmlscm_prod_96_6, 6, 1},
    {(Production*) xmlscm_prod_96_7, 6, 1}
};

static const Production xmlscm_prod_97_0[3] =
{
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544322, 5,
        {0, 17}},
    {
        335544321, 2,
        {0, 11}}
};

static const Production xmlscm_prod_97_1[2] =
{
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544322, 5,
        {0, 17}}
};

static const Production xmlscm_prod_97_2[5] =
{
    {
        503316486, 96,
        {3, 120}},
    {
        503316485, 96,
        {3, 59}},
    {
        503316484, 95,
        {3, 46}},
    {
        503316483, 49,
        {3, 50}},
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_97_3[3] =
{
    {
        503316486, 96,
        {3, 120}},
    {
        503316485, 96,
        {3, 59}},
    {
        503316484, 95,
        {3, 46}}
};

static const Production xmlscm_prod_97_4[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_97_5[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_97_6[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_97[7] =
{
    {(Production*) xmlscm_prod_97_0, 3, 6},
    {(Production*) xmlscm_prod_97_1, 2, 4},
    {(Production*) xmlscm_prod_97_2, 5, 2},
    {(Production*) xmlscm_prod_97_3, 3, 0},
    {(Production*) xmlscm_prod_97_4, 1, 1},
    {(Production*) xmlscm_prod_97_5, 1, 1},
    {(Production*) xmlscm_prod_97_6, 1, 1}
};

static const Production xmlscm_prod_98_0[3] =
{
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544322, 5,
        {0, 17}},
    {
        335544321, 2,
        {0, 11}}
};

static const Production xmlscm_prod_98_1[2] =
{
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544322, 5,
        {0, 17}}
};

static const Production xmlscm_prod_98_2[6] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316486, 74,
        {3, 52}},
    {
        503316485, 72,
        {3, 56}},
    {
        503316484, 71,
        {3, 55}},
    {
        503316483, 49,
        {3, 50}},
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_98_3[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316486, 74,
        {3, 52}},
    {
        503316485, 72,
        {3, 56}},
    {
        503316484, 71,
        {3, 55}}
};

static const Production xmlscm_prod_98_4[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316486, 74,
        {3, 52}},
    {
        503316485, 72,
        {3, 56}},
    {
        503316484, 71,
        {3, 55}}
};

static const Production xmlscm_prod_98_5[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316486, 74,
        {3, 52}},
    {
        503316485, 72,
        {3, 56}},
    {
        503316484, 71,
        {3, 55}}
};

static const Production xmlscm_prod_98_6[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_98[7] =
{
    {(Production*) xmlscm_prod_98_0, 3, 6},
    {(Production*) xmlscm_prod_98_1, 2, 4},
    {(Production*) xmlscm_prod_98_2, 6, 3},
    {(Production*) xmlscm_prod_98_3, 4, 1},
    {(Production*) xmlscm_prod_98_4, 4, 1},
    {(Production*) xmlscm_prod_98_5, 4, 1},
    {(Production*) xmlscm_prod_98_6, 1, 1}
};

static const Production xmlscm_prod_99_0[3] =
{
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544322, 13,
        {0, 24}},
    {
        335544321, 2,
        {0, 11}}
};

static const Production xmlscm_prod_99_1[2] =
{
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544322, 13,
        {0, 24}}
};

static const Production xmlscm_prod_99_2[7] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316487, 98,
        {3, 56}},
    {
        503316486, 97,
        {3, 79}},
    {
        503316485, 94,
        {3, 62}},
    {
        503316484, 70,
        {3, 128}},
    {
        503316483, 49,
        {3, 50}},
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_99_3[6] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316487, 98,
        {3, 56}},
    {
        503316486, 97,
        {3, 79}},
    {
        503316485, 94,
        {3, 62}},
    {
        503316484, 70,
        {3, 128}},
    {
        503316483, 49,
        {3, 50}}
};

static const Production xmlscm_prod_99_4[6] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316487, 98,
        {3, 56}},
    {
        503316486, 97,
        {3, 79}},
    {
        503316485, 94,
        {3, 62}},
    {
        503316484, 70,
        {3, 128}},
    {
        503316483, 49,
        {3, 50}}
};

static const Production xmlscm_prod_99_5[6] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316487, 98,
        {3, 56}},
    {
        503316486, 97,
        {3, 79}},
    {
        503316485, 94,
        {3, 62}},
    {
        503316484, 70,
        {3, 128}},
    {
        503316483, 49,
        {3, 50}}
};

static const Production xmlscm_prod_99_6[6] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316487, 98,
        {3, 56}},
    {
        503316486, 97,
        {3, 79}},
    {
        503316485, 94,
        {3, 62}},
    {
        503316484, 70,
        {3, 128}},
    {
        503316483, 49,
        {3, 50}}
};

static const Production xmlscm_prod_99_7[6] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316487, 98,
        {3, 56}},
    {
        503316486, 97,
        {3, 79}},
    {
        503316485, 94,
        {3, 62}},
    {
        503316484, 70,
        {3, 128}},
    {
        503316483, 49,
        {3, 50}}
};

static const GrammarRule xmlscm_rule_99[8] =
{
    {(Production*) xmlscm_prod_99_0, 3, 6},
    {(Production*) xmlscm_prod_99_1, 2, 4},
    {(Production*) xmlscm_prod_99_2, 7, 3},
    {(Production*) xmlscm_prod_99_3, 6, 1},
    {(Production*) xmlscm_prod_99_4, 6, 1},
    {(Production*) xmlscm_prod_99_5, 6, 1},
    {(Production*) xmlscm_prod_99_6, 6, 1},
    {(Production*) xmlscm_prod_99_7, 6, 1}
};

static const Production xmlscm_prod_100_0[8] =
{
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544327, 5,
        {0, 17}},
    {
        335544326, 2,
        {0, 11}},
    {
        335544325, 39,
        {0, 9}},
    {
        335544324, 39,
        {0, 7}},
    {
        335544323, 39,
        {0, 5}},
    {
        335544322, 39,
        {0, 3}},
    {
        335544321, 15,
        {0, 0}}
};

static const Production xmlscm_prod_100_1[7] =
{
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544327, 5,
        {0, 17}},
    {
        335544326, 2,
        {0, 11}},
    {
        335544325, 39,
        {0, 9}},
    {
        335544324, 39,
        {0, 7}},
    {
        335544323, 39,
        {0, 5}},
    {
        335544322, 39,
        {0, 3}}
};

static const Production xmlscm_prod_100_2[6] =
{
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544327, 5,
        {0, 17}},
    {
        335544326, 2,
        {0, 11}},
    {
        335544325, 39,
        {0, 9}},
    {
        335544324, 39,
        {0, 7}},
    {
        335544323, 39,
        {0, 5}}
};

static const Production xmlscm_prod_100_3[5] =
{
    {
        369098755, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544327, 5,
        {0, 17}},
    {
        335544326, 2,
        {0, 11}},
    {
        335544325, 39,
        {0, 9}},
    {
        335544324, 39,
        {0, 7}}
};

static const Production xmlscm_prod_100_4[4] =
{
    {
        369098756, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544327, 5,
        {0, 17}},
    {
        335544326, 2,
        {0, 11}},
    {
        335544325, 39,
        {0, 9}}
};

static const Production xmlscm_prod_100_5[3] =
{
    {
        369098757, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544327, 5,
        {0, 17}},
    {
        335544326, 2,
        {0, 11}}
};

static const Production xmlscm_prod_100_6[2] =
{
    {
        369098758, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544327, 5,
        {0, 17}}
};

static const Production xmlscm_prod_100_7[11] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 86,
        {3, 86}},
    {
        503316495, 85,
        {3, 84}},
    {
        503316494, 85,
        {3, 137}},
    {
        503316493, 82,
        {3, 62}},
    {
        503316492, 60,
        {3, 128}},
    {
        503316491, 49,
        {3, 50}},
    {
        369098759, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544330, 10,
        {0, 29}},
    {
        335544329, 10,
        {0, 26}},
    {
        335544328, 15,
        {0, 19}}
};

static const Production xmlscm_prod_100_8[10] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 86,
        {3, 86}},
    {
        503316495, 85,
        {3, 84}},
    {
        503316494, 85,
        {3, 137}},
    {
        503316493, 82,
        {3, 62}},
    {
        503316492, 60,
        {3, 128}},
    {
        503316491, 49,
        {3, 50}},
    {
        369098760, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544330, 10,
        {0, 29}},
    {
        335544329, 10,
        {0, 26}}
};

static const Production xmlscm_prod_100_9[9] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 86,
        {3, 86}},
    {
        503316495, 85,
        {3, 84}},
    {
        503316494, 85,
        {3, 137}},
    {
        503316493, 82,
        {3, 62}},
    {
        503316492, 60,
        {3, 128}},
    {
        503316491, 49,
        {3, 50}},
    {
        369098761, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544330, 10,
        {0, 29}}
};

static const Production xmlscm_prod_100_10[8] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 86,
        {3, 86}},
    {
        503316495, 85,
        {3, 84}},
    {
        503316494, 85,
        {3, 137}},
    {
        503316493, 82,
        {3, 62}},
    {
        503316492, 60,
        {3, 128}},
    {
        503316491, 49,
        {3, 50}},
    {
        369098762, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_100_11[6] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 86,
        {3, 86}},
    {
        503316495, 85,
        {3, 84}},
    {
        503316494, 85,
        {3, 137}},
    {
        503316493, 82,
        {3, 62}},
    {
        503316492, 60,
        {3, 128}}
};

static const Production xmlscm_prod_100_12[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 86,
        {3, 86}},
    {
        503316495, 85,
        {3, 84}},
    {
        503316494, 85,
        {3, 137}}
};

static const Production xmlscm_prod_100_13[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 86,
        {3, 86}},
    {
        503316495, 85,
        {3, 84}},
    {
        503316494, 85,
        {3, 137}}
};

static const Production xmlscm_prod_100_14[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 86,
        {3, 86}},
    {
        503316495, 85,
        {3, 84}},
    {
        503316494, 85,
        {3, 137}}
};

static const Production xmlscm_prod_100_15[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 86,
        {3, 86}},
    {
        503316495, 85,
        {3, 84}},
    {
        503316494, 85,
        {3, 137}}
};

static const Production xmlscm_prod_100_16[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 86,
        {3, 86}},
    {
        503316495, 85,
        {3, 84}},
    {
        503316494, 85,
        {3, 137}}
};

static const GrammarRule xmlscm_rule_100[17] =
{
    {(Production*) xmlscm_prod_100_0, 8, 16},
    {(Production*) xmlscm_prod_100_1, 7, 14},
    {(Production*) xmlscm_prod_100_2, 6, 12},
    {(Production*) xmlscm_prod_100_3, 5, 10},
    {(Production*) xmlscm_prod_100_4, 4, 8},
    {(Production*) xmlscm_prod_100_5, 3, 6},
    {(Production*) xmlscm_prod_100_6, 2, 4},
    {(Production*) xmlscm_prod_100_7, 11, 9},
    {(Production*) xmlscm_prod_100_8, 10, 7},
    {(Production*) xmlscm_prod_100_9, 9, 5},
    {(Production*) xmlscm_prod_100_10, 8, 3},
    {(Production*) xmlscm_prod_100_11, 6, 1},
    {(Production*) xmlscm_prod_100_12, 4, 1},
    {(Production*) xmlscm_prod_100_13, 4, 1},
    {(Production*) xmlscm_prod_100_14, 4, 1},
    {(Production*) xmlscm_prod_100_15, 4, 1},
    {(Production*) xmlscm_prod_100_16, 4, 1}
};

static const Production xmlscm_prod_101_0[5] =
{
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544324, 5,
        {0, 17}},
    {
        335544323, 2,
        {0, 11}},
    {
        335544322, 39,
        {0, 9}},
    {
        335544321, 39,
        {0, 5}}
};

static const Production xmlscm_prod_101_1[4] =
{
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544324, 5,
        {0, 17}},
    {
        335544323, 2,
        {0, 11}},
    {
        335544322, 39,
        {0, 9}}
};

static const Production xmlscm_prod_101_2[3] =
{
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544324, 5,
        {0, 17}},
    {
        335544323, 2,
        {0, 11}}
};

static const Production xmlscm_prod_101_3[2] =
{
    {
        369098755, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544324, 5,
        {0, 17}}
};

static const Production xmlscm_prod_101_4[5] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316487, 60,
        {3, 128}},
    {
        503316486, 49,
        {3, 50}},
    {
        369098756, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544325, 10,
        {0, 29}}
};

static const Production xmlscm_prod_101_5[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316487, 60,
        {3, 128}},
    {
        503316486, 49,
        {3, 50}},
    {
        369098757, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_101_6[2] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316487, 60,
        {3, 128}}
};

static const Production xmlscm_prod_101_7[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_101[8] =
{
    {(Production*) xmlscm_prod_101_0, 5, 10},
    {(Production*) xmlscm_prod_101_1, 4, 8},
    {(Production*) xmlscm_prod_101_2, 3, 6},
    {(Production*) xmlscm_prod_101_3, 2, 4},
    {(Production*) xmlscm_prod_101_4, 5, 5},
    {(Production*) xmlscm_prod_101_5, 4, 3},
    {(Production*) xmlscm_prod_101_6, 2, 1},
    {(Production*) xmlscm_prod_101_7, 1, 1}
};

static const Production xmlscm_prod_102_0[1] =
{
    {
        838860801, 61,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_102_1[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_102[2] =
{
    {(Production*) xmlscm_prod_102_0, 1, 0},
    {(Production*) xmlscm_prod_102_1, 1, 1}
};

static const Production xmlscm_prod_103_0[3] =
{
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544322, 5,
        {0, 17}},
    {
        335544321, 2,
        {0, 11}}
};

static const Production xmlscm_prod_103_1[2] =
{
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544322, 5,
        {0, 17}}
};

static const Production xmlscm_prod_103_2[5] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316485, 49,
        {3, 50}},
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544324, 13,
        {0, 27}},
    {
        335544323, 61,
        {0, 21}}
};

static const Production xmlscm_prod_103_3[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316485, 49,
        {3, 50}},
    {
        369098755, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544324, 13,
        {0, 27}}
};

static const Production xmlscm_prod_103_4[3] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316485, 49,
        {3, 50}},
    {
        369098756, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_103_5[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_103[6] =
{
    {(Production*) xmlscm_prod_103_0, 3, 6},
    {(Production*) xmlscm_prod_103_1, 2, 4},
    {(Production*) xmlscm_prod_103_2, 5, 7},
    {(Production*) xmlscm_prod_103_3, 4, 5},
    {(Production*) xmlscm_prod_103_4, 3, 3},
    {(Production*) xmlscm_prod_103_5, 1, 1}
};

static const Production xmlscm_prod_104_0[21] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316499, 103,
        {3, 104}},
    {
        503316498, 101,
        {3, 55}},
    {
        503316497, 100,
        {3, 68}},
    {
        503316496, 98,
        {3, 56}},
    {
        503316495, 97,
        {3, 79}},
    {
        503316494, 94,
        {3, 62}},
    {
        503316493, 70,
        {3, 128}},
    {
        503316492, 49,
        {3, 50}},
    {
        503316491, 99,
        {3, 113}},
    {
        503316490, 58,
        {3, 82}},
    {
        503316489, 57,
        {3, 83}},
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544328, 41,
        {0, 32}},
    {
        335544327, 13,
        {0, 28}},
    {
        335544326, 39,
        {1, 2}},
    {
        335544325, 2,
        {0, 11}},
    {
        335544324, 39,
        {0, 8}},
    {
        335544323, 46,
        {0, 6}},
    {
        335544322, 39,
        {0, 4}},
    {
        335544321, 46,
        {0, 1}}
};

static const Production xmlscm_prod_104_1[20] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316499, 103,
        {3, 104}},
    {
        503316498, 101,
        {3, 55}},
    {
        503316497, 100,
        {3, 68}},
    {
        503316496, 98,
        {3, 56}},
    {
        503316495, 97,
        {3, 79}},
    {
        503316494, 94,
        {3, 62}},
    {
        503316493, 70,
        {3, 128}},
    {
        503316492, 49,
        {3, 50}},
    {
        503316491, 99,
        {3, 113}},
    {
        503316490, 58,
        {3, 82}},
    {
        503316489, 57,
        {3, 83}},
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544328, 41,
        {0, 32}},
    {
        335544327, 13,
        {0, 28}},
    {
        335544326, 39,
        {1, 2}},
    {
        335544325, 2,
        {0, 11}},
    {
        335544324, 39,
        {0, 8}},
    {
        335544323, 46,
        {0, 6}},
    {
        335544322, 39,
        {0, 4}}
};

static const Production xmlscm_prod_104_2[19] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316499, 103,
        {3, 104}},
    {
        503316498, 101,
        {3, 55}},
    {
        503316497, 100,
        {3, 68}},
    {
        503316496, 98,
        {3, 56}},
    {
        503316495, 97,
        {3, 79}},
    {
        503316494, 94,
        {3, 62}},
    {
        503316493, 70,
        {3, 128}},
    {
        503316492, 49,
        {3, 50}},
    {
        503316491, 99,
        {3, 113}},
    {
        503316490, 58,
        {3, 82}},
    {
        503316489, 57,
        {3, 83}},
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544328, 41,
        {0, 32}},
    {
        335544327, 13,
        {0, 28}},
    {
        335544326, 39,
        {1, 2}},
    {
        335544325, 2,
        {0, 11}},
    {
        335544324, 39,
        {0, 8}},
    {
        335544323, 46,
        {0, 6}}
};

static const Production xmlscm_prod_104_3[18] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316499, 103,
        {3, 104}},
    {
        503316498, 101,
        {3, 55}},
    {
        503316497, 100,
        {3, 68}},
    {
        503316496, 98,
        {3, 56}},
    {
        503316495, 97,
        {3, 79}},
    {
        503316494, 94,
        {3, 62}},
    {
        503316493, 70,
        {3, 128}},
    {
        503316492, 49,
        {3, 50}},
    {
        503316491, 99,
        {3, 113}},
    {
        503316490, 58,
        {3, 82}},
    {
        503316489, 57,
        {3, 83}},
    {
        369098755, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544328, 41,
        {0, 32}},
    {
        335544327, 13,
        {0, 28}},
    {
        335544326, 39,
        {1, 2}},
    {
        335544325, 2,
        {0, 11}},
    {
        335544324, 39,
        {0, 8}}
};

static const Production xmlscm_prod_104_4[17] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316499, 103,
        {3, 104}},
    {
        503316498, 101,
        {3, 55}},
    {
        503316497, 100,
        {3, 68}},
    {
        503316496, 98,
        {3, 56}},
    {
        503316495, 97,
        {3, 79}},
    {
        503316494, 94,
        {3, 62}},
    {
        503316493, 70,
        {3, 128}},
    {
        503316492, 49,
        {3, 50}},
    {
        503316491, 99,
        {3, 113}},
    {
        503316490, 58,
        {3, 82}},
    {
        503316489, 57,
        {3, 83}},
    {
        369098756, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544328, 41,
        {0, 32}},
    {
        335544327, 13,
        {0, 28}},
    {
        335544326, 39,
        {1, 2}},
    {
        335544325, 2,
        {0, 11}}
};

static const Production xmlscm_prod_104_5[16] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316499, 103,
        {3, 104}},
    {
        503316498, 101,
        {3, 55}},
    {
        503316497, 100,
        {3, 68}},
    {
        503316496, 98,
        {3, 56}},
    {
        503316495, 97,
        {3, 79}},
    {
        503316494, 94,
        {3, 62}},
    {
        503316493, 70,
        {3, 128}},
    {
        503316492, 49,
        {3, 50}},
    {
        503316491, 99,
        {3, 113}},
    {
        503316490, 58,
        {3, 82}},
    {
        503316489, 57,
        {3, 83}},
    {
        369098757, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544328, 41,
        {0, 32}},
    {
        335544327, 13,
        {0, 28}},
    {
        335544326, 39,
        {1, 2}}
};

static const Production xmlscm_prod_104_6[15] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316499, 103,
        {3, 104}},
    {
        503316498, 101,
        {3, 55}},
    {
        503316497, 100,
        {3, 68}},
    {
        503316496, 98,
        {3, 56}},
    {
        503316495, 97,
        {3, 79}},
    {
        503316494, 94,
        {3, 62}},
    {
        503316493, 70,
        {3, 128}},
    {
        503316492, 49,
        {3, 50}},
    {
        503316491, 99,
        {3, 113}},
    {
        503316490, 58,
        {3, 82}},
    {
        503316489, 57,
        {3, 83}},
    {
        369098758, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544328, 41,
        {0, 32}},
    {
        335544327, 13,
        {0, 28}}
};

static const Production xmlscm_prod_104_7[14] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316499, 103,
        {3, 104}},
    {
        503316498, 101,
        {3, 55}},
    {
        503316497, 100,
        {3, 68}},
    {
        503316496, 98,
        {3, 56}},
    {
        503316495, 97,
        {3, 79}},
    {
        503316494, 94,
        {3, 62}},
    {
        503316493, 70,
        {3, 128}},
    {
        503316492, 49,
        {3, 50}},
    {
        503316491, 99,
        {3, 113}},
    {
        503316490, 58,
        {3, 82}},
    {
        503316489, 57,
        {3, 83}},
    {
        369098759, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544328, 41,
        {0, 32}}
};

static const Production xmlscm_prod_104_8[13] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316499, 103,
        {3, 104}},
    {
        503316498, 101,
        {3, 55}},
    {
        503316497, 100,
        {3, 68}},
    {
        503316496, 98,
        {3, 56}},
    {
        503316495, 97,
        {3, 79}},
    {
        503316494, 94,
        {3, 62}},
    {
        503316493, 70,
        {3, 128}},
    {
        503316492, 49,
        {3, 50}},
    {
        503316491, 99,
        {3, 113}},
    {
        503316490, 58,
        {3, 82}},
    {
        503316489, 57,
        {3, 83}},
    {
        369098760, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_104_9[12] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316499, 103,
        {3, 104}},
    {
        503316498, 101,
        {3, 55}},
    {
        503316497, 100,
        {3, 68}},
    {
        503316496, 98,
        {3, 56}},
    {
        503316495, 97,
        {3, 79}},
    {
        503316494, 94,
        {3, 62}},
    {
        503316493, 70,
        {3, 128}},
    {
        503316492, 49,
        {3, 50}},
    {
        503316491, 99,
        {3, 113}},
    {
        503316490, 58,
        {3, 82}},
    {
        503316489, 57,
        {3, 83}}
};

static const Production xmlscm_prod_104_10[12] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316499, 103,
        {3, 104}},
    {
        503316498, 101,
        {3, 55}},
    {
        503316497, 100,
        {3, 68}},
    {
        503316496, 98,
        {3, 56}},
    {
        503316495, 97,
        {3, 79}},
    {
        503316494, 94,
        {3, 62}},
    {
        503316493, 70,
        {3, 128}},
    {
        503316492, 49,
        {3, 50}},
    {
        503316491, 99,
        {3, 113}},
    {
        503316490, 58,
        {3, 82}},
    {
        503316489, 57,
        {3, 83}}
};

static const Production xmlscm_prod_104_11[12] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316499, 103,
        {3, 104}},
    {
        503316498, 101,
        {3, 55}},
    {
        503316497, 100,
        {3, 68}},
    {
        503316496, 98,
        {3, 56}},
    {
        503316495, 97,
        {3, 79}},
    {
        503316494, 94,
        {3, 62}},
    {
        503316493, 70,
        {3, 128}},
    {
        503316492, 49,
        {3, 50}},
    {
        503316491, 99,
        {3, 113}},
    {
        503316490, 58,
        {3, 82}},
    {
        503316489, 57,
        {3, 83}}
};

static const Production xmlscm_prod_104_12[12] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316499, 103,
        {3, 104}},
    {
        503316498, 101,
        {3, 55}},
    {
        503316497, 100,
        {3, 68}},
    {
        503316496, 98,
        {3, 56}},
    {
        503316495, 97,
        {3, 79}},
    {
        503316494, 94,
        {3, 62}},
    {
        503316493, 70,
        {3, 128}},
    {
        503316492, 49,
        {3, 50}},
    {
        503316491, 99,
        {3, 113}},
    {
        503316490, 58,
        {3, 82}},
    {
        503316489, 57,
        {3, 83}}
};

static const Production xmlscm_prod_104_13[9] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316500, 49,
        {3, 50}},
    {
        503316499, 103,
        {3, 104}},
    {
        503316498, 101,
        {3, 55}},
    {
        503316497, 100,
        {3, 68}},
    {
        503316496, 98,
        {3, 56}},
    {
        503316495, 97,
        {3, 79}},
    {
        503316494, 94,
        {3, 62}},
    {
        503316493, 70,
        {3, 128}}
};

static const Production xmlscm_prod_104_14[9] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316500, 49,
        {3, 50}},
    {
        503316499, 103,
        {3, 104}},
    {
        503316498, 101,
        {3, 55}},
    {
        503316497, 100,
        {3, 68}},
    {
        503316496, 98,
        {3, 56}},
    {
        503316495, 97,
        {3, 79}},
    {
        503316494, 94,
        {3, 62}},
    {
        503316493, 70,
        {3, 128}}
};

static const Production xmlscm_prod_104_15[9] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316500, 49,
        {3, 50}},
    {
        503316499, 103,
        {3, 104}},
    {
        503316498, 101,
        {3, 55}},
    {
        503316497, 100,
        {3, 68}},
    {
        503316496, 98,
        {3, 56}},
    {
        503316495, 97,
        {3, 79}},
    {
        503316494, 94,
        {3, 62}},
    {
        503316493, 70,
        {3, 128}}
};

static const Production xmlscm_prod_104_16[9] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316500, 49,
        {3, 50}},
    {
        503316499, 103,
        {3, 104}},
    {
        503316498, 101,
        {3, 55}},
    {
        503316497, 100,
        {3, 68}},
    {
        503316496, 98,
        {3, 56}},
    {
        503316495, 97,
        {3, 79}},
    {
        503316494, 94,
        {3, 62}},
    {
        503316493, 70,
        {3, 128}}
};

static const Production xmlscm_prod_104_17[9] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316500, 49,
        {3, 50}},
    {
        503316499, 103,
        {3, 104}},
    {
        503316498, 101,
        {3, 55}},
    {
        503316497, 100,
        {3, 68}},
    {
        503316496, 98,
        {3, 56}},
    {
        503316495, 97,
        {3, 79}},
    {
        503316494, 94,
        {3, 62}},
    {
        503316493, 70,
        {3, 128}}
};

static const Production xmlscm_prod_104_18[9] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316500, 49,
        {3, 50}},
    {
        503316499, 103,
        {3, 104}},
    {
        503316498, 101,
        {3, 55}},
    {
        503316497, 100,
        {3, 68}},
    {
        503316496, 98,
        {3, 56}},
    {
        503316495, 97,
        {3, 79}},
    {
        503316494, 94,
        {3, 62}},
    {
        503316493, 70,
        {3, 128}}
};

static const Production xmlscm_prod_104_19[9] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316500, 49,
        {3, 50}},
    {
        503316499, 103,
        {3, 104}},
    {
        503316498, 101,
        {3, 55}},
    {
        503316497, 100,
        {3, 68}},
    {
        503316496, 98,
        {3, 56}},
    {
        503316495, 97,
        {3, 79}},
    {
        503316494, 94,
        {3, 62}},
    {
        503316493, 70,
        {3, 128}}
};

static const Production xmlscm_prod_104_20[9] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316500, 49,
        {3, 50}},
    {
        503316499, 103,
        {3, 104}},
    {
        503316498, 101,
        {3, 55}},
    {
        503316497, 100,
        {3, 68}},
    {
        503316496, 98,
        {3, 56}},
    {
        503316495, 97,
        {3, 79}},
    {
        503316494, 94,
        {3, 62}},
    {
        503316493, 70,
        {3, 128}}
};

static const GrammarRule xmlscm_rule_104[21] =
{
    {(Production*) xmlscm_prod_104_0, 21, 19},
    {(Production*) xmlscm_prod_104_1, 20, 17},
    {(Production*) xmlscm_prod_104_2, 19, 15},
    {(Production*) xmlscm_prod_104_3, 18, 13},
    {(Production*) xmlscm_prod_104_4, 17, 11},
    {(Production*) xmlscm_prod_104_5, 16, 9},
    {(Production*) xmlscm_prod_104_6, 15, 7},
    {(Production*) xmlscm_prod_104_7, 14, 5},
    {(Production*) xmlscm_prod_104_8, 13, 3},
    {(Production*) xmlscm_prod_104_9, 12, 1},
    {(Production*) xmlscm_prod_104_10, 12, 1},
    {(Production*) xmlscm_prod_104_11, 12, 1},
    {(Production*) xmlscm_prod_104_12, 12, 1},
    {(Production*) xmlscm_prod_104_13, 9, 1},
    {(Production*) xmlscm_prod_104_14, 9, 1},
    {(Production*) xmlscm_prod_104_15, 9, 1},
    {(Production*) xmlscm_prod_104_16, 9, 1},
    {(Production*) xmlscm_prod_104_17, 9, 1},
    {(Production*) xmlscm_prod_104_18, 9, 1},
    {(Production*) xmlscm_prod_104_19, 9, 1},
    {(Production*) xmlscm_prod_104_20, 9, 1}
};

static const Production xmlscm_prod_105_0[18] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 74,
        {3, 52}},
    {
        503316495, 72,
        {3, 56}},
    {
        503316494, 71,
        {3, 55}},
    {
        503316493, 89,
        {3, 120}},
    {
        503316492, 89,
        {3, 59}},
    {
        503316491, 81,
        {3, 46}},
    {
        503316490, 79,
        {3, 79}},
    {
        503316489, 80,
        {3, 60}},
    {
        503316488, 77,
        {3, 121}},
    {
        503316487, 49,
        {3, 50}},
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544326, 5,
        {0, 17}},
    {
        335544325, 15,
        {0, 16}},
    {
        335544324, 2,
        {0, 11}},
    {
        335544323, 39,
        {0, 7}},
    {
        335544322, 39,
        {0, 3}},
    {
        335544321, 15,
        {0, 0}}
};

static const Production xmlscm_prod_105_1[17] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 74,
        {3, 52}},
    {
        503316495, 72,
        {3, 56}},
    {
        503316494, 71,
        {3, 55}},
    {
        503316493, 89,
        {3, 120}},
    {
        503316492, 89,
        {3, 59}},
    {
        503316491, 81,
        {3, 46}},
    {
        503316490, 79,
        {3, 79}},
    {
        503316489, 80,
        {3, 60}},
    {
        503316488, 77,
        {3, 121}},
    {
        503316487, 49,
        {3, 50}},
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544326, 5,
        {0, 17}},
    {
        335544325, 15,
        {0, 16}},
    {
        335544324, 2,
        {0, 11}},
    {
        335544323, 39,
        {0, 7}},
    {
        335544322, 39,
        {0, 3}}
};

static const Production xmlscm_prod_105_2[16] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 74,
        {3, 52}},
    {
        503316495, 72,
        {3, 56}},
    {
        503316494, 71,
        {3, 55}},
    {
        503316493, 89,
        {3, 120}},
    {
        503316492, 89,
        {3, 59}},
    {
        503316491, 81,
        {3, 46}},
    {
        503316490, 79,
        {3, 79}},
    {
        503316489, 80,
        {3, 60}},
    {
        503316488, 77,
        {3, 121}},
    {
        503316487, 49,
        {3, 50}},
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544326, 5,
        {0, 17}},
    {
        335544325, 15,
        {0, 16}},
    {
        335544324, 2,
        {0, 11}},
    {
        335544323, 39,
        {0, 7}}
};

static const Production xmlscm_prod_105_3[15] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 74,
        {3, 52}},
    {
        503316495, 72,
        {3, 56}},
    {
        503316494, 71,
        {3, 55}},
    {
        503316493, 89,
        {3, 120}},
    {
        503316492, 89,
        {3, 59}},
    {
        503316491, 81,
        {3, 46}},
    {
        503316490, 79,
        {3, 79}},
    {
        503316489, 80,
        {3, 60}},
    {
        503316488, 77,
        {3, 121}},
    {
        503316487, 49,
        {3, 50}},
    {
        369098755, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544326, 5,
        {0, 17}},
    {
        335544325, 15,
        {0, 16}},
    {
        335544324, 2,
        {0, 11}}
};

static const Production xmlscm_prod_105_4[14] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 74,
        {3, 52}},
    {
        503316495, 72,
        {3, 56}},
    {
        503316494, 71,
        {3, 55}},
    {
        503316493, 89,
        {3, 120}},
    {
        503316492, 89,
        {3, 59}},
    {
        503316491, 81,
        {3, 46}},
    {
        503316490, 79,
        {3, 79}},
    {
        503316489, 80,
        {3, 60}},
    {
        503316488, 77,
        {3, 121}},
    {
        503316487, 49,
        {3, 50}},
    {
        369098756, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544326, 5,
        {0, 17}},
    {
        335544325, 15,
        {0, 16}}
};

static const Production xmlscm_prod_105_5[13] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 74,
        {3, 52}},
    {
        503316495, 72,
        {3, 56}},
    {
        503316494, 71,
        {3, 55}},
    {
        503316493, 89,
        {3, 120}},
    {
        503316492, 89,
        {3, 59}},
    {
        503316491, 81,
        {3, 46}},
    {
        503316490, 79,
        {3, 79}},
    {
        503316489, 80,
        {3, 60}},
    {
        503316488, 77,
        {3, 121}},
    {
        503316487, 49,
        {3, 50}},
    {
        369098757, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544326, 5,
        {0, 17}}
};

static const Production xmlscm_prod_105_6[12] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 74,
        {3, 52}},
    {
        503316495, 72,
        {3, 56}},
    {
        503316494, 71,
        {3, 55}},
    {
        503316493, 89,
        {3, 120}},
    {
        503316492, 89,
        {3, 59}},
    {
        503316491, 81,
        {3, 46}},
    {
        503316490, 79,
        {3, 79}},
    {
        503316489, 80,
        {3, 60}},
    {
        503316488, 77,
        {3, 121}},
    {
        503316487, 49,
        {3, 50}},
    {
        369098758, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_105_7[10] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 74,
        {3, 52}},
    {
        503316495, 72,
        {3, 56}},
    {
        503316494, 71,
        {3, 55}},
    {
        503316493, 89,
        {3, 120}},
    {
        503316492, 89,
        {3, 59}},
    {
        503316491, 81,
        {3, 46}},
    {
        503316490, 79,
        {3, 79}},
    {
        503316489, 80,
        {3, 60}},
    {
        503316488, 77,
        {3, 121}}
};

static const Production xmlscm_prod_105_8[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_105_9[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_105_10[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 74,
        {3, 52}},
    {
        503316495, 72,
        {3, 56}},
    {
        503316494, 71,
        {3, 55}}
};

static const Production xmlscm_prod_105_11[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 74,
        {3, 52}},
    {
        503316495, 72,
        {3, 56}},
    {
        503316494, 71,
        {3, 55}}
};

static const Production xmlscm_prod_105_12[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 74,
        {3, 52}},
    {
        503316495, 72,
        {3, 56}},
    {
        503316494, 71,
        {3, 55}}
};

static const Production xmlscm_prod_105_13[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 74,
        {3, 52}},
    {
        503316495, 72,
        {3, 56}},
    {
        503316494, 71,
        {3, 55}}
};

static const Production xmlscm_prod_105_14[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 74,
        {3, 52}},
    {
        503316495, 72,
        {3, 56}},
    {
        503316494, 71,
        {3, 55}}
};

static const Production xmlscm_prod_105_15[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316496, 74,
        {3, 52}},
    {
        503316495, 72,
        {3, 56}},
    {
        503316494, 71,
        {3, 55}}
};

static const Production xmlscm_prod_105_16[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_105[17] =
{
    {(Production*) xmlscm_prod_105_0, 18, 15},
    {(Production*) xmlscm_prod_105_1, 17, 13},
    {(Production*) xmlscm_prod_105_2, 16, 11},
    {(Production*) xmlscm_prod_105_3, 15, 9},
    {(Production*) xmlscm_prod_105_4, 14, 7},
    {(Production*) xmlscm_prod_105_5, 13, 5},
    {(Production*) xmlscm_prod_105_6, 12, 3},
    {(Production*) xmlscm_prod_105_7, 10, 1},
    {(Production*) xmlscm_prod_105_8, 1, 1},
    {(Production*) xmlscm_prod_105_9, 1, 1},
    {(Production*) xmlscm_prod_105_10, 4, 1},
    {(Production*) xmlscm_prod_105_11, 4, 1},
    {(Production*) xmlscm_prod_105_12, 4, 1},
    {(Production*) xmlscm_prod_105_13, 4, 1},
    {(Production*) xmlscm_prod_105_14, 4, 1},
    {(Production*) xmlscm_prod_105_15, 4, 1},
    {(Production*) xmlscm_prod_105_16, 1, 1}
};

static const Production xmlscm_prod_106_0[2] =
{
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544321, 10,
        {0, 2}}
};

static const Production xmlscm_prod_106_1[24] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316503, 74,
        {3, 52}},
    {
        503316502, 72,
        {3, 56}},
    {
        503316501, 71,
        {3, 55}},
    {
        503316500, 68,
        {3, 109}},
    {
        503316499, 67,
        {3, 138}},
    {
        503316498, 66,
        {3, 69}},
    {
        503316497, 65,
        {3, 94}},
    {
        503316496, 65,
        {3, 97}},
    {
        503316495, 65,
        {3, 87}},
    {
        503316494, 65,
        {3, 77}},
    {
        503316493, 64,
        {3, 133}},
    {
        503316492, 63,
        {3, 93}},
    {
        503316491, 63,
        {3, 92}},
    {
        503316490, 63,
        {3, 96}},
    {
        503316489, 63,
        {3, 95}},
    {
        503316488, 60,
        {3, 128}},
    {
        503316487, 89,
        {3, 120}},
    {
        503316486, 89,
        {3, 59}},
    {
        503316485, 81,
        {3, 46}},
    {
        503316484, 79,
        {3, 79}},
    {
        503316483, 49,
        {3, 50}},
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544322, 2,
        {0, 11}}
};

static const Production xmlscm_prod_106_2[23] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316503, 74,
        {3, 52}},
    {
        503316502, 72,
        {3, 56}},
    {
        503316501, 71,
        {3, 55}},
    {
        503316500, 68,
        {3, 109}},
    {
        503316499, 67,
        {3, 138}},
    {
        503316498, 66,
        {3, 69}},
    {
        503316497, 65,
        {3, 94}},
    {
        503316496, 65,
        {3, 97}},
    {
        503316495, 65,
        {3, 87}},
    {
        503316494, 65,
        {3, 77}},
    {
        503316493, 64,
        {3, 133}},
    {
        503316492, 63,
        {3, 93}},
    {
        503316491, 63,
        {3, 92}},
    {
        503316490, 63,
        {3, 96}},
    {
        503316489, 63,
        {3, 95}},
    {
        503316488, 60,
        {3, 128}},
    {
        503316487, 89,
        {3, 120}},
    {
        503316486, 89,
        {3, 59}},
    {
        503316485, 81,
        {3, 46}},
    {
        503316484, 79,
        {3, 79}},
    {
        503316483, 49,
        {3, 50}},
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_106_3[21] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316503, 74,
        {3, 52}},
    {
        503316502, 72,
        {3, 56}},
    {
        503316501, 71,
        {3, 55}},
    {
        503316500, 68,
        {3, 109}},
    {
        503316499, 67,
        {3, 138}},
    {
        503316498, 66,
        {3, 69}},
    {
        503316497, 65,
        {3, 94}},
    {
        503316496, 65,
        {3, 97}},
    {
        503316495, 65,
        {3, 87}},
    {
        503316494, 65,
        {3, 77}},
    {
        503316493, 64,
        {3, 133}},
    {
        503316492, 63,
        {3, 93}},
    {
        503316491, 63,
        {3, 92}},
    {
        503316490, 63,
        {3, 96}},
    {
        503316489, 63,
        {3, 95}},
    {
        503316488, 60,
        {3, 128}},
    {
        503316487, 89,
        {3, 120}},
    {
        503316486, 89,
        {3, 59}},
    {
        503316485, 81,
        {3, 46}},
    {
        503316484, 79,
        {3, 79}}
};

static const Production xmlscm_prod_106_4[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316503, 74,
        {3, 52}},
    {
        503316502, 72,
        {3, 56}},
    {
        503316501, 71,
        {3, 55}}
};

static const Production xmlscm_prod_106_5[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316503, 74,
        {3, 52}},
    {
        503316502, 72,
        {3, 56}},
    {
        503316501, 71,
        {3, 55}}
};

static const Production xmlscm_prod_106_6[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316503, 74,
        {3, 52}},
    {
        503316502, 72,
        {3, 56}},
    {
        503316501, 71,
        {3, 55}}
};

static const Production xmlscm_prod_106_7[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316503, 74,
        {3, 52}},
    {
        503316502, 72,
        {3, 56}},
    {
        503316501, 71,
        {3, 55}}
};

static const Production xmlscm_prod_106_8[16] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316503, 74,
        {3, 52}},
    {
        503316502, 72,
        {3, 56}},
    {
        503316501, 71,
        {3, 55}},
    {
        503316500, 68,
        {3, 109}},
    {
        503316499, 67,
        {3, 138}},
    {
        503316498, 66,
        {3, 69}},
    {
        503316497, 65,
        {3, 94}},
    {
        503316496, 65,
        {3, 97}},
    {
        503316495, 65,
        {3, 87}},
    {
        503316494, 65,
        {3, 77}},
    {
        503316493, 64,
        {3, 133}},
    {
        503316492, 63,
        {3, 93}},
    {
        503316491, 63,
        {3, 92}},
    {
        503316490, 63,
        {3, 96}},
    {
        503316489, 63,
        {3, 95}}
};

static const Production xmlscm_prod_106_9[16] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316503, 74,
        {3, 52}},
    {
        503316502, 72,
        {3, 56}},
    {
        503316501, 71,
        {3, 55}},
    {
        503316500, 68,
        {3, 109}},
    {
        503316499, 67,
        {3, 138}},
    {
        503316498, 66,
        {3, 69}},
    {
        503316497, 65,
        {3, 94}},
    {
        503316496, 65,
        {3, 97}},
    {
        503316495, 65,
        {3, 87}},
    {
        503316494, 65,
        {3, 77}},
    {
        503316493, 64,
        {3, 133}},
    {
        503316492, 63,
        {3, 93}},
    {
        503316491, 63,
        {3, 92}},
    {
        503316490, 63,
        {3, 96}},
    {
        503316489, 63,
        {3, 95}}
};

static const Production xmlscm_prod_106_10[16] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316503, 74,
        {3, 52}},
    {
        503316502, 72,
        {3, 56}},
    {
        503316501, 71,
        {3, 55}},
    {
        503316500, 68,
        {3, 109}},
    {
        503316499, 67,
        {3, 138}},
    {
        503316498, 66,
        {3, 69}},
    {
        503316497, 65,
        {3, 94}},
    {
        503316496, 65,
        {3, 97}},
    {
        503316495, 65,
        {3, 87}},
    {
        503316494, 65,
        {3, 77}},
    {
        503316493, 64,
        {3, 133}},
    {
        503316492, 63,
        {3, 93}},
    {
        503316491, 63,
        {3, 92}},
    {
        503316490, 63,
        {3, 96}},
    {
        503316489, 63,
        {3, 95}}
};

static const Production xmlscm_prod_106_11[16] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316503, 74,
        {3, 52}},
    {
        503316502, 72,
        {3, 56}},
    {
        503316501, 71,
        {3, 55}},
    {
        503316500, 68,
        {3, 109}},
    {
        503316499, 67,
        {3, 138}},
    {
        503316498, 66,
        {3, 69}},
    {
        503316497, 65,
        {3, 94}},
    {
        503316496, 65,
        {3, 97}},
    {
        503316495, 65,
        {3, 87}},
    {
        503316494, 65,
        {3, 77}},
    {
        503316493, 64,
        {3, 133}},
    {
        503316492, 63,
        {3, 93}},
    {
        503316491, 63,
        {3, 92}},
    {
        503316490, 63,
        {3, 96}},
    {
        503316489, 63,
        {3, 95}}
};

static const Production xmlscm_prod_106_12[16] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316503, 74,
        {3, 52}},
    {
        503316502, 72,
        {3, 56}},
    {
        503316501, 71,
        {3, 55}},
    {
        503316500, 68,
        {3, 109}},
    {
        503316499, 67,
        {3, 138}},
    {
        503316498, 66,
        {3, 69}},
    {
        503316497, 65,
        {3, 94}},
    {
        503316496, 65,
        {3, 97}},
    {
        503316495, 65,
        {3, 87}},
    {
        503316494, 65,
        {3, 77}},
    {
        503316493, 64,
        {3, 133}},
    {
        503316492, 63,
        {3, 93}},
    {
        503316491, 63,
        {3, 92}},
    {
        503316490, 63,
        {3, 96}},
    {
        503316489, 63,
        {3, 95}}
};

static const Production xmlscm_prod_106_13[16] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316503, 74,
        {3, 52}},
    {
        503316502, 72,
        {3, 56}},
    {
        503316501, 71,
        {3, 55}},
    {
        503316500, 68,
        {3, 109}},
    {
        503316499, 67,
        {3, 138}},
    {
        503316498, 66,
        {3, 69}},
    {
        503316497, 65,
        {3, 94}},
    {
        503316496, 65,
        {3, 97}},
    {
        503316495, 65,
        {3, 87}},
    {
        503316494, 65,
        {3, 77}},
    {
        503316493, 64,
        {3, 133}},
    {
        503316492, 63,
        {3, 93}},
    {
        503316491, 63,
        {3, 92}},
    {
        503316490, 63,
        {3, 96}},
    {
        503316489, 63,
        {3, 95}}
};

static const Production xmlscm_prod_106_14[16] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316503, 74,
        {3, 52}},
    {
        503316502, 72,
        {3, 56}},
    {
        503316501, 71,
        {3, 55}},
    {
        503316500, 68,
        {3, 109}},
    {
        503316499, 67,
        {3, 138}},
    {
        503316498, 66,
        {3, 69}},
    {
        503316497, 65,
        {3, 94}},
    {
        503316496, 65,
        {3, 97}},
    {
        503316495, 65,
        {3, 87}},
    {
        503316494, 65,
        {3, 77}},
    {
        503316493, 64,
        {3, 133}},
    {
        503316492, 63,
        {3, 93}},
    {
        503316491, 63,
        {3, 92}},
    {
        503316490, 63,
        {3, 96}},
    {
        503316489, 63,
        {3, 95}}
};

static const Production xmlscm_prod_106_15[16] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316503, 74,
        {3, 52}},
    {
        503316502, 72,
        {3, 56}},
    {
        503316501, 71,
        {3, 55}},
    {
        503316500, 68,
        {3, 109}},
    {
        503316499, 67,
        {3, 138}},
    {
        503316498, 66,
        {3, 69}},
    {
        503316497, 65,
        {3, 94}},
    {
        503316496, 65,
        {3, 97}},
    {
        503316495, 65,
        {3, 87}},
    {
        503316494, 65,
        {3, 77}},
    {
        503316493, 64,
        {3, 133}},
    {
        503316492, 63,
        {3, 93}},
    {
        503316491, 63,
        {3, 92}},
    {
        503316490, 63,
        {3, 96}},
    {
        503316489, 63,
        {3, 95}}
};

static const Production xmlscm_prod_106_16[16] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316503, 74,
        {3, 52}},
    {
        503316502, 72,
        {3, 56}},
    {
        503316501, 71,
        {3, 55}},
    {
        503316500, 68,
        {3, 109}},
    {
        503316499, 67,
        {3, 138}},
    {
        503316498, 66,
        {3, 69}},
    {
        503316497, 65,
        {3, 94}},
    {
        503316496, 65,
        {3, 97}},
    {
        503316495, 65,
        {3, 87}},
    {
        503316494, 65,
        {3, 77}},
    {
        503316493, 64,
        {3, 133}},
    {
        503316492, 63,
        {3, 93}},
    {
        503316491, 63,
        {3, 92}},
    {
        503316490, 63,
        {3, 96}},
    {
        503316489, 63,
        {3, 95}}
};

static const Production xmlscm_prod_106_17[16] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316503, 74,
        {3, 52}},
    {
        503316502, 72,
        {3, 56}},
    {
        503316501, 71,
        {3, 55}},
    {
        503316500, 68,
        {3, 109}},
    {
        503316499, 67,
        {3, 138}},
    {
        503316498, 66,
        {3, 69}},
    {
        503316497, 65,
        {3, 94}},
    {
        503316496, 65,
        {3, 97}},
    {
        503316495, 65,
        {3, 87}},
    {
        503316494, 65,
        {3, 77}},
    {
        503316493, 64,
        {3, 133}},
    {
        503316492, 63,
        {3, 93}},
    {
        503316491, 63,
        {3, 92}},
    {
        503316490, 63,
        {3, 96}},
    {
        503316489, 63,
        {3, 95}}
};

static const Production xmlscm_prod_106_18[16] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316503, 74,
        {3, 52}},
    {
        503316502, 72,
        {3, 56}},
    {
        503316501, 71,
        {3, 55}},
    {
        503316500, 68,
        {3, 109}},
    {
        503316499, 67,
        {3, 138}},
    {
        503316498, 66,
        {3, 69}},
    {
        503316497, 65,
        {3, 94}},
    {
        503316496, 65,
        {3, 97}},
    {
        503316495, 65,
        {3, 87}},
    {
        503316494, 65,
        {3, 77}},
    {
        503316493, 64,
        {3, 133}},
    {
        503316492, 63,
        {3, 93}},
    {
        503316491, 63,
        {3, 92}},
    {
        503316490, 63,
        {3, 96}},
    {
        503316489, 63,
        {3, 95}}
};

static const Production xmlscm_prod_106_19[16] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316503, 74,
        {3, 52}},
    {
        503316502, 72,
        {3, 56}},
    {
        503316501, 71,
        {3, 55}},
    {
        503316500, 68,
        {3, 109}},
    {
        503316499, 67,
        {3, 138}},
    {
        503316498, 66,
        {3, 69}},
    {
        503316497, 65,
        {3, 94}},
    {
        503316496, 65,
        {3, 97}},
    {
        503316495, 65,
        {3, 87}},
    {
        503316494, 65,
        {3, 77}},
    {
        503316493, 64,
        {3, 133}},
    {
        503316492, 63,
        {3, 93}},
    {
        503316491, 63,
        {3, 92}},
    {
        503316490, 63,
        {3, 96}},
    {
        503316489, 63,
        {3, 95}}
};

static const Production xmlscm_prod_106_20[16] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316503, 74,
        {3, 52}},
    {
        503316502, 72,
        {3, 56}},
    {
        503316501, 71,
        {3, 55}},
    {
        503316500, 68,
        {3, 109}},
    {
        503316499, 67,
        {3, 138}},
    {
        503316498, 66,
        {3, 69}},
    {
        503316497, 65,
        {3, 94}},
    {
        503316496, 65,
        {3, 97}},
    {
        503316495, 65,
        {3, 87}},
    {
        503316494, 65,
        {3, 77}},
    {
        503316493, 64,
        {3, 133}},
    {
        503316492, 63,
        {3, 93}},
    {
        503316491, 63,
        {3, 92}},
    {
        503316490, 63,
        {3, 96}},
    {
        503316489, 63,
        {3, 95}}
};

static const Production xmlscm_prod_106_21[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316503, 74,
        {3, 52}},
    {
        503316502, 72,
        {3, 56}},
    {
        503316501, 71,
        {3, 55}}
};

static const Production xmlscm_prod_106_22[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316503, 74,
        {3, 52}},
    {
        503316502, 72,
        {3, 56}},
    {
        503316501, 71,
        {3, 55}}
};

static const Production xmlscm_prod_106_23[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_106[24] =
{
    {(Production*) xmlscm_prod_106_0, 2, 4},
    {(Production*) xmlscm_prod_106_1, 24, 5},
    {(Production*) xmlscm_prod_106_2, 23, 3},
    {(Production*) xmlscm_prod_106_3, 21, 1},
    {(Production*) xmlscm_prod_106_4, 4, 1},
    {(Production*) xmlscm_prod_106_5, 4, 1},
    {(Production*) xmlscm_prod_106_6, 4, 1},
    {(Production*) xmlscm_prod_106_7, 4, 1},
    {(Production*) xmlscm_prod_106_8, 16, 1},
    {(Production*) xmlscm_prod_106_9, 16, 1},
    {(Production*) xmlscm_prod_106_10, 16, 1},
    {(Production*) xmlscm_prod_106_11, 16, 1},
    {(Production*) xmlscm_prod_106_12, 16, 1},
    {(Production*) xmlscm_prod_106_13, 16, 1},
    {(Production*) xmlscm_prod_106_14, 16, 1},
    {(Production*) xmlscm_prod_106_15, 16, 1},
    {(Production*) xmlscm_prod_106_16, 16, 1},
    {(Production*) xmlscm_prod_106_17, 16, 1},
    {(Production*) xmlscm_prod_106_18, 16, 1},
    {(Production*) xmlscm_prod_106_19, 16, 1},
    {(Production*) xmlscm_prod_106_20, 16, 1},
    {(Production*) xmlscm_prod_106_21, 4, 1},
    {(Production*) xmlscm_prod_106_22, 4, 1},
    {(Production*) xmlscm_prod_106_23, 1, 1}
};

static const Production xmlscm_prod_107_0[22] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316500, 86,
        {3, 86}},
    {
        503316499, 85,
        {3, 84}},
    {
        503316498, 85,
        {3, 137}},
    {
        503316497, 82,
        {3, 62}},
    {
        503316496, 60,
        {3, 128}},
    {
        503316495, 49,
        {3, 50}},
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544334, 10,
        {0, 29}},
    {
        335544333, 10,
        {0, 26}},
    {
        335544332, 10,
        {0, 22}},
    {
        335544331, 15,
        {0, 19}},
    {
        335544330, 5,
        {0, 17}},
    {
        335544329, 34,
        {0, 15}},
    {
        335544328, 39,
        {0, 13}},
    {
        335544327, 2,
        {0, 11}},
    {
        335544326, 46,
        {0, 10}},
    {
        335544325, 39,
        {0, 9}},
    {
        335544324, 39,
        {0, 7}},
    {
        335544323, 39,
        {0, 5}},
    {
        335544322, 39,
        {0, 3}},
    {
        335544321, 15,
        {0, 0}}
};

static const Production xmlscm_prod_107_1[21] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316500, 86,
        {3, 86}},
    {
        503316499, 85,
        {3, 84}},
    {
        503316498, 85,
        {3, 137}},
    {
        503316497, 82,
        {3, 62}},
    {
        503316496, 60,
        {3, 128}},
    {
        503316495, 49,
        {3, 50}},
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544334, 10,
        {0, 29}},
    {
        335544333, 10,
        {0, 26}},
    {
        335544332, 10,
        {0, 22}},
    {
        335544331, 15,
        {0, 19}},
    {
        335544330, 5,
        {0, 17}},
    {
        335544329, 34,
        {0, 15}},
    {
        335544328, 39,
        {0, 13}},
    {
        335544327, 2,
        {0, 11}},
    {
        335544326, 46,
        {0, 10}},
    {
        335544325, 39,
        {0, 9}},
    {
        335544324, 39,
        {0, 7}},
    {
        335544323, 39,
        {0, 5}},
    {
        335544322, 39,
        {0, 3}}
};

static const Production xmlscm_prod_107_2[20] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316500, 86,
        {3, 86}},
    {
        503316499, 85,
        {3, 84}},
    {
        503316498, 85,
        {3, 137}},
    {
        503316497, 82,
        {3, 62}},
    {
        503316496, 60,
        {3, 128}},
    {
        503316495, 49,
        {3, 50}},
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544334, 10,
        {0, 29}},
    {
        335544333, 10,
        {0, 26}},
    {
        335544332, 10,
        {0, 22}},
    {
        335544331, 15,
        {0, 19}},
    {
        335544330, 5,
        {0, 17}},
    {
        335544329, 34,
        {0, 15}},
    {
        335544328, 39,
        {0, 13}},
    {
        335544327, 2,
        {0, 11}},
    {
        335544326, 46,
        {0, 10}},
    {
        335544325, 39,
        {0, 9}},
    {
        335544324, 39,
        {0, 7}},
    {
        335544323, 39,
        {0, 5}}
};

static const Production xmlscm_prod_107_3[19] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316500, 86,
        {3, 86}},
    {
        503316499, 85,
        {3, 84}},
    {
        503316498, 85,
        {3, 137}},
    {
        503316497, 82,
        {3, 62}},
    {
        503316496, 60,
        {3, 128}},
    {
        503316495, 49,
        {3, 50}},
    {
        369098755, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544334, 10,
        {0, 29}},
    {
        335544333, 10,
        {0, 26}},
    {
        335544332, 10,
        {0, 22}},
    {
        335544331, 15,
        {0, 19}},
    {
        335544330, 5,
        {0, 17}},
    {
        335544329, 34,
        {0, 15}},
    {
        335544328, 39,
        {0, 13}},
    {
        335544327, 2,
        {0, 11}},
    {
        335544326, 46,
        {0, 10}},
    {
        335544325, 39,
        {0, 9}},
    {
        335544324, 39,
        {0, 7}}
};

static const Production xmlscm_prod_107_4[18] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316500, 86,
        {3, 86}},
    {
        503316499, 85,
        {3, 84}},
    {
        503316498, 85,
        {3, 137}},
    {
        503316497, 82,
        {3, 62}},
    {
        503316496, 60,
        {3, 128}},
    {
        503316495, 49,
        {3, 50}},
    {
        369098756, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544334, 10,
        {0, 29}},
    {
        335544333, 10,
        {0, 26}},
    {
        335544332, 10,
        {0, 22}},
    {
        335544331, 15,
        {0, 19}},
    {
        335544330, 5,
        {0, 17}},
    {
        335544329, 34,
        {0, 15}},
    {
        335544328, 39,
        {0, 13}},
    {
        335544327, 2,
        {0, 11}},
    {
        335544326, 46,
        {0, 10}},
    {
        335544325, 39,
        {0, 9}}
};

static const Production xmlscm_prod_107_5[17] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316500, 86,
        {3, 86}},
    {
        503316499, 85,
        {3, 84}},
    {
        503316498, 85,
        {3, 137}},
    {
        503316497, 82,
        {3, 62}},
    {
        503316496, 60,
        {3, 128}},
    {
        503316495, 49,
        {3, 50}},
    {
        369098757, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544334, 10,
        {0, 29}},
    {
        335544333, 10,
        {0, 26}},
    {
        335544332, 10,
        {0, 22}},
    {
        335544331, 15,
        {0, 19}},
    {
        335544330, 5,
        {0, 17}},
    {
        335544329, 34,
        {0, 15}},
    {
        335544328, 39,
        {0, 13}},
    {
        335544327, 2,
        {0, 11}},
    {
        335544326, 46,
        {0, 10}}
};

static const Production xmlscm_prod_107_6[16] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316500, 86,
        {3, 86}},
    {
        503316499, 85,
        {3, 84}},
    {
        503316498, 85,
        {3, 137}},
    {
        503316497, 82,
        {3, 62}},
    {
        503316496, 60,
        {3, 128}},
    {
        503316495, 49,
        {3, 50}},
    {
        369098758, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544334, 10,
        {0, 29}},
    {
        335544333, 10,
        {0, 26}},
    {
        335544332, 10,
        {0, 22}},
    {
        335544331, 15,
        {0, 19}},
    {
        335544330, 5,
        {0, 17}},
    {
        335544329, 34,
        {0, 15}},
    {
        335544328, 39,
        {0, 13}},
    {
        335544327, 2,
        {0, 11}}
};

static const Production xmlscm_prod_107_7[15] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316500, 86,
        {3, 86}},
    {
        503316499, 85,
        {3, 84}},
    {
        503316498, 85,
        {3, 137}},
    {
        503316497, 82,
        {3, 62}},
    {
        503316496, 60,
        {3, 128}},
    {
        503316495, 49,
        {3, 50}},
    {
        369098759, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544334, 10,
        {0, 29}},
    {
        335544333, 10,
        {0, 26}},
    {
        335544332, 10,
        {0, 22}},
    {
        335544331, 15,
        {0, 19}},
    {
        335544330, 5,
        {0, 17}},
    {
        335544329, 34,
        {0, 15}},
    {
        335544328, 39,
        {0, 13}}
};

static const Production xmlscm_prod_107_8[14] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316500, 86,
        {3, 86}},
    {
        503316499, 85,
        {3, 84}},
    {
        503316498, 85,
        {3, 137}},
    {
        503316497, 82,
        {3, 62}},
    {
        503316496, 60,
        {3, 128}},
    {
        503316495, 49,
        {3, 50}},
    {
        369098760, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544334, 10,
        {0, 29}},
    {
        335544333, 10,
        {0, 26}},
    {
        335544332, 10,
        {0, 22}},
    {
        335544331, 15,
        {0, 19}},
    {
        335544330, 5,
        {0, 17}},
    {
        335544329, 34,
        {0, 15}}
};

static const Production xmlscm_prod_107_9[13] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316500, 86,
        {3, 86}},
    {
        503316499, 85,
        {3, 84}},
    {
        503316498, 85,
        {3, 137}},
    {
        503316497, 82,
        {3, 62}},
    {
        503316496, 60,
        {3, 128}},
    {
        503316495, 49,
        {3, 50}},
    {
        369098761, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544334, 10,
        {0, 29}},
    {
        335544333, 10,
        {0, 26}},
    {
        335544332, 10,
        {0, 22}},
    {
        335544331, 15,
        {0, 19}},
    {
        335544330, 5,
        {0, 17}}
};

static const Production xmlscm_prod_107_10[12] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316500, 86,
        {3, 86}},
    {
        503316499, 85,
        {3, 84}},
    {
        503316498, 85,
        {3, 137}},
    {
        503316497, 82,
        {3, 62}},
    {
        503316496, 60,
        {3, 128}},
    {
        503316495, 49,
        {3, 50}},
    {
        369098762, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544334, 10,
        {0, 29}},
    {
        335544333, 10,
        {0, 26}},
    {
        335544332, 10,
        {0, 22}},
    {
        335544331, 15,
        {0, 19}}
};

static const Production xmlscm_prod_107_11[11] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316500, 86,
        {3, 86}},
    {
        503316499, 85,
        {3, 84}},
    {
        503316498, 85,
        {3, 137}},
    {
        503316497, 82,
        {3, 62}},
    {
        503316496, 60,
        {3, 128}},
    {
        503316495, 49,
        {3, 50}},
    {
        369098763, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544334, 10,
        {0, 29}},
    {
        335544333, 10,
        {0, 26}},
    {
        335544332, 10,
        {0, 22}}
};

static const Production xmlscm_prod_107_12[10] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316500, 86,
        {3, 86}},
    {
        503316499, 85,
        {3, 84}},
    {
        503316498, 85,
        {3, 137}},
    {
        503316497, 82,
        {3, 62}},
    {
        503316496, 60,
        {3, 128}},
    {
        503316495, 49,
        {3, 50}},
    {
        369098764, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544334, 10,
        {0, 29}},
    {
        335544333, 10,
        {0, 26}}
};

static const Production xmlscm_prod_107_13[9] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316500, 86,
        {3, 86}},
    {
        503316499, 85,
        {3, 84}},
    {
        503316498, 85,
        {3, 137}},
    {
        503316497, 82,
        {3, 62}},
    {
        503316496, 60,
        {3, 128}},
    {
        503316495, 49,
        {3, 50}},
    {
        369098765, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544334, 10,
        {0, 29}}
};

static const Production xmlscm_prod_107_14[8] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316500, 86,
        {3, 86}},
    {
        503316499, 85,
        {3, 84}},
    {
        503316498, 85,
        {3, 137}},
    {
        503316497, 82,
        {3, 62}},
    {
        503316496, 60,
        {3, 128}},
    {
        503316495, 49,
        {3, 50}},
    {
        369098766, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_107_15[6] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316500, 86,
        {3, 86}},
    {
        503316499, 85,
        {3, 84}},
    {
        503316498, 85,
        {3, 137}},
    {
        503316497, 82,
        {3, 62}},
    {
        503316496, 60,
        {3, 128}}
};

static const Production xmlscm_prod_107_16[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316500, 86,
        {3, 86}},
    {
        503316499, 85,
        {3, 84}},
    {
        503316498, 85,
        {3, 137}}
};

static const Production xmlscm_prod_107_17[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316500, 86,
        {3, 86}},
    {
        503316499, 85,
        {3, 84}},
    {
        503316498, 85,
        {3, 137}}
};

static const Production xmlscm_prod_107_18[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316500, 86,
        {3, 86}},
    {
        503316499, 85,
        {3, 84}},
    {
        503316498, 85,
        {3, 137}}
};

static const Production xmlscm_prod_107_19[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316500, 86,
        {3, 86}},
    {
        503316499, 85,
        {3, 84}},
    {
        503316498, 85,
        {3, 137}}
};

static const Production xmlscm_prod_107_20[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316500, 86,
        {3, 86}},
    {
        503316499, 85,
        {3, 84}},
    {
        503316498, 85,
        {3, 137}}
};

static const GrammarRule xmlscm_rule_107[21] =
{
    {(Production*) xmlscm_prod_107_0, 22, 31},
    {(Production*) xmlscm_prod_107_1, 21, 29},
    {(Production*) xmlscm_prod_107_2, 20, 27},
    {(Production*) xmlscm_prod_107_3, 19, 25},
    {(Production*) xmlscm_prod_107_4, 18, 23},
    {(Production*) xmlscm_prod_107_5, 17, 21},
    {(Production*) xmlscm_prod_107_6, 16, 19},
    {(Production*) xmlscm_prod_107_7, 15, 17},
    {(Production*) xmlscm_prod_107_8, 14, 15},
    {(Production*) xmlscm_prod_107_9, 13, 13},
    {(Production*) xmlscm_prod_107_10, 12, 11},
    {(Production*) xmlscm_prod_107_11, 11, 9},
    {(Production*) xmlscm_prod_107_12, 10, 7},
    {(Production*) xmlscm_prod_107_13, 9, 5},
    {(Production*) xmlscm_prod_107_14, 8, 3},
    {(Production*) xmlscm_prod_107_15, 6, 1},
    {(Production*) xmlscm_prod_107_16, 4, 1},
    {(Production*) xmlscm_prod_107_17, 4, 1},
    {(Production*) xmlscm_prod_107_18, 4, 1},
    {(Production*) xmlscm_prod_107_19, 4, 1},
    {(Production*) xmlscm_prod_107_20, 4, 1}
};

static const Production xmlscm_prod_108_0[14] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316492, 90,
        {3, 51}},
    {
        503316491, 89,
        {3, 120}},
    {
        503316490, 89,
        {3, 59}},
    {
        503316489, 81,
        {3, 46}},
    {
        503316488, 79,
        {3, 79}},
    {
        503316487, 88,
        {3, 68}},
    {
        503316486, 49,
        {3, 50}},
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544325, 10,
        {0, 22}},
    {
        335544324, 5,
        {0, 17}},
    {
        335544323, 34,
        {0, 15}},
    {
        335544322, 39,
        {0, 13}},
    {
        335544321, 2,
        {0, 11}}
};

static const Production xmlscm_prod_108_1[13] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316492, 90,
        {3, 51}},
    {
        503316491, 89,
        {3, 120}},
    {
        503316490, 89,
        {3, 59}},
    {
        503316489, 81,
        {3, 46}},
    {
        503316488, 79,
        {3, 79}},
    {
        503316487, 88,
        {3, 68}},
    {
        503316486, 49,
        {3, 50}},
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544325, 10,
        {0, 22}},
    {
        335544324, 5,
        {0, 17}},
    {
        335544323, 34,
        {0, 15}},
    {
        335544322, 39,
        {0, 13}}
};

static const Production xmlscm_prod_108_2[12] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316492, 90,
        {3, 51}},
    {
        503316491, 89,
        {3, 120}},
    {
        503316490, 89,
        {3, 59}},
    {
        503316489, 81,
        {3, 46}},
    {
        503316488, 79,
        {3, 79}},
    {
        503316487, 88,
        {3, 68}},
    {
        503316486, 49,
        {3, 50}},
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544325, 10,
        {0, 22}},
    {
        335544324, 5,
        {0, 17}},
    {
        335544323, 34,
        {0, 15}}
};

static const Production xmlscm_prod_108_3[11] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316492, 90,
        {3, 51}},
    {
        503316491, 89,
        {3, 120}},
    {
        503316490, 89,
        {3, 59}},
    {
        503316489, 81,
        {3, 46}},
    {
        503316488, 79,
        {3, 79}},
    {
        503316487, 88,
        {3, 68}},
    {
        503316486, 49,
        {3, 50}},
    {
        369098755, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544325, 10,
        {0, 22}},
    {
        335544324, 5,
        {0, 17}}
};

static const Production xmlscm_prod_108_4[10] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316492, 90,
        {3, 51}},
    {
        503316491, 89,
        {3, 120}},
    {
        503316490, 89,
        {3, 59}},
    {
        503316489, 81,
        {3, 46}},
    {
        503316488, 79,
        {3, 79}},
    {
        503316487, 88,
        {3, 68}},
    {
        503316486, 49,
        {3, 50}},
    {
        369098756, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544325, 10,
        {0, 22}}
};

static const Production xmlscm_prod_108_5[9] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316492, 90,
        {3, 51}},
    {
        503316491, 89,
        {3, 120}},
    {
        503316490, 89,
        {3, 59}},
    {
        503316489, 81,
        {3, 46}},
    {
        503316488, 79,
        {3, 79}},
    {
        503316487, 88,
        {3, 68}},
    {
        503316486, 49,
        {3, 50}},
    {
        369098757, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_108_6[7] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316492, 90,
        {3, 51}},
    {
        503316491, 89,
        {3, 120}},
    {
        503316490, 89,
        {3, 59}},
    {
        503316489, 81,
        {3, 46}},
    {
        503316488, 79,
        {3, 79}},
    {
        503316487, 88,
        {3, 68}}
};

static const Production xmlscm_prod_108_7[7] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316492, 90,
        {3, 51}},
    {
        503316491, 89,
        {3, 120}},
    {
        503316490, 89,
        {3, 59}},
    {
        503316489, 81,
        {3, 46}},
    {
        503316488, 79,
        {3, 79}},
    {
        503316487, 88,
        {3, 68}}
};

static const Production xmlscm_prod_108_8[7] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316492, 90,
        {3, 51}},
    {
        503316491, 89,
        {3, 120}},
    {
        503316490, 89,
        {3, 59}},
    {
        503316489, 81,
        {3, 46}},
    {
        503316488, 79,
        {3, 79}},
    {
        503316487, 88,
        {3, 68}}
};

static const Production xmlscm_prod_108_9[7] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316492, 90,
        {3, 51}},
    {
        503316491, 89,
        {3, 120}},
    {
        503316490, 89,
        {3, 59}},
    {
        503316489, 81,
        {3, 46}},
    {
        503316488, 79,
        {3, 79}},
    {
        503316487, 88,
        {3, 68}}
};

static const Production xmlscm_prod_108_10[7] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316492, 90,
        {3, 51}},
    {
        503316491, 89,
        {3, 120}},
    {
        503316490, 89,
        {3, 59}},
    {
        503316489, 81,
        {3, 46}},
    {
        503316488, 79,
        {3, 79}},
    {
        503316487, 88,
        {3, 68}}
};

static const Production xmlscm_prod_108_11[7] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316492, 90,
        {3, 51}},
    {
        503316491, 89,
        {3, 120}},
    {
        503316490, 89,
        {3, 59}},
    {
        503316489, 81,
        {3, 46}},
    {
        503316488, 79,
        {3, 79}},
    {
        503316487, 88,
        {3, 68}}
};

static const Production xmlscm_prod_108_12[7] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316492, 90,
        {3, 51}},
    {
        503316491, 89,
        {3, 120}},
    {
        503316490, 89,
        {3, 59}},
    {
        503316489, 81,
        {3, 46}},
    {
        503316488, 79,
        {3, 79}},
    {
        503316487, 88,
        {3, 68}}
};

static const GrammarRule xmlscm_rule_108[13] =
{
    {(Production*) xmlscm_prod_108_0, 14, 13},
    {(Production*) xmlscm_prod_108_1, 13, 11},
    {(Production*) xmlscm_prod_108_2, 12, 9},
    {(Production*) xmlscm_prod_108_3, 11, 7},
    {(Production*) xmlscm_prod_108_4, 10, 5},
    {(Production*) xmlscm_prod_108_5, 9, 3},
    {(Production*) xmlscm_prod_108_6, 7, 1},
    {(Production*) xmlscm_prod_108_7, 7, 1},
    {(Production*) xmlscm_prod_108_8, 7, 1},
    {(Production*) xmlscm_prod_108_9, 7, 1},
    {(Production*) xmlscm_prod_108_10, 7, 1},
    {(Production*) xmlscm_prod_108_11, 7, 1},
    {(Production*) xmlscm_prod_108_12, 7, 1}
};

static const Production xmlscm_prod_109_0[11] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316489, 89,
        {3, 120}},
    {
        503316488, 89,
        {3, 59}},
    {
        503316487, 81,
        {3, 46}},
    {
        503316486, 49,
        {3, 50}},
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544325, 10,
        {0, 22}},
    {
        335544324, 5,
        {0, 17}},
    {
        335544323, 34,
        {0, 15}},
    {
        335544322, 39,
        {0, 13}},
    {
        335544321, 2,
        {0, 11}}
};

static const Production xmlscm_prod_109_1[10] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316489, 89,
        {3, 120}},
    {
        503316488, 89,
        {3, 59}},
    {
        503316487, 81,
        {3, 46}},
    {
        503316486, 49,
        {3, 50}},
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544325, 10,
        {0, 22}},
    {
        335544324, 5,
        {0, 17}},
    {
        335544323, 34,
        {0, 15}},
    {
        335544322, 39,
        {0, 13}}
};

static const Production xmlscm_prod_109_2[9] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316489, 89,
        {3, 120}},
    {
        503316488, 89,
        {3, 59}},
    {
        503316487, 81,
        {3, 46}},
    {
        503316486, 49,
        {3, 50}},
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544325, 10,
        {0, 22}},
    {
        335544324, 5,
        {0, 17}},
    {
        335544323, 34,
        {0, 15}}
};

static const Production xmlscm_prod_109_3[8] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316489, 89,
        {3, 120}},
    {
        503316488, 89,
        {3, 59}},
    {
        503316487, 81,
        {3, 46}},
    {
        503316486, 49,
        {3, 50}},
    {
        369098755, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544325, 10,
        {0, 22}},
    {
        335544324, 5,
        {0, 17}}
};

static const Production xmlscm_prod_109_4[7] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316489, 89,
        {3, 120}},
    {
        503316488, 89,
        {3, 59}},
    {
        503316487, 81,
        {3, 46}},
    {
        503316486, 49,
        {3, 50}},
    {
        369098756, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544325, 10,
        {0, 22}}
};

static const Production xmlscm_prod_109_5[6] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316489, 89,
        {3, 120}},
    {
        503316488, 89,
        {3, 59}},
    {
        503316487, 81,
        {3, 46}},
    {
        503316486, 49,
        {3, 50}},
    {
        369098757, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_109_6[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316489, 89,
        {3, 120}},
    {
        503316488, 89,
        {3, 59}},
    {
        503316487, 81,
        {3, 46}}
};

static const Production xmlscm_prod_109_7[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_109_8[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_109_9[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_109[10] =
{
    {(Production*) xmlscm_prod_109_0, 11, 13},
    {(Production*) xmlscm_prod_109_1, 10, 11},
    {(Production*) xmlscm_prod_109_2, 9, 9},
    {(Production*) xmlscm_prod_109_3, 8, 7},
    {(Production*) xmlscm_prod_109_4, 7, 5},
    {(Production*) xmlscm_prod_109_5, 6, 3},
    {(Production*) xmlscm_prod_109_6, 4, 1},
    {(Production*) xmlscm_prod_109_7, 1, 1},
    {(Production*) xmlscm_prod_109_8, 1, 1},
    {(Production*) xmlscm_prod_109_9, 1, 1}
};

static const Production xmlscm_prod_110_0[9] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316487, 74,
        {3, 52}},
    {
        503316486, 72,
        {3, 56}},
    {
        503316485, 71,
        {3, 55}},
    {
        503316484, 49,
        {3, 50}},
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544323, 10,
        {0, 22}},
    {
        335544322, 5,
        {0, 17}},
    {
        335544321, 2,
        {0, 11}}
};

static const Production xmlscm_prod_110_1[8] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316487, 74,
        {3, 52}},
    {
        503316486, 72,
        {3, 56}},
    {
        503316485, 71,
        {3, 55}},
    {
        503316484, 49,
        {3, 50}},
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544323, 10,
        {0, 22}},
    {
        335544322, 5,
        {0, 17}}
};

static const Production xmlscm_prod_110_2[7] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316487, 74,
        {3, 52}},
    {
        503316486, 72,
        {3, 56}},
    {
        503316485, 71,
        {3, 55}},
    {
        503316484, 49,
        {3, 50}},
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544323, 10,
        {0, 22}}
};

static const Production xmlscm_prod_110_3[6] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316487, 74,
        {3, 52}},
    {
        503316486, 72,
        {3, 56}},
    {
        503316485, 71,
        {3, 55}},
    {
        503316484, 49,
        {3, 50}},
    {
        369098755, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_110_4[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316487, 74,
        {3, 52}},
    {
        503316486, 72,
        {3, 56}},
    {
        503316485, 71,
        {3, 55}}
};

static const Production xmlscm_prod_110_5[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316487, 74,
        {3, 52}},
    {
        503316486, 72,
        {3, 56}},
    {
        503316485, 71,
        {3, 55}}
};

static const Production xmlscm_prod_110_6[4] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316487, 74,
        {3, 52}},
    {
        503316486, 72,
        {3, 56}},
    {
        503316485, 71,
        {3, 55}}
};

static const Production xmlscm_prod_110_7[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_110[8] =
{
    {(Production*) xmlscm_prod_110_0, 9, 9},
    {(Production*) xmlscm_prod_110_1, 8, 7},
    {(Production*) xmlscm_prod_110_2, 7, 5},
    {(Production*) xmlscm_prod_110_3, 6, 3},
    {(Production*) xmlscm_prod_110_4, 4, 1},
    {(Production*) xmlscm_prod_110_5, 4, 1},
    {(Production*) xmlscm_prod_110_6, 4, 1},
    {(Production*) xmlscm_prod_110_7, 1, 1}
};

static const Production xmlscm_prod_111_0[8] =
{
    {
        503316487, 62,
        {3, 136}},
    {
        503316486, 61,
        {3, 88}},
    {
        503316485, 59,
        {3, 115}},
    {
        503316484, 49,
        {3, 50}},
    {
        369098752, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544323, 5,
        {0, 17}},
    {
        335544322, 2,
        {0, 11}},
    {
        335544321, 39,
        {0, 7}}
};

static const Production xmlscm_prod_111_1[7] =
{
    {
        503316487, 62,
        {3, 136}},
    {
        503316486, 61,
        {3, 88}},
    {
        503316485, 59,
        {3, 115}},
    {
        503316484, 49,
        {3, 50}},
    {
        369098753, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544323, 5,
        {0, 17}},
    {
        335544322, 2,
        {0, 11}}
};

static const Production xmlscm_prod_111_2[6] =
{
    {
        503316487, 62,
        {3, 136}},
    {
        503316486, 61,
        {3, 88}},
    {
        503316485, 59,
        {3, 115}},
    {
        503316484, 49,
        {3, 50}},
    {
        369098754, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        335544323, 5,
        {0, 17}}
};

static const Production xmlscm_prod_111_3[5] =
{
    {
        503316487, 62,
        {3, 136}},
    {
        503316486, 61,
        {3, 88}},
    {
        503316485, 59,
        {3, 115}},
    {
        503316484, 49,
        {3, 50}},
    {
        369098755, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_111_4[3] =
{
    {
        503316487, 62,
        {3, 136}},
    {
        503316486, 61,
        {3, 88}},
    {
        503316485, 59,
        {3, 115}}
};

static const Production xmlscm_prod_111_5[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_111_6[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const Production xmlscm_prod_111_7[1] =
{
    {
        687865855, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_rule_111[8] =
{
    {(Production*) xmlscm_prod_111_0, 8, 8},
    {(Production*) xmlscm_prod_111_1, 7, 6},
    {(Production*) xmlscm_prod_111_2, 6, 4},
    {(Production*) xmlscm_prod_111_3, 5, 2},
    {(Production*) xmlscm_prod_111_4, 3, 0},
    {(Production*) xmlscm_prod_111_5, 1, 1},
    {(Production*) xmlscm_prod_111_6, 1, 1},
    {(Production*) xmlscm_prod_111_7, 1, 1}
};

static CONST EXIGrammar xmlscm_grammarTable[117] =
{
   {(GrammarRule*) xmlscm_rule_0, 33554432, 2},
   {(GrammarRule*) xmlscm_rule_1, 570425344, 2},
   {(GrammarRule*) xmlscm_rule_2, 33554432, 2},
   {(GrammarRule*) xmlscm_rule_3, 570425344, 2},
   {(GrammarRule*) xmlscm_rule_4, 33554432, 2},
   {(GrammarRule*) xmlscm_rule_5, 570425344, 2},
   {(GrammarRule*) xmlscm_rule_6, 570425344, 2},
   {(GrammarRule*) xmlscm_rule_7, 33554432, 2},
   {(GrammarRule*) xmlscm_rule_8, 33554432, 2},
   {(GrammarRule*) xmlscm_rule_9, 570425344, 2},
   {(GrammarRule*) xmlscm_rule_10, 33554432, 2},
   {(GrammarRule*) xmlscm_rule_11, 570425344, 2},
   {(GrammarRule*) xmlscm_rule_12, 570425345, 2},
   {(GrammarRule*) xmlscm_rule_13, 33554432, 2},
   {(GrammarRule*) xmlscm_rule_14, 33554432, 2},
   {(GrammarRule*) xmlscm_rule_15, 33554432, 2},
   {(GrammarRule*) xmlscm_rule_16, 33554432, 2},
   {(GrammarRule*) xmlscm_rule_17, 33554432, 2},
   {(GrammarRule*) xmlscm_rule_18, 33554432, 2},
   {(GrammarRule*) xmlscm_rule_19, 570425344, 2},
   {(GrammarRule*) xmlscm_rule_20, 33554432, 2},
   {(GrammarRule*) xmlscm_rule_21, 33554432, 2},
   {(GrammarRule*) xmlscm_rule_22, 33554432, 2},
   {(GrammarRule*) xmlscm_rule_23, 33554432, 2},
   {(GrammarRule*) xmlscm_rule_24, 33554432, 2},
   {(GrammarRule*) xmlscm_rule_25, 33554432, 2},
   {(GrammarRule*) xmlscm_rule_26, 33554432, 2},
   {(GrammarRule*) xmlscm_rule_27, 33554432, 2},
   {(GrammarRule*) xmlscm_rule_28, 33554432, 2},
   {(GrammarRule*) xmlscm_rule_29, 570425344, 2},
   {(GrammarRule*) xmlscm_rule_30, 570425344, 2},
   {(GrammarRule*) xmlscm_rule_31, 33554432, 2},
   {(GrammarRule*) xmlscm_rule_32, 570425344, 2},
   {(GrammarRule*) xmlscm_rule_33, 33554432, 2},
   {(GrammarRule*) xmlscm_rule_34, 570425344, 2},
   {(GrammarRule*) xmlscm_rule_35, 570425344, 2},
   {(GrammarRule*) xmlscm_rule_36, 570425344, 2},
   {(GrammarRule*) xmlscm_rule_37, 33554432, 2},
   {(GrammarRule*) xmlscm_rule_38, 570425344, 2},
   {(GrammarRule*) xmlscm_rule_39, 570425344, 2},
   {(GrammarRule*) xmlscm_rule_40, 33554432, 2},
   {(GrammarRule*) xmlscm_rule_41, 570425344, 2},
   {(GrammarRule*) xmlscm_rule_42, 33554432, 2},
   {(GrammarRule*) xmlscm_rule_43, 570425344, 2},
   {(GrammarRule*) xmlscm_rule_44, 570425344, 2},
   {(GrammarRule*) xmlscm_rule_45, 570425344, 2},
   {(GrammarRule*) xmlscm_rule_46, 1644167168, 1},
   {(GrammarRule*) xmlscm_rule_47, 1107296257, 3},
   {(GrammarRule*) xmlscm_rule_48, 1107296258, 4},
   {(GrammarRule*) xmlscm_rule_49, 1107296257, 4},
   {(GrammarRule*) xmlscm_rule_50, 1644167169, 3},
   {(GrammarRule*) xmlscm_rule_51, 1107296256, 2},
   {(GrammarRule*) xmlscm_rule_52, 1644167168, 2},
   {(GrammarRule*) xmlscm_rule_53, 1107296256, 2},
   {(GrammarRule*) xmlscm_rule_54, 1644167168, 2},
   {(GrammarRule*) xmlscm_rule_55, 1107296256, 2},
   {(GrammarRule*) xmlscm_rule_56, 1644167168, 2},
   {(GrammarRule*) xmlscm_rule_57, 1107296258, 4},
   {(GrammarRule*) xmlscm_rule_58, 1107296259, 5},
   {(GrammarRule*) xmlscm_rule_59, 1107296258, 17},
   {(GrammarRule*) xmlscm_rule_60, 1107296257, 6},
   {(GrammarRule*) xmlscm_rule_61, 1107296258, 5},
   {(GrammarRule*) xmlscm_rule_62, 1107296258, 5},
   {(GrammarRule*) xmlscm_rule_63, 1644167171, 5},
   {(GrammarRule*) xmlscm_rule_64, 1107296259, 5},
   {(GrammarRule*) xmlscm_rule_65, 1107296259, 5},
   {(GrammarRule*) xmlscm_rule_66, 1107296258, 4},
   {(GrammarRule*) xmlscm_rule_67, 1107296259, 5},
   {(GrammarRule*) xmlscm_rule_68, 1107296258, 4},
   {(GrammarRule*) xmlscm_rule_69, 1644167168, 2},
   {(GrammarRule*) xmlscm_rule_70, 1107296259, 8},
   {(GrammarRule*) xmlscm_rule_71, 1644167176, 11},
   {(GrammarRule*) xmlscm_rule_72, 1107296258, 4},
   {(GrammarRule*) xmlscm_rule_73, 1644167168, 2},
   {(GrammarRule*) xmlscm_rule_74, 1107296259, 5},
   {(GrammarRule*) xmlscm_rule_75, 1107296258, 20},
   {(GrammarRule*) xmlscm_rule_76, 1107296258, 7},
   {(GrammarRule*) xmlscm_rule_77, 1107296257, 5},
   {(GrammarRule*) xmlscm_rule_78, 1644167168, 2},
   {(GrammarRule*) xmlscm_rule_79, 1107296260, 6},
   {(GrammarRule*) xmlscm_rule_80, 1107296258, 6},
   {(GrammarRule*) xmlscm_rule_81, 1107296259, 6},
   {(GrammarRule*) xmlscm_rule_82, 1107296258, 13},
   {(GrammarRule*) xmlscm_rule_83, 1107296258, 4},
   {(GrammarRule*) xmlscm_rule_84, 1107296258, 4},
   {(GrammarRule*) xmlscm_rule_85, 1107296258, 7},
   {(GrammarRule*) xmlscm_rule_86, 1107296259, 8},
   {(GrammarRule*) xmlscm_rule_87, 1644167168, 2},
   {(GrammarRule*) xmlscm_rule_88, 1644167179, 18},
   {(GrammarRule*) xmlscm_rule_89, 1644167171, 10},
   {(GrammarRule*) xmlscm_rule_90, 1107296261, 7},
   {(GrammarRule*) xmlscm_rule_91, 1107296267, 18},
   {(GrammarRule*) xmlscm_rule_92, 1107296258, 11},
   {(GrammarRule*) xmlscm_rule_93, 1644167170, 11},
   {(GrammarRule*) xmlscm_rule_94, 1107296262, 17},
   {(GrammarRule*) xmlscm_rule_95, 1107296257, 4},
   {(GrammarRule*) xmlscm_rule_96, 1107296257, 8},
   {(GrammarRule*) xmlscm_rule_97, 1107296258, 7},
   {(GrammarRule*) xmlscm_rule_98, 1107296258, 7},
   {(GrammarRule*) xmlscm_rule_99, 1107296258, 8},
   {(GrammarRule*) xmlscm_rule_100, 1107296266, 17},
   {(GrammarRule*) xmlscm_rule_101, 1107296261, 8},
   {(GrammarRule*) xmlscm_rule_102, 1107296256, 2},
   {(GrammarRule*) xmlscm_rule_103, 1107296260, 6},
   {(GrammarRule*) xmlscm_rule_104, 1107296264, 21},
   {(GrammarRule*) xmlscm_rule_105, 1644167174, 17},
   {(GrammarRule*) xmlscm_rule_106, 1644167170, 24},
   {(GrammarRule*) xmlscm_rule_107, 1644167182, 21},
   {(GrammarRule*) xmlscm_rule_108, 1644167173, 13},
   {(GrammarRule*) xmlscm_rule_109, 1644167173, 10},
   {(GrammarRule*) xmlscm_rule_110, 1644167171, 8},
   {(GrammarRule*) xmlscm_rule_111, 1644167171, 8},
   {NULL, 0, 0},
   {NULL, 0, 0},
   {NULL, 0, 0},
   {NULL, 0, 0},
   {NULL, 0, 0},
};

static CONST String xmlscm_PfxEntry_0[2] =
{
    {NULL, 0},
    {NULL, 0}
};

static CONST LnEntry xmlscm_LnEntry_0[34] =
{
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_0_0, 8},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_0_1, 20},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_0_2, 4},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_0_3, 5},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_0_4, 12},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_0_5, 7},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_0_6, 18},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_0_7, 5},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_0_8, 12},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_0_9, 5},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_0_10, 4},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_0_11, 2},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_0_12, 8},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_0_13, 9},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_0_14, 11},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_0_15, 9},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_0_16, 5},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_0_17, 4},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_0_18, 9},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_0_19, 8},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_0_20, 15},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_0_21, 6},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_0_22, 3},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_0_23, 5},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_0_24, 14},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_0_25, 6},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_0_26, 17},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_0_27, 6},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_0_28, 15},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_0_29, 4},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_0_30, 3},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_0_31, 5},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_0_32, 7},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_0_33, 5},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    }
};

static CONST String xmlscm_PfxEntry_1[2] =
{
    {(CharType*) xmlscm_PFX_1_0, 3},
    {NULL, 0}
};

static CONST LnEntry xmlscm_LnEntry_1[5] =
{
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_1_0, 4},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_1_1, 2},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_1_2, 4},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_1_3, 5},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_1_4, 12},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    }
};

static CONST String xmlscm_PfxEntry_2[2] =
{
    {(CharType*) xmlscm_PFX_2_0, 3},
    {NULL, 0}
};

static CONST LnEntry xmlscm_LnEntry_2[2] =
{
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_2_0, 3},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_2_1, 4},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    }
};

static CONST LnEntry xmlscm_LnEntry_3[140] =
{
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_0, 8},
        INDEX_MAX, 0, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_1, 6},
        INDEX_MAX, 1, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_2, 2},
        INDEX_MAX, 2, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_3, 5},
        INDEX_MAX, 3, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_4, 6},
        INDEX_MAX, 4, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_5, 6},
        INDEX_MAX, 5, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_6, 7},
        INDEX_MAX, 6, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_7, 8},
        INDEX_MAX, 7, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_8, 8},
        INDEX_MAX, 8, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_9, 4},
        INDEX_MAX, 9, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_10, 5},
        INDEX_MAX, 10, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_11, 13},
        INDEX_MAX, 11, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_12, 7},
        INDEX_MAX, 12, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_13, 6},
        INDEX_MAX, 13, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_14, 12},
        INDEX_MAX, 14, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_15, 7},
        INDEX_MAX, 15, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_16, 4},
        INDEX_MAX, 16, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_17, 4},
        INDEX_MAX, 17, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_18, 8},
        INDEX_MAX, 18, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_19, 7},
        INDEX_MAX, 19, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_20, 6},
        INDEX_MAX, 20, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_21, 8},
        INDEX_MAX, 21, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_22, 5},
        INDEX_MAX, 22, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_23, 4},
        INDEX_MAX, 23, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_24, 6},
        INDEX_MAX, 24, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_25, 9},
        INDEX_MAX, 25, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_26, 5},
        INDEX_MAX, 26, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_27, 10},
        INDEX_MAX, 27, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_28, 9},
        INDEX_MAX, 28, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_29, 3},
        INDEX_MAX, 29, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_30, 7},
        INDEX_MAX, 30, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_31, 8},
        INDEX_MAX, 31, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_32, 4},
        INDEX_MAX, 32, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_33, 15},
        INDEX_MAX, 33, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_34, 18},
        INDEX_MAX, 34, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_35, 18},
        INDEX_MAX, 35, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_36, 16},
        INDEX_MAX, 36, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_37, 15},
        INDEX_MAX, 37, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_38, 5},
        INDEX_MAX, 38, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_39, 6},
        INDEX_MAX, 39, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_40, 4},
        INDEX_MAX, 40, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_41, 5},
        INDEX_MAX, 41, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_42, 12},
        INDEX_MAX, 42, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_43, 11},
        INDEX_MAX, 43, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_44, 12},
        INDEX_MAX, 44, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_45, 13},
        INDEX_MAX, 45, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_46, 3},
        81, 81, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_47, 8},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_48, 6},
        INDEX_MAX, 78, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_49, 9},
        INDEX_MAX, 50, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_50, 10},
        49, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_51, 3},
        90, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_52, 12},
        74, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_53, 7},
        47, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_54, 9},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_55, 9},
        101, 71, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_56, 14},
        98, 110, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_57, 17},
        INDEX_MAX, 72, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_58, 8},
        INDEX_MAX, 87, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_59, 6},
        89, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_60, 14},
        80, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_61, 22},
        INDEX_MAX, 92, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_62, 11},
        94, 105, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_63, 16},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_64, 6},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_65, 17},
        INDEX_MAX, 52, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_66, 13},
        INDEX_MAX, 54, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_67, 13},
        48, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_68, 7},
        100, 107, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_69, 11},
        66, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_70, 13},
        INDEX_MAX, 89, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_71, 9},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_72, 13},
        INDEX_MAX, 93, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_73, 5},
        INDEX_MAX, 63, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_74, 6},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_75, 5},
        84, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_76, 10},
        INDEX_MAX, 51, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_77, 14},
        65, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_78, 17},
        INDEX_MAX, 56, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_79, 5},
        97, 108, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_80, 8},
        INDEX_MAX, 79, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_81, 18},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_82, 6},
        58, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_83, 7},
        57, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_84, 3},
        85, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_85, 7},
        INDEX_MAX, 85, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_86, 6},
        86, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_87, 6},
        65, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_88, 4},
        61, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_89, 16},
        INDEX_MAX, 82, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_90, 12},
        INDEX_MAX, 88, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_91, 15},
        INDEX_MAX, 60, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_92, 12},
        63, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_93, 12},
        63, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_94, 9},
        65, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_95, 12},
        63, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_96, 12},
        63, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_97, 9},
        65, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_98, 19},
        INDEX_MAX, 98, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_99, 10},
        INDEX_MAX, 97, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_100, 13},
        INDEX_MAX, 73, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_101, 12},
        INDEX_MAX, 91, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_102, 14},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_103, 12},
        INDEX_MAX, 66, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_104, 8},
        103, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_105, 8},
        INDEX_MAX, 65, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_106, 6},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_107, 9},
        INDEX_MAX, 46, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_108, 8},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_109, 7},
        68, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_110, 6},
        INDEX_MAX, 102, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_111, 9},
        INDEX_MAX, 109, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_112, 11},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_113, 8},
        99, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_114, 24},
        INDEX_MAX, 53, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_115, 11},
        59, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_116, 15},
        INDEX_MAX, 106, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_117, 6},
        104, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_118, 9},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_119, 8},
        83, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_120, 8},
        89, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_121, 13},
        77, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_122, 16},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_123, 19},
        INDEX_MAX, 69, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_124, 19},
        INDEX_MAX, 96, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_125, 19},
        INDEX_MAX, 76, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_126, 22},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_127, 21},
        INDEX_MAX, 75, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_128, 10},
        70, 111, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_129, 17},
        INDEX_MAX, 101, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_130, 19},
        INDEX_MAX, 94, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_131, 15},
        INDEX_MAX, 100, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_132, 18},
        INDEX_MAX, 70, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_133, 11},
        64, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_134, 15},
        INDEX_MAX, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_135, 21},
        INDEX_MAX, 55, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_136, 5},
        62, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_137, 6},
        85, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_138, 10},
        67, INDEX_MAX, INDEX_MAX
    },
    {
#if VALUE_CROSSTABLE_USE
         NULL,
#endif
        {(CharType*) xmlscm_LN_3_139, 8},
        INDEX_MAX, 74, INDEX_MAX
    }
};

static CONST UriEntry xmlscm_uriEntry[14] =
{
    {
        {{sizeof(LnEntry), 34, 34}, xmlscm_LnEntry_0, 34},
        {{sizeof(String), 1, 2}, xmlscm_PfxEntry_0, 1},
        {NULL, 0}
    },
    {
        {{sizeof(LnEntry), 5, 5}, xmlscm_LnEntry_1, 5},
        {{sizeof(String), 1, 2}, xmlscm_PfxEntry_1, 1},
        {(CharType*) xmlscm_URI_1, 36}
    },
    {
        {{sizeof(LnEntry), 2, 2}, xmlscm_LnEntry_2, 2},
        {{sizeof(String), 1, 2}, xmlscm_PfxEntry_2, 1},
        {(CharType*) xmlscm_URI_2, 41}
    },
    {
        {{sizeof(LnEntry), 140, 140}, xmlscm_LnEntry_3, 140},
        {{sizeof(String), 0, 0}, NULL, 0},
        {(CharType*) xmlscm_URI_3, 32}
    },
    {
        {{sizeof(LnEntry), 0, 0}, NULL, 0},
        {{sizeof(String), 0, 0}, NULL, 0},
        {NULL, 0}
    },
    {
        {{sizeof(LnEntry), 0, 0}, NULL, 0},
        {{sizeof(String), 0, 0}, NULL, 0},
        {NULL, 0}
    },
    {
        {{sizeof(LnEntry), 0, 0}, NULL, 0},
        {{sizeof(String), 0, 0}, NULL, 0},
        {NULL, 0}
    },
    {
        {{sizeof(LnEntry), 0, 0}, NULL, 0},
        {{sizeof(String), 0, 0}, NULL, 0},
        {NULL, 0}
    },
    {
        {{sizeof(LnEntry), 0, 0}, NULL, 0},
        {{sizeof(String), 0, 0}, NULL, 0},
        {NULL, 0}
    },
    {
        {{sizeof(LnEntry), 0, 0}, NULL, 0},
        {{sizeof(String), 0, 0}, NULL, 0},
        {NULL, 0}
    },
    {
        {{sizeof(LnEntry), 0, 0}, NULL, 0},
        {{sizeof(String), 0, 0}, NULL, 0},
        {NULL, 0}
    },
    {
        {{sizeof(LnEntry), 0, 0}, NULL, 0},
        {{sizeof(String), 0, 0}, NULL, 0},
        {NULL, 0}
    },
    {
        {{sizeof(LnEntry), 0, 0}, NULL, 0},
        {{sizeof(String), 0, 0}, NULL, 0},
        {NULL, 0}
    },
    {
        {{sizeof(LnEntry), 0, 0}, NULL, 0},
        {{sizeof(String), 0, 0}, NULL, 0},
        {NULL, 0}
    }
};

static const Production xmlscm_prod_doc_content[42] =
{
    {
        536870913, INDEX_MAX,
        {URI_MAX, LN_MAX}},
    {
        503316481, 67,
        {3, 138}},
    {
        503316481, 85,
        {3, 137}},
    {
        503316481, 62,
        {3, 136}},
    {
        503316481, 64,
        {3, 133}},
    {
        503316481, 70,
        {3, 128}},
    {
        503316481, 77,
        {3, 121}},
    {
        503316481, 89,
        {3, 120}},
    {
        503316481, 83,
        {3, 119}},
    {
        503316481, 104,
        {3, 117}},
    {
        503316481, 59,
        {3, 115}},
    {
        503316481, 99,
        {3, 113}},
    {
        503316481, 68,
        {3, 109}},
    {
        503316481, 103,
        {3, 104}},
    {
        503316481, 65,
        {3, 97}},
    {
        503316481, 63,
        {3, 96}},
    {
        503316481, 63,
        {3, 95}},
    {
        503316481, 65,
        {3, 94}},
    {
        503316481, 63,
        {3, 93}},
    {
        503316481, 63,
        {3, 92}},
    {
        503316481, 61,
        {3, 88}},
    {
        503316481, 65,
        {3, 87}},
    {
        503316481, 86,
        {3, 86}},
    {
        503316481, 85,
        {3, 84}},
    {
        503316481, 57,
        {3, 83}},
    {
        503316481, 58,
        {3, 82}},
    {
        503316481, 97,
        {3, 79}},
    {
        503316481, 65,
        {3, 77}},
    {
        503316481, 84,
        {3, 75}},
    {
        503316481, 66,
        {3, 69}},
    {
        503316481, 100,
        {3, 68}},
    {
        503316481, 48,
        {3, 67}},
    {
        503316481, 94,
        {3, 62}},
    {
        503316481, 80,
        {3, 60}},
    {
        503316481, 89,
        {3, 59}},
    {
        503316481, 98,
        {3, 56}},
    {
        503316481, 101,
        {3, 55}},
    {
        503316481, 47,
        {3, 53}},
    {
        503316481, 74,
        {3, 52}},
    {
        503316481, 90,
        {3, 51}},
    {
        503316481, 49,
        {3, 50}},
    {
        503316481, 81,
        {3, 46}}
};

static const Production xmlscm_prod_doc_end[1] =
{
    {
        0xAFFFFFF, INDEX_MAX,
        {URI_MAX, LN_MAX}}
};

static const GrammarRule xmlscm_docGrammarRule[2] =
{
    {(Production*) xmlscm_prod_doc_content, 42, 0},
    {(Production*) xmlscm_prod_doc_end, 1, 0}
};

static const SimpleType xmlscm_simpleTypes[62] =
{
    {1174405120, 1, 0x0000000000000000, 0x0000000000000000},
    {167776256, 0, 0x0000000000000000, 0x0000000000000000},
    {167772160, 0, 0x0000000000000000, 0x0000000000000000},
    {167776256, 0, 0x0000000000000000, 0x0000000000000000},
    {1174405120, 3, 0x0000000000000000, 0x0000000000000000},
    {167776256, 0, 0x0000000000000000, 0x0000000000000000},
    {167776256, 0, 0x0000000000000000, 0x0000000000000000},
    {1174405120, 6, 0x0000000000000000, 0x0000000000000000},
    {167772160, 0, 0x0000000000000000, 0x0000000000000000},
    {167776256, 0, 0x0000000000000000, 0x0000000000000000},
    {167772160, 0, 0x0000000000000000, 0x0000000000000000},
    {167776256, 0, 0x0000000000000000, 0x0000000000000000},
    {4096, 0, 0x0000000000000000, 0x0000000000000000},
    {167772160, 0, 0x0000000000000000, 0x0000000000000000},
    {1006632960, 0, 0x0000000000000000, 0x0000000000000000},
    {838860800, 0, 0x0000000000000000, 0x0000000000000000},
    {1526727232, 0, 0x000000000000007F, 0x00000000FFFFFF80},
    {704643072, 0, 0x0000000000000000, 0x0000000000000000},
    {671088640, 0, 0x0000000000000000, 0x0000000000000000},
    {503320576, 0, 0x0000000000000000, 0x0000000000000000},
    {335544320, 0, 0x0000000000000000, 0x0000000000000000},
    {167772160, 0, 0x0000000000000000, 0x0000000000000000},
    {335544320, 0, 0x0000000000000000, 0x0000000000000000},
    {721420288, 0, 0x0000000000000000, 0x0000000000000000},
    {721420288, 0, 0x0000000000000000, 0x0000000000000000},
    {721420288, 0, 0x0000000000000000, 0x0000000000000000},
    {687865856, 0, 0x0000000000000000, 0x0000000000000000},
    {704643072, 0, 0x0000000000000000, 0x0000000000000000},
    {1023410176, 0, 0x0000000000000000, 0x0000000000000000},
    {1509953536, 0, 0x0000000000000000, 0x0000000000000000},
    {1509953536, 0, 0x0000000000000000, 0x0000000000000000},
    {167772160, 0, 0x0000000000000000, 0x0000000000000000},
    {1509953536, 0, 0x0000000000000000, 0x0000000000000000},
    {1509949504, 0, 0x00000000FFFFFFFF, 0x0000000000000000},
    {1543508480, 0, 0x0000000000000000, 0x0000000000000000},
    {1509953600, 0, 0x0000000000000000, 0x0000000000000000},
    {167776256, 0, 0x0000000000000000, 0x0000000000000000},
    {1543504384, 0, 0x0000000000000000, 0x0000000000000001},
    {1509954112, 0, 0x0000000000007FFF, 0x00000000FFFF8000},
    {167776256, 0, 0x0000000000000000, 0x0000000000000000},
    {738197504, 0, 0x0000000000000000, 0x0000000000000000},
    {167776256, 0, 0x0000000000000000, 0x0000000000000000},
    {1526727232, 0, 0x00000000000000FF, 0x0000000000000000},
    {1543508480, 0, 0x0000000000000000, 0x0000000000000000},
    {1543508480, 0, 0x0000000000000000, 0x0000000000000000},
    {1543508544, 0, 0x000000000000FFFF, 0x0000000000000000},
    {167772176, 0, 0x0000000000000000, 0x0000000000000000},
    {167772176, 0, 0x0000000000000000, 0x0000000000000000},
    {167772176, 0, 0x0000000000000000, 0x0000000000000000},
    {167772176, 0, 0x0000000000000000, 0x0000000000000000},
    {1174405120, 10, 0x0000000000000000, 0x0000000000000000},
    {167772176, 0, 0x0000000000000000, 0x0000000000000000},
    {167772176, 0, 0x0000000000000000, 0x0000000000000000},
    {167772176, 0, 0x0000000000000000, 0x0000000000000000},
    {167772168, 0, 0x0000000000000000, 0x0000000000000000},
    {167772168, 0, 0x0000000000000000, 0x0000000000000000},
    {167772176, 0, 0x0000000000000000, 0x0000000000000000},
    {1543504400, 0, 0x0000000000000000, 0x0000000000000000},
    {167772176, 0, 0x0000000000000000, 0x0000000000000000},
    {1543504400, 0, 0x0000000000000000, 0x0000000000000000},
    {167772176, 0, 0x0000000000000000, 0x0000000000000000},
    {167772160, 0, 0x0000000000000000, 0x0000000000000000}
};

const CharType xmlscm_ENUM_0_0[] = {0x71, 0x75, 0x61, 0x6c, 0x69, 0x66, 0x69, 0x65, 0x64}; /* qualified */
const CharType xmlscm_ENUM_0_1[] = {0x75, 0x6e, 0x71, 0x75, 0x61, 0x6c, 0x69, 0x66, 0x69, 0x65, 0x64}; /* unqualified */

static const String xmlscm_enumValues_0[2] = { 
   {(CharType*) xmlscm_ENUM_0_0, 9},
   {(CharType*) xmlscm_ENUM_0_1, 11}
};

const CharType xmlscm_ENUM_1_0[] = {0x73, 0x75, 0x62, 0x73, 0x74, 0x69, 0x74, 0x75, 0x74, 0x69, 0x6f, 0x6e}; /* substitution */
const CharType xmlscm_ENUM_1_1[] = {0x65, 0x78, 0x74, 0x65, 0x6e, 0x73, 0x69, 0x6f, 0x6e}; /* extension */
const CharType xmlscm_ENUM_1_2[] = {0x72, 0x65, 0x73, 0x74, 0x72, 0x69, 0x63, 0x74, 0x69, 0x6f, 0x6e}; /* restriction */
const CharType xmlscm_ENUM_1_3[] = {0x6c, 0x69, 0x73, 0x74}; /* list */
const CharType xmlscm_ENUM_1_4[] = {0x75, 0x6e, 0x69, 0x6f, 0x6e}; /* union */

static const String xmlscm_enumValues_1[5] = { 
   {(CharType*) xmlscm_ENUM_1_0, 12},
   {(CharType*) xmlscm_ENUM_1_1, 9},
   {(CharType*) xmlscm_ENUM_1_2, 11},
   {(CharType*) xmlscm_ENUM_1_3, 4},
   {(CharType*) xmlscm_ENUM_1_4, 5}
};

const CharType xmlscm_ENUM_2_0[] = {0x65, 0x78, 0x74, 0x65, 0x6e, 0x73, 0x69, 0x6f, 0x6e}; /* extension */
const CharType xmlscm_ENUM_2_1[] = {0x72, 0x65, 0x73, 0x74, 0x72, 0x69, 0x63, 0x74, 0x69, 0x6f, 0x6e}; /* restriction */

static const String xmlscm_enumValues_2[2] = { 
   {(CharType*) xmlscm_ENUM_2_0, 9},
   {(CharType*) xmlscm_ENUM_2_1, 11}
};

const CharType xmlscm_ENUM_3_0[] = {0x65, 0x78, 0x74, 0x65, 0x6e, 0x73, 0x69, 0x6f, 0x6e}; /* extension */
const CharType xmlscm_ENUM_3_1[] = {0x72, 0x65, 0x73, 0x74, 0x72, 0x69, 0x63, 0x74, 0x69, 0x6f, 0x6e}; /* restriction */
const CharType xmlscm_ENUM_3_2[] = {0x6c, 0x69, 0x73, 0x74}; /* list */
const CharType xmlscm_ENUM_3_3[] = {0x75, 0x6e, 0x69, 0x6f, 0x6e}; /* union */

static const String xmlscm_enumValues_3[4] = { 
   {(CharType*) xmlscm_ENUM_3_0, 9},
   {(CharType*) xmlscm_ENUM_3_1, 11},
   {(CharType*) xmlscm_ENUM_3_2, 4},
   {(CharType*) xmlscm_ENUM_3_3, 5}
};

const CharType xmlscm_ENUM_4_0[] = {0x70, 0x72, 0x65, 0x73, 0x65, 0x72, 0x76, 0x65}; /* preserve */
const CharType xmlscm_ENUM_4_1[] = {0x72, 0x65, 0x70, 0x6c, 0x61, 0x63, 0x65}; /* replace */
const CharType xmlscm_ENUM_4_2[] = {0x63, 0x6f, 0x6c, 0x6c, 0x61, 0x70, 0x73, 0x65}; /* collapse */

static const String xmlscm_enumValues_4[3] = { 
   {(CharType*) xmlscm_ENUM_4_0, 8},
   {(CharType*) xmlscm_ENUM_4_1, 7},
   {(CharType*) xmlscm_ENUM_4_2, 8}
};

const CharType xmlscm_ENUM_5_0[] = {0x70, 0x72, 0x6f, 0x68, 0x69, 0x62, 0x69, 0x74, 0x65, 0x64}; /* prohibited */
const CharType xmlscm_ENUM_5_1[] = {0x6f, 0x70, 0x74, 0x69, 0x6f, 0x6e, 0x61, 0x6c}; /* optional */
const CharType xmlscm_ENUM_5_2[] = {0x72, 0x65, 0x71, 0x75, 0x69, 0x72, 0x65, 0x64}; /* required */

static const String xmlscm_enumValues_5[3] = { 
   {(CharType*) xmlscm_ENUM_5_0, 10},
   {(CharType*) xmlscm_ENUM_5_1, 8},
   {(CharType*) xmlscm_ENUM_5_2, 8}
};

const CharType xmlscm_ENUM_6_0[] = {0x73, 0x6b, 0x69, 0x70}; /* skip */
const CharType xmlscm_ENUM_6_1[] = {0x6c, 0x61, 0x78}; /* lax */
const CharType xmlscm_ENUM_6_2[] = {0x73, 0x74, 0x72, 0x69, 0x63, 0x74}; /* strict */

static const String xmlscm_enumValues_6[3] = { 
   {(CharType*) xmlscm_ENUM_6_0, 4},
   {(CharType*) xmlscm_ENUM_6_1, 3},
   {(CharType*) xmlscm_ENUM_6_2, 6}
};

const CharType xmlscm_ENUM_7_0[] = {0x73, 0x6b, 0x69, 0x70}; /* skip */
const CharType xmlscm_ENUM_7_1[] = {0x6c, 0x61, 0x78}; /* lax */
const CharType xmlscm_ENUM_7_2[] = {0x73, 0x74, 0x72, 0x69, 0x63, 0x74}; /* strict */

static const String xmlscm_enumValues_7[3] = { 
   {(CharType*) xmlscm_ENUM_7_0, 4},
   {(CharType*) xmlscm_ENUM_7_1, 3},
   {(CharType*) xmlscm_ENUM_7_2, 6}
};


static const UnsignedInteger xmlscm_enumValues_8[2] = { 
   0x0000000000000000,
   0x0000000000000001
};

const CharType xmlscm_ENUM_9_0[] = {0x30}; /* 0 */
const CharType xmlscm_ENUM_9_1[] = {0x31}; /* 1 */

static const String xmlscm_enumValues_9[2] = { 
   {(CharType*) xmlscm_ENUM_9_0, 1},
   {(CharType*) xmlscm_ENUM_9_1, 1}
};


static const UnsignedInteger xmlscm_enumValues_10[2] = { 
   0x0000000000000000,
   0x0000000000000001
};

const CharType xmlscm_ENUM_11_0[] = {0x31}; /* 1 */

static const String xmlscm_enumValues_11[1] = { 
   {(CharType*) xmlscm_ENUM_11_0, 1}
};

static const EnumDefinition xmlscm_enumTable[12] = { 
   {46, (void*) xmlscm_enumValues_0, 2},
   {47, (void*) xmlscm_enumValues_1, 5},
   {48, (void*) xmlscm_enumValues_2, 2},
   {49, (void*) xmlscm_enumValues_3, 4},
   {51, (void*) xmlscm_enumValues_4, 3},
   {52, (void*) xmlscm_enumValues_5, 3},
   {53, (void*) xmlscm_enumValues_6, 3},
   {56, (void*) xmlscm_enumValues_7, 3},
   {57, (void*) xmlscm_enumValues_8, 2},
   {58, (void*) xmlscm_enumValues_9, 2},
   {59, (void*) xmlscm_enumValues_10, 2},
   {60, (void*) xmlscm_enumValues_11, 1}
};

CONST EXIPSchema xmlscm_schema =
{
    {NULL, NULL,0},
    {{sizeof(UriEntry), 4, 14}, xmlscm_uriEntry, 4},
    {(GrammarRule*) xmlscm_docGrammarRule, 100663296, 2},
    {{sizeof(SimpleType), 62, 62}, (SimpleType*) xmlscm_simpleTypes, 62},
    {{sizeof(EXIGrammar), 112, 117}, xmlscm_grammarTable, 112},
    112,
    {{sizeof(EnumDefinition), 12, 12}, (EnumDefinition*) xmlscm_enumTable, 12}
};

