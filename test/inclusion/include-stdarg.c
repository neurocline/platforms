// include-stdarg.c

#include <stdarg.h>

#if defined(TEST_CANONICAL) && !defined(CANONICAL_ISO_C18_STDARG_H)
#error "Expected the canonical stdarg.h header"
#endif

#if defined(TEST_DIAGNOSTIC) && !defined(DIAGNOSTIC_ISO_C18_STDARG_H)
#error "Expected the diagnostic stdarg.h header"
#endif

#if defined(TEST_POSIX_ON_WIN32) && !defined(_POSIX_ON_WIN32__STDARG_H)
#error "Expected the posix-on-win32 stdarg.h header"
#endif

// stub to prevent "empty compilation unit" warning
static void included() {}
