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

/* Start a test. 
 *  It initiate `test_data` struct and print the `p_title`, signaling the
 *  starting of test.
 *
 * @param 
 *  `p_title` - Title of the test that will be displayed onto screen.
 *
 * @noreturn
 *
 * @noerror */
static void test_start(const char* p_title) {
    if(test_data.is_testing) return; 
    printf("--%s--\n", p_title);
    test_data.passed = 0; 
    test_data.total = 0; 
    test_data.is_testing = true;
}

/* Test a condition. 
 *  It updates the counter in `test_data` of the test count and print the status
 *  of test. 
 *
 * @param 
 *  `p_condition` - `true` means passed, `false` mean fail.
 *  `p_description` - Description of the test.
 *
 * @noreturn
 *
 * @noerror */
static void test(bool p_condition, const char* p_description) {
    if(!test_data.is_testing) return;
    printf("[%c] %s\n", p_condition?'*':' ', p_description);
    if(p_condition) test_data.passed++; 
    test_data.total++;
}

/* Finish test and print the result. 
 *  It ends the test and print the result of the test. 
 *
 * @noparam
 *
 * @noreturn
 *
 * @noerror */
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
