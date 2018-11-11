// include-stdio.c

#include <stdio.h>

#if defined(TEST_CANONICAL) && !defined(CANONICAL_ISO_C18_STDIO_H)
#error "Expected the canonical stdio.h header"
#endif

#if defined(TEST_DIAGNOSTIC) && !defined(DIAGNOSTIC_ISO_C18_STDIO_H)
#error "Expected the diagnostic stdio.h header"
#endif

#if defined(TEST_POSIX_ON_WIN32) && !defined(_POSIX_ON_WIN32__STDIO_H)
#error "Expected the posix-on-win32 stdio.h header"
#endif

// stub to prevent "empty compilation unit" warning
static void included() {}
