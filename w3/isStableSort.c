#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ANSI colour codes
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"

// -----------------------------------------------------------------------------
// Data Structure Declaration
// -----------------------------------------------------------------------------
typedef struct {
    int a;
    int b;
} Item;

// -----------------------------------------------------------------------------
// Function Prototype for the candidate's implementation
// -----------------------------------------------------------------------------
bool isStableSort(Item original[], Item sorted[], int size);

// -----------------------------------------------------------------------------
// Test Suite Helper Functions
// -----------------------------------------------------------------------------
static void run_test(const char *test_name, bool expected, bool result) {
    if (expected == result) {
        printf("%sTest %s: PASSED%s\n", GREEN, test_name, RESET);
    } else {
        printf("%sTest %s: FAILED (expected %d, got %d)%s\n", RED, test_name, expected, result, RESET);
    }
}

static void print_test_suite_header(const char *suite_name) {
    printf("\nTest Suite: %s\n", suite_name);
    printf("-----------------------\n");
}

// -----------------------------------------------------------------------------
// Test Cases for isStableSort()
// -----------------------------------------------------------------------------

// Test 1: Empty array (size == 0)
static void test_empty_array(void) {
    print_test_suite_header("Empty Array");
    Item *original = NULL;
    Item *sorted = NULL;
    bool result = isStableSort(original, sorted, 0);
    run_test("Empty array", true, result);
}

// Test 2: Single element array should be considered stable.
static void test_single_element(void) {
    print_test_suite_header("Single Element");
    Item original[1] = { {5, 100} };
    Item sorted[1] = { {5, 100} };
    bool result = isStableSort(original, sorted, 1);
    run_test("Single element", true, result);
}

// Test 3: Stable sort on an array with duplicate keys.
// The sorted array preserves the original relative order for items with equal key 'a'.
static void test_stable_duplicates(void) {
    print_test_suite_header("Stable Sort with Duplicates");
    Item original[] = { {1, 10}, {1, 20}, {2, 30}, {2, 40} };
    // Stable sort: relative order of duplicate keys (here key 1 and key 2) is preserved.
    Item sorted[]   = { {1, 10}, {1, 20}, {2, 30}, {2, 40} };
    int size = sizeof(original) / sizeof(original[0]);
    bool result = isStableSort(original, sorted, size);
    run_test("Stable sort with duplicates", true, result);
}

// Test 4: Unstable sort on an array with duplicate keys.
// The sorted array changes the relative order of items with equal key 'a'.
static void test_unstable_duplicates(void) {
    print_test_suite_header("Unstable Sort with Duplicates");
    Item original[] = { {1, 10}, {1, 20}, {2, 30}, {2, 40} };
    // Unstable sort: order is swapped for items with equal keys.
    Item sorted[]   = { {1, 20}, {1, 10}, {2, 40}, {2, 30} };
    int size = sizeof(original) / sizeof(original[0]);
    bool result = isStableSort(original, sorted, size);
    run_test("Unstable sort with duplicates", false, result);
}

// Test 5: Sorted array with unique keys.
// Even though stability isn’t an issue when keys are unique, the function should return stable.
static void test_unique_keys(void) {
    print_test_suite_header("Unique Keys");
    Item original[] = { {3, 10}, {1, 20}, {2, 30} };
    // Sorted by 'a' field.
    Item sorted[]   = { {1, 20}, {2, 30}, {3, 10} };
    int size = sizeof(original) / sizeof(original[0]);
    bool result = isStableSort(original, sorted, size);
    run_test("Unique keys sorted", true, result);
}

// Test 6: Larger array with mixed duplicates (stable version)
static void test_large_stable(void) {
    print_test_suite_header("Larger Array - Stable");
    Item original[] = {
        {2, 100}, {1, 200}, {2, 300}, {1, 400}, {3, 500}
    };
    // For key 1: order is {1,200} then {1,400}; for key 2: order is {2,100} then {2,300}
    Item sorted[] = {
        {1, 200}, {1, 400}, {2, 100}, {2, 300}, {3, 500}
    };
    int size = sizeof(original) / sizeof(original[0]);
    bool result = isStableSort(original, sorted, size);
    run_test("Larger array stable sort", true, result);
}

// Test 7: Larger array with mixed duplicates (unstable version)
static void test_large_unstable(void) {
    print_test_suite_header("Larger Array - Unstable");
    Item original[] = {
        {2, 100}, {1, 200}, {2, 300}, {1, 400}, {3, 500}
    };
    // Unstable sort: for duplicate keys, the relative order is reversed.
    Item sorted[] = {
        {1, 400}, {1, 200}, {2, 300}, {2, 100}, {3, 500}
    };
    int size = sizeof(original) / sizeof(original[0]);
    bool result = isStableSort(original, sorted, size);
    run_test("Larger array unstable sort", false, result);
}

// -----------------------------------------------------------------------------
// Run All Tests
// -----------------------------------------------------------------------------
static void run_tests(void) {
    test_empty_array();
    test_single_element();
    test_stable_duplicates();
    test_unstable_duplicates();
    test_unique_keys();
    test_large_stable();
    test_large_unstable();
}

// -----------------------------------------------------------------------------
// Main Function
// -----------------------------------------------------------------------------
int main(void) {
    run_tests();
    return 0;
}

bool isStableSort(Item original[], Item sorted[], int size) {
    // For each key check position
    for (int i = 0; i < size; i++) {
        // Get the key of the sorted item
        int key = sorted[i].a;
        int j = 0;
        int k = 0;
        // Check this for all numbers matching the key
        while (j < size && k < size) {
            // Find the position of the key in the sorted array
            for (; j < size; j++) {
                if (sorted[j].a == key) {
                    break;
                }
            }
            // Find the position of the key in the original array
            for (; k < size; k++) {
                if (original[k].a == key) {
                    break;
                }
            }
            // If position is found
            if (j < size && k < size) {
                // If the secondary keys do not match, then the order is not stable
                if (sorted[j].b != original[k].b) {
                    return false;
                }
                j++;
                k++;
            }
        }
    }
    return true;
}
