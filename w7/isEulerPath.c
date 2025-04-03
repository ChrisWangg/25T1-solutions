#include "Graph.h"
#include "stdbool.h"
#include <stdio.h>
#include <stdlib.h>

/* Definition for struct edge */
struct edge {
    int v;
    int w;
};

/**
 * Checks whether a given path is an Euler Path.
 * To verify whether or not it is a valid Euler Path:
 *      - Uses every edge in the graph (checks 1 & 2)
 *      - Uses each edge exactly once (check 4)
 *      - Forms a continuous trail (check 3)
 */
bool isEulerPath(Graph g, struct edge e[], int nE) {
    /* 1. Check edge list has same number of edges as Graph.
     *    Why? Because for an Euler Path to exist,
     *         it must include all edges in the graph.
     */
    if (nE != GraphNumEdges(g)) {
        return false;
    }

    /* 2. Check edges are actually in the graph.
     *    Why? Because an Euler Path must only use edges that exist in the graph.
     */
    for (int i = 0; i < GraphNumEdges(g); i++) {
        if (!GraphIsAdjacent(g, e[i].v, e[i].w)) {
            return false;
        }
    }

    /* 3. Check that the edges form a valid path.
     *    Why? Because an Euler Path must be a continuous trail — 
     *         the end of one edge must be the start of the next.
     */
    for (int i = 0; i < GraphNumEdges(g) - 1; i++) {
        if (e[i].w != e[i + 1].v) {
            return false;
        }
    }

    /* 4. Check that each edge is included exactly once.
     *    Why? Because an Euler Path must not reuse any edge —
     *         each edge in the graph must be used once and only once.
     */
    for (int i = 0; i < GraphNumEdges(g); i++) {
        for (int j = i + 1; j < GraphNumEdges(g); j++) {
            if (e[i].v == e[j].v && e[i].w == e[j].w) return false;
            if (e[i].v == e[j].w && e[i].w == e[j].v) return false;
        }
    }

    return true;
}

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
static void run_test(const char *test_name, bool condition) {
    if (condition)
        printf("%sTest %s: PASSED%s\n", GREEN, test_name, RESET);
    else
        printf("%sTest %s: FAILED%s\n", RED, test_name, RESET);
}

static void print_header(const char *header) {
    printf("\n----- %s -----\n", header);
}

/* -----------------------------------------------------------------------------
// isEulerPath Tests
// -----------------------------------------------------------------------------
*/

/*
 * Test: Valid Euler Path
 *
 * Create a graph with 3 vertices (0, 1, 2) and 3 edges:
 *      0 -> 1, 1 -> 2, and 2 -> 0.
 * The edge array {0,1}, {1,2}, {2,0} is continuous and uses each edge exactly once.
 */
static void test_valid_euler_path(void) {
    print_header("Valid Euler Path Test");

    /* Create a graph with 3 vertices.
     * For this test we assume GraphInsertEdge inserts a single instance
     * of an edge (i.e. the graph is treated as directed for storage).
     */
    Graph g = GraphNew(3);
    GraphInsertEdge(g, 0, 1);
    GraphInsertEdge(g, 1, 2);
    GraphInsertEdge(g, 2, 0);
    /* GraphNumEdges(g) should now be 3. */

    struct edge path[3] = {
        {0, 1},
        {1, 2},
        {2, 0}
    };

    run_test("Valid Euler Path", isEulerPath(g, path, 3));
    GraphFree(g);
}

/*
 * Test: Missing Edge
 *
 * Create the same graph as above but supply a path that only uses 2 edges.
 * This should fail because the Euler Path does not cover all edges.
 */
static void test_missing_edge(void) {
    print_header("Missing Edge Test");

    Graph g = GraphNew(3);
    GraphInsertEdge(g, 0, 1);
    GraphInsertEdge(g, 1, 2);
    GraphInsertEdge(g, 2, 0);

    struct edge path[2] = {
        {0, 1},
        {1, 2}
    };

    run_test("Missing Edge", !isEulerPath(g, path, 2));
    GraphFree(g);
}

/*
 * Test: Nonexistent Edge
 *
 * Create the graph with edges: 0->1, 1->2, 2->0.
 * Then provide a path that contains an edge not in the graph.
 */
static void test_nonexistent_edge(void) {
    print_header("Nonexistent Edge Test");

    Graph g = GraphNew(3);
    GraphInsertEdge(g, 0, 1);
    GraphInsertEdge(g, 1, 2);
    GraphInsertEdge(g, 2, 0);

    /* Use an edge (1, 0) which is not in the graph (assuming directed storage) */
    struct edge path[3] = {
        {0, 1},
        {1, 0},
        {0, 2}
    };

    run_test("Nonexistent Edge", !isEulerPath(g, path, 3));
    GraphFree(g);
}

/*
 * Test: Discontinuous Path
 *
 * Create a valid graph and then supply an edge list that is not continuous.
 */
static void test_discontinuous_path(void) {
    print_header("Discontinuous Path Test");

    Graph g = GraphNew(3);
    GraphInsertEdge(g, 0, 1);
    GraphInsertEdge(g, 1, 2);
    GraphInsertEdge(g, 2, 0);

    /* Create a discontinuous path.
     * For example, if the edges do not connect properly:
     *  {0,1}, {2,0}, {1,2} is discontinuous because the end of the first edge (1)
     *  does not match the start of the second edge (2).
     */
    struct edge path[3] = {
        {0, 1},
        {2, 0},
        {1, 2}
    };

    run_test("Discontinuous Path", !isEulerPath(g, path, 3));
    GraphFree(g);
}

/*
 * Test: Repeated Edge
 *
 * Create the valid graph and then supply a path that repeats an edge.
 */
static void test_repeated_edge(void) {
    print_header("Repeated Edge Test");

    Graph g = GraphNew(3);
    GraphInsertEdge(g, 0, 1);
    GraphInsertEdge(g, 1, 2);
    GraphInsertEdge(g, 2, 0);

    /* Create a path with a repeated edge:
     * {0,1}, {1,2}, {1,2} — the edge {1,2} appears twice.
     */
    struct edge path[3] = {
        {0, 1},
        {1, 2},
        {1, 2}
    };

    run_test("Repeated Edge", !isEulerPath(g, path, 3));
    GraphFree(g);
}

/* -----------------------------------------------------------------------------
// Run All Euler Path Tests
// -----------------------------------------------------------------------------
*/
static void run_all_tests(void) {
    test_valid_euler_path();
    test_missing_edge();
    test_nonexistent_edge();
    test_discontinuous_path();
    test_repeated_edge();
}

/* -----------------------------------------------------------------------------
// Main Function
// -----------------------------------------------------------------------------
*/
int main(void) {
    run_all_tests();
    return 0;
}
