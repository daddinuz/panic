# Panic

[![Build Status](https://travis-ci.org/daddinuz/panic.svg?branch=master)](https://travis-ci.org/daddinuz/panic)

A panic library to abort execution of the current thread on non-recoverable errors with a detailed message.

```c
#include <stdlib.h>
#include <stdio.h>
#include <panic.h>

// thread local handler called before terminating the thread.
static void panicHandler(void) {
    fprintf(stderr, " Here: '%s:%d (%s)'\n", __FILE__, __LINE__, __func__);
}

// global handler called before terminating the whole program, this handler will run after panicHandler.
static void exitHandler(void) {
    fprintf(stderr, " Here: '%s:%d (%s)'\n", __FILE__, __LINE__, __func__);
}

static double divide(const double dividend, const double divisor) {
    panic_assert(0.000001 < divisor || divisor < -0.000001, "Division by zero");
    return dividend / divisor;
}

int main(void) {
    atexit(exitHandler);
    panic_registerHandler(panicHandler);
    printf("%f\r\n", divide(8, 0));
    return 0;
}
```

Output (with `PANIC_UNWIND_SUPPORT` enabled):

```text
Traceback (most recent call last):
  [0]: (main)
  ->-: (divide) current function

   At: '/panic/examples/main.c:43'
Cause: Division by zero
 Here: '/panic/examples/main.c:34 (panicHandler)'
 Here: '/panic/examples/main.c:39 (exitHandler)'
```

### Optional features

#### PANIC_UNWIND_SUPPORT

Disabled by default, prints a traceback with function calls useful for debugging.  
Enable this feature running `cmake -DPANIC_UNWIND_SUPPORT=1` by command line or setting option to ON in `sources/build.cmake`.

**Note:** In order to enable this feature [libunwind](https://github.com/libunwind/libunwind) is required.
