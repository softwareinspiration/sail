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

#ifndef SAIL_CODEC_LAYOUT_V3_H
#define SAIL_CODEC_LAYOUT_V3_H

/*
 * This is a codec layout definition file (version 3).
 *
 * It's intedened to be used as a reference how codecs V3 are organized. It's also could
 * be used by codecs' developers to compile their codecs directly into a testing application
 * to simplify debugging.
 */

#include <sail-common/error.h>
#include <sail-common/export.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Decoding functions.
 */

/*
 * Starts decoding the specified io stream using the specified options. The specified read options
 * will be deep copied into an internal buffer.
 *
 * STATE explanation: Pass the address of a local void* pointer. Codecs will store an internal state
 * in it and destroy it in sail_codec_read_finish_vx(). States must be used per image. DO NOT use the same state
 * to read multiple images in the same time.
 *
 * Returns 0 on success or sail_status_t on error.
 */
SAIL_EXPORT sail_status_t sail_codec_read_init_v3(struct sail_io *io, const struct sail_read_options *read_options, void **state);

/*
 * Seeks to the next frame. The frame is NOT immediately read or decoded by most SAIL codecs.
 * SAIL uses this method in reading and probing operations.
 *
 * SAIL uses sail_codec_read_seek_next_pass() + sail_codec_read_frame() to actually read the frame.
 * The assigned image MUST be destroyed later with sail_destroy_image() by the client.
 *
 * This method MUST allocate the image and the source image (sail_image.sail_source_image).
 * It MUST NOT allocate image pixels. They will be allocated by libsail and will be available in
 * sail_codec_read_seek_next_pass()/sail_codec_read_frame().
 *
 * Returns 0 on success or sail_status_t on error.
 */
SAIL_EXPORT sail_status_t sail_codec_read_seek_next_frame_v3(void *state, struct sail_io *io, struct sail_image **image);

/*
 * Seeks to the next pass if the specified image has multiple passes. Does nothing otherwise.
 *
 * Returns 0 on success or sail_status_t on error.
 */
SAIL_EXPORT sail_status_t sail_codec_read_seek_next_pass_v3(void *state, struct sail_io *io, const struct sail_image *image);

/*
 * Reads the next frame of the current image in the current pass. The image pixels are pre-allocated by libsail.
 *
 * Returns 0 on success or sail_status_t on error.
 */
SAIL_EXPORT sail_status_t sail_codec_read_frame_v3(void *state, struct sail_io *io, struct sail_image *image);

/*
 * Finilizes reading operation. No more readings are possible after calling this function.
 * This function doesn't close the io stream. It just stops decoding. Use io->close() or sail_destroy_io()
 * to actually close the io stream.
 *
 * Returns 0 on success or sail_status_t on error.
 */
SAIL_EXPORT sail_status_t sail_codec_read_finish_v3(void **state, struct sail_io *io);

/*
 * Encoding functions.
 */

/*
 * Starts encoding the specified io stream using the specified options. The specified write options
 * will be deep copied into an internal buffer.
 *
 * STATE explanation: Pass the address of a local void* pointer. Codecs will store an internal state
 * in it and destroy it in sail_codec_write_finish_vx(). States must be used per image. DO NOT use the same state
 * to write multiple images in the same time.
 *
 * Returns 0 on success or sail_status_t on error.
 */
SAIL_EXPORT sail_status_t sail_codec_write_init_v3(struct sail_io *io, const struct sail_write_options *write_options, void **state);

/*
 * Seeks to a next frame before writing it. The frame is NOT immediately written. Use sail_codec_write_seek_next_pass()
 * and sail_codec_write_frame() to actually write a frame.
 *
 * Returns 0 on success or sail_status_t on error.
 */
SAIL_EXPORT sail_status_t sail_codec_write_seek_next_frame_v3(void *state, struct sail_io *io, const struct sail_image *image);

/*
 * Seeks to a next pass before writing it if the specified image is interlaced. Does nothing otherwise.
 *
 * Returns 0 on success or sail_status_t on error.
 */
SAIL_EXPORT sail_status_t sail_codec_write_seek_next_pass_v3(void *state, struct sail_io *io, const struct sail_image *image);

/*
 * Writes a next frame of the current image in the current pass.
 *
 * Returns 0 on success or sail_status_t on error.
 */
SAIL_EXPORT sail_status_t sail_codec_write_frame_v3(void *state, struct sail_io *io, const struct sail_image *image);

/*
 * Finilizes writing operation. No more writings are possible after calling this function.
 * This function doesn't close the io stream. Use io->close() or sail_destroy_io() to actually
 * close the io stream.
 *
 * Returns 0 on success or sail_status_t on error.
 */
SAIL_EXPORT sail_status_t sail_codec_write_finish_v3(void **state, struct sail_io *io);

/* extern "C" */
#ifdef __cplusplus
}
#endif

#endif
