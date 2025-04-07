#include <stdbool.h>
typedef struct graph *Graph;

typedef int Vertex;

/**
 * Returns a new graph with nV vertices
 */
Graph GraphNew(int nV);

/**
 * Frees all memory allocated to the graph
 */
void GraphFree(Graph g);

/**
 * Returns the number of vertices in the graph
 */
int GraphNumVertices(Graph g);

/**
 * Returns the number of edges in the graph
 */
int GraphNumEdges(Graph g);

/**
 * Returns true if there is an edge between v and w,
 * and false otherwise
 */
bool GraphIsAdjacent(Graph g, Vertex v, Vertex w);

/**
 * Adds an edge between v and w
 */
void GraphInsertEdge(Graph g, Vertex v, Vertex w);

/**
 * Removes an edge between v and w
 */
void GraphRemoveEdge(Graph g, Vertex v, Vertex w);

/**
 * Displays the graph
 */
void GraphShow(Graph g);