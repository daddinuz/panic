/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2020 Davide Di Carlo
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

#pragma once

#include <trace/trace.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>

#if !defined(__GNUC__)
#define __attribute__(...)
#endif

/**
 * Type signature of the callback to be executed before terminating the current thread.
 */
typedef void (*PanicHandler)(void);

/**
 * Registers the handler function to execute before terminating the current thread.
 *
 * @param handler The function to be executed, if NULL nothing will be executed.
 * @return The previous registered handler if any else NULL.
 */
extern PanicHandler panic_register(PanicHandler handler);

/**
 * Reports the error and terminates execution of the current thread.
 * Takes printf-like arguments.
 */
#define panic(...) \
    __panic(__TRACE__, __VA_ARGS__)

/**
 * Panics if the condition is true.
 */
#define panic_when(c) \
    ((void) ((c) ? (panic("`%s` is false", stringify(c)), 0) : 0))

/**
 * Panics if the condition is false.
 */
#define panic_unless(c) \
    panic_when(!(c))

/*
 * @attention this function must be treated as opaque therefore must not be called directly.
 */
extern void __panic(const char *restrict trace, const char *restrict format, ...)
__attribute__((__noreturn__, __nonnull__(1, 2), __format__(__printf__, 2, 3)));

/*
 * @attention this function must be treated as opaque therefore must not be called directly.
 */
extern void __vpanic(const char *restrict trace, const char *restrict format, va_list args)
__attribute__((__noreturn__, __nonnull__(1, 2), __format__(__printf__, 2, 0)));

#ifdef __cplusplus
}
#endif
