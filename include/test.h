#ifndef _TEST_H_
#define _TEST_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint32_t test_uint;

static struct {
    bool is_testing; 
    test_uint passed; 
    test_uint total; 
} test_data = {0};

/* Start a test. */
static void test_start(const char* p_title) {
    if(test_data.is_testing) return; 
    printf("--%s--\n", p_title);
    test_data.passed = 0; 
    test_data.total = 0; 
    test_data.is_testing = true;
}

/* Test a condition. */
static void test(bool p_condition, const char* p_description) {
    if(!test_data.is_testing) return;
    printf("[%c] %s\n", p_condition?'*':' ', p_description);
    if(p_condition) test_data.passed++; 
    test_data.total++;
}

/* Finish test and print the result. */
static void test_end() {
    if(!test_data.is_testing) return;
    printf(
            "-----\n"
            "Total test: %u\n"
            "Total passed: %u\n"
            "Percentage passed: %3u%%\n",
            test_data.total, test_data.passed, (test_data.passed * 100) / test_data.total
            );
    test_data.is_testing = false; 
}

#endif //_TEST_H_
