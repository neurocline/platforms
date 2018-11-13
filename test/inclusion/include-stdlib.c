// include-stdlib.c

#include <stdlib.h>

#if defined(TEST_CANONICAL) && !defined(CANONICAL_ISO_C18_STDLIB_H)
#error "Expected the canonical stdlib.h header"
#endif

#if defined(TEST_DIAGNOSTIC) && !defined(DIAGNOSTIC_ISO_C18_STDLIB_H)
#error "Expected the diagnostic stdlib.h header"
#endif

#if defined(TEST_POSIX_ON_WIN32) && !defined(_POSIX_ON_WIN32_ISO_STDLIB_H)
#error "Expected the posix-on-win32 stdlib.h header"
#endif

// stub to prevent "empty compilation unit" warning
static void included() {}
