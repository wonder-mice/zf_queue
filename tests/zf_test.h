#pragma once

#include <stdio.h>

#if !defined(_ZF_TEST_STRINGIFY) && !defined(_ZF_TEST__STRINGIFY)
#define _ZF_TEST__STRINGIFY(x) #x
#define _ZF_TEST_STRINGIFY(x) _ZF_TEST__STRINGIFY(x)
#endif

typedef struct _zf_test_runner
{
    unsigned nerror;
}
_zf_test_runner;

#define TEST_RUNNER_CREATE(argc, argv) \
    (void)argc; (void)argv; \
    _zf_test_runner _zf_test_runner_instance; \
    _zf_test_runner_instance.nerror = 0;

#define TEST_SUIT_ARGUMENTS

#define TEST_VERIFY_TRUE(a) \
    if (!(a)) { \
        fprintf(stderr, "%s:%u: %s:\n", __FILE__, __LINE__, "not true"); \
        fprintf(stderr, "    false: %s\n", _ZF_TEST_STRINGIFY(a)); \
    }

#define TEST_VERIFY_FALSE(a) \
    if ((a)) { \
        fprintf(stderr, "%s:%u: %s:\n", __FILE__, __LINE__, "not false"); \
        fprintf(stderr, "    true: %s\n", _ZF_TEST_STRINGIFY(a)); \
    }

#define TEST_VERIFY_EQUAL(a, b) \
    if (!((a) == (b))) { \
        fprintf(stderr, "%s:%u: %s:\n", __FILE__, __LINE__, "not equal"); \
        fprintf(stderr, "    left:   %s\n", _ZF_TEST_STRINGIFY(a)); \
        fprintf(stderr, "    reight: %s\n", _ZF_TEST_STRINGIFY(b)); \
    }

#define TEST_EXECUTE(f) \
    f

#define TEST_EXECUTE_SUITE(s) \
    s()

#define TEST_RUNNER_EXIT_CODE() \
    0
