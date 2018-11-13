#! python3
# coding=utf-8

import glob
import os
import sys

def main():
    master = sys.argv[1]
    canonical = sys.argv[2]
    diagnostic = sys.argv[3]
    posix = sys.argv[4]

    for path in glob.glob("%s/**" % master, recursive=True):
        if os.path.isdir(path):
            continue
        print("path: %s" % path)
        parse(path, master, canonical, diagnostic, posix)

def parse(path, master, canonical, diagnostic, posix):
    print("Reading master from %s" % path)
    make_canonical(path, master, canonical)
    make_diagnostic(path, master, diagnostic)
    make_posix(path, master, posix)

def make_canonical(path, master, canonical):
    header = path[len(master)+1:].replace('\\', '/')
    hdir = os.path.join(canonical, os.path.dirname(header))
    if not os.path.exists(hdir):
        os.mkdir(hdir)

    target = canonical + path[len(master):]
    guard = make_guard("CANONICAL_ISO_C18", header)
    posix_guard = make_guard("CANONICAL_POSIX_2017", header)
    # print("Guard is %s" % guard)
    #if os.path.exists(target):
    #    print("Skipping - existing %s" % target)
    #    return

    print("Writing canonical to %s" % target)
    lines = loadfile(path)
    lines = canonical_markup(lines, guard, posix_guard)

    with open(target, "wt", encoding="utf-8") as fout:
        for line in lines:
            print("%s" % line, file=fout)

def canonical_markup(lines, guard, posix_guard):
    n = len(lines)
    i = 0
    while i < n:
        line = lines[i]
        #print("%d/%d: %s" % (i, n, line))
        i = i + 1

        # in canonical output, strip everything bracketed
        # in [!MSVCRT]..[/!MSVCRT]
        if line == '[!MSVCRT]':
            e = find_section(lines, i, '[/!MSVCRT]')
            #print("removing", lines[i-1:e+1])
            del lines[i-1:e+1]
            n = n - (e - i + 2)
            if n != len(lines):
                raise Exception("math", n, len(lines))
            i = i - 1
            #print("remaining %d/%d" % (i, n), lines[i:])
            continue

        # Our canonical header
        if line == '[BODY]':
            replaced = [
                '// ---------------------------------------------------------------------------',
                '// Canonical header',
                '']
            #print("expanded", replaced)
            lines[i-1:i] = replaced
            n = n + len(replaced) - 1
            if n != len(lines):
                raise Exception("math", n, len(lines))
            i = i + len(replaced) - 1
            continue

        replaced = expand_line(line, guard, posix_guard)
        if replaced is not None:
            #print("expanded", replaced)
            lines[i-1:i] = replaced
            n = n + len(replaced) - 1
            if n != len(lines):
                raise Exception("math", n, len(lines))
            i = i + len(replaced) - 1
            continue

        # in canonical output, posix-only annotations disappear from output
        if line in ('[MSVCRT]', '[/MSVCRT]', '[FOOTER]','[NOWINDOWS]', '[IGNOREWINDOWS]', '[MICROSOFT_VC_INCLUDE]'):
            #print("removed", lines[i-1:i])
            del lines[i-1:i]
            n = n - 1
            if n != len(lines):
                raise Exception("math", n, len(lines))
            i = i - 1
            continue

        # in canonical output, [CARP] disappears
        pos = line.find('[CARP')
        if pos != -1:
            stripcarp = line[0:pos] + line[line.find(']',pos)+1:]
            #print("replaced", stripcarp)
            lines[i-1] = stripcarp
            continue

    return lines

def make_diagnostic(path, master, diagnostic):
    header = path[len(master)+1:].replace('\\', '/')
    hdir = os.path.join(diagnostic, os.path.dirname(header))
    if not os.path.exists(hdir):
        os.mkdir(hdir)

    target = diagnostic + path[len(master):]
    guard = make_guard("DIAGNOSTIC_ISO_C18", header)
    posix_guard = make_guard("DIAGNOSTIC_POSIX_2017", header)
    #print("Guard is %s" % guard)
    #if os.path.exists(target):
    #    print("Skipping - existing %s" % target)
    #    return

    print("Writing diagnostic to %s" % target)
    lines = loadfile(path)
    lines = diagnostic_markup(lines, guard, posix_guard)

    with open(target, "wt", encoding="utf-8") as fout:
        for line in lines:
            print("%s" % line, file=fout)

def diagnostic_markup(lines, guard, posix_guard):
    carpmap = {'[C99]': 'ISO C99', '[C11]': 'ISO C11', '[C18]': 'ISO C18',
               '[POSIX]': 'POSIX 2017.1', '[Glibc]': 'Glibc', '[Microsoft]': 'Microsoft'}
    carp_kind = 'ISO C95'
    n = len(lines)
    i = 0
    while i < n:
        line = lines[i]
        #print("%d/%d: %s" % (i, n, line))
        i = i + 1

        # in diagnostic output, strip everything bracketed
        # in [!MSVCRT]..[/!MSVCRT]
        if line == '[!MSVCRT]':
            e = find_section(lines, i, '[/!MSVCRT]')
            #print("removing", lines[i-1:e+1])
            del lines[i-1:e+1]
            n = n - (e - i + 2)
            if n != len(lines):
                raise Exception("math", n, len(lines))
            i = i - 1
            #print("remaining %d/%d" % (i, n), lines[i:])
            continue

        # Our diagnostic header
        if line == '[BODY]':
            replaced = [
                '#include <internal/carp.h>',
                '',
                '// ---------------------------------------------------------------------------',
                '// Diagnostic header',
                '']
            #print("expanded", replaced)
            lines[i-1:i] = replaced
            n = n + len(replaced) - 1
            if n != len(lines):
                raise Exception("math", n, len(lines))
            i = i + len(replaced) - 1
            continue

        # preflight for ISO, POSIX, Glibc, Microsoft to change carp_kind
        if line in carpmap:
            carp_kind = carpmap[line]

        # Do common expansions
        replaced = expand_line(line, guard, posix_guard)
        if replaced is not None:
            #print("expanded", replaced)
            lines[i-1:i] = replaced
            n = n + len(replaced) - 1
            if n != len(lines):
                raise Exception("math", n, len(lines))
            i = i + len(replaced) - 1
            continue

        # in diagnostic output, posix-only annotations disappear from output
        if line in ('[MSVCRT]', '[/MSVCRT]', '[FOOTER]','[NOWINDOWS]', '[IGNOREWINDOWS]', '[MICROSOFT_VC_INCLUDE]'):
            #print("removed", lines[i-1:i])
            del lines[i-1:i]
            n = n - 1
            if n != len(lines):
                raise Exception("math", n, len(lines))
            i = i - 1
            continue

        # in canonical output, [CARP] expands
        pos = line.find('[CARP')
        if pos != -1:
            e = line.find(']', pos+1)
            carpmsg = 'CARP("%s:%s") ' % (carp_kind, line[pos+5:e])
            #print("replaced", carpmsg)
            lines[i-1] = line[0:pos] + carpmsg + line[e+1:]

    return lines

def make_posix(path, master, posix):
    header = path[len(master)+1:].replace('\\', '/')
    hdir = os.path.join(posix, os.path.dirname(header))
    if not os.path.exists(hdir):
        os.mkdir(hdir)

    target = posix + path[len(master):]
    guard = make_guard("_POSIX_ON_WIN32_ISO", header)
    posix_guard = make_guard("_POSIX_ON_WIN32_POSIX", header)
    #print("Guard is %s" % guard)
    #if os.path.exists(target):
    #    print("Skipping - existing %s" % target)
    #    return

    print("Writing posix-on-win32 to %s" % target)
    lines = loadfile(path)
    lines = posix_markup(lines, guard, posix_guard, header)

    with open(target, "wt", encoding="utf-8") as fout:
        for line in lines:
            print("%s" % line, file=fout)

def posix_markup(lines, guard, posix_guard, header):
    nowindows = False
    ignoreWindows = False
    vcInclude = False
    n = len(lines)
    i = 0
    while i < n:
        line = lines[i]
        #print("%d/%d: %s" % (i, n, line))
        i = i + 1

        # [NOWINDOWS] means we don't need to include a Windows
        # header (because it doesn't exist)
        if line == '[NOWINDOWS]':
            nowindows = True
            del lines[i-1:i]
            n = n - 1
            i = i - 1
            continue

        # [IGNOREWINDOWS] means we don't include the existing
        # Windows header (it's not useful for our purpose)
        if line == '[IGNOREWINDOWS]':
            ignoreWindows = True
            del lines[i-1:i]
            n = n - 1
            i = i - 1
            continue

        # [MICROSOFT_VC_INCLUDE] means we include_next from the VC
        # compiler hierarchy rather than the Windows Kit
        if line == '[MICROSOFT_VC_INCLUDE]':
            vcInclude = True
            del lines[i-1:i]
            n = n - 1
            i = i - 1
            continue

        # in posix output, strip everything bracketed
        # in [MSVCRT]..[/MSVCRT]
        if line == '[MSVCRT]':
            e = find_section(lines, i, '[/MSVCRT]')
            #print("removed", lines[i-1:e+1])
            del lines[i-1:e+1]
            n = n - (e - i + 2)
            if n != len(lines):
                raise Exception("math", n, len(lines))
            i = i - 1
            continue

        # Our posix header
        if line == '[BODY]':
            replaced = posix_header(header, vcInclude, nowindows, ignoreWindows)
            #print("expanded", replaced)
            lines[i-1:i] = replaced
            n = n + len(replaced) - 1
            if n != len(lines):
                raise Exception("math", n, len(lines))
            i = i + len(replaced) - 1
            continue

        # Our posix footer
        if line == '[FOOTER]':
            replaced = posix_footer(header, nowindows, ignoreWindows)
            #print("expanded", replaced)
            lines[i-1:i] = replaced
            n = n + len(replaced) - 1
            if n != len(lines):
                raise Exception("math", n, len(lines))
            i = i + len(replaced) - 1
            continue

        replaced = expand_line(line, guard, posix_guard)
        if replaced is not None:
            #print("expanded", replaced)
            lines[i-1:i] = replaced
            n = n + len(replaced) - 1
            if n != len(lines):
                raise Exception("math", n, len(lines))
            i = i + len(replaced) - 1
            continue

        # in posix output, [!MSVCRT] disappears but not
        # the bracketed lines
        if line == '[!MSVCRT]' or line == '[/!MSVCRT]':
            #print("removed", lines[i-1:i])
            del lines[i-1:i]
            n = n - 1
            if n != len(lines):
                raise Exception("math", n, len(lines))
            i = i - 1
            continue

        # in posix output, [CARP] disappears
        pos = line.find('[CARP')
        if pos != -1:
            stripcarp = line[0:pos] + line[line.find(']',pos)+1:]
            #print("replaced", stripcarp)
            lines[i-1] = stripcarp
            continue

    return lines

def posix_header(header, vcInclude, nowindows, ignoreWindows):
    if nowindows:
        return [
            '// There is no Windows <%s> file, so we don\'t need to override anything.' % header,
            '',
            '// ---------------------------------------------------------------------------',
            '// POSIX on Win32 header',
            '']

    macroize = header.upper().replace('.', '_').replace('/', '_').replace('\\', '_')
    macroize = macroize[:-2]
    guard_no = '_POSIX_ON_WIN32_NO_WIN32_' + macroize
    guard_use = '_POSIX_ON_WIN32_USE_WIN32_' + macroize

    includenext = 'VC' if vcInclude else 'UCRT'

    # On the ignoreWindows path, we don't include a Windows header and
    # we put our code in the else path
    if ignoreWindows:
        return [
            '// Default to not using the Windows %s file' % header,
            '#ifndef %s' % guard_no,
            '// #define %s' % guard_use,
            '#endif',
            '',
            '// -----------------------------------------------------------------------------------------------',
            '',
            '#if defined(%s)' % guard_use,
            '',
            '#error "This path not supported"',
            '',
            #'// Get MSVC emulation of #include_next',
            #'// #include <posix_win32_include_next.h>',
            #'',
            #'// #pragma push_macro("_CRT_NO_TIME_T")',
            #'// #undef _CRT_NO_TIME_T',
            #'// #define _CRT_NO_TIME_T',
            #'// #include _MICROSOFT_%s_INCLUDE_NEXT(%s)' % (includenext, header),
            #'// #pragma pop_macro("_CRT_NO_TIME_T")',
            #'',
            '#endif // defined(%s)' % guard_use,
            '',
            '// -----------------------------------------------------------------------------------------------',
            '',
            '#if !defined(%s)' % guard_use,
            '',
        ]

    lines = [
        '// Default to using the Windows %s file' % header,
        '#ifndef %s' % guard_no,
        '#define %s' % guard_use,
        '#endif',
        '',
        '// -----------------------------------------------------------------------------------------------',
        '',
        '#if defined(%s)' % guard_use,
        ''
        '// Get MSVC emulation of #include_next',
        '#include <posix_win32_include_next.h>',
        '',
        '#pragma push_macro("_CRT_NO_TIME_T")',
        '#pragma push_macro("_CRT_NONSTDC_NO_DEPRECATE")',
        '#undef _CRT_NO_TIME_T',
        '#define _CRT_NO_TIME_T',
        '#undef _CRT_NONSTDC_NO_DEPRECATE',
        '#define _CRT_NONSTDC_NO_DEPRECATE',
    ]
    if header != 'errno.h':
        lines.append('#include _MICROSOFT_%s_INCLUDE_NEXT(%s)' % (includenext, header))
    else:
        lines.extend([
            '#ifdef errno',
            '#pragma push_macro("errno")',
            '#undef errno',
            '#include _MICROSOFT_%s_INCLUDE_NEXT(%s)' % (includenext, header),
            '#pragma pop_macro("errno")',
            '#else',
            '#include _MICROSOFT_%s_INCLUDE_NEXT(%s)' % (includenext, header),
            '#endif',
        ])
    lines.extend([
        '#pragma pop_macro("_CRT_NONSTDC_NO_DEPRECATE")',
        '#pragma pop_macro("_CRT_NO_TIME_T")',
        '',
    ])
    return lines

# TBD fix files so that we don't have blank lines at the end, it's
# caused by the ordering of [FOOTER] and [GUARD] in files like assert.h
def posix_footer(header, nowindows, ignoreWindows):
    if nowindows:
        return []

    macroize = header.upper().replace('.', '_').replace('/', '_').replace('\\', '_')
    macroize = macroize[:-2]
    guard_use = '_POSIX_ON_WIN32_USE_WIN32_' + macroize

    if ignoreWindows:
        return [
            '#endif // !defined(%s)' % guard_use,
            '',
        ]

    return [
        '#endif // defined(%s)' % guard_use,
        '',
        '// -----------------------------------------------------------------------------------------------',
        '',
        '#if !defined(%s)' % guard_use,
        '',
        '#error "This path not supported"',
        '',
        '#endif // !defined(%s)' % guard_use,
        '',
    ]

def find_section(lines, start, endtag):
    i = start
    n = len(lines)
    while i < n:
        if lines[i] == endtag:
            return i
        i = i + 1
    raise Exception("could not find %s" % endtag)

def expand_line(line, guard, posix_guard):

    # If this is markup we expand, then expand it
    if line == '[C99]':
        return [
            '// ----------------------------',
            '// C99',
            '']
    elif line == '[C11]':
        return [
            '// ----------------------------',
            '// C11',
            '']
    elif line == '[C18]':
        return [
            '// ----------------------------',
            '// C18',
            '']
    elif line == '[POSIX]':
        return [
            '// ----------------------------',
            '// POSIX',
            '']
    elif line == '[Glibc]':
        return [
            '// ----------------------------',
            '// Glibc',
            '']
    elif line == '[Microsoft]':
        return [
            '// ----------------------------',
            '// Microsoft',
            '']
    elif line == '[CDECL]':
        return [
            '// Tell C++ this is a C header',
            '#ifdef  __cplusplus',
            'extern "C" {',
            '#endif']
    elif line == '[/CDECL]':
        return [
            '#ifdef  __cplusplus',
            '}',
            '#endif']
    elif line == '[GUARD]':
        return [
            '#ifndef %s' % guard,
            '#define %s' % guard]
    elif line == '[/GUARD]':
        return [
            '// -----------------------------------------------------------------------------------------------',
            '',
            '#endif // %s' % guard]
    elif line == '[GUARD_POSIX]':
        return [
            '#ifndef %s' % posix_guard,
            '#define %s' % posix_guard]
    elif line == '[/GUARD_POSIX]':
        return [
            '// -----------------------------------------------------------------------------------------------',
            '',
            '#endif // %s' % posix_guard]

    return None

def loadfile(path):
    lines = []
    with open(path, "rt", encoding="utf-8") as fin:
        for line in fin:
            lines.append(line.rstrip())
    return lines

def make_guard(prefix, leaf):
    leaf = leaf.upper().replace('.', '_').replace('/', '_').replace('\\', '_')
    return prefix + '_' + leaf

# -----------------------------------------------------------------------------------------------

# This is just so that we can write code in what seems reasonable rather than
# in the order Python execution needs it.
if __name__ == '__main__':
    main()
