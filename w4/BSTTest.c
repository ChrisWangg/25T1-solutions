#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// -----------------------------------------------------------------------------
// ANSI Colour Codes for Test Output
// -----------------------------------------------------------------------------
#define RESET   "\033[0m"
#define GREEN   "\033[0;32m"
#define RED     "\033[0;31m"

// -----------------------------------------------------------------------------
// BST Node Definition
// -----------------------------------------------------------------------------
struct node {
    int value;
    struct node *left;
    struct node *right;
};

// -----------------------------------------------------------------------------
// Utility Functions
// -----------------------------------------------------------------------------

/*
 * Function: max
 * ---------------------
 * Returns the maximum of two integers.
 *
 * a: first integer.
 * b: second integer.
 *
 * returns: the larger of a and b.
 */
int max(int a, int b) {
    if (a > b) return a;
    return b;
}

// -----------------------------------------------------------------------------
// BST Function Prototypes and Implementations
// -----------------------------------------------------------------------------

/*
 * Function: bstNumNodes
 * ---------------------
 * Counts the total number of nodes in a tree.
 *
 * t: pointer to the root of the BST.
 *
 * returns: the total number of nodes in the tree.
 */
int bstNumNodes(struct node *t) {
    if (t == NULL) return 0;
    return 1 + bstNumNodes(t->left) + bstNumNodes(t->right);
}

/*
 * Function: bstCountOdds
 * ---------------------
 * Counts the number of nodes in the tree with odd values.
 *
 * t: pointer to the root of the BST.
 *
 * returns: the number of nodes that have an odd value.
 */
int bstCountOdds(struct node *t) {
    if (t == NULL) return 0;
    int count = bstCountOdds(t->left) + bstCountOdds(t->right);
    if (t->value % 2 == 1)
        count++;
    return count;
}

/*
 * Function: bstCountInternal
 * ---------------------
 * Counts the number of internal nodes in a tree.
 * An internal node is defined as a node with at least one child.
 *
 * t: pointer to the root of the BST.
 *
 * returns: the number of internal nodes in the tree.
 */
int bstCountInternal(struct node *t) {
    if (t == NULL) return 0;
    if (t->left == NULL && t->right == NULL) return 0;
    return 1 + bstCountInternal(t->left) + bstCountInternal(t->right);
}

/*
 * Function: bstHeight
 * ---------------------
 * Computes the height of a tree.
 * The height is defined as the length of the longest path from the root to a leaf.
 * For an empty tree, the height is defined as -1.
 *
 * t: pointer to the root of the BST.
 *
 * returns: the height of the tree.
 */
int bstHeight(struct node *t) {
    if (t == NULL) return -1;
    return 1 + max(bstHeight(t->left), bstHeight(t->right));
}

/*
 * Function: bstNodeLevel
 * ---------------------
 * Returns the level of the node containing a given key in the BST.
 * The level of the root is 0. If the key is not found, returns -1.
 *
 * t: pointer to the root of the BST.
 * key: the value to search for.
 *
 * returns: the level of the node with the given key, or -1 if not found.
 */
int bstNodeLevel(struct node *t, int key) {
    if (t == NULL) return -1;
    if (t->value == key) return 0;
    if (key < t->value) {
        int level = bstNodeLevel(t->left, key);
        if (level == -1) return -1;
        return level + 1;
    } else {
        int level = bstNodeLevel(t->right, key);
        if (level == -1) return -1;
        return level + 1;
    }
}

/*
 * Function: bstCountGreater
 * ---------------------
 * Counts the number of nodes in the BST whose values are greater than a given value.
 * This function leverages BST properties to access as few nodes as possible.
 *
 * t: pointer to the root of the BST.
 * val: the value to compare.
 *
 * returns: the number of nodes with values greater than val.
 */
int bstCountGreater(struct node *t, int val) {
    if (t == NULL) return 0;
    if (t->value <= val)
        return bstCountGreater(t->right, val);
    return 1 + bstCountGreater(t->left, val) + bstCountGreater(t->right, val);
}

// -----------------------------------------------------------------------------
// Helper Functions for Building and Freeing a BST
// -----------------------------------------------------------------------------

/*
 * Function: newNode
 * ---------------------
 * Creates a new BST node with the given value.
 *
 * value: the value to store in the node.
 *
 * returns: pointer to the newly allocated node.
 */
static struct node *newNode(int value) {
    struct node *n = malloc(sizeof(struct node));
    n->value = value;
    n->left = NULL;
    n->right = NULL;
    return n;
}

/*
 * Function: bstInsert
 * ---------------------
 * Inserts a value into the BST.
 *
 * t: pointer to the root of the BST.
 * value: the value to insert.
 *
 * returns: pointer to the root of the updated BST.
 */
static struct node *bstInsert(struct node *t, int value) {
    if (t == NULL)
        return newNode(value);
    if (value < t->value)
        t->left = bstInsert(t->left, value);
    else
        t->right = bstInsert(t->right, value);
    return t;
}

/*
 * Function: buildBST
 * ---------------------
 * Builds a BST from an array of integers.
 *
 * vals: pointer to the array of integers.
 * n: number of elements in the array.
 *
 * returns: pointer to the root of the created BST.
 */
static struct node *buildBST(int *vals, int n) {
    struct node *root = NULL;
    for (int i = 0; i < n; i++) {
        root = bstInsert(root, vals[i]);
    }
    return root;
}

/*
 * Function: freeBST
 * ---------------------
 * Frees all nodes in the BST.
 *
 * t: pointer to the root of the BST.
 */
static void freeBST(struct node *t) {
    if (t == NULL)
        return;
    freeBST(t->left);
    freeBST(t->right);
    free(t);
}

// -----------------------------------------------------------------------------
// Test Helper Functions
// -----------------------------------------------------------------------------

/*
 * Function: run_test
 * ---------------------
 * Prints "PASSED" or "FAILED" for a given test based on a boolean condition.
 *
 * test_name: description of the test.
 * condition: boolean value indicating whether the test passed.
 */
static void run_test(const char *test_name, bool condition) {
    if (condition)
        printf("%sTest %s: PASSED%s\n", GREEN, test_name, RESET);
    else
        printf("%sTest %s: FAILED%s\n", RED, test_name, RESET);
}

/*
 * Function: print_header
 * ---------------------
 * Prints a header for a group of tests.
 *
 * header: the header text to print.
 */
static void print_header(const char *header) {
    printf("\n----- %s -----\n", header);
}

// -----------------------------------------------------------------------------
// Grouped Test Cases by Function (Questions)
// -----------------------------------------------------------------------------

// Tests for bstNumNodes
static void test_bstNumNodes(void) {
    print_header("bstNumNodes Tests");

    // Empty tree test
    struct node *root = NULL;
    run_test("Empty tree", bstNumNodes(root) == 0);

    // Single node test
    int vals1[] = {10};
    root = buildBST(vals1, 1);
    run_test("Single node", bstNumNodes(root) == 1);
    freeBST(root);

    // Small tree test
    int vals2[] = {8, 3, 10, 1, 6};
    root = buildBST(vals2, 5);
    run_test("Small tree", bstNumNodes(root) == 5);
    freeBST(root);

    // Larger tree test
    int vals3[] = {15, 10, 20, 8, 12, 17, 25, 6, 9};
    root = buildBST(vals3, 9);
    run_test("Larger tree", bstNumNodes(root) == 9);
    freeBST(root);
}

// Tests for bstCountOdds
static void test_bstCountOdds(void) {
    print_header("bstCountOdds Tests");

    // Empty tree test
    struct node *root = NULL;
    run_test("Empty tree", bstCountOdds(root) == 0);

    // Single node even test
    int vals1[] = {10};
    root = buildBST(vals1, 1);
    run_test("Single even node", bstCountOdds(root) == 0);
    freeBST(root);

    // Single node odd test
    int vals2[] = {7};
    root = buildBST(vals2, 1);
    run_test("Single odd node", bstCountOdds(root) == 1);
    freeBST(root);

    // Small tree test (8, 3, 10, 1, 6) — odd values: 3 and 1
    int vals3[] = {8, 3, 10, 1, 6};
    root = buildBST(vals3, 5);
    run_test("Small tree", bstCountOdds(root) == 2);
    freeBST(root);

    // Larger tree test
    int vals4[] = {15, 11, 20, 7, 13, 18, 25};
    root = buildBST(vals4, 7);
    // Odd values: 15, 11, 7, 13, 25 (total 5)
    run_test("Larger tree", bstCountOdds(root) == 5);
    freeBST(root);
}

// Tests for bstCountInternal
static void test_bstCountInternal(void) {
    print_header("bstCountInternal Tests");

    // Empty tree test
    struct node *root = NULL;
    run_test("Empty tree", bstCountInternal(root) == 0);

    // Single node test (no internal nodes)
    int vals1[] = {10};
    root = buildBST(vals1, 1);
    run_test("Single node", bstCountInternal(root) == 0);
    freeBST(root);

    // Small tree test (8, 3, 10, 1, 6)
    int vals2[] = {8, 3, 10, 1, 6};
    root = buildBST(vals2, 5);
    // Internal nodes: 8 (has children 3,10) and 3 (has children 1,6)
    run_test("Small tree", bstCountInternal(root) == 2);
    freeBST(root);

    // Larger tree test
    int vals3[] = {15, 10, 20, 8, 12, 17, 25};
    root = buildBST(vals3, 7);
    // Internal nodes: 15, 10, 20 (total 3)
    run_test("Larger tree", bstCountInternal(root) == 3);
    freeBST(root);
}

// Tests for bstHeight
static void test_bstHeight(void) {
    print_header("bstHeight Tests");

    // Empty tree test: height should be -1
    struct node *root = NULL;
    run_test("Empty tree", bstHeight(root) == -1);

    // Single node test: height should be 0
    int vals1[] = {10};
    root = buildBST(vals1, 1);
    run_test("Single node", bstHeight(root) == 0);
    freeBST(root);

    // Small tree test: (8, 3, 10, 1, 6) => height should be 2
    int vals2[] = {8, 3, 10, 1, 6};
    root = buildBST(vals2, 5);
    run_test("Small tree", bstHeight(root) == 2);
    freeBST(root);

    // Left-skewed tree test
    int vals3[] = {10, 8, 6, 4, 2};
    root = buildBST(vals3, 5);
    // For a left-skewed tree, height should be 4
    run_test("Left-skewed tree", bstHeight(root) == 4);
    freeBST(root);

    // Right-skewed tree test
    int vals4[] = {2, 4, 6, 8, 10};
    root = buildBST(vals4, 5);
    // For a right-skewed tree, height should be 4
    run_test("Right-skewed tree", bstHeight(root) == 4);
    freeBST(root);
}

// Tests for bstNodeLevel
static void test_bstNodeLevel(void) {
    print_header("bstNodeLevel Tests");

    // Empty tree test
    struct node *root = NULL;
    run_test("Empty tree (not found)", bstNodeLevel(root, 10) == -1);

    // Single node test
    int vals1[] = {10};
    root = buildBST(vals1, 1);
    run_test("Single node (found)", bstNodeLevel(root, 10) == 0);
    run_test("Single node (not found)", bstNodeLevel(root, 5) == -1);
    freeBST(root);

    // Small tree test: (8, 3, 10, 1, 6)
    int vals2[] = {8, 3, 10, 1, 6};
    root = buildBST(vals2, 5);
    run_test("Small tree (root=8)", bstNodeLevel(root, 8) == 0);
    run_test("Small tree (leaf=1)", bstNodeLevel(root, 1) == 2);
    run_test("Small tree (not found)", bstNodeLevel(root, 99) == -1);
    freeBST(root);
}

// Tests for bstCountGreater
static void test_bstCountGreater(void) {
    print_header("bstCountGreater Tests");

    // Empty tree test
    struct node *root = NULL;
    run_test("Empty tree", bstCountGreater(root, 10) == 0);

    // Single node test
    int vals1[] = {10};
    root = buildBST(vals1, 1);
    run_test("Single node (10 > 5)", bstCountGreater(root, 5) == 1);
    run_test("Single node (10 not > 10)", bstCountGreater(root, 10) == 0);
    freeBST(root);

    // Small tree test: (8, 3, 10, 1, 6)
    int vals2[] = {8, 3, 10, 1, 6};
    root = buildBST(vals2, 5);
    // Nodes greater than 5: 8, 6, 10 => 3
    run_test("Small tree (val=5)", bstCountGreater(root, 5) == 3);
    // Nodes greater than 10: none
    run_test("Small tree (val=10)", bstCountGreater(root, 10) == 0);
    freeBST(root);

    // Larger tree test
    int vals3[] = {15, 10, 20, 8, 12, 17, 25};
    root = buildBST(vals3, 7);
    // Nodes greater than 12: 15, 20, 17, 25 => 4
    run_test("Larger tree (val=12)", bstCountGreater(root, 12) == 4);
    // Nodes greater than 25: none
    run_test("Larger tree (val=25)", bstCountGreater(root, 25) == 0);
    freeBST(root);
}

// -----------------------------------------------------------------------------
// Run All Tests
// -----------------------------------------------------------------------------
static void run_all_tests(void) {
    test_bstNumNodes();
    test_bstCountOdds();
    test_bstCountInternal();
    test_bstHeight();
    test_bstNodeLevel();
    test_bstCountGreater();
}

// -----------------------------------------------------------------------------
// Main Function
// -----------------------------------------------------------------------------
int main(void) {
    run_all_tests();
    return 0;
}
