// <stdarg.h>
//
// Diagnostic header that prints out usage of items
// See canonical stdarg.h for documentation on contents

#ifndef DIAGNOSTIC_ISO_C18_STDARG_H
#define DIAGNOSTIC_ISO_C18_STDARG_H

#include <internal/carp.h>

typedef char* va_list;

#define va_arg(VA_LIST, ARG_TYPE) (__diagnostic_va_arg_impl(), *(ARG_TYPE*)((VA_LIST += sizeof(ARG_TYPE)) - sizeof(ARG_TYPE)))
#define va_copy(DEST_VA_LIST, SRC_VA_LIST) (void)(__diagnostic_va_copy_impl(), DEST_VA_LIST = SRC_VA_LIST)
#define va_end(VA_LIST) (void)(__diagnostic_va_end_impl(), VA_LIST = (va_list)0)
#define va_start(VA_LIST, VA_PARAM) (void)(__diagnostic_va_start_impl(), VA_LIST = (char*)&VA_PARAM)

void CARP("ISO C18: va_arg()") static inline __diagnostic_va_arg_impl() {}
void CARP("ISO C18: va_copy()") static inline __diagnostic_va_copy_impl() {}
void CARP("ISO C18: va_end()") static inline __diagnostic_va_end_impl() {}
void CARP("ISO C18: va_start()") static inline __diagnostic_va_start_impl() {}

#endif // DIAGNOSTIC_ISO_C18_STDARG_H
