// include-sys_types.c

#include <sys/types.h>

#if defined(TEST_CANONICAL) && !defined(CANONICAL_POSIX_2017_SYS_TYPES_H)
#error "Expected the canonical sys/types.h header"
#endif

#if defined(TEST_DIAGNOSTIC) && !defined(DIAGNOSTIC_POSIX_2017_SYS_TYPES_H)
#error "Expected the diagnostic sys/types.h header"
#endif

#if defined(TEST_POSIX_ON_WIN32) && !defined(_POSIX_ON_WIN32__SYS_TYPES_H)
#error "Expected the posix-on-win32 sys/types.h header"
#endif

// stub to prevent "empty compilation unit" warning
static void included() {}
