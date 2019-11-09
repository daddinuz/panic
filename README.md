# Panic

[![Build Status](https://travis-ci.org/daddinuz/panic.svg?branch=master)](https://travis-ci.org/daddinuz/panic)

A panic library to abort execution on non-recoverable errors with a detailed message.

```c
#include <stdio.h>
#include <panic.h>

double divide(const double dividend, const double divisor) {
    panic_when(0 == divisor);
    return dividend / divisor;
}

int main() {
    printf("%lf\r\n", divide(8, 0));
    return 0;
}
```

Output (with `PANIC_UNWIND_SUPPORT` enabled):

```text
Traceback (most recent call last):
  [0]: (main)
  ->-: (divide) current function

   At: '/panic/examples/main.c:37'
Cause: `0 == divisor`
```

### Optional features

#### PANIC_UNWIND_SUPPORT

Disabled by default, prints a traceback with function calls useful for debugging.  
Enable this feature running `cmake -DPANIC_UNWIND_SUPPORT=1` by command line or setting option to ON in `sources/build.cmake`.

**Note:** In order to enable this feature [libunwind](https://github.com/libunwind/libunwind) is required.
