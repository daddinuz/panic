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

static void panicHandler(void) {}

Feature(panic) {
    const size_t counter = traitsUnit_getWrappedSignalsCounter();

    traitsUnit_wrap(SIGABRT) {
        panic("%s", "A panic message");
    }

    assert_equal(traitsUnit_getWrappedSignalsCounter(), counter + 1);
}

Feature(panic_when) {
    const size_t counter = traitsUnit_getWrappedSignalsCounter();

    // protect against double expansion
    int i = 1;
    panic_when(i--);
    assert_equal(0, i);

    traitsUnit_wrap(SIGABRT) {
        panic_when(true);
    }

    assert_equal(traitsUnit_getWrappedSignalsCounter(), counter + 1);
    panic_when(false);
}

Feature(panic_unless) {
    const size_t counter = traitsUnit_getWrappedSignalsCounter();

    // protect against double expansion
    int i = 0;
    panic_unless(i++);
    assert_equal(1, i);

    traitsUnit_wrap(SIGABRT) {
        panic_unless(false);
    }

    assert_equal(traitsUnit_getWrappedSignalsCounter(), counter + 1);
    panic_unless(true);
}

Feature(handler) {
    assert_null(panic_register(panicHandler));
    assert_equal(panicHandler, panic_register(NULL));
}
