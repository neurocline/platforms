// main.cpp

#include <assert.h>
#include <stdint.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    printf("argc=%d argv=%08X", argc, (uintptr_t) argv);
    assert(0);
}
