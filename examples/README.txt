/**
 * @defgroup exmaples Example applications
 *
 * @brief Information on the included example applications and how to build and run them.
 *
 * Demo applications:
 *   <dl>
 *     <dt>exipd</dt> <dd>Decodes arbitrary exi streams</dd> 		
 *     <dt>exipe</dt> <dd>Encodes a sample exi stream</dd>
 *     <dt>exipd-coffeeshop</dt> <dd>Decodes the CoffeeShop example stream</dd>
 *     <dt>exipe-coffeeshop</dt> <dd>Encodes a CoffeeShop example stream</dd>
 *   </dl>
 *
 * CoffeeShop quick run:
 *   1) Generate EXI schemas from XSD files via xsd2exip:
 *      - examples/simpleEncoding/coffeeshop.xsd -> examples/simpleEncoding/exipe-coffeeshop-xsd.exi
 *      - examples/simpleDecoding/coffeeshop.xsd -> examples/simpleDecoding/exipd-coffeeshop-xsd.exi
 *   2) Build targets: exipe-coffeeshop and exipd-coffeeshop
 *   3) Encode then decode:
 *      exipe-coffeeshop -schema=<.../exipe-coffeeshop-xsd.exi> /tmp/coffeeshop.exi
 *      exipd-coffeeshop -schema=<.../exipd-coffeeshop-xsd.exi> /tmp/coffeeshop.exi
 *
 * @date Jun 20, 2012
 * @author Rumen Kyusakov
 * @version 0.5
 * @par[Revision] $Id: README.txt 328 2013-10-30 16:00:10Z kjussakov $
 */