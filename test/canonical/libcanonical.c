// libcanonical.c

#if defined(__cplusplus)
extern "C" {
#endif

void __canonical_assert_impl(const char* assertion, const char* file,
               unsigned int line, const char* function) { assertion; file; line; function; }

// This is typically a function that converts the errnum to a error
// message string and then calls __canonical_assert_impl.
#if defined(__USE_GNU)
void __canonical_assert_perror_impl(int errnum, const char* file,
               unsigned int line, const char* function) {}
#endif

#if defined(__cplusplus)
}
#endif