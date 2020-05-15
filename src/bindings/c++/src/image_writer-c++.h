/*  This file is part of SAIL (https://github.com/smoked-herring/sail)

    Copyright (c) 2020 Dmitry Baryshev <dmitrymq@gmail.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 3 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this library. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef SAIL_IMAGE_WRITER_CPP_H
#define SAIL_IMAGE_WRITER_CPP_H

#include <cstddef>
#include <string>

#ifdef SAIL_BUILD
    #include "error.h"
    #include "export.h"
#else
    #include <sail-common/error.h>
    #include <sail-common/export.h>
#endif

namespace sail
{

class context;
class image;
class io;
class plugin_info;
class write_options;

/*
 * A C++ interface to the SAIL image writing functions.
 */
class SAIL_EXPORT image_writer
{
public:
    image_writer();
    image_writer(context *ctx);
    ~image_writer();

    bool is_valid() const;

    /*
     * An interface to sail_write(). See sail_write() for more.
     *
     * WARNING: These functions allocate a local static context and never destroy it. ASAN will report
     * memory leaks which is OK.
     */
    sail_error_t write(const std::string &path, const image &simage);
    sail_error_t write(const char *path, const image &simage);

    /*
     * An interface to sail_start_writing(). See sail_start_writing() for more.
     */
    sail_error_t start_writing(const std::string &path);
    sail_error_t start_writing(const char *path);

    /*
     * An interface to sail_start_writing(). See sail_start_writing() for more.
     */
    sail_error_t start_writing(const std::string &path, const plugin_info &splugin_info);
    sail_error_t start_writing(const char *path, const plugin_info &splugin_info);

    /*
     * An interface to sail_start_writing_with_options(). See sail_start_writing_with_options() for more.
     */
    sail_error_t start_writing(const std::string &path, const write_options &swrite_options);
    sail_error_t start_writing(const char *path, const write_options &swrite_options);

    /*
     * An interface to sail_start_writing_with_options(). See sail_start_writing_with_options() for more.
     */
    sail_error_t start_writing(const std::string &path, const plugin_info &splugin_info, const write_options &swrite_options);
    sail_error_t start_writing(const char *path, const plugin_info &splugin_info, const write_options &swrite_options);

    /*
     * An interface to sail_start_writing_mem(). See sail_start_writing_mem() for more.
     */
    sail_error_t start_writing(void *buffer, size_t buffer_length, const plugin_info &splugin_info);
    sail_error_t start_writing(void *buffer, size_t buffer_length, const plugin_info &splugin_info, const write_options &swrite_options);

    /*
     * An interface to sail_start_writing_io(). See sail_start_writing_io() for more.
     */
    sail_error_t start_writing(const io &sio, const plugin_info &splugin_info);
    sail_error_t start_writing(const io &sio, const plugin_info &splugin_info, const write_options &swrite_options);

    /*
     * An interface to sail_write_next_frame(). See sail_write_next_frame() for more.
     */
    sail_error_t write_next_frame(const image &simage);

    /*
     * An interface to sail_stop_writing(). See sail_stop_writing() for more.
     */
    sail_error_t stop_writing();

    /*
     * An interface to sail_stop_writing_with_written(). See sail_stop_writing_with_written() for more.
     */
    sail_error_t stop_writing(size_t *written);

private:
    class pimpl;
    pimpl * const d;
};

}

#endif