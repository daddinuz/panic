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

#include <panic.h>
#include <traits/traits.h>
#include "features.h"

void *context = NULL;

static void panicHandler(void) {
    assert_not_null(context);
    int *const theAnswer = context;
    *theAnswer = 42;
}

Feature(panic_registerHandler) {
    assert_null(panic_registerHandler(panicHandler));
    assert_equal(panicHandler, panic_registerHandler(NULL));
    assert_null(panic_registerHandler(panicHandler));

    context = traitsUnit_getContext();
    panic("Panicking");

    // unreachable
    assert_that(false);
}

Feature(panic_abort) {
    assert_null(panic_registerHandler(panicHandler));
    context = traitsUnit_getContext();

    panic_abort(TRACE, "Panicking");

    // unreachable
    assert_that(false);
}

Feature(panic_assertWith) {
    // Protect against double expansion.
    // 
    // Note:
    //      Ensuring that no handler is registered so that
    //      if `panic_assertWith` would not work properly,
    //      assertions in PanicTeardown won't pass.
    panic_registerHandler(NULL);
    int i = 1;
    panic_assertWith(TRACE, i--, "Unmet condition");
    assert_equal(0, i);

    // Registering the handler now, we are going to terminate the current thread.
    assert_null(panic_registerHandler(panicHandler));
    context = traitsUnit_getContext();

    panic_assertWith(TRACE, false, "Unmet condition");

    // unreachable
    assert_that(false);
}

Feature(panic_assert) {
    // Protect against double expansion.
    // 
    // Note:
    //      Ensuring that no handler is registered so that
    //      if `panic_assert` would not work properly,
    //      assertions in PanicTeardown won't pass.
    panic_registerHandler(NULL);
    int i = 1;
    panic_assert(i--, "Unmet condition");
    assert_equal(0, i);

    // Registering the handler now, we are going to terminate the current thread.
    assert_null(panic_registerHandler(panicHandler));
    context = traitsUnit_getContext();

    panic_assert(false, "Unmet condition");

    // unreachable
    assert_that(false);
}

Feature(panic) {
    assert_null(panic_registerHandler(panicHandler));
    context = traitsUnit_getContext();

    panic("Panicking");

    // unreachable
    assert_that(false);
}
