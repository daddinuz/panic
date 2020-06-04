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
    printf(" `here` ");
    panic("%s", "A panic message");
    printf(" `can't see this` ");
    assert_that(false);
}

Feature(panic_assert) {
    // protect against double expansion
    int i = 1;
    printf(" `step 1` ");
    panic_assert(i--);
    printf(" `step 2` ");
    assert_equal(0, i);

    printf(" `step 3` ");
    panic_assert(false);
    printf(" `can't see this` ");
    assert_that(false);
}

Feature(panic_handler) {
    assert_null(panic_registerHandler(panicHandler));
    assert_equal(panicHandler, panic_registerHandler(NULL));
}
