#! python3
# coding=utf-8

import glob
import os
import re
import sys

def main():
    lines = loadfile(sys.argv[1])

    re1 = re.compile(r'^(\d+)>(.+): warning C4996: (.+)$')
    funcs = dict()
    for line in lines:
        m = re1.match(line)
        if m:
            path = m.group(2)
            leaf = os.path.basename(path)
            carp = m.group(3)
            # print("file %s: %s" % (leaf, carp))
            place(funcs, leaf, carp)

    for f in sorted(funcs):
        print("%12s: " % f, end = "")
        for leaf in sorted(funcs[f]):
            print(" %s" % leaf, end = "")
        print()

def place(funcs, leaf, carp):
    re2 = re.compile(r"^'([^:]+)': ([^:]+): ([^(]+)\(\)$")
    m = re2.match(carp)
    if not m:
        raise Exception("failed on %s" % carp)
    note = m.group(1)
    kind = m.group(2)
    func = m.group(3)
    # print("file=%s note=%s kind=%s func=%s" % (leaf, note, kind, func))
    if func not in funcs:
        funcs[func] = []
    if leaf not in funcs[func]:
        funcs[func].append(leaf)

def loadfile(path):
    lines = []
    with open(path, "rt", encoding="utf-8") as fin:
        for line in fin:
            lines.append(line.rstrip())
    return lines

# -----------------------------------------------------------------------------------------------

# This is just so that we can write code in what seems reasonable rather than
# in the order Python execution needs it.
if __name__ == '__main__':
    main()
