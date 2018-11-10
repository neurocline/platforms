// include-assert.c

#include <assert.h>

#if defined(TEST_CANONICAL) && !defined(CANONICAL_ISO_C18_ASSERT_H)
#error "Expected the canonical assert.h header"
#endif

#if defined(TEST_DIAGNOSTIC) && !defined(DIAGNOSTIC_ISO_C18_ASSERT_H)
#error "Expected the diagnostic assert.h header"
#endif

#if defined(TEST_POSIX_ON_WIN32) && !defined(_POSIX_ON_WIN32__ASSERT_H)
#error "Expected the posix-on-win32 assert.h header"
#endif

// stub to prevent "empty compilation unit" warning
static void included() {}
