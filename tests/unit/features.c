/*
Author: daddinuz
email:  daddinuz@gmail.com

Copyright (c) 2018 Davide Di Carlo

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
 */

#include <panic.h>
#include <traits/traits.h>
#include "features.h"

Feature(Panic_terminate) {
    const size_t counter = traits_unit_get_wrapped_signals_counter();
    traits_unit_wraps(SIGABRT) {
        Panic_terminate("%s", "A panic message");
    }
    assert_equal(traits_unit_get_wrapped_signals_counter(), counter + 1);
}

Feature(Panic_when) {
    Panic_when(false);

    const size_t counter = traits_unit_get_wrapped_signals_counter();
    traits_unit_wraps(SIGABRT) {
        Panic_when(true);
    }
    assert_equal(traits_unit_get_wrapped_signals_counter(), counter + 1);
}

Feature(Panic_unless) {
    Panic_unless(true);

    const size_t counter = traits_unit_get_wrapped_signals_counter();
    traits_unit_wraps(SIGABRT) {
        Panic_unless(false);
    }
    assert_equal(traits_unit_get_wrapped_signals_counter(), counter + 1);
}
