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

#ifndef SAIL_ICCP_CPP_H
#define SAIL_ICCP_CPP_H

#ifdef SAIL_BUILD
    #include "error.h"
    #include "export.h"
#else
    #include <sail-common/error.h>
    #include <sail-common/export.h>
#endif

struct sail_iccp;

namespace sail
{

/*
 * ICC profile representation. It provides access to raw ICC profile data.
 */
class SAIL_EXPORT iccp
{
    friend class image;

public:
    iccp();
    iccp(const iccp &ic);
    iccp& operator=(const iccp &ic);
    ~iccp();

    /*
     * Returns true if the ICC profile has non-NULL data. It doesn't validate the data.
     */
    bool is_valid() const;

    /*
     * Returns the ICC profile binary data.
     */
    const void* data() const;

    /*
     * Returns the length of the ICC binary data.
     */
    unsigned data_length() const;

    /*
     * Sets a new ICC profile binary data.
     */
    iccp& with_data(const void *data, unsigned data_length);

private:
    /*
     * Makes a deep copy of the specified ICC profile.
     */
    iccp(const sail_iccp *ic);

    sail_status_t to_sail_iccp(sail_iccp *ic) const;

private:
    class pimpl;
    pimpl * const d;
};

}

#endif
