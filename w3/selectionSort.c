#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// ANSI colour codes
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"

// -----------------------------------------------------------------------------
// Data Structure Declaration
// -----------------------------------------------------------------------------
struct node {
    int value;
    struct node *next;
};

// -----------------------------------------------------------------------------
// Function Prototype for the candidate's implementation
// -----------------------------------------------------------------------------
struct node *selectionSort(struct node *list);
struct node *findMin(struct node *list);

// -----------------------------------------------------------------------------
// Helper Functions for Linked List Management
// -----------------------------------------------------------------------------

// Create a new node with the given value.
struct node *create_node(int value) {
    struct node *new_node = malloc(sizeof(struct node));
    if (!new_node) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

// Create a linked list from an array of integers.
struct node *create_list_from_array(int arr[], int size) {
    struct node *head = NULL;
    struct node *tail = NULL;
    for (int i = 0; i < size; i++) {
        struct node *new_node = create_node(arr[i]);
        if (head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }
    return head;
}

// Free all nodes in the linked list.
void free_list(struct node *head) {
    while (head) {
        struct node *temp = head;
        head = head->next;
        free(temp);
    }
}

// Check if the linked list is sorted in ascending order.
bool is_sorted(struct node *head) {
    if (head == NULL)
        return true;
    while (head->next) {
        if (head->value > head->next->value)
            return false;
        head = head->next;
    }
    return true;
}

// (Optional) Print the linked list (useful for debugging).
void print_list(struct node *head) {
    while (head) {
        printf("%d -> ", head->value);
        head = head->next;
    }
    printf("NULL\n");
}

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
// Test Cases for selectionSort()
// -----------------------------------------------------------------------------

// Test 1: Empty List
static void test_empty_list(void) {
    print_test_suite_header("Empty List");
    struct node *list = NULL;
    struct node *sorted_list = selectionSort(list);
    bool result = (sorted_list == NULL);
    run_test("Empty list sorted", true, result);
}

// Test 2: Single Element List
static void test_single_element(void) {
    print_test_suite_header("Single Element List");
    int arr[] = {42};
    struct node *list = create_list_from_array(arr, 1);
    struct node *sorted_list = selectionSort(list);
    bool result = is_sorted(sorted_list);
    run_test("Single element list sorted", true, result);
    free_list(sorted_list);
}

// Test 3: Unsorted List
static void test_unsorted_list(void) {
    print_test_suite_header("Unsorted List");
    int arr[] = {3, 1, 4, 2};
    int size = sizeof(arr) / sizeof(arr[0]);
    struct node *list = create_list_from_array(arr, size);
    struct node *sorted_list = selectionSort(list);
    bool result = is_sorted(sorted_list);
    run_test("Unsorted list sorted", true, result);
    free_list(sorted_list);
}

// Test 4: Already Sorted List
static void test_sorted_list(void) {
    print_test_suite_header("Already Sorted List");
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    struct node *list = create_list_from_array(arr, size);
    struct node *sorted_list = selectionSort(list);
    bool result = is_sorted(sorted_list);
    run_test("Already sorted list remains sorted", true, result);
    free_list(sorted_list);
}

// Test 5: Reverse Sorted List
static void test_reverse_list(void) {
    print_test_suite_header("Reverse Sorted List");
    int arr[] = {5, 4, 3, 2, 1};
    int size = sizeof(arr) / sizeof(arr[0]);
    struct node *list = create_list_from_array(arr, size);
    struct node *sorted_list = selectionSort(list);
    bool result = is_sorted(sorted_list);
    run_test("Reverse sorted list becomes sorted", true, result);
    free_list(sorted_list);
}

// Test 6: List with Duplicates
static void test_duplicates_list(void) {
    print_test_suite_header("List with Duplicates");
    int arr[] = {2, 3, 2, 1, 1};
    int size = sizeof(arr) / sizeof(arr[0]);
    struct node *list = create_list_from_array(arr, size);
    struct node *sorted_list = selectionSort(list);
    bool result = is_sorted(sorted_list);
    run_test("List with duplicates sorted", true, result);
    free_list(sorted_list);
}

// -----------------------------------------------------------------------------
// Run All Tests
// -----------------------------------------------------------------------------
static void run_tests(void) {
    test_empty_list();
    test_single_element();
    test_unsorted_list();
    test_sorted_list();
    test_reverse_list();
    test_duplicates_list();
}

// -----------------------------------------------------------------------------
// Main Function
// -----------------------------------------------------------------------------
int main(void) {
    run_tests();
    return 0;
}

struct node *selectionSort(struct node *list) {
    struct node *unsortedHead = list;
    while (unsortedHead != NULL) {
        struct node *minimum = findMin(unsortedHead);

        int temp = unsortedHead->value;
        unsortedHead->value = minimum->value;
        minimum->value = temp;

        unsortedHead = unsortedHead->next;
    }
    return list;
}

// Finds and returns the smallest node in a linked list
struct node *findMin(struct node *list) {
    int min_value = list->value;
    struct node *curr_smallest = list;
    while (list != NULL) {
        if (list->value < min_value) {
            curr_smallest = list;
            min_value = list->value;
        }
        list = list->next;
    }
    return curr_smallest;
}
