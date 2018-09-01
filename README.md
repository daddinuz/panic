# Panic

A panic library to abort execution on non-recoverable errors with a detailed message.

### Examples

```c
#include <stdio.h>
#include <panic.h>

static FILE *stream = NULL;

void onTerminate(void) {
    if (NULL != stream) {
        fclose(stream);
    }
}

void ensureOpen(const char *path) {
    stream = fopen(path, "r");
    if (NULL == stream) {
        Panic_terminate("Unable to open file: %s", path);
    }
    Panic_registerCallback(onTerminate);
}

void ensureWrite(const char *message) {
    if (fputs(message, stream) < 0) {
        Panic_terminate("Unable to write to file");
    }
}

int main() {
    ensureOpen("/tmp/testfile");
    ensureWrite("Hello world!\n");
    fclose(stream);
    return 0;
}
```

Output (with `PANIC_UNWIND_SUPPORT` enabled):

```text

Traceback (most recent call last):
  [0]: (main)
  ->-: (ensureWrite) current function

   At: /home/guest/Workspace/panic/examples/main.c:49
Error: (22) Invalid argument
Cause: Unable to write to file

```

### Optional features

#### PANIC_UNWIND_SUPPORT

Disabled by default, prints a traceback with function calls useful for debugging.
Enable this feature running `cmake -DPANIC_UNWIND_SUPPORT=1` by command line or setting option to ON in `sources/build.cmake`.
**Note:** libunwind must be installed on the system in order to enable this feature.
