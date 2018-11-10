// include-fcntl.c

#include <fcntl.h>

#if defined(TEST_CANONICAL) && !defined(CANONICAL_POSIX_2017_FCNTL_H)
#error "Expected the canonical fcntl.h header"
#endif

#if defined(TEST_DIAGNOSTIC) && !defined(DIAGNOSTIC_POSIX_2017_FCNTL_H)
#error "Expected the diagnostic fcntl.h header"
#endif

#if defined(TEST_POSIX_ON_WIN32) && !defined(_POSIX_ON_WIN32__FCNTL_H)
#error "Expected the posix-on-win32 fcntl.h header"
#endif

// stub to prevent "empty compilation unit" warning
static void included() {}
