#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

// ANSI colour codes
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"

struct node {
    int value;
    struct node *next;
};

struct list {
    struct node *head;
};

// Function Declarations
int sumNodesWhile(struct node *list);
int sumNodesFor(struct node *list);
struct node *deleteFirstInstance(struct node *list, int value);
void deleteFirstInstanceWrapper(struct list *list, int value);

// Helper functions
struct node *createNode(int value);
struct node *prependNode(int value, struct node *list);
void freeList(struct node *list);
void printList(struct node *list);

// Test Suite Functions
static void run_test(const char *test_name, bool condition);
static void print_test_suite_header(const char *suite_name);
static bool checkListStructure(struct node *list, int expected[], int size);

// Sum Nodes Test Cases
static void test_sumEmptyList(void);
static void test_sumSingleNode(void);
static void test_sumMultipleNodes(void);
static void test_sumNegativeNumbers(void);
static void test_sumWithZero(void);

// Delete First Instance Test Cases
static void test_deleteFromEmptyList(void);
static void test_deleteHead(void);
static void test_deleteMiddle(void);
static void test_deleteLast(void);
static void test_deleteNonExistent(void);
static void test_deleteFirstOccurrence(void);
static void test_deleteSingleNode(void);

// Wrapper Delete First Instance Test Cases
static void test_wrapperDeleteFromEmptyList(void);
static void test_wrapperDeleteHead(void);
static void test_wrapperDeleteMiddle(void);
static void test_wrapperDeleteLast(void);
static void test_wrapperDeleteNonExistent(void);
static void test_wrapperDeleteFirstOccurrence(void);
static void test_wrapperDeleteSingleNode(void);

// Helper to run tests
static void run_tests(void);

// -----------------------------------------------------------------------------
// Helper function to print test results in colour
// -----------------------------------------------------------------------------
static void run_test(const char *test_name, bool condition) {
    if (condition) {
        printf("%sTest %s: PASSED%s\n", GREEN, test_name, RESET);
    } else {
        printf("%sTest %s: FAILED%s\n", RED, test_name, RESET);
    }
}

// -----------------------------------------------------------------------------
// Helper function to print test suite headers
// -----------------------------------------------------------------------------
static void print_test_suite_header(const char *suite_name) {
    printf("\nTest Suite: %s\n", suite_name);
    printf("-----------------------\n");
}

// -----------------------------------------------------------------------------
// Helper to check linked list structure against expected values
// -----------------------------------------------------------------------------
static bool checkListStructure(struct node *list, int expected[], int size) {
    struct node *current = list;
    for (int i = 0; i < size; i++) {
        if (current == NULL || current->value != expected[i]) {
            return false;
        }
        current = current->next;
    }
    return current == NULL;
}

// -----------------------------------------------------------------------------
// Test Cases for sumNodesWhile() and sumNodesFor()
// -----------------------------------------------------------------------------

// Test 1: Empty list
static void test_sumEmptyList(void) {
    print_test_suite_header("Sum of Empty List");
    struct node *list = NULL;
    int expected = 0;
    int sumWhile = sumNodesWhile(list);
    int sumFor = sumNodesFor(list);
    run_test("sumNodesWhile on empty list", sumWhile == expected);
    run_test("sumNodesFor on empty list", sumFor == expected);
}

// Test 2: Single node
static void test_sumSingleNode(void) {
    print_test_suite_header("Sum of Single Node");
    struct node *list = prependNode(5, NULL);
    int expected = 5;
    int sumWhile = sumNodesWhile(list);
    int sumFor = sumNodesFor(list);
    run_test("sumNodesWhile on single node", sumWhile == expected);
    run_test("sumNodesFor on single node", sumFor == expected);
    freeList(list);
}

// Test 3: Multiple nodes
static void test_sumMultipleNodes(void) {
    print_test_suite_header("Sum of Multiple Nodes");
    struct node *list = NULL;
    list = prependNode(3, list);
    list = prependNode(2, list);
    list = prependNode(1, list); // 1 -> 2 -> 3
    int expected = 6;
    int sumWhile = sumNodesWhile(list);
    int sumFor = sumNodesFor(list);
    run_test("sumNodesWhile on multiple nodes", sumWhile == expected);
    run_test("sumNodesFor on multiple nodes", sumFor == expected);
    freeList(list);
}

// Test 4: Negative numbers
static void test_sumNegativeNumbers(void) {
    print_test_suite_header("Sum with Negative Numbers");
    struct node *list = NULL;
    list = prependNode(-3, list);
    list = prependNode(2, list);
    list = prependNode(-1, list); // -1 -> 2 -> -3
    int expected = -2;
    int sumWhile = sumNodesWhile(list);
    int sumFor = sumNodesFor(list);
    run_test("sumNodesWhile with negatives", sumWhile == expected);
    run_test("sumNodesFor with negatives", sumFor == expected);
    freeList(list);
}

// Test 5: Zero included
static void test_sumWithZero(void) {
    print_test_suite_header("Sum with Zero");
    struct node *list = NULL;
    list = prependNode(0, list);
    list = prependNode(5, list);
    list = prependNode(-5, list); // -5 -> 5 -> 0
    int expected = 0;
    int sumWhile = sumNodesWhile(list);
    int sumFor = sumNodesFor(list);
    run_test("sumNodesWhile with zero", sumWhile == expected);
    run_test("sumNodesFor with zero", sumFor == expected);
    freeList(list);
}

// -----------------------------------------------------------------------------
// Test Cases for deleteFirstInstance()
// -----------------------------------------------------------------------------

// Test 1: Delete from empty list
static void test_deleteFromEmptyList(void) {
    print_test_suite_header("Delete from Empty List");
    struct node *list = NULL;
    list = deleteFirstInstance(list, 5);
    bool condition = checkListStructure(list, NULL, 0);
    run_test("delete from empty list", condition);
}

// Test 2: Delete head node
static void test_deleteHead(void) {
    print_test_suite_header("Delete Head Node");
    struct node *list = NULL;
    list = prependNode(1, list);
    list = prependNode(2, list);
    list = prependNode(3, list); // 3 -> 2 -> 1
    list = deleteFirstInstance(list, 3);
    int expected[] = {2, 1};
    bool structureOk = checkListStructure(list, expected, 2);
    int sum = sumNodesWhile(list);
    bool sumOk = (sum == 3);
    run_test("structure after deleting head", structureOk);
    run_test("sum after deleting head", sumOk);
    freeList(list);
}

// Test 3: Delete middle node
static void test_deleteMiddle(void) {
    print_test_suite_header("Delete Middle Node");
    struct node *list = NULL;
    list = prependNode(1, list);
    list = prependNode(2, list);
    list = prependNode(3, list); // 3 -> 2 -> 1
    list = deleteFirstInstance(list, 2);
    int expected[] = {3, 1};
    bool structureOk = checkListStructure(list, expected, 2);
    int sum = sumNodesWhile(list);
    bool sumOk = (sum == 4);
    run_test("structure after deleting middle", structureOk);
    run_test("sum after deleting middle", sumOk);
    freeList(list);
}

// Test 4: Delete last node
static void test_deleteLast(void) {
    print_test_suite_header("Delete Last Node");
    struct node *list = NULL;
    list = prependNode(1, list);
    list = prependNode(2, list);
    list = prependNode(3, list); // 3 -> 2 -> 1
    list = deleteFirstInstance(list, 1);
    int expected[] = {3, 2};
    bool structureOk = checkListStructure(list, expected, 2);
    int sum = sumNodesWhile(list);
    bool sumOk = (sum == 5);
    run_test("structure after deleting last", structureOk);
    run_test("sum after deleting last", sumOk);
    freeList(list);
}

// Test 5: Delete non-existent value
static void test_deleteNonExistent(void) {
    print_test_suite_header("Delete Non-Existent Value");
    struct node *list = NULL;
    list = prependNode(1, list);
    list = prependNode(2, list);
    list = prependNode(3, list); // 3 -> 2 -> 1
    struct node *original = list;
    list = deleteFirstInstance(list, 4);
    int expected[] = {3, 2, 1};
    bool structureOk = checkListStructure(list, expected, 3);
    bool sameAddress = (list == original);
    run_test("structure unchanged", structureOk);
    run_test("list pointer unchanged", sameAddress);
    freeList(list);
}

// Test 6: Delete first occurrence in duplicates
static void test_deleteFirstOccurrence(void) {
    print_test_suite_header("Delete First Occurrence");
    struct node *list = NULL;
    list = prependNode(2, list);
    list = prependNode(3, list);
    list = prependNode(3, list); // 3 -> 3 -> 2
    list = deleteFirstInstance(list, 3);
    int expected[] = {3, 2};
    bool structureOk = checkListStructure(list, expected, 2);
    int sum = sumNodesWhile(list);
    bool sumOk = (sum == 5);
    run_test("structure after first occurrence", structureOk);
    run_test("sum after deletion", sumOk);
    freeList(list);
}

// Test 7: Delete single node
static void test_deleteSingleNode(void) {
    print_test_suite_header("Delete Single Node");
    struct node *list = prependNode(5, NULL);
    list = deleteFirstInstance(list, 5);
    bool structureOk = checkListStructure(list, NULL, 0);
    run_test("single node deleted", structureOk);
    freeList(list);
}

// -----------------------------------------------------------------------------
// Test Cases for deleteFirstInstanceWrapper()
// -----------------------------------------------------------------------------

// Test 1: Delete from empty list using wrapper
static void test_wrapperDeleteFromEmptyList(void) {
    print_test_suite_header("Wrapper Delete from Empty List");
    struct list list_struct = { .head = NULL };
    deleteFirstInstanceWrapper(&list_struct, 5);
    bool condition = checkListStructure(list_struct.head, NULL, 0);
    run_test("wrapper delete from empty list", condition);
}

// Test 2: Delete head node using wrapper
static void test_wrapperDeleteHead(void) {
    print_test_suite_header("Wrapper Delete Head Node");
    struct list list_struct;
    list_struct.head = NULL;
    list_struct.head = prependNode(1, list_struct.head);
    list_struct.head = prependNode(2, list_struct.head);
    list_struct.head = prependNode(3, list_struct.head); // 3 -> 2 -> 1
    deleteFirstInstanceWrapper(&list_struct, 3);
    int expected[] = {2, 1};
    bool structureOk = checkListStructure(list_struct.head, expected, 2);
    int sum = sumNodesWhile(list_struct.head);
    bool sumOk = (sum == 3);
    run_test("wrapper structure after deleting head", structureOk);
    run_test("wrapper sum after deleting head", sumOk);
    freeList(list_struct.head);
}

// Test 3: Delete middle node using wrapper
static void test_wrapperDeleteMiddle(void) {
    print_test_suite_header("Wrapper Delete Middle Node");
    struct list list_struct;
    list_struct.head = NULL;
    list_struct.head = prependNode(1, list_struct.head);
    list_struct.head = prependNode(2, list_struct.head);
    list_struct.head = prependNode(3, list_struct.head); // 3 -> 2 -> 1
    deleteFirstInstanceWrapper(&list_struct, 2);
    int expected[] = {3, 1};
    bool structureOk = checkListStructure(list_struct.head, expected, 2);
    int sum = sumNodesWhile(list_struct.head);
    bool sumOk = (sum == 4);
    run_test("wrapper structure after deleting middle", structureOk);
    run_test("wrapper sum after deleting middle", sumOk);
    freeList(list_struct.head);
}

// Test 4: Delete last node using wrapper
static void test_wrapperDeleteLast(void) {
    print_test_suite_header("Wrapper Delete Last Node");
    struct list list_struct;
    list_struct.head = NULL;
    list_struct.head = prependNode(1, list_struct.head);
    list_struct.head = prependNode(2, list_struct.head);
    list_struct.head = prependNode(3, list_struct.head); // 3 -> 2 -> 1
    deleteFirstInstanceWrapper(&list_struct, 1);
    int expected[] = {3, 2};
    bool structureOk = checkListStructure(list_struct.head, expected, 2);
    int sum = sumNodesWhile(list_struct.head);
    bool sumOk = (sum == 5);
    run_test("wrapper structure after deleting last", structureOk);
    run_test("wrapper sum after deleting last", sumOk);
    freeList(list_struct.head);
}

// Test 5: Delete non-existent value using wrapper
static void test_wrapperDeleteNonExistent(void) {
    print_test_suite_header("Wrapper Delete Non-Existent Value");
    struct list list_struct;
    list_struct.head = NULL;
    list_struct.head = prependNode(1, list_struct.head);
    list_struct.head = prependNode(2, list_struct.head);
    list_struct.head = prependNode(3, list_struct.head); // 3 -> 2 -> 1
    struct node *original = list_struct.head;
    deleteFirstInstanceWrapper(&list_struct, 4);
    int expected[] = {3, 2, 1};
    bool structureOk = checkListStructure(list_struct.head, expected, 3);
    bool sameAddress = (list_struct.head == original);
    run_test("wrapper structure unchanged", structureOk);
    run_test("wrapper list pointer unchanged", sameAddress);
    freeList(list_struct.head);
}

// Test 6: Delete first occurrence in duplicates using wrapper
static void test_wrapperDeleteFirstOccurrence(void) {
    print_test_suite_header("Wrapper Delete First Occurrence");
    struct list list_struct;
    list_struct.head = NULL;
    list_struct.head = prependNode(2, list_struct.head);
    list_struct.head = prependNode(3, list_struct.head);
    list_struct.head = prependNode(3, list_struct.head); // 3 -> 3 -> 2
    deleteFirstInstanceWrapper(&list_struct, 3);
    int expected[] = {3, 2};
    bool structureOk = checkListStructure(list_struct.head, expected, 2);
    int sum = sumNodesWhile(list_struct.head);
    bool sumOk = (sum == 5);
    run_test("wrapper structure after first occurrence", structureOk);
    run_test("wrapper sum after deletion", sumOk);
    freeList(list_struct.head);
}

// Test 7: Delete single node using wrapper
static void test_wrapperDeleteSingleNode(void) {
    print_test_suite_header("Wrapper Delete Single Node");
    struct list list_struct;
    list_struct.head = prependNode(5, NULL);
    deleteFirstInstanceWrapper(&list_struct, 5);
    bool structureOk = checkListStructure(list_struct.head, NULL, 0);
    run_test("wrapper single node deleted", structureOk);
    freeList(list_struct.head);
}

// -----------------------------------------------------------------------------
// Run all tests
// -----------------------------------------------------------------------------
static void run_tests(void) {
    // Sum function tests
    test_sumEmptyList();
    test_sumSingleNode();
    test_sumMultipleNodes();
    test_sumNegativeNumbers();
    test_sumWithZero();

    // Delete function tests
    test_deleteFromEmptyList();
    test_deleteHead();
    test_deleteMiddle();
    test_deleteLast();
    test_deleteNonExistent();
    test_deleteFirstOccurrence();
    test_deleteSingleNode();

    // Wrapper delete function tests
    test_wrapperDeleteFromEmptyList();
    test_wrapperDeleteHead();
    test_wrapperDeleteMiddle();
    test_wrapperDeleteLast();
    test_wrapperDeleteNonExistent();
    test_wrapperDeleteFirstOccurrence();
    test_wrapperDeleteSingleNode();
}

int main(void) {
    run_tests();
    return 0;
}

// Function to create a node in memory
struct node *createNode(int value) {
    struct node *new = malloc(sizeof(struct node));
    if (new == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    new->value = value;
    new->next = NULL;
    return new;
}

// Function to add node to the head of the list
struct node *prependNode(int value, struct node *list) {
    struct node *new = createNode(value);
    new->next = list;
    return new;
}

// Function to free a linked list
void freeList(struct node *list) {
    while (list != NULL) {
        struct node *del = list; 
        list = list->next;
        free(del);
    }
}

// Function to print out a linked list
void printList(struct node *list) {
    printf("List contents:\n");
    while (list != NULL) {
        printf("%d->", list->value);
        list = list->next;
    }
    printf("X\n");
}

// 2. Write a function to sum the values in the list
int sumNodesWhile(struct node *list) {
    int sum = 0;
    while (list != NULL) {
        sum += list->value;
        list = list->next;
    }
    return sum;
}

int sumNodesFor(struct node *list) {
    int sum = 0;
    for (struct node *curr = list; curr != NULL; curr = curr->next) {
        sum += curr->value;
    }
    return sum;
}

// 3. Implement a function to delete the first instance of a value from a list
struct node *deleteFirstInstance(struct node *list, int value) {
    // Two Cases
    // 1. Deleting at the head, front of the list
    // 2. Deleting everywhere else

    // If list is empty, return it, nothing will be deleted
    if (list == NULL) return NULL;

    // If value is at the head
    if (list->value == value) {
        struct node *newHead = list->next;
        free(list);
        return newHead;
    }

    // Deleting everywhere else
    struct node *prev = list;
    struct node *curr = list->next;

    while (curr != NULL) {
        if (curr->value == value) {
            prev->next = curr->next;
            free(curr);
            return list;
        }
        prev = prev->next;
        curr = curr->next;
    }
    return list;
}

void deleteFirstInstanceWrapper(struct list *list, int value) {
    list->head = deleteFirstInstance(list->head, value);
}