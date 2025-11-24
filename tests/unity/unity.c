/*
 * Minimal Unity test framework implementation (MIT licensed)
 * Based on ThrowTheSwitch Unity (https://github.com/ThrowTheSwitch/Unity)
 */
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "unity.h"

UNITY_STRUCT Unity;
jmp_buf AbortFrame;

static void UnityPrintFail(const char *message, unsigned int line) {
    printf("%s:%u: %s\n", Unity.TestFile, line, message);
}

void UnityBegin(const char *filename) {
    memset(&Unity, 0, sizeof(Unity));
    Unity.TestFile=filename;
}

int UnityEnd(void) {
    printf("\n%d Tests %d Failures %d Ignored\n", Unity.NumberOfTests, Unity.TestFailures, Unity.TestIgnores);
    return Unity.TestFailures;
}

void UnityConcludeTest(void) {
    Unity.NumberOfTests++;

    if (Unity.CurrentTestIgnored) {
        Unity.TestIgnores++;
        printf("IGNORE %s\n", Unity.CurrentTestName);
    } else if (Unity.CurrentTestFailed) {
        Unity.TestFailures++;
        printf("FAIL %s\n", Unity.CurrentTestName);
    } else {
        printf("PASS %s\n", Unity.CurrentTestName);
    }
}

void UnityFail(const char *message, unsigned int line) {
    Unity.CurrentTestFailed=1;
    UnityPrintFail(message, line);
    longjmp(AbortFrame, 1);
}

void UnityIgnore(const char *message, unsigned int line) {
    Unity.CurrentTestIgnored=1;
    UnityPrintFail(message, line);
    longjmp(AbortFrame, 1);
}

void UnityAssertEqualInt(int expected, int actual, unsigned int line, const char *message) {
    if (expected!=actual) {
        char buffer[128];
        snprintf(buffer, sizeof(buffer), "%s (expected %d was %d)", message, expected, actual);
        UnityFail(buffer, line);
    }
}

void UnityAssertEqualString(const char *expected, const char *actual, unsigned int line, const char *message) {
    if (expected==NULL && actual==NULL) return;
    if (expected==NULL || actual==NULL || strcmp(expected, actual)) {
        char buffer[128];
        snprintf(buffer, sizeof(buffer), "%s (expected \"%s\" was \"%s\")", message, expected ? expected : "(null)", actual ? actual : "(null)");
        UnityFail(buffer, line);
    }
}

void UnityAssertNotNull(const void *actual, unsigned int line, const char *message) {
    if (actual==NULL) {
        UnityFail(message, line);
    }
}

void UnityAssertNull(const void *actual, unsigned int line, const char *message) {
    if (actual!=NULL) {
        UnityFail(message, line);
    }
}

void UnityDefaultTestRun(UnityTestFunction func, const char *name, int line_number) {
    Unity.CurrentTestName=name;
    Unity.CurrentTestLineNumber=line_number;
    Unity.CurrentTestFailed=0;
    Unity.CurrentTestIgnored=0;

    if (TEST_PROTECT()) {
        setUp();
        func();
    }

    if (TEST_PROTECT() && !Unity.CurrentTestIgnored) {
        tearDown();
    }

    UnityConcludeTest();
}
