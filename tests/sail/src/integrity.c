/*  This file is part of SAIL (https://github.com/smoked-herring/sail)

    Copyright (c) 2020 Dmitry Baryshev

    The MIT License

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#include "sail-common.h"

#include "munit.h"

/*
 * Pixel formats.
 */
static MunitResult test_pixel_format_to_string(const MunitParameter params[], void *user_data) {
    (void)params;
    (void)user_data;

    const char *result;

#define TEST_SAIL_CONVERSION(e, s)           \
    result = NULL;                           \
    sail_pixel_format_to_string(e, &result); \
    munit_assert_string_equal(result, s);

    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_UNKNOWN, "UNKNOWN");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_AUTO,    "AUTO");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_SOURCE,  "SOURCE");

    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP1,   "BPP1");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP2,   "BPP2");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP4,   "BPP4");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP8,   "BPP8");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP16,  "BPP16");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP24,  "BPP24");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP32,  "BPP32");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP48,  "BPP48");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP64,  "BPP64");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP72,  "BPP72");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP96,  "BPP96");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP128, "BPP128");

    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP1_INDEXED,  "BPP1-INDEXED");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP2_INDEXED,  "BPP2-INDEXED");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP4_INDEXED,  "BPP4-INDEXED");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP8_INDEXED,  "BPP8-INDEXED");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP16_INDEXED, "BPP16-INDEXED");

    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP1_GRAYSCALE,  "BPP1-GRAYSCALE");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP2_GRAYSCALE,  "BPP2-GRAYSCALE");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP4_GRAYSCALE,  "BPP4-GRAYSCALE");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP8_GRAYSCALE,  "BPP8-GRAYSCALE");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP16_GRAYSCALE, "BPP16-GRAYSCALE");

    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP4_GRAYSCALE_ALPHA,  "BPP4-GRAYSCALE-ALPHA");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP8_GRAYSCALE_ALPHA,  "BPP8-GRAYSCALE-ALPHA");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP16_GRAYSCALE_ALPHA, "BPP16-GRAYSCALE-ALPHA");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP32_GRAYSCALE_ALPHA, "BPP32-GRAYSCALE-ALPHA");

    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP16_RGB555, "BPP16-RGB555");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP16_BGR555, "BPP16-BGR555");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP16_RGB565, "BPP16-RGB565");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP16_BGR565, "BPP16-BGR565");

    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP24_RGB, "BPP24-RGB");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP24_BGR, "BPP24-BGR");

    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP48_RGB, "BPP48-RGB");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP48_BGR, "BPP48-BGR");

    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP32_RGBX, "BPP32-RGBX");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP32_BGRX, "BPP32-BGRX");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP32_XRGB, "BPP32-XRGB");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP32_XBGR, "BPP32-XBGR");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP32_RGBA, "BPP32-RGBA");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP32_BGRA, "BPP32-BGRA");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP32_ARGB, "BPP32-ARGB");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP32_ABGR, "BPP32-ABGR");

    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP64_RGBX, "BPP64-RGBX");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP64_BGRX, "BPP64-BGRX");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP64_XRGB, "BPP64-XRGB");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP64_XBGR, "BPP64-XBGR");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP64_RGBA, "BPP64-RGBA");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP64_BGRA, "BPP64-BGRA");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP64_ARGB, "BPP64-ARGB");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP64_ABGR, "BPP64-ABGR");

    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP32_CMYK, "BPP32-CMYK");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP64_CMYK, "BPP64-CMYK");

    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP24_YCBCR, "BPP24-YCBCR");

    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP32_YCCK, "BPP32-YCCK");

    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP24_CIE_LAB, "BPP24-CIE-LAB");
    TEST_SAIL_CONVERSION(SAIL_PIXEL_FORMAT_BPP48_CIE_LAB, "BPP48-CIE-LAB");

#undef TEST_SAIL_CONVERSION

    return MUNIT_OK;
}

static MunitResult test_pixel_format_from_string(const MunitParameter params[], void *user_data) {
    (void)params;
    (void)user_data;

    enum SailPixelFormat result;

#define TEST_SAIL_CONVERSION(s, e)             \
    result = SAIL_PIXEL_FORMAT_UNKNOWN;        \
    sail_pixel_format_from_string(s, &result); \
    munit_assert(result == e);

    TEST_SAIL_CONVERSION("UNKNOWN", SAIL_PIXEL_FORMAT_UNKNOWN);
    TEST_SAIL_CONVERSION("AUTO",    SAIL_PIXEL_FORMAT_AUTO);
    TEST_SAIL_CONVERSION("SOURCE",  SAIL_PIXEL_FORMAT_SOURCE);

    TEST_SAIL_CONVERSION("BPP1",   SAIL_PIXEL_FORMAT_BPP1);
    TEST_SAIL_CONVERSION("BPP2",   SAIL_PIXEL_FORMAT_BPP2);
    TEST_SAIL_CONVERSION("BPP4",   SAIL_PIXEL_FORMAT_BPP4);
    TEST_SAIL_CONVERSION("BPP8",   SAIL_PIXEL_FORMAT_BPP8);
    TEST_SAIL_CONVERSION("BPP16",  SAIL_PIXEL_FORMAT_BPP16);
    TEST_SAIL_CONVERSION("BPP24",  SAIL_PIXEL_FORMAT_BPP24);
    TEST_SAIL_CONVERSION("BPP32",  SAIL_PIXEL_FORMAT_BPP32);
    TEST_SAIL_CONVERSION("BPP48",  SAIL_PIXEL_FORMAT_BPP48);
    TEST_SAIL_CONVERSION("BPP64",  SAIL_PIXEL_FORMAT_BPP64);
    TEST_SAIL_CONVERSION("BPP72",  SAIL_PIXEL_FORMAT_BPP72);
    TEST_SAIL_CONVERSION("BPP96",  SAIL_PIXEL_FORMAT_BPP96);
    TEST_SAIL_CONVERSION("BPP128", SAIL_PIXEL_FORMAT_BPP128);

    TEST_SAIL_CONVERSION("BPP1-INDEXED",  SAIL_PIXEL_FORMAT_BPP1_INDEXED);
    TEST_SAIL_CONVERSION("BPP2-INDEXED",  SAIL_PIXEL_FORMAT_BPP2_INDEXED);
    TEST_SAIL_CONVERSION("BPP4-INDEXED",  SAIL_PIXEL_FORMAT_BPP4_INDEXED);
    TEST_SAIL_CONVERSION("BPP8-INDEXED",  SAIL_PIXEL_FORMAT_BPP8_INDEXED);
    TEST_SAIL_CONVERSION("BPP16-INDEXED", SAIL_PIXEL_FORMAT_BPP16_INDEXED);

    TEST_SAIL_CONVERSION("BPP1-GRAYSCALE",  SAIL_PIXEL_FORMAT_BPP1_GRAYSCALE);
    TEST_SAIL_CONVERSION("BPP2-GRAYSCALE",  SAIL_PIXEL_FORMAT_BPP2_GRAYSCALE);
    TEST_SAIL_CONVERSION("BPP4-GRAYSCALE",  SAIL_PIXEL_FORMAT_BPP4_GRAYSCALE);
    TEST_SAIL_CONVERSION("BPP8-GRAYSCALE",  SAIL_PIXEL_FORMAT_BPP8_GRAYSCALE);
    TEST_SAIL_CONVERSION("BPP16-GRAYSCALE", SAIL_PIXEL_FORMAT_BPP16_GRAYSCALE);

    TEST_SAIL_CONVERSION("BPP4-GRAYSCALE-ALPHA",  SAIL_PIXEL_FORMAT_BPP4_GRAYSCALE_ALPHA);
    TEST_SAIL_CONVERSION("BPP8-GRAYSCALE-ALPHA",  SAIL_PIXEL_FORMAT_BPP8_GRAYSCALE_ALPHA);
    TEST_SAIL_CONVERSION("BPP16-GRAYSCALE-ALPHA", SAIL_PIXEL_FORMAT_BPP16_GRAYSCALE_ALPHA);
    TEST_SAIL_CONVERSION("BPP32-GRAYSCALE-ALPHA", SAIL_PIXEL_FORMAT_BPP32_GRAYSCALE_ALPHA);

    TEST_SAIL_CONVERSION("BPP16-RGB555", SAIL_PIXEL_FORMAT_BPP16_RGB555);
    TEST_SAIL_CONVERSION("BPP16-BGR555", SAIL_PIXEL_FORMAT_BPP16_BGR555);
    TEST_SAIL_CONVERSION("BPP16-RGB565", SAIL_PIXEL_FORMAT_BPP16_RGB565);
    TEST_SAIL_CONVERSION("BPP16-BGR565", SAIL_PIXEL_FORMAT_BPP16_BGR565);

    TEST_SAIL_CONVERSION("BPP24-RGB", SAIL_PIXEL_FORMAT_BPP24_RGB);
    TEST_SAIL_CONVERSION("BPP24-BGR", SAIL_PIXEL_FORMAT_BPP24_BGR);

    TEST_SAIL_CONVERSION("BPP48-RGB", SAIL_PIXEL_FORMAT_BPP48_RGB);
    TEST_SAIL_CONVERSION("BPP48-BGR", SAIL_PIXEL_FORMAT_BPP48_BGR);

    TEST_SAIL_CONVERSION("BPP32-RGBX", SAIL_PIXEL_FORMAT_BPP32_RGBX);
    TEST_SAIL_CONVERSION("BPP32-BGRX", SAIL_PIXEL_FORMAT_BPP32_BGRX);
    TEST_SAIL_CONVERSION("BPP32-XRGB", SAIL_PIXEL_FORMAT_BPP32_XRGB);
    TEST_SAIL_CONVERSION("BPP32-XBGR", SAIL_PIXEL_FORMAT_BPP32_XBGR);
    TEST_SAIL_CONVERSION("BPP32-RGBA", SAIL_PIXEL_FORMAT_BPP32_RGBA);
    TEST_SAIL_CONVERSION("BPP32-BGRA", SAIL_PIXEL_FORMAT_BPP32_BGRA);
    TEST_SAIL_CONVERSION("BPP32-ARGB", SAIL_PIXEL_FORMAT_BPP32_ARGB);
    TEST_SAIL_CONVERSION("BPP32-ABGR", SAIL_PIXEL_FORMAT_BPP32_ABGR);

    TEST_SAIL_CONVERSION("BPP64-RGBX", SAIL_PIXEL_FORMAT_BPP64_RGBX);
    TEST_SAIL_CONVERSION("BPP64-BGRX", SAIL_PIXEL_FORMAT_BPP64_BGRX);
    TEST_SAIL_CONVERSION("BPP64-XRGB", SAIL_PIXEL_FORMAT_BPP64_XRGB);
    TEST_SAIL_CONVERSION("BPP64-XBGR", SAIL_PIXEL_FORMAT_BPP64_XBGR);
    TEST_SAIL_CONVERSION("BPP64-RGBA", SAIL_PIXEL_FORMAT_BPP64_RGBA);
    TEST_SAIL_CONVERSION("BPP64-BGRA", SAIL_PIXEL_FORMAT_BPP64_BGRA);
    TEST_SAIL_CONVERSION("BPP64-ARGB", SAIL_PIXEL_FORMAT_BPP64_ARGB);
    TEST_SAIL_CONVERSION("BPP64-ABGR", SAIL_PIXEL_FORMAT_BPP64_ABGR);

    TEST_SAIL_CONVERSION("BPP32-CMYK", SAIL_PIXEL_FORMAT_BPP32_CMYK);
    TEST_SAIL_CONVERSION("BPP64-CMYK", SAIL_PIXEL_FORMAT_BPP64_CMYK);

    TEST_SAIL_CONVERSION("BPP24-YCBCR", SAIL_PIXEL_FORMAT_BPP24_YCBCR);

    TEST_SAIL_CONVERSION("BPP32-YCCK", SAIL_PIXEL_FORMAT_BPP32_YCCK);

    TEST_SAIL_CONVERSION("BPP24-CIE-LAB", SAIL_PIXEL_FORMAT_BPP24_CIE_LAB);
    TEST_SAIL_CONVERSION("BPP48-CIE-LAB", SAIL_PIXEL_FORMAT_BPP48_CIE_LAB);

#undef TEST_SAIL_CONVERSION

    return MUNIT_OK;
}

/*
 * Image properties.
 */
static MunitResult test_image_property_to_string(const MunitParameter params[], void *user_data) {
    (void)params;
    (void)user_data;

    const char *result;

#define TEST_SAIL_CONVERSION(e, s)             \
    sail_image_property_to_string(e, &result); \
    munit_assert_string_equal(result, s);

    TEST_SAIL_CONVERSION(SAIL_IMAGE_PROPERTY_FLIPPED_VERTICALLY, "FLIPPED-VERTICALLY");
    TEST_SAIL_CONVERSION(SAIL_IMAGE_PROPERTY_INTERLACED,         "INTERLACED");

#undef TEST_SAIL_CONVERSION

    return MUNIT_OK;
}

static MunitResult test_image_property_from_string(const MunitParameter params[], void *user_data) {
    (void)params;
    (void)user_data;

    enum SailImageProperty result;

#define TEST_SAIL_CONVERSION(s, e)               \
    sail_image_property_from_string(s, &result); \
    munit_assert(result == e);

    TEST_SAIL_CONVERSION("FLIPPED-VERTICALLY", SAIL_IMAGE_PROPERTY_FLIPPED_VERTICALLY);
    TEST_SAIL_CONVERSION("INTERLACED",         SAIL_IMAGE_PROPERTY_INTERLACED);

#undef TEST_SAIL_CONVERSION

    return MUNIT_OK;
}

/*
 * Compression types.
 */
static MunitResult test_compression_to_string(const MunitParameter params[], void *user_data) {
    (void)params;
    (void)user_data;

    const char *result;

#define TEST_SAIL_CONVERSION(e, s)          \
    result = NULL;                          \
    sail_compression_to_string(e, &result); \
    munit_assert_string_equal(result, s);

    TEST_SAIL_CONVERSION(SAIL_COMPRESSION_UNSUPPORTED,   "UNSUPPORTED");
    TEST_SAIL_CONVERSION(SAIL_COMPRESSION_NONE,          "NONE");
    TEST_SAIL_CONVERSION(SAIL_COMPRESSION_ADOBE_DEFLATE, "ADOBE-DEFLATE");
    TEST_SAIL_CONVERSION(SAIL_COMPRESSION_CCITT_FAX3,    "CCITT-FAX3");
    TEST_SAIL_CONVERSION(SAIL_COMPRESSION_CCITT_FAX4,    "CCITT-FAX4");
    TEST_SAIL_CONVERSION(SAIL_COMPRESSION_CCITT_RLE,     "CCITT-RLE");
    TEST_SAIL_CONVERSION(SAIL_COMPRESSION_CCITT_RLEW,    "CCITT-RLEW");
    TEST_SAIL_CONVERSION(SAIL_COMPRESSION_CCITT_T4,      "CCITT-T4");
    TEST_SAIL_CONVERSION(SAIL_COMPRESSION_CCITT_T6,      "CCITT-T6");
    TEST_SAIL_CONVERSION(SAIL_COMPRESSION_DCS,           "DCS");
    TEST_SAIL_CONVERSION(SAIL_COMPRESSION_DEFLATE,       "DEFLATE");
    TEST_SAIL_CONVERSION(SAIL_COMPRESSION_IT8_BL,        "IT8-BL");
    TEST_SAIL_CONVERSION(SAIL_COMPRESSION_IT8_CTPAD,     "IT8-CTPAD");
    TEST_SAIL_CONVERSION(SAIL_COMPRESSION_IT8_LW,        "IT8-LW");
    TEST_SAIL_CONVERSION(SAIL_COMPRESSION_IT8_MP,        "IT8-MP");
    TEST_SAIL_CONVERSION(SAIL_COMPRESSION_JBIG,          "JBIG");
    TEST_SAIL_CONVERSION(SAIL_COMPRESSION_JPEG,          "JPEG");
    TEST_SAIL_CONVERSION(SAIL_COMPRESSION_JPEG2000,      "JPEG2000");
    TEST_SAIL_CONVERSION(SAIL_COMPRESSION_LERC,          "LERC");
    TEST_SAIL_CONVERSION(SAIL_COMPRESSION_LZMA,          "LZMA");
    TEST_SAIL_CONVERSION(SAIL_COMPRESSION_LZW,           "LZW");
    TEST_SAIL_CONVERSION(SAIL_COMPRESSION_NEXT,          "NEXT");
    TEST_SAIL_CONVERSION(SAIL_COMPRESSION_OJPEG,         "OJPEG");
    TEST_SAIL_CONVERSION(SAIL_COMPRESSION_PACKBITS,      "PACKBITS");
    TEST_SAIL_CONVERSION(SAIL_COMPRESSION_PIXAR_FILM,    "PIXAR-FILM");
    TEST_SAIL_CONVERSION(SAIL_COMPRESSION_PIXAR_LOG,     "PIXAR-LOG");
    TEST_SAIL_CONVERSION(SAIL_COMPRESSION_RLE,           "RLE");
    TEST_SAIL_CONVERSION(SAIL_COMPRESSION_SGI_LOG,       "SGI-LOG");
    TEST_SAIL_CONVERSION(SAIL_COMPRESSION_SGI_LOG24,     "SGI-LOG24");
    TEST_SAIL_CONVERSION(SAIL_COMPRESSION_T43,           "T43");
    TEST_SAIL_CONVERSION(SAIL_COMPRESSION_T85,           "T85");
    TEST_SAIL_CONVERSION(SAIL_COMPRESSION_THUNDERSCAN,   "THUNDERSCAN");
    TEST_SAIL_CONVERSION(SAIL_COMPRESSION_WEBP,          "WEBP");
    TEST_SAIL_CONVERSION(SAIL_COMPRESSION_ZSTD,          "ZSTD");

#undef TEST_SAIL_CONVERSION

    return MUNIT_OK;
}

static MunitResult test_compression_from_string(const MunitParameter params[], void *user_data) {
    (void)params;
    (void)user_data;

    enum SailCompression result;

#define TEST_SAIL_CONVERSION(s, e)            \
    result = SAIL_COMPRESSION_UNSUPPORTED;    \
    sail_compression_from_string(s, &result); \
    munit_assert(result == e);

    TEST_SAIL_CONVERSION("UNSUPPORTED",   SAIL_COMPRESSION_UNSUPPORTED);
    TEST_SAIL_CONVERSION("NONE",          SAIL_COMPRESSION_NONE);
    TEST_SAIL_CONVERSION("ADOBE-DEFLATE", SAIL_COMPRESSION_ADOBE_DEFLATE);
    TEST_SAIL_CONVERSION("CCITT-FAX3",    SAIL_COMPRESSION_CCITT_FAX3);
    TEST_SAIL_CONVERSION("CCITT-FAX4",    SAIL_COMPRESSION_CCITT_FAX4);
    TEST_SAIL_CONVERSION("CCITT-RLE",     SAIL_COMPRESSION_CCITT_RLE);
    TEST_SAIL_CONVERSION("CCITT-RLEW",    SAIL_COMPRESSION_CCITT_RLEW);
    TEST_SAIL_CONVERSION("CCITT-T4",      SAIL_COMPRESSION_CCITT_T4);
    TEST_SAIL_CONVERSION("CCITT-T6",      SAIL_COMPRESSION_CCITT_T6);
    TEST_SAIL_CONVERSION("DCS",           SAIL_COMPRESSION_DCS);
    TEST_SAIL_CONVERSION("DEFLATE",       SAIL_COMPRESSION_DEFLATE);
    TEST_SAIL_CONVERSION("IT8-BL",        SAIL_COMPRESSION_IT8_BL);
    TEST_SAIL_CONVERSION("IT8-CTPAD",     SAIL_COMPRESSION_IT8_CTPAD);
    TEST_SAIL_CONVERSION("IT8-LW",        SAIL_COMPRESSION_IT8_LW);
    TEST_SAIL_CONVERSION("IT8-MP",        SAIL_COMPRESSION_IT8_MP);
    TEST_SAIL_CONVERSION("JBIG",          SAIL_COMPRESSION_JBIG);
    TEST_SAIL_CONVERSION("JPEG",          SAIL_COMPRESSION_JPEG);
    TEST_SAIL_CONVERSION("JPEG2000",      SAIL_COMPRESSION_JPEG2000);
    TEST_SAIL_CONVERSION("LERC",          SAIL_COMPRESSION_LERC);
    TEST_SAIL_CONVERSION("LZMA",          SAIL_COMPRESSION_LZMA);
    TEST_SAIL_CONVERSION("LZW",           SAIL_COMPRESSION_LZW);
    TEST_SAIL_CONVERSION("NEXT",          SAIL_COMPRESSION_NEXT);
    TEST_SAIL_CONVERSION("OJPEG",         SAIL_COMPRESSION_OJPEG);
    TEST_SAIL_CONVERSION("PACKBITS",      SAIL_COMPRESSION_PACKBITS);
    TEST_SAIL_CONVERSION("PIXAR-FILM",    SAIL_COMPRESSION_PIXAR_FILM);
    TEST_SAIL_CONVERSION("PIXAR-LOG",     SAIL_COMPRESSION_PIXAR_LOG);
    TEST_SAIL_CONVERSION("RLE",           SAIL_COMPRESSION_RLE);
    TEST_SAIL_CONVERSION("SGI-LOG",       SAIL_COMPRESSION_SGI_LOG);
    TEST_SAIL_CONVERSION("SGI-LOG24",     SAIL_COMPRESSION_SGI_LOG24);
    TEST_SAIL_CONVERSION("T43",           SAIL_COMPRESSION_T43);
    TEST_SAIL_CONVERSION("T85",           SAIL_COMPRESSION_T85);
    TEST_SAIL_CONVERSION("THUNDERSCAN",   SAIL_COMPRESSION_THUNDERSCAN);
    TEST_SAIL_CONVERSION("WEBP",          SAIL_COMPRESSION_WEBP);
    TEST_SAIL_CONVERSION("ZSTD",          SAIL_COMPRESSION_ZSTD);

#undef TEST_SAIL_CONVERSION

    return MUNIT_OK;
}

/*
 * Codec features.
 */
static MunitResult test_codec_feature_to_string(const MunitParameter params[], void *user_data) {
    (void)params;
    (void)user_data;

    const char *result;

#define TEST_SAIL_CONVERSION(e, s)             \
    sail_codec_feature_to_string(e, &result); \
    munit_assert_string_equal(result, s);

    TEST_SAIL_CONVERSION(SAIL_CODEC_FEATURE_STATIC,      "STATIC");
    TEST_SAIL_CONVERSION(SAIL_CODEC_FEATURE_ANIMATED,    "ANIMATED");
    TEST_SAIL_CONVERSION(SAIL_CODEC_FEATURE_MULTI_FRAME, "MULTI-FRAME");
    TEST_SAIL_CONVERSION(SAIL_CODEC_FEATURE_META_INFO,   "META-INFO");
    TEST_SAIL_CONVERSION(SAIL_CODEC_FEATURE_EXIF,        "EXIF");
    TEST_SAIL_CONVERSION(SAIL_CODEC_FEATURE_INTERLACED,  "INTERLACED");
    TEST_SAIL_CONVERSION(SAIL_CODEC_FEATURE_ICCP,        "ICCP");

#undef TEST_SAIL_CONVERSION

    return MUNIT_OK;
}

static MunitResult test_codec_feature_from_string(const MunitParameter params[], void *user_data) {
    (void)params;
    (void)user_data;

    enum SailCodecFeature result;

#define TEST_SAIL_CONVERSION(s, e)               \
    sail_codec_feature_from_string(s, &result); \
    munit_assert(result == e);

    TEST_SAIL_CONVERSION("STATIC",      SAIL_CODEC_FEATURE_STATIC);
    TEST_SAIL_CONVERSION("ANIMATED",    SAIL_CODEC_FEATURE_ANIMATED);
    TEST_SAIL_CONVERSION("MULTI-FRAME", SAIL_CODEC_FEATURE_MULTI_FRAME);
    TEST_SAIL_CONVERSION("META-INFO",   SAIL_CODEC_FEATURE_META_INFO);
    TEST_SAIL_CONVERSION("EXIF",        SAIL_CODEC_FEATURE_EXIF);
    TEST_SAIL_CONVERSION("INTERLACED",  SAIL_CODEC_FEATURE_INTERLACED);
    TEST_SAIL_CONVERSION("ICCP",        SAIL_CODEC_FEATURE_ICCP);

#undef TEST_SAIL_CONVERSION

    return MUNIT_OK;
}

static MunitTest test_suite_tests[] = {
    { (char *)"/pixel-format-to-string",   test_pixel_format_to_string,     NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { (char *)"/pixel-format-from-string", test_pixel_format_from_string,   NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

    { (char *)"/image-property-to-string",   test_image_property_to_string,   NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { (char *)"/image-property-from-string", test_image_property_from_string, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

    { (char *)"/compression-to-string",   test_compression_to_string,   NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { (char *)"/compression-from-string", test_compression_from_string, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

    { (char *)"/codec-feature-to-string",   test_codec_feature_to_string,   NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { (char *)"/codec-feature-from-string", test_codec_feature_from_string, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite test_suite = {
    (char *)"/integrity",
    test_suite_tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&test_suite, NULL, argc, argv);
}
