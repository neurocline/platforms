// libdiagnostic.c

#if defined(__cplusplus)
extern "C" {
#endif

void __diagnostic_assert_impl(const char* assertion, const char* file,
               unsigned int line, const char* function)
{
    if (assertion)
        __diagnostic_assert_impl(assertion, file, line, function);
}

#if defined(__cplusplus)
}
#endif
