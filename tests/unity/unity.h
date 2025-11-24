/*
 * Minimal Unity test framework implementation (MIT licensed)
 * Based on ThrowTheSwitch Unity (https://github.com/ThrowTheSwitch/Unity)
 */
#ifndef UNITY_H
#define UNITY_H

#include <setjmp.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*UnityTestFunction)(void);

typedef struct {
    const char *TestFile;
    const char *CurrentTestName;
    unsigned int CurrentTestLineNumber;
    unsigned int NumberOfTests;
    unsigned int TestFailures;
    unsigned int TestIgnores;
    int CurrentTestFailed;
    int CurrentTestIgnored;
} UNITY_STRUCT;

extern UNITY_STRUCT Unity;
extern jmp_buf AbortFrame;

void UnityBegin(const char *filename);
int UnityEnd(void);
void UnityConcludeTest(void);
void UnityFail(const char *message, unsigned int line);
void UnityIgnore(const char *message, unsigned int line);
void UnityDefaultTestRun(UnityTestFunction func, const char *name, int line_number);

void UnityAssertEqualInt(int expected, int actual, unsigned int line, const char *message);
void UnityAssertEqualString(const char *expected, const char *actual, unsigned int line, const char *message);
void UnityAssertNotNull(const void *actual, unsigned int line, const char *message);
void UnityAssertNull(const void *actual, unsigned int line, const char *message);

#define UNITY_BEGIN() (UnityBegin(__FILE__))
#define UNITY_END() UnityEnd()

#define RUN_TEST(func) UnityDefaultTestRun(func, #func, __LINE__)

#define TEST_ASSERT(cond) if (!(cond)) UnityFail("Expression evaluated to false", __LINE__)
#define TEST_ASSERT_TRUE(actual) UnityAssertEqualInt(1, (actual) ? 1 : 0, __LINE__, "Expected TRUE")
#define TEST_ASSERT_FALSE(actual) UnityAssertEqualInt(0, (actual) ? 1 : 0, __LINE__, "Expected FALSE")
#define TEST_ASSERT_EQUAL_INT(expected, actual) UnityAssertEqualInt((expected), (actual), __LINE__, "Ints not equal")
#define TEST_ASSERT_EQUAL(expected, actual) UnityAssertEqualInt((expected), (actual), __LINE__, "Ints not equal")
#define TEST_ASSERT_EQUAL_STRING(expected, actual) UnityAssertEqualString((expected), (actual), __LINE__, "Strings not equal")
#define TEST_ASSERT_NULL(actual) UnityAssertNull((actual), __LINE__, "Expected NULL")
#define TEST_ASSERT_NOT_NULL(actual) UnityAssertNotNull((actual), __LINE__, "Expected non-NULL")

#define TEST_PROTECT() (setjmp(AbortFrame) == 0)

#ifndef UNITY_LINE_TYPE
#define UNITY_LINE_TYPE unsigned int
#endif

/* These functions must be provided by the test file */
void setUp(void);
void tearDown(void);

#ifdef __cplusplus
}
#endif

#endif
