// carp.h

#ifndef CANONICAL_INTERNAL_CARP_CARP_H
#define CANONICAL_INTERNAL_CARP_CARP_H

// ---------------------------------------------------------------------------

#undef CARP_HAS_EXTENSION
#ifdef __has_extension
#define CARP_HAS_EXTENSION(EXTENSION) __has_extension(EXTENSION)
#else
#define CARP_HAS_EXTENSION(EXTENSION) 0
#endif

// Some compilers support "deprecated with custom message"

// C++14 introduced [[deprecated(msg)]]
#if defined(__cplusplus) && (__cplusplus >= 201402L)
#define CARP(msg) [[deprecated(msg)]]

// Clang with __has_extension(attribute_deprecated_with_message)
#elif CARP_HAS_EXTENSION(attribute_deprecated_with_message)
#define CARP(msg) __attribute__((deprecated(msg)))

// GCC 4.5 introduced __attribute__((deprecated(msg)))
#elif defined(__GNUC__) && (__GNUC__ * 10000 + __GNUC_MINOR__*100) >= 40500
#define CARP(msg) __attribute__((deprecated(msg)))

// MSVC 14 introduced __declspec(deprecated(msg))
#elif defined(_MSC_VER) && _MSC_VER >= 1400
#define CARP(msg) __declspec(deprecated(msg))

// -----------------------------------

// Some compilers just have "deprecated", without a custom message

// Clang with __has_extension(attribute_deprecated)
#elif CARP_HAS_EXTENSION(attribute_deprecated)
#define CARP(msg) __attribute__((deprecated))

// GCC 3.1 introduced __attribute__((deprecated))
#elif defined(__GNUC__) && (__GNUC__ * 10000 + __GNUC_MINOR__*100) >= 30100
#define CARP(msg) __attribute__((deprecated))

// MSVC 13.10 introduced __declspec(deprecated)
#elif defined(_MSC_VER) && _MSC_FULL_VER >= ((13 * 1000000) + (10 * 10000))
#define CARP(msg) __declspec(deprecated)

// -----------------------------------

// And then many compilers don't have this at all

#else
#pragma message("WARNING: This compiler probably can't implement CARP")
#define CARP(msg)
#endif

// ---------------------------------------------------------------------------

// Reference
// - Clang: https://clang.llvm.org/docs/LanguageExtensions.html
// - Clang: https://releases.llvm.org/3.1/tools/clang/docs/LanguageExtensions.html
// - GCC: https://gcc.gnu.org/onlinedocs/gcc/C-Extensions.html

#endif // CANONICAL_INTERNAL_CARP_CARP_H
