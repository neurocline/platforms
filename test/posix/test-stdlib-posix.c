// test-stdlib-posix.c

#include <stdlib.h>

#include <assert.h>
#include <float.h>

void my_exit(void)
{
}

int test_stdlib()
{
    // Check that Microsoft functions we didn't override
    // exist and work.
    // TBD finish partial list.
    div_t dt = {1, 2};
    ldiv_t dtl = {3, 4};
    lldiv_t dtll = {5, 6};

    assert(dt.quot == 1);
    assert(dt.rem == 2);
    assert(dtl.quot == 3);
    assert(dtl.rem == 4);
    assert(dtll.quot == 5);
    assert(dtll.rem == 6);

    int err = EXIT_SUCCESS;
    void* pdx = NULL;
    if (pdx == NULL)
        err = EXIT_FAILURE;

    double e = 1.192092896e-07F;
    double v = atof("1.0");
    assert(v > 1.0 - 2*e && v < 1.0 + 2*e);

    atexit(my_exit);
    at_quick_exit(my_exit);

    // testing these means ending the program, so just check
    // that they have storage.
    _Noreturn void (*abortfn)(void) = abort;
    _Noreturn void (*exitfn)(int) = exit;
    _Noreturn void (*exitfn2)(int) = _Exit;
    assert(abortfn != NULL);
    assert(exitfn != NULL);
    assert(exitfn2 != NULL);

    abortfn = NULL;
    exitfn = NULL;
    exitfn2 = NULL;

    int (*systemfn)(const char*) = system;

    systemfn = NULL;

    return 0;
}
