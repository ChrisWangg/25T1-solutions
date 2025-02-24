#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ANSI colour codes
#define RESET "\033[0m"
#define GREEN "\033[32m"
#define RED "\033[31m"

// -----------------------------------------------------------------------------
// Function Declaration: twoSum
// -----------------------------------------------------------------------------
// Returns true if there exist two distinct elements in the array 'nums' 
// whose sum equals 'target'. Uses a double for loop approach.
bool twoSum(int *nums, int numsSize, int target);

// -----------------------------------------------------------------------------
// Test Suite Function Declarations
// -----------------------------------------------------------------------------
static void run_test(const char *test_name, bool condition);
static void print_test_suite_header(const char *suite_name);

// -----------------------------------------------------------------------------
// Test Case Declarations
// -----------------------------------------------------------------------------
static void test_twoSum_standard(void);
static void test_twoSum_another(void);
static void test_twoSum_negative(void);
static void test_twoSum_two_numbers(void);
static void test_twoSum_no_solution(void);

// -----------------------------------------------------------------------------
// Run All Tests
// -----------------------------------------------------------------------------
static void run_tests(void);

// -----------------------------------------------------------------------------
// Main Function
// -----------------------------------------------------------------------------
int main(void) {
    run_tests();
    return 0;
}

// -----------------------------------------------------------------------------
// Implementation of twoSum()
// -----------------------------------------------------------------------------
bool twoSum(int *nums, int numsSize, int target) {
    for (int i = 0; i < numsSize; i++) {
        for (int j = i + 1; j < numsSize; j++) {
            if (nums[i] + nums[j] == target) {
                return true;
            }
        }
    }
    return false;
}

// -----------------------------------------------------------------------------
// Test Suite Helper Functions
// -----------------------------------------------------------------------------
static void run_test(const char *test_name, bool condition) {
    if (condition) {
        printf("%sTest %s: PASSED%s\n", GREEN, test_name, RESET);
    } else {
        printf("%sTest %s: FAILED%s\n", RED, test_name, RESET);
    }
}

static void print_test_suite_header(const char *suite_name) {
    printf("\nTest Suite: %s\n", suite_name);
    printf("-----------------------\n");
}

// -----------------------------------------------------------------------------
// Test Cases for twoSum()
// -----------------------------------------------------------------------------

// Test 1: Standard test using the array [2, 7, 11, 15] with target 9.
// Expected result: true, since 2 + 7 == 9.
static void test_twoSum_standard(void) {
    print_test_suite_header("Standard Two Sum Test");
    int nums[] = {2, 7, 11, 15};
    int target = 9;
    bool result = twoSum(nums, 4, target);
    run_test("twoSum returns true for [2,7,11,15] with target 9", result == true);
}

// Test 2: Test using the array [3, 2, 4] with target 6.
// Expected result: true, since 2 + 4 == 6.
static void test_twoSum_another(void) {
    print_test_suite_header("Another Two Sum Test");
    int nums[] = {3, 2, 4};
    int target = 6;
    bool result = twoSum(nums, 3, target);
    run_test("twoSum returns true for [3,2,4] with target 6", result == true);
}

// Test 3: Test with negative numbers using the array [-3, 4, 3, 90] with target 0.
// Expected result: true, since -3 + 3 == 0.
static void test_twoSum_negative(void) {
    print_test_suite_header("Two Sum with Negative Numbers");
    int nums[] = {-3, 4, 3, 90};
    int target = 0;
    bool result = twoSum(nums, 4, target);
    run_test("twoSum returns true for [-3,4,3,90] with target 0", result == true);
}

// Test 4: Test with an array of exactly two numbers [1, 2] with target 3.
// Expected result: true, since 1 + 2 == 3.
static void test_twoSum_two_numbers(void) {
    print_test_suite_header("Two Sum with Two Numbers");
    int nums[] = {1, 2};
    int target = 3;
    bool result = twoSum(nums, 2, target);
    run_test("twoSum returns true for [1,2] with target 3", result == true);
}

// Test 5: Test when no solution exists using the array [1, 2, 3] with target 7.
// Expected result: false, since no two numbers add up to 7.
static void test_twoSum_no_solution(void) {
    print_test_suite_header("Two Sum with No Solution");
    int nums[] = {1, 2, 3};
    int target = 7;
    bool result = twoSum(nums, 3, target);
    run_test("twoSum returns false for [1,2,3] with target 7", result == false);
}

// -----------------------------------------------------------------------------
// Run All Tests
// -----------------------------------------------------------------------------
static void run_tests(void) {
    test_twoSum_standard();
    test_twoSum_another();
    test_twoSum_negative();
    test_twoSum_two_numbers();
    test_twoSum_no_solution();
}
