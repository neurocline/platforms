// libcanonical.c

#include <stdio.h>
#include <stdlib.h>

#if defined(__cplusplus)
extern "C" {
#endif

#if 0
void __canonical_assert_impl(const char* assertion, const char* file,
               unsigned int line, const char* function)
{
    if (function != 0 && *function != 0)
        printf("Assertion failed: %s, file %s, line %d, function %s\n",
               assertion, file, line, function);
    else
        printf("Assertion failed: %s, file %s, line %d\n",
               assertion, file, line);
    abort();
}

// This is typically a function that converts the errnum to a error
// message string and then calls __canonical_assert_impl.
#if defined(__USE_GNU)
void __canonical_assert_perror_impl(int errnum, const char* file,
               unsigned int line, const char* function)
{
    if (errnum)
        __canonical_assert_perror_impl(errnum, file, line, function);

}
#endif
#endif

#if defined(__cplusplus)
}
#endif
