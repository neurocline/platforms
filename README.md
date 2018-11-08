# Platforms

This repo describes platform headers of all kinds, and tools used
to extract out information.

## Canonical headers

What would canonical headers for ISO C, POSIX, C++ etc look like? "Real"
headers are full of all kinds of implementation details. Is there a place
for minimal perfect headers, as a complement to standards documentation?
Ones that make some implementation decisions?

This is in `include/canonical`.

To emulate specific environments:

- POSIX: set `_POSIX_C_SOURCE` to an appropriate value
- LINUX: define `_GNU_SOURCE` (will add more at some point)
- Windows: define `_WIN32`/`_WIN64`, set `_WIN32_WINNT` and `WINVER` to an appropriate value

## Diagnostic headers

What about headers you could include that would then tell you everything
that the code in question is using? These are complete headers, but
with output that can be scraped and coalesced to create reports.

This is in `include/diagnostic`.

## POSIX

IEEE Std 1003.1 and POSIX.1 refer to the same thing. We use the latter for brevity.

Feature setting (note that this has to be manually set by the user, no compiler can
infer it). Also note that all the revisions past 2008 are still identified by the
same feature version.

- POSIX.1-1990: `_POSIX_SOURCE` is defined (obsolete feature macro)
- POSIX.1-1990: `_POSIX_C_SOURCE` is `1`
- POSIX.1-1992: `_POSIX_C_SOURCE` is `2`
- POSIX.1-1993: `_POSIX_C_SOURCE` is `199309L`
- POSIX.1-1995: `_POSIX_C_SOURCE` is `199506L`
- POSIX.1-2001: `_POSIX_C_SOURCE` is `200112L`
- POSIX.1-2008: `_POSIX_C_SOURCE` is `200809L`
- POSIX.1-2017: `_POSIX_C_SOURCE` is `200809L`

## ISO C

- C89: ANSI X3.159-1989
- C90: ISO/IEC 9899:1990
- C95/AMD1: ISO/IEC 9899:1990/AMD 1:1995
- C99: ISO/IEC 9899:1999 [N1256](http://www.open-std.org/jtc1/sc22/WG14/www/docs/n1256.pdf)
- C11: ISO/IEC 9899:2011 [N1570](http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf)
- C17/C18: ISO/IEC 9899:2018 [N2176](http://www.open-std.org/jtc1/sc22/wg14/www/abq/c17_updated_proposed_fdis.pdf)
  - [N2244: Clarification Request Summary for C11](http://www.open-std.org/jtc1/sc22/wg14/www/docs/n2244.htm)

Feature test

- C90: `__STDC_VERSION__` has no value
- C95: `__STDC_VERSION__` is `199401L`
- C99: `__STDC_VERSION__` is `199001L`
- C11: `__STDC_VERSION__` is `201112L`

## ISO C++

- C++98: ISO/IEC 14882:1998
- C++03: ISO 14882:2003
- C++11: ISO/IEC 14882:2011
- C++14: ISO/IEC 14882:2014
- C++17: ISO/IEC 14882:2017 [N3797](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3797.pdf)

Feature test

- C++ older: `__cplusplus` is `1`
- C++98: `__cplusplus` is `199711L`
- C++11: `__cplusplus` is `201103L`
- C++14: `__cplusplus` is `201402L`
- C++17: `__cplusplus` is `201703L`

## Windows

Feature test (`WINVER` set to same value)

- Windows NT 4.0: `_WIN32_WINNT` is `0x0400` (`_WIN32_WINNT_NT4`)
- Windows 2000: `_WIN32_WINNT` is `0x0500` (`_WIN32_WINNT_WIN2K`)
- Windows XP: `_WIN32_WINNT` is `0x0501` (`_WIN32_WINNT_WINXP`)
- Windows Server 2003: `_WIN32_WINNT` is `0x0502` (`_WIN32_WINNT_WS03`)
- Windows Vista: `_WIN32_WINNT` is `0x0600` (`_WIN32_WINNT_VISTA`, `_WIN32_WINNT_WIN6`, `_WIN32_WINNT_LONGHORN`)
- Windows Server 2008: `_WIN32_WINNT` is `0x0600` (`_WIN32_WINNT_WS08`)
- Windows 7: `WIN32_WINNT` is `0x0601` (`_WIN32_WINNT_WIN7`)
- Windows 8: `WIN32_WINNT` is `0x0602` (`_WIN32_WINNT_WIN8`)
- Windows 8.1: `WIN32_WINNT` is `0x0603` (`_WIN32_WINNT_WINBLUE`)
- Windows 10: `WIN32_WINNT` is `0x0A00` (`_WIN32_WINNT_WIN10`, `_WIN32_WINNT_WINTHRESHOLD`)
