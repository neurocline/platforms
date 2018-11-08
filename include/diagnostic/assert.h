// assert.h
//
// Diagnostic header that prints out usage of items
// See canonical assert.h for documentation on contents

#include <internal/carp.h>

// __func__ didn't exist until C99 and C++11, so use
// empty string before that point. This is a good place to insert
// platform-specific __func__ workarounds.
#undef __FUNC__
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) \
    || (defined(__cplusplus) && __cplusplus >= 201103L)
#define __FUNC__ __func__
#else
#define __FUNC__ ""
#endif

#define assert(condition) \
    __diagnostic_assert_impl(#condition, __FILE__, __LINE__, __FUNC__)

void CARP("ISO C99: assert()") \
__diagnostic_assert_impl(const char* assertion, const char* file,
               unsigned int line, const char* function);
