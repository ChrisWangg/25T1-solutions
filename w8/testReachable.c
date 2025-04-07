#include "Graph.h"
#include "Set.h"
#include "Reachable.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* -----------------------------------------------------------------------------
// ANSI Colour Codes for Test Output
// -----------------------------------------------------------------------------
*/
#define RESET   "\033[0m"
#define GREEN   "\033[0;32m"
#define RED     "\033[0;31m"

/* -----------------------------------------------------------------------------
// Test Helper Functions
// -----------------------------------------------------------------------------
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

/*
 * checkReachable compares the contents of the Set (returned by reachable())
 * with an expected list of vertices.
 *
 * totalVertices is the number of vertices in the graph (used as the maximum
 * possible vertex value).
 *
 * It works by iterating from 0 to totalVertices-1, counting the number of
 * vertices in the set and checking that each vertex in the set is present in
 * the expected array.
 */
static bool checkReachable(Set s, int expected[], int nExpected, int totalVertices) {
    int count = 0;
    for (int i = 0; i < totalVertices; i++) {
        if (SetContains(s, i)) {
            // Verify this vertex is one we expected.
            bool found = false;
            for (int j = 0; j < nExpected; j++) {
                if (expected[j] == i) {
                    found = true;
                    break;
                }
            }
            if (!found) return false;
            count++;
        }
    }
    return count == nExpected;
}

/* -----------------------------------------------------------------------------
// reachable() Tests
// -----------------------------------------------------------------------------
*/

/*
 * Test: Single Vertex
 *
 * Create a graph with one vertex (0) and no edges. The only vertex reachable
 * from vertex 0 should be 0 itself.
 */
static void test_single_vertex(void) {
    print_header("Single Vertex Test");

    Graph g = GraphNew(1);
    Set r = reachable(g, 0);

    int expected[] = { 0 };
    bool condition = checkReachable(r, expected, 1, GraphNumVertices(g));
    run_test("Single Vertex", condition);

    SetFree(r);
    GraphFree(g);
}

/*
 * Test: Linear Chain
 *
 * Create a graph with 4 vertices connected in a chain:
 *      0 -> 1, 1 -> 2, 2 -> 3.
 * Starting from vertex 0, all vertices should be reachable.
 */
static void test_chain(void) {
    print_header("Chain Test");

    Graph g = GraphNew(4);
    GraphInsertEdge(g, 0, 1);
    GraphInsertEdge(g, 1, 2);
    GraphInsertEdge(g, 2, 3);

    Set r = reachable(g, 0);
    int expected[] = { 0, 1, 2, 3 };
    bool condition = checkReachable(r, expected, 4, GraphNumVertices(g));
    run_test("Chain", condition);

    SetFree(r);
    GraphFree(g);
}

/*
 * Test: Cycle
 *
 * Create a graph with a cycle:
 *      0 -> 1, 1 -> 2, 2 -> 0.
 * Starting from vertex 0, the reachable set should be {0, 1, 2}.
 */
static void test_cycle(void) {
    print_header("Cycle Test");

    Graph g = GraphNew(3);
    GraphInsertEdge(g, 0, 1);
    GraphInsertEdge(g, 1, 2);
    GraphInsertEdge(g, 2, 0);

    Set r = reachable(g, 0);
    int expected[] = { 0, 1, 2 };
    bool condition = checkReachable(r, expected, 3, GraphNumVertices(g));
    run_test("Cycle", condition);

    SetFree(r);
    GraphFree(g);
}

/*
 * Test: Branching Graph
 *
 * Create a graph with branches:
 *         0
 *        / \
 *       1   2
 *        \ /
 *         3
 *
 * Starting from 0, reachable vertices should be {0, 1, 2, 3}.
 */
static void test_branch(void) {
    print_header("Branch Test");

    Graph g = GraphNew(4);
    GraphInsertEdge(g, 0, 1);
    GraphInsertEdge(g, 0, 2);
    GraphInsertEdge(g, 1, 3);
    GraphInsertEdge(g, 2, 3);

    Set r = reachable(g, 0);
    int expected[] = { 0, 1, 2, 3 };
    bool condition = checkReachable(r, expected, 4, GraphNumVertices(g));
    run_test("Branch", condition);

    SetFree(r);
    GraphFree(g);
}

/*
 * Test: Disconnected Graph
 *
 * Create a graph with two disconnected components:
 *  Component 1: 0 -> 1, 1 -> 2
 *  Component 2: 3 -> 4
 *
 * Test reachable() starting from vertex 0 (should yield {0, 1, 2}) and
 * starting from vertex 3 (should yield {3, 4}).
 */
static void test_disconnected(void) {
    print_header("Disconnected Graph Test");

    Graph g = GraphNew(5);
    GraphInsertEdge(g, 0, 1);
    GraphInsertEdge(g, 1, 2);
    GraphInsertEdge(g, 3, 4);

    Set r1 = reachable(g, 0);
    int expected1[] = { 0, 1, 2 };
    bool condition1 = checkReachable(r1, expected1, 3, GraphNumVertices(g));
    run_test("Component 1", condition1);
    SetFree(r1);

    Set r2 = reachable(g, 3);
    int expected2[] = { 3, 4 };
    bool condition2 = checkReachable(r2, expected2, 2, GraphNumVertices(g));
    run_test("Component 2", condition2);
    SetFree(r2);

    GraphFree(g);
}

/* -----------------------------------------------------------------------------
// Run All Tests
// -----------------------------------------------------------------------------
*/
static void run_all_tests(void) {
    test_single_vertex();
    test_chain();
    test_cycle();
    test_branch();
    test_disconnected();
}

/* -----------------------------------------------------------------------------
// Main Function
// -----------------------------------------------------------------------------
*/
int main(void) {
    run_all_tests();
    return 0;
}
