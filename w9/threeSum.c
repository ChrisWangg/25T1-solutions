#include "HashTable.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/* -----------------------------------------------------------------------------
   threeSum Function
   -----------------------------------------------------------------------------
   Returns true if any three numbers in arr[] sum to target.
*/
bool threeSum(int arr[], int size, int target) {
    HashTable ht = HashTableNew();
    for (int i = 0; i < size; i++) {
        if (HashTableContains(ht, target - arr[i])) {
            return true;
        }
        for (int j = 0; j < i; j++) {
            HashTableInsert(ht, arr[i] + arr[j], 0);
        }
    }
    HashTableFree(ht);
    return false;
}

/* -----------------------------------------------------------------------------
   ANSI Colour Codes for Test Output
   -----------------------------------------------------------------------------
*/
#define RESET   "\033[0m"
#define GREEN   "\033[0;32m"
#define RED     "\033[0;31m"

/* -----------------------------------------------------------------------------
   Test Helper Functions
   -----------------------------------------------------------------------------
*/

// run_test prints whether a test passed or failed.
static void run_test(const char *test_name, bool condition) {
    if (condition)
        printf("%sTest %s: PASSED%s\n", GREEN, test_name, RESET);
    else
        printf("%sTest %s: FAILED%s\n", RED, test_name, RESET);
}

// print_header prints a header for a group of tests.
static void print_header(const char *header) {
    printf("\n----- %s -----\n", header);
}

/* -----------------------------------------------------------------------------
   Tests for threeSum
   -----------------------------------------------------------------------------
*/

// Test: A simple case with an array that both does and does not have a valid 3-sum.
static void test_simple_case(void) {
    print_header("Simple Case Test");

    int arr[] = {1, 2, 3, 4};
    // Test: 2+3+4 = 9 so threeSum should return true for target 9.
    bool result1 = threeSum(arr, 4, 9);
    run_test("Target 9 (exists)", result1 == true);

    // Test: No three numbers sum to 10.
    bool result2 = threeSum(arr, 4, 10);
    run_test("Target 10 (non-existent)", result2 == false);
}

// Test: Array with fewer than three elements should always return false.
static void test_small_array(void) {
    print_header("Small Array Test");

    int arr[] = {1, 2};
    bool result = threeSum(arr, 2, 3);
    run_test("Less than three numbers", result == false);
}

// Test: All Zeroes
static void test_all_zeroes(void) {
    print_header("All Zeroes Test");

    int arr[] = {0, 0, 0, 0};
    // With all zeroes, any triple will sum to 0.
    bool result = threeSum(arr, 4, 0);
    run_test("All zero triple (target 0)", result == true);
}

// Test: Duplicate Numbers
static void test_duplicates(void) {
    print_header("Duplicates Test");

    int arr[] = {2, 2, 2, 2};
    // Expect a triple with 2+2+2 == 6.
    bool result = threeSum(arr, 4, 6);
    run_test("Triple of duplicates (target 6)", result == true);
}

// Test: Negative Numbers
static void test_negative_numbers(void) {
    print_header("Negative Numbers Test");

    int arr[] = {1, 2, -3, 4};
    // 1 + 2 + (-3) = 0 should be detected.
    bool result1 = threeSum(arr, 4, 0);
    run_test("Triple with negatives (target 0)", result1 == true);

    // No combination should sum to 10.
    bool result2 = threeSum(arr, 4, 10);
    run_test("Triple with negatives (target 10)", result2 == false);
}

// Run all tests.
static void run_all_tests(void) {
    test_simple_case();
    test_small_array();
    test_all_zeroes();
    test_duplicates();
    test_negative_numbers();
}

/* -----------------------------------------------------------------------------
   Main Function
   -----------------------------------------------------------------------------
*/
int main(void) {
    run_all_tests();
    return 0;
}
