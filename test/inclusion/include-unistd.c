// include-unistd.c

#include <unistd.h>

#if defined(TEST_CANONICAL) && !defined(CANONICAL_POSIX_2017_UNISTD_H)
#error "Expected the canonical unistd.h header"
#endif

#if defined(TEST_DIAGNOSTIC) && !defined(DIAGNOSTIC_POSIX_2017_UNISTD_H)
#error "Expected the diagnostic unistd.h header"
#endif

#if defined(TEST_POSIX_ON_WIN32) && !defined(_POSIX_ON_WIN32__UNISTD_H)
#error "Expected the posix-on-win32 unistd.h header"
#endif

// stub to prevent "empty compilation unit" warning
static void included() {}
