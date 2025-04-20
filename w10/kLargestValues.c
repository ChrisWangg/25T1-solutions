// kLargestValues.c

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"
#include "MinHeap.h"

/**
 * Return a List of the k largest values in arr[0..n-1], in ascending order.
 * Precondition: 0 <= k <= n.
 */
List kLargestValues(int arr[], int n, int k) {
    MinHeap h = MinHeapNew();
    for (int i = 0; i < n; i++) {
        MinHeapInsert(h, arr[i]);
        if (MinHeapSize(h) > k) {
            MinHeapDeleteMin(h);
        }
    }

    List res = ListNew();
    while (!MinHeapEmpty(h)) {
        ListAppend(res, MinHeapDeleteMin(h));
    }
    MinHeapFree(h);
    return res;
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
static void run_test(const char *test_name, bool condition) {
    printf("%sTest %s: %s%s\n",
           condition ? GREEN : RED,
           test_name,
           condition ? "PASSED" : "FAILED",
           RESET);
}

static void print_header(const char *header) {
    printf("\n----- %s -----\n", header);
}

static bool listEquals(List lst, int expected[], int k) {
    if (ListSize(lst) != k) return false;
    for (int i = 0; i < k; i++) {
        if (ListGet(lst, i) != expected[i]) return false;
    }
    return true;
}

/* -----------------------------------------------------------------------------
   Tests for kLargestValues
   -----------------------------------------------------------------------------
*/
static void test_simple(void) {
    print_header("Simple Case");
    int arr[] = {7,4,2,5,9};
    List res = kLargestValues(arr, 5, 3);
    int exp[] = {5,7,9};
    run_test("5,7,9", listEquals(res, exp, 3));
    ListFree(res);
}

static void test_k_equals_n(void) {
    print_header("k == n");
    int arr[] = {3,1,2};
    List res = kLargestValues(arr, 3, 3);
    int exp[] = {1,2,3};
    run_test("1,2,3", listEquals(res, exp, 3));
    ListFree(res);
}

static void test_k_one(void) {
    print_header("k == 1");
    int arr[] = {4,8,6,2};
    List res = kLargestValues(arr, 4, 1);
    int exp[] = {8};
    run_test("8", listEquals(res, exp, 1));
    ListFree(res);
}

static void test_negative(void) {
    print_header("Negative numbers");
    int arr[] = {-1,-5,3,0};
    List res = kLargestValues(arr, 4, 2);
    int exp[] = {0,3};
    run_test("0,3", listEquals(res, exp, 2));
    ListFree(res);
}

static void test_duplicates(void) {
    print_header("Duplicates");
    int arr[] = {5,1,5,2};
    List res = kLargestValues(arr, 4, 2);
    int exp[] = {5,5};
    run_test("5,5", listEquals(res, exp, 2));
    ListFree(res);
}

int main(void) {
    test_simple();
    test_k_equals_n();
    test_k_one();
    test_negative();
    test_duplicates();
    return 0;
}
