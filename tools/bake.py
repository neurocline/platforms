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
        parse(path, master, canonical, diagnostic, posix)

def parse(path, master, canonical, diagnostic, posix):
    print("Reading master from %s" % path)
    make_canonical(path, master, canonical)
    make_diagnostic(path, master, diagnostic)
    make_posix(path, master, posix)

def make_canonical(path, master, canonical):
    if not os.path.exists(canonical):
        os.mkdir(canonical)
    header = path[len(master)+1:]
    target = canonical + path[len(master):]
    guard = make_guard("CANONICAL_ISO_C18", header)
    # print("Guard is %s" % guard)
    if os.path.exists(target):
        print("Skipping - existing %s" % target)
        return

    print("Writing canonical to %s" % target)
    lines = loadfile(path)
    lines = canonical_markup(lines, guard)

    with open(target, "wt", encoding="utf-8") as fout:
        for line in lines:
            print("%s" % line, file=fout)

def canonical_markup(lines, guard):
    n = len(lines)
    i = 0
    while i < n:
        line = lines[i]
        i = i + 1

        # if this is a [!MSVCRT] section, we strip everything to
        # the next [/!MSVCRT] from canonical
        if line == '[!MSVCRT]':
            j = i
            while j < n:
                line = lines[j]
                j = j + 1
                if line == '[/!MSVCRT]':
                    break
            del lines[i-1:j]
            n = n - (j - i + 1)
            continue

        # If this is markup we expand, then expand it
        if line == '[BODY]':
            lines[i-1:i] = [
                '// ---------------------------------------------------------------------------',
                '// Canonical header',
                '']
            n = n + 2
            i = i + 2
            continue
        elif line == '[C11]':
            lines[i-1:i] = [
                '// ----------------------------',
                '// C11',
                '']
            n = n + 2
            i = i + 2
            continue
        elif line == '[POSIX]':
            lines[i-1:i] = [
                '// ----------------------------',
                '// POSIX',
                '']
            n = n + 2
            i = i + 2
            continue
        elif line == '[Glibc]':
            lines[i-1:i] = [
                '// ----------------------------',
                '// Glibc',
                '']
            n = n + 2
            i = i + 2
            continue
        elif line == '[Microsoft]':
            lines[i-1:i] = [
                '// ----------------------------',
                '// Microsoft',
                '']
            n = n + 2
            i = i + 2
            continue
        elif line == '[CDECL]':
            lines[i-1:i] = [
                '// Tell C++ this is a C header',
                '#ifdef  __cplusplus',
                'extern "C" {',
                '#endif']
            n = n + 3
            i = i + 3
            continue
        elif line == '[/CDECL]':
            lines[i-1:i] = [
                '// Tell C++ this is a C header',
                '#ifdef  __cplusplus',
                '}',
                '#endif']
            n = n + 3
            i = i + 3
            continue
        elif line == '[GUARD]':
            lines[i-1:i] = [
                '#ifndef %s' % guard,
                '#define %s' % guard]
            n = n + 1
            i = i + 1
            continue
        elif line == '[/GUARD]':
            lines[i-1:i] = [
                '#endif // %s' % guard]
            continue
        elif line == '[MSVCRT]' or line == '[/MSVCRT]':
            del lines[i-1:i]
            n = n - 1
            i = i - 1
            continue

        pos = line.find('[CARP')
        if pos != -1:
            lines[i-1] = line[0:pos] + line[line.find(']',pos)+1:]
            continue

    return lines

def loadfile(path):
    lines = []
    with open(path, "rt", encoding="utf-8") as fin:
        for line in fin:
            lines.append(line.rstrip())
    return lines

def make_guard(prefix, leaf):
    leaf = leaf.upper().replace('.', '_').replace('/', '_').replace('\\', '_')
    return prefix + '_' + leaf

def canonical_markup_line(line, guard):
    if line == '[MSVCRT]' or line == '[/MSVCRT]':
        return None

    if line == '[BODY]':
        return '// ---------------------------------------------------------------------------\n// Canonical header\n'
    if line == '[C11]':
        return '// ----------------------------\n// C11\n'
    if line == '[POSIX]':
        return '// ----------------------------\n// POSIX\n'
    if line == '[Glibc]':
        return '// ----------------------------\n// Glibc\n'
    if line == '[Microsoft]':
        return '// ----------------------------\n// Microsoft\n'
    if line == '[CDECL]':
        return '// Tell C++ this is a C header\n#ifdef  __cplusplus\nextern "C" {\n#endif'
    if line == '[/CDECL]':
        return '#ifdef  __cplusplus\n}\n#endif'
    if line == '[GUARD]':
        return '#ifndef %s\n#define %s' % (guard, guard)
    if line == '[/GUARD]':
        return '#endif // %s' % guard

    pos = line.find('[CARP')
    if pos != -1:
        return line[0:pos] + line[line.find(']',pos)+1:]

    return line

def make_diagnostic(path, master, diagnostic):
    if not os.path.exists(diagnostic):
        os.mkdir(diagnostic)
    header = path[len(master)+1:]
    target = diagnostic + path[len(master):]
    guard = make_guard("DIAGNOSTIC_ISO_C18", header)
    #print("Guard is %s" % guard)
    if os.path.exists(target):
        print("Skipping - existing %s" % target)
        return

    print("Writing diagnostic to %s" % target)
    lines = loadfile(path)

    with open(target, "wt", encoding="utf-8") as fout:
        for line in lines:
            line = diagnostic_markup(line.rstrip(), guard)
            if line is not None:
                print("%s" % line, file=fout)

def diagnostic_markup(line, guard):
    if line == '[MSVCRT]' or line == '[/MSVCRT]':
        return None

    if line == '[BODY]':
        return '// ---------------------------------------------------------------------------\n// Diagnostic header\n'
    if line == '[C11]':
        return '// ----------------------------\n// C11\n'
    if line == '[POSIX]':
        return '// ----------------------------\n// POSIX\n'
    if line == '[Glibc]':
        return '// ----------------------------\n// Glibc\n'
    if line == '[Microsoft]':
        return '// ----------------------------\n// Microsoft\n'
    if line == '[CDECL]':
        return '// Tell C++ this is a C header\n#ifdef  __cplusplus\nextern "C" {\n#endif'
    if line == '[/CDECL]':
        return '#ifdef  __cplusplus\n}\n#endif'
    if line == '[GUARD]':
        return '#ifndef %s\n#define %s' % (guard, guard)
    if line == '[/GUARD]':
        return '#endif // %s' % guard

    pos = line.find('[CARP')
    if pos != -1:
        e = line.find(']', pos+1)
        carpmsg = 'CARP("ISO C99:%s") ' % line[pos+5:e]
        return line[0:pos] + carpmsg + line[e+1:]

    return line

def make_posix(path, master, posix):
    pass

# -----------------------------------------------------------------------------------------------

# This is just so that we can write code in what seems reasonable rather than
# in the order Python execution needs it.
if __name__ == '__main__':
    main()
