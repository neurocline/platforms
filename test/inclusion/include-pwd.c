// include-pwd.c

#include <pwd.h>

#if defined(TEST_CANONICAL) && !defined(CANONICAL_POSIX_2017_PWD_H)
#error "Expected the canonical pwd.h header"
#endif

#if defined(TEST_DIAGNOSTIC) && !defined(DIAGNOSTIC_POSIX_2017_PWD_H)
#error "Expected the diagnostic pwd.h header"
#endif

#if defined(TEST_POSIX_ON_WIN32) && !defined(_POSIX_ON_WIN32_POSIX_PWD_H)
#error "Expected the posix-on-win32 pwd.h header"
#endif

// stub to prevent "empty compilation unit" warning
static void included() {}
