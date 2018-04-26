/*
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 *
 * Copyright (c) 2018 Davide Di Carlo
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "panic.h"

#define __str(x)    #x
#define str(x)      __str(x)

const char *
panic_version(void) {
    return (PANIC_VERSION_IS_RELEASE || sizeof(PANIC_VERSION_SUFFIX) <= 1)
           ?
           str(PANIC_VERSION_MAJOR) "."
           str(PANIC_VERSION_MINOR)
           "."
           str(PANIC_VERSION_PATCH)
           :
           str(PANIC_VERSION_MAJOR)
           "."
           str(PANIC_VERSION_MINOR)
           "."
           str(PANIC_VERSION_PATCH)
           "-"
           PANIC_VERSION_SUFFIX;
}

void __panic(const char *file, int line, const char *format, ...) {
    assert(file);
    assert(format);
    va_list args;
    va_start(args, format);
    __panic_variadic(file, line, format, args);
}

void __panic_variadic(const char *file, int line, const char *format, va_list args) {
    assert(file);
    assert(format);
    fprintf(stderr, "\nAt: %s:%d:\n", file, line);
    if (errno != 0) {
        fprintf(stderr, "errno: (%d) %s\n", errno, strerror(errno));
    }
    vfprintf(stderr, format, args);
    va_end(args);
    abort();
}
