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

#ifndef SAIL_IO_MEM_H
#define SAIL_IO_MEM_H

#include <stddef.h>

#ifdef SAIL_BUILD
    #include "error.h"
    #include "export.h"
#else
    #include <sail/error.h>
    #include <sail/export.h>
#endif

struct sail_io;

/*
 * Opens the specified memory buffer for reading and allocates a new I/O object for it.
 * The assigned I/O object MUST be destroyed later with sail_destroy_io().
 *
 * Returns 0 on success or sail_error_t on error.
 */
SAIL_HIDDEN sail_error_t alloc_io_read_mem(const void *buffer, size_t buffer_length, struct sail_io **io);

/*
 * Opens the specified memory buffer for writing and allocates a new I/O object for it.
 * The assigned I/O object MUST be destroyed later with sail_destroy_io().
 *
 * Returns 0 on success or sail_error_t on error.
 */
SAIL_HIDDEN sail_error_t alloc_io_write_mem(void *buffer, size_t buffer_length, struct sail_io **io);

#endif