// include-time.c

#include <time.h>

#if defined(TEST_CANONICAL) && !defined(CANONICAL_ISO_C18_TIME_H)
#error "Expected the canonical time.h header"
#endif

#if defined(TEST_DIAGNOSTIC) && !defined(DIAGNOSTIC_ISO_C18_TIME_H)
#error "Expected the diagnostic time.h header"
#endif

#if defined(TEST_POSIX_ON_WIN32) && !defined(_POSIX_ON_WIN32__TIME_H)
#error "Expected the posix-on-win32 time.h header"
#endif

// stub to prevent "empty compilation unit" warning
static void included() {}
