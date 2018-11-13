// include-limits.c

#include <limits.h>

#if defined(TEST_CANONICAL) && !defined(CANONICAL_ISO_C18_LIMITS_H)
#error "Expected the canonical limits.h header"
#endif

#if defined(TEST_DIAGNOSTIC) && !defined(DIAGNOSTIC_ISO_C18_LIMITS_H)
#error "Expected the diagnostic limits.h header"
#endif

#if defined(TEST_POSIX_ON_WIN32) && !defined(_POSIX_ON_WIN32_ISO_LIMITS_H)
#error "Expected the posix-on-win32 limits.h header"
#endif

// stub to prevent "empty compilation unit" warning
static void included() {}
