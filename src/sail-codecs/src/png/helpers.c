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

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "sail-common.h"

#include "helpers.h"

void my_error_fn(png_structp png_ptr, png_const_charp text) {

    (void)png_ptr;

    SAIL_LOG_ERROR("PNG: %s", text);
}

void my_warning_fn(png_structp png_ptr, png_const_charp text) {

    (void)png_ptr;

    SAIL_LOG_WARNING("PNG: %s", text);
}

enum SailPixelFormat png_color_type_to_pixel_format(int color_type, int bit_depth) {

    switch (color_type) {
        case PNG_COLOR_TYPE_GRAY: {
            switch (bit_depth) {
                case 1:  return SAIL_PIXEL_FORMAT_BPP1_GRAYSCALE;
                case 2:  return SAIL_PIXEL_FORMAT_BPP2_GRAYSCALE;
                case 4:  return SAIL_PIXEL_FORMAT_BPP4_GRAYSCALE;
                case 8:  return SAIL_PIXEL_FORMAT_BPP8_GRAYSCALE;
                case 16: return SAIL_PIXEL_FORMAT_BPP16_GRAYSCALE;
            }
            break;
        }

        case PNG_COLOR_TYPE_GRAY_ALPHA: {
            switch (bit_depth) {
                case 8:  return SAIL_PIXEL_FORMAT_BPP8_GRAYSCALE_ALPHA;
                case 16: return SAIL_PIXEL_FORMAT_BPP16_GRAYSCALE_ALPHA;
            }
            break;
        }

        case PNG_COLOR_TYPE_PALETTE: {
            switch (bit_depth) {
                case 1: return SAIL_PIXEL_FORMAT_BPP1_INDEXED;
                case 2: return SAIL_PIXEL_FORMAT_BPP2_INDEXED;
                case 4: return SAIL_PIXEL_FORMAT_BPP4_INDEXED;
                case 8: return SAIL_PIXEL_FORMAT_BPP8_INDEXED;
            }
            break;
        }

        case PNG_COLOR_TYPE_RGB: {
            switch (bit_depth) {
                case 8:  return SAIL_PIXEL_FORMAT_BPP24_RGB;
                case 16: return SAIL_PIXEL_FORMAT_BPP48_RGB;
            }
            break;
        }

        case PNG_COLOR_TYPE_RGB_ALPHA: {
            switch (bit_depth) {
                case 8:  return SAIL_PIXEL_FORMAT_BPP32_RGBA;
                case 16: return SAIL_PIXEL_FORMAT_BPP64_RGBA;
            }
            break;
        }
    }

    return SAIL_PIXEL_FORMAT_UNKNOWN;
}

sail_status_t pixel_format_to_png_color_type(enum SailPixelFormat pixel_format, int *color_type, int *bit_depth) {

    SAIL_CHECK_PTR(color_type);
    SAIL_CHECK_PTR(bit_depth);

    switch (pixel_format) {
        case SAIL_PIXEL_FORMAT_BPP1_INDEXED: {
            *color_type = PNG_COLOR_TYPE_PALETTE;
            *bit_depth = 1;
            return SAIL_OK;
        }

        case SAIL_PIXEL_FORMAT_BPP2_INDEXED: {
            *color_type = PNG_COLOR_TYPE_PALETTE;
            *bit_depth = 2;
            return SAIL_OK;
        }

        case SAIL_PIXEL_FORMAT_BPP4_INDEXED: {
            *color_type = PNG_COLOR_TYPE_PALETTE;
            *bit_depth = 4;
            return SAIL_OK;
        }

        case SAIL_PIXEL_FORMAT_BPP8_INDEXED: {
            *color_type = PNG_COLOR_TYPE_PALETTE;
            *bit_depth = 8;
            return SAIL_OK;
        }

        case SAIL_PIXEL_FORMAT_BPP24_RGB:
        case SAIL_PIXEL_FORMAT_BPP24_BGR: {
            *color_type = PNG_COLOR_TYPE_RGB;
            *bit_depth = 8;
            return SAIL_OK;
        }

        case SAIL_PIXEL_FORMAT_BPP48_RGB:
        case SAIL_PIXEL_FORMAT_BPP48_BGR: {
            *color_type = PNG_COLOR_TYPE_RGB;
            *bit_depth = 16;
            return SAIL_OK;
        }

        case SAIL_PIXEL_FORMAT_BPP32_RGBA:
        case SAIL_PIXEL_FORMAT_BPP32_BGRA:
        case SAIL_PIXEL_FORMAT_BPP32_ARGB:
        case SAIL_PIXEL_FORMAT_BPP32_ABGR: {
            *color_type = PNG_COLOR_TYPE_RGB_ALPHA;
            *bit_depth = 8;
            return SAIL_OK;
        }

        case SAIL_PIXEL_FORMAT_BPP64_RGBA:
        case SAIL_PIXEL_FORMAT_BPP64_BGRA:
        case SAIL_PIXEL_FORMAT_BPP64_ARGB:
        case SAIL_PIXEL_FORMAT_BPP64_ABGR: {
            *color_type = PNG_COLOR_TYPE_RGB_ALPHA;
            *bit_depth = 16;
            return SAIL_OK;
        }

        default: {
            return SAIL_ERROR_UNSUPPORTED_PIXEL_FORMAT;
        }
    }
}

sail_status_t supported_read_output_pixel_format(enum SailPixelFormat pixel_format) {

    switch (pixel_format) {
        case SAIL_PIXEL_FORMAT_SOURCE:
        case SAIL_PIXEL_FORMAT_BPP24_RGB:
        case SAIL_PIXEL_FORMAT_BPP24_BGR:
        case SAIL_PIXEL_FORMAT_BPP32_RGBA:
        case SAIL_PIXEL_FORMAT_BPP32_BGRA:
        case SAIL_PIXEL_FORMAT_BPP32_ARGB:
        case SAIL_PIXEL_FORMAT_BPP32_ABGR: {
            return SAIL_OK;
        }

        default: {
            return SAIL_ERROR_UNSUPPORTED_PIXEL_FORMAT;
        }
    }
}

sail_status_t supported_write_output_pixel_format(enum SailPixelFormat pixel_format) {

    switch (pixel_format) {
        case SAIL_PIXEL_FORMAT_AUTO:
        case SAIL_PIXEL_FORMAT_SOURCE: {
            return SAIL_OK;
        }

        default: {
            return SAIL_ERROR_UNSUPPORTED_PIXEL_FORMAT;
        }
    }
}

sail_status_t read_png_text(png_structp png_ptr, png_infop info_ptr, struct sail_meta_entry_node **target_meta_entry_node) {

    SAIL_CHECK_PTR(png_ptr);
    SAIL_CHECK_PTR(info_ptr);
    SAIL_CHECK_PTR(target_meta_entry_node);

#ifdef PNG_TEXT_SUPPORTED
    struct sail_meta_entry_node **last_meta_entry_node = target_meta_entry_node;

    png_textp lines;
    int num_text;

    png_get_text(png_ptr, info_ptr, &lines, &num_text);

    for (int i = 0; i < num_text; i++) {
        struct sail_meta_entry_node *meta_entry_node;

        SAIL_TRY(sail_alloc_meta_entry_node(&meta_entry_node));
        SAIL_TRY_OR_CLEANUP(sail_strdup(lines[i].key, &meta_entry_node->key),
                            /* cleanup */ sail_destroy_meta_entry_node(meta_entry_node));
        SAIL_TRY_OR_CLEANUP(sail_strdup_length(lines[i].text, strlen(lines[i].text), &meta_entry_node->value),
                            /* cleanup */ sail_destroy_meta_entry_node(meta_entry_node));

        *last_meta_entry_node = meta_entry_node;
        last_meta_entry_node = &meta_entry_node->next;
    }
#endif

    return SAIL_OK;
}

sail_status_t write_png_text(png_structp png_ptr, png_infop info_ptr, const struct sail_meta_entry_node *meta_entry_node) {

    SAIL_CHECK_PTR(png_ptr);
    SAIL_CHECK_PTR(info_ptr);

#ifdef PNG_TEXT_SUPPORTED
    /* To avoid allocating dynamic arrays, allow only 32 text pairs. */
    png_text lines[32];
    int count = 0;

    /* Build PNG lines. */
    while (meta_entry_node != NULL && count < 32) {
        lines[count].compression = PNG_TEXT_COMPRESSION_zTXt;
        lines[count].key         = meta_entry_node->key;
        lines[count].text        = meta_entry_node->value;

        count++;
        meta_entry_node = meta_entry_node->next;
    }

    png_set_text(png_ptr, info_ptr, lines, count);
#else
    (void)meta_entry_node;
#endif

    return SAIL_OK;
}

sail_status_t fetch_iccp(png_structp png_ptr, png_infop info_ptr, struct sail_iccp **iccp) {

    SAIL_CHECK_PTR(png_ptr);
    SAIL_CHECK_PTR(info_ptr);
    SAIL_CHECK_ICCP_PTR(iccp);

    char *name;
    int compression;
    png_bytep data;
    unsigned data_length;

    bool ok = png_get_iCCP(png_ptr,
                           info_ptr,
                           &name,
                           &compression,
                           &data,
                           &data_length) == PNG_INFO_iCCP;

    if (ok) {
        SAIL_TRY(sail_alloc_iccp_with_data(iccp, data, data_length));
        SAIL_LOG_DEBUG("PNG: Found ICC profile '%s' %u bytes long", name, data_length);
    } else {
        SAIL_LOG_DEBUG("PNG: ICC profile is not found");
    }

    return SAIL_OK;
}

SAIL_HIDDEN sail_status_t fetch_palette(png_structp png_ptr, png_infop info_ptr, struct sail_palette **palette) {

    SAIL_CHECK_PTR(png_ptr);
    SAIL_CHECK_PTR(info_ptr);
    SAIL_CHECK_PALETTE_PTR(palette);

    png_colorp png_palette;
    int png_palette_color_count;

    if (png_get_PLTE(png_ptr, info_ptr, &png_palette, &png_palette_color_count) == 0) {
        SAIL_LOG_ERROR("The indexed image has no palette");
        return SAIL_ERROR_MISSING_PALETTE;
    }

    /* Always use RGB palette. */
    SAIL_TRY(sail_alloc_palette(palette));
    (*palette)->pixel_format = SAIL_PIXEL_FORMAT_BPP24_RGB;
    (*palette)->color_count = png_palette_color_count;
    SAIL_TRY(sail_malloc(&(*palette)->data, png_palette_color_count * 3));

    unsigned char *palette_ptr = (*palette)->data;

    for (int i = 0; i < png_palette_color_count; i++) {
        *palette_ptr++ = png_palette[i].red;
        *palette_ptr++ = png_palette[i].green;
        *palette_ptr++ = png_palette[i].blue;
    }

    return SAIL_OK;
}

#ifdef PNG_APNG_SUPPORTED

sail_status_t blend_source(unsigned bytes_per_pixel, void *dst_raw, unsigned dst_offset, const void *src_raw, unsigned src_length) {

    SAIL_CHECK_PTR(dst_raw);
    SAIL_CHECK_PTR(src_raw);

    if (bytes_per_pixel == 4) {
        memcpy((uint8_t*)dst_raw + dst_offset, src_raw, src_length);
    } else if (bytes_per_pixel == 8) {
        memcpy((uint16_t*)dst_raw + dst_offset, src_raw, src_length);
    } else {
        return SAIL_ERROR_UNSUPPORTED_BIT_DEPTH;
    }

    return SAIL_OK;
}

sail_status_t blend_over(unsigned bytes_per_pixel, unsigned width, const void *src_raw, void *dst_raw, unsigned dst_offset) {

    SAIL_CHECK_PTR(src_raw);
    SAIL_CHECK_PTR(dst_raw);

    if (bytes_per_pixel == 4) {
        const uint8_t *src = src_raw;
        uint8_t *dst = (uint8_t *)dst_raw + dst_offset;

        while (width--) {
            const double src_a = *(src+3) / 255.0;
            const double dst_a = *(dst+3) / 255.0;

            *dst = (uint8_t)(src_a * (*src) + (1-src_a) * dst_a * (*dst)); src++; dst++;
            *dst = (uint8_t)(src_a * (*src) + (1-src_a) * dst_a * (*dst)); src++; dst++;
            *dst = (uint8_t)(src_a * (*src) + (1-src_a) * dst_a * (*dst)); src++; dst++;
            *dst = (uint8_t)((src_a + (1-src_a) * dst_a) * 255);           src++; dst++;
        }
    } else if (bytes_per_pixel == 8) {
        const uint16_t *src = src_raw;
        uint16_t *dst = (uint16_t *)dst_raw + dst_offset;

        while (width--) {
            const double src_a = *(src+3) / 65535.0;
            const double dst_a = *(dst+3) / 65535.0;

            *dst = (uint16_t)(src_a * (*src) + (1-src_a) * dst_a * (*dst)); src++; dst++;
            *dst = (uint16_t)(src_a * (*src) + (1-src_a) * dst_a * (*dst)); src++; dst++;
            *dst = (uint16_t)(src_a * (*src) + (1-src_a) * dst_a * (*dst)); src++; dst++;
            *dst = (uint16_t)((src_a + (1-src_a) * dst_a) * 65535);         src++; dst++;
        }
    } else {
        return SAIL_ERROR_UNSUPPORTED_BIT_DEPTH;
    }

    return SAIL_OK;
}

sail_status_t skip_hidden_frame(unsigned bytes_per_line, unsigned height, png_structp png_ptr, png_infop info_ptr, void **row) {

    SAIL_CHECK_PTR(png_ptr);
    SAIL_CHECK_PTR(info_ptr);
    SAIL_CHECK_PTR(row);

    SAIL_TRY(sail_malloc(row, bytes_per_line));

    png_read_frame_head(png_ptr, info_ptr);

    for (unsigned i = 0; i < height; i++) {
        png_read_row(png_ptr, (png_bytep)(*row), NULL);
    }

    sail_free(*row);
    *row = NULL;

    return SAIL_OK;
}

sail_status_t alloc_rows(png_bytep **A, unsigned row_length, unsigned height) {

    void *temp_ptr;
    SAIL_TRY(sail_malloc(&temp_ptr, height * sizeof(png_bytep)));

    *A = temp_ptr;

    for (unsigned row = 0; row < height; row++) {
        (*A)[row] = NULL;
    }

    for (unsigned row = 0; row < height; row++) {
        SAIL_TRY(sail_malloc(&(*A)[row], row_length));

        memset((*A)[row], 0, row_length);
    }

    return SAIL_OK;
}

void destroy_rows(png_bytep **A, unsigned height) {

    if (*A == NULL) {
        return;
    }

    for (unsigned row = 0; row < height; row++) {
        sail_free((*A)[row]);
    }

    sail_free(*A);
    *A = NULL;
}

#endif
