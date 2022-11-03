#include <list.h>
#include <test.h>
#include <stdbool.h>
#include "test_list.h"

#define ARRAY_LEN(p_array) (sizeof(p_array) / sizeof(p_array[0]))

LIST_DEFINE_STRUCT(int, int, );
LIST_DEFINE_GETTER(int, int, static); 
LIST_DEFINE_SETTER(int, int, static); 

static void test_list_from_array();
static void test_list_equal();
static void test_list_get();
static void test_list_length();
static void test_list_find();
static void test_list_set();
static void test_list_insert();
static void test_list_erase();
static void test_list_append();
static void test_list_prepend();
static void test_list_pop_back();
static void test_list_pop_front();

/* >> test_list
 *  entrance for testing list.
 *
 * @noparam 
 *
 * @noreturn 
 *
 * @noerror
 * <<
 * */
void test_list() {
    test_start("Test list."); 
    test_list_from_array();
    test_list_equal();
    test_list_get(); 
    test_list_length(); 
    test_list_find(); 
    test_list_set(); 
    test_list_insert();
    test_list_erase();
    test_list_append();
    test_list_prepend();
    test_list_pop_back();
    test_list_pop_front();
    test_end();
}

/* >> test_list_from_array
 *  Test `ID_list_from_array` function.
 *
 * @noparam 
 *
 * @noreturn 
 *
 * @noerror
 * <<
 * */
static void test_list_from_array() {
    int array[] = {1, 2, 3, 4, 5};
    struct int_list list = {0};
    int_list_from_array(array, ARRAY_LEN(array), &list); 
    test(!memcmp(array, list.items, sizeof(array)), "`ID_list_from_array`");
    int_list_free_items(&list); 
}

/* >> test_list_equal
 *  Test `ID_list_equal` function.
 *  This depends on `ID_list_from_array` function.
 *
 * @noparam 
 *
 * @noreturn 
 *
 * @noerror
 * <<
 * */
static void test_list_equal() {
    int array_a[] = {1, 2, 3, 4, 5, 2};
    int array_b[] = {1, 4, 3, 4, 5, 2};
    struct int_list list_a = {0};
    struct int_list list_b = {0};
    int_list_from_array(array_a, ARRAY_LEN(array_a), &list_a); 
    int_list_from_array(array_a, ARRAY_LEN(array_a), &list_b); 
    test(int_list_equal(&list_a, &list_b), "`ID_list_equal` with equal list.");
    int_list_from_array(array_b, ARRAY_LEN(array_b), &list_b); 
    test(!int_list_equal(&list_a, &list_b), "`ID_list_equal` with inequal list.");
    int_list_free_items(&list_a); 
    int_list_free_items(&list_b);
}
/* >> test_list_get
 *  Test `ID_list_get` function.
 *  This depends on `ID_list_from_array` function.
 *
 * @noparam 
 *
 * @noreturn 
 *
 * @noerror
 * <<
 * */
static void test_list_get() {
    const int array[] = {1, 2, 3, 4, 5};
    const int index = 2;
    struct int_list list = {0};
    int item = 0; 
    bool result = 0;
    int_list_from_array(array, ARRAY_LEN(array), &list); 
    result = int_list_get(&list, ARRAY_LEN(array), &item); 
    test(!result && (item == 0), "`ID_list_get` with invalid index."); 
    result = int_list_get(&list, index, &item); 
    test(result && (item == array[index]), "`ID_list_get` with valid index");
    int_list_free_items(&list); 
}

/* >> test_list_length
 *  Test `ID_list_length` function.
 *  This depends on `ID_list_from_array` function.
 *
 * @noparam 
 *
 * @noreturn 
 *
 * @noerror
 * <<
 * */
static void test_list_length() {
    int array[] = {1, 2, 3, 4, 5};
    struct int_list list = {0};
    int_list_from_array(array, ARRAY_LEN(array), &list); 
    test(int_list_length(&list) == ARRAY_LEN(array), "`ID_list_length`");
    int_list_free_items(&list); 
}

/* >> test_list_find
 *  Test `ID_list_find` function.
 *  This depends on `ID_list_from_array` function.
 *
 * @noparam 
 *
 * @noreturn 
 *
 * @noerror
 * <<
 * */
static void test_list_find() {
    int array[] = {1, 2, 3, 4, 5, 2};
    struct int_list list = {0};
    bool result = false;
    int index = 0;
    int_list_from_array(array, ARRAY_LEN(array), &list); 

    result = int_list_find(&list, 3, 0, &index); 
    test(result && (index == 2), "`ID_list_find` with existing 1th item.");

    index = 0;
    result = int_list_find(&list, 6, 0, &index); 
    test(!result && (index == 0), "`ID_list_find` with non-existing 1th item.");

    index = 0; 
    result = int_list_find(&list, 2, 1, &index); 
    test(result && (index == 5), "`ID_list_find` with existing 2th item.");

    index = 0; 
    result = int_list_find(&list, 3, 1, &index); 
    test(!result && (index == 0), "`ID_list_find` with non-existing 2th item.");

    int_list_free_items(&list);
}
 
/* >> test_list_set
 *  Test `ID_list_set` function.
 *  This depends on `ID_list_from_array` function and `ID_list_equal` function.
 *
 * @noparam 
 *
 * @noreturn 
 *
 * @noerror
 * <<
 * */
static void test_list_set() {
    int array_a[] = {1, 2, 3, 4, 5, 2};
    int array_b[] = {1, 4, 3, 4, 5, 2};
    struct int_list list_a = {0};
    struct int_list list_b = {0};
    bool result = false;
    int_list_from_array(array_a, ARRAY_LEN(array_a), &list_a); 
    int_list_from_array(array_b, ARRAY_LEN(array_b), &list_b); 

    result = int_list_set(&list_b, 2, 1);
    test(result && int_list_equal(&list_a, &list_b), "`ID_list_set` with valid index."); 
    result = int_list_set(&list_b, 2, 20);
    test(!result && int_list_equal(&list_a, &list_b), "`ID_list_set` with invalid index."); 

    int_list_free_items(&list_a);
    int_list_free_items(&list_b);
}

/* >> test_list_insert
 *  Test `ID_list_insert` function.
 *  This depends on `ID_list_from_array` function and `ID_list_equal` function.
 *
 * @noparam 
 *
 * @noreturn 
 *
 * @noerror
 * <<
 * */
static void test_list_insert() {
    int array_a[] = {1, 2, 3, 4, 5, 2};
    int array_b[] = {1, 2, 6, 3, 4, 5, 2};
    struct int_list list_a = {0};
    struct int_list list_b = {0};
    bool result = false;
    int_list_from_array(array_a, ARRAY_LEN(array_a), &list_a); 
    int_list_from_array(array_b, ARRAY_LEN(array_b), &list_b); 

    result = int_list_insert(&list_a, 6, 2); 
    test(result && int_list_equal(&list_a, &list_b), "`ID_list_insert` with valid index."); 
    result = int_list_set(&list_a, 2, 20);
    test(!result && int_list_equal(&list_a, &list_b), "`ID_list_insert` with invalid index."); 

    int_list_free_items(&list_a);
    int_list_free_items(&list_b);
}


/* >> test_list_erase
 *  Test `ID_list_erase` function.
 *  This depends on `ID_list_from_array` function and `ID_list_equal` function.
 *
 * @noparam 
 *
 * @noreturn 
 *
 * @noerror
 * <<
 * */
static void test_list_erase() {
    int array_a[] = {1, 2, 3, 4, 5, 2};
    int array_b[] = {1, 2, 3, 5, 2};
    struct int_list list_a = {0};
    struct int_list list_b = {0};
    bool result = false;
    int_list_from_array(array_a, ARRAY_LEN(array_a), &list_a); 
    int_list_from_array(array_b, ARRAY_LEN(array_b), &list_b); 

    result = int_list_erase(&list_a, 3); 
    test(result && int_list_equal(&list_a, &list_b), "`ID_list_erase` with valid index."); 
    result = int_list_erase(&list_a, 20);
    test(!result && int_list_equal(&list_a, &list_b), "`ID_list_erase` with invalid index."); 

    int_list_free_items(&list_a);
    int_list_free_items(&list_b);
}

/* >> test_list_append
 *  Test `ID_list_append` function.
 *  This depends on `ID_list_from_array` function and `ID_list_equal` function.
 *
 * @noparam 
 *
 * @noreturn 
 *
 * @noerror
 * <<
 * */
static void test_list_append() {
    int array_a[] = {1, 2, 3, 4, 5, 2};
    int array_b[] = {1, 2, 3, 4, 5, 2, 6};
    struct int_list list_a = {0};
    struct int_list list_b = {0};
    bool result = false;
    int_list_from_array(array_a, ARRAY_LEN(array_a), &list_a); 
    int_list_from_array(array_b, ARRAY_LEN(array_b), &list_b); 

    result = int_list_append(&list_a, 6); 
    test(result && int_list_equal(&list_a, &list_b), "`ID_list_append`."); 

    int_list_free_items(&list_a);
    int_list_free_items(&list_b);
}

/* >> test_list_prepend
 *  Test `ID_list_prepend` function.
 *  This depends on `ID_list_from_array` function and `ID_list_equal` function.
 *
 * @noparam 
 *
 * @noreturn 
 *
 * @noerror
 * <<
 * */
static void test_list_prepend() {
    int array_a[] = {1, 2, 3, 4, 5, 2};
    int array_b[] = {10, 1, 2, 3, 4, 5, 2};
    struct int_list list_a = {0};
    struct int_list list_b = {0};
    bool result = false;
    int_list_from_array(array_a, ARRAY_LEN(array_a), &list_a); 
    int_list_from_array(array_b, ARRAY_LEN(array_b), &list_b); 

    result = int_list_prepend(&list_a, 10); 
    test(result && int_list_equal(&list_a, &list_b), "`ID_list_prepend`."); 

    int_list_free_items(&list_a);
    int_list_free_items(&list_b);
}

/* >> test_list_pop_back
 *  Test `ID_list_pop_back` function.
 *  This depends on `ID_list_from_array` function and `ID_list_equal` function.
 *
 * @noparam 
 *
 * @noreturn 
 *
 * @noerror
 * <<
 * */
static void test_list_pop_back() {
    int array_a[] = {1, 2, 3, 4, 5, 2};
    int array_b[] = {1, 2, 3, 4, 5};
    struct int_list list_a = {0};
    struct int_list list_b = {0};
    bool result = false;
    int popped = 0;
    int_list_from_array(array_a, ARRAY_LEN(array_a), &list_a); 
    int_list_from_array(array_b, ARRAY_LEN(array_b), &list_b); 

    result = int_list_pop_back(&list_a, &popped); 
    test(result && int_list_equal(&list_a, &list_b) && (popped == 2), "`ID_list_pop_back`."); 

    int_list_free_items(&list_a);
    int_list_free_items(&list_b);
}

/* >> test_list_pop_front
 *  Test `ID_list_pop_front` function.
 *  This depends on `ID_list_from_array` function and `ID_list_equal` function.
 *
 * @noparam 
 *
 * @noreturn 
 *
 * @noerror
 * <<
 * */
static void test_list_pop_front() {
    int array_a[] = {25, 1, 2, 3, 4, 5, 2};
    int array_b[] = {1, 2, 3, 4, 5, 2};
    struct int_list list_a = {0};
    struct int_list list_b = {0};
    bool result = false;
    int popped = 0;
    int_list_from_array(array_a, ARRAY_LEN(array_a), &list_a); 
    int_list_from_array(array_b, ARRAY_LEN(array_b), &list_b); 

    result = int_list_pop_front(&list_a, &popped);
    test(result && int_list_equal(&list_a, &list_b) && (popped == 25), "`ID_list_pop_front`."); 

    int_list_free_items(&list_a);
    int_list_free_items(&list_b);
}
