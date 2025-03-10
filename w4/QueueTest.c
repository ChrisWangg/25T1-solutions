#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Queue.h"

// ANSI colour codes
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"

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
// Test Cases for QueueEnqueue() and QueueDequeue()
// -----------------------------------------------------------------------------

// Test 1: Empty Queue
// Verify that a new queue is empty.
static void test_empty_queue(void) {
    print_test_suite_header("Empty Queue");
    Queue q = QueueNew();
    bool empty = QueueIsEmpty(q);
    run_test("Queue should be empty upon creation", empty);
    QueueFree(q);
}

// Test 2: Single Enqueue-Dequeue
// Enqueue one element and then dequeue it. The queue should be empty afterwards.
static void test_single_enqueue_dequeue(void) {
    print_test_suite_header("Single Enqueue-Dequeue");
    Queue q = QueueNew();
    QueueEnqueue(q, 42);
    
    // The queue should not be empty after enqueuing.
    bool notEmpty = !QueueIsEmpty(q);
    int item = QueueDequeue(q);
    bool emptyAfter = QueueIsEmpty(q);
    
    bool result = (notEmpty && (item == 42) && emptyAfter);
    run_test("Single enqueue and dequeue", result);
    QueueFree(q);
}

// Test 3: Multiple Enqueue-Dequeue in FIFO Order
// Enqueue multiple items and then dequeue them, verifying FIFO order.
static void test_multiple_enqueue_dequeue(void) {
    print_test_suite_header("Multiple Enqueue-Dequeue");
    Queue q = QueueNew();
    int elements[] = {10, 20, 30, 40, 50};
    int n = sizeof(elements) / sizeof(elements[0]);
    
    // Enqueue all elements.
    for (int i = 0; i < n; i++) {
        QueueEnqueue(q, elements[i]);
    }
    
    bool correct_order = true;
    // Dequeue and check that each element matches the expected order.
    for (int i = 0; i < n; i++) {
        int dequeued = QueueDequeue(q);
        if (dequeued != elements[i]) {
            correct_order = false;
            break;
        }
    }
    run_test("FIFO order maintained for multiple elements", correct_order);
    QueueFree(q);
}

// Test 4: Interleaved Enqueue and Dequeue Operations
// Enqueue some elements, dequeue a few, then enqueue more and finally dequeue the rest.
static void test_interleaved_operations(void) {
    print_test_suite_header("Interleaved Operations");
    Queue q = QueueNew();
    
    // Enqueue initial elements.
    QueueEnqueue(q, 1);
    QueueEnqueue(q, 2);
    // Dequeue one element (expected 1).
    int first = QueueDequeue(q);
    
    // Enqueue more elements.
    QueueEnqueue(q, 3);
    QueueEnqueue(q, 4);
    
    // Dequeue remaining elements: should be 2, then 3, then 4.
    int second = QueueDequeue(q);
    int third = QueueDequeue(q);
    int fourth = QueueDequeue(q);
    
    bool condition = (first == 1 && second == 2 && third == 3 && fourth == 4 && QueueIsEmpty(q));
    run_test("Interleaved enqueue and dequeue operations", condition);
    QueueFree(q);
}

// Test 5: Large Queue Operations
// Enqueue a larger number of elements and then dequeue them to test performance and correctness.
static void test_large_queue(void) {
    print_test_suite_header("Large Queue");
    Queue q = QueueNew();
    int n = 1000;
    bool condition = true;
    
    // Enqueue 0 to 999.
    for (int i = 0; i < n; i++) {
        QueueEnqueue(q, i);
    }
    
    // Dequeue and check that the elements are in FIFO order.
    for (int i = 0; i < n; i++) {
        if (QueueDequeue(q) != i) {
            condition = false;
            break;
        }
    }
    condition = condition && QueueIsEmpty(q);
    run_test("Large queue enqueue and dequeue operations", condition);
    QueueFree(q);
}

// -----------------------------------------------------------------------------
// Run All Tests
// -----------------------------------------------------------------------------
static void run_tests(void) {
    test_empty_queue();
    test_single_enqueue_dequeue();
    test_multiple_enqueue_dequeue();
    test_interleaved_operations();
    test_large_queue();
}

// -----------------------------------------------------------------------------
// Main Function
// -----------------------------------------------------------------------------
int main(void) {
    run_tests();
    return 0;
}
