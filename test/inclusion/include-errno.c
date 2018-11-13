// include-errno.c

#include <errno.h>

#if defined(TEST_CANONICAL) && !defined(CANONICAL_ISO_C18_ERRNO_H)
#error "Expected the canonical errno.h header"
#endif

#if defined(TEST_DIAGNOSTIC) && !defined(DIAGNOSTIC_ISO_C18_ERRNO_H)
#error "Expected the diagnostic errno.h header"
#endif

#if defined(TEST_POSIX_ON_WIN32) && !defined(_POSIX_ON_WIN32_ISO_ERRNO_H)
#error "Expected the posix-on-win32 errno.h header"
#endif

// stub to prevent "empty compilation unit" warning
static void included() {}
