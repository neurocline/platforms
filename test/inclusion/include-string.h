// include-string.c

#include <string.h>

#if defined(TEST_CANONICAL) && !defined(CANONICAL_ISO_C18_STRING_H)
#error "Expected the canonical string.h header"
#endif

#if defined(TEST_DIAGNOSTIC) && !defined(DIAGNOSTIC_ISO_C18_STRING_H)
#error "Expected the diagnostic string.h header"
#endif

#if defined(TEST_POSIX_ON_WIN32) && !defined(_POSIX_ON_WIN32__STRING_H)
#error "Expected the posix-on-win32 string.h header"
#endif

// stub to prevent "empty compilation unit" warning
static void included() {}
