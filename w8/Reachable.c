#include "Set.h"
#include "Graph.h"
#include "Reachable.h"

static void dfs(Graph g, Vertex curr, Set reachableVertices);

Set reachable(Graph g, Vertex src) {
    Set reachableVertices = SetNew(GraphNumVertices(g));
    dfs(g, src, reachableVertices);
    return reachableVertices;
}

static void dfs(Graph g, Vertex curr, Set reachableVertices) {
    SetInsert(reachableVertices, curr);
    for (int i = 0; i < GraphNumVertices(g); i++) {
        if (SetContains(reachableVertices, i)) continue;
        if (GraphIsAdjacent(g, curr, i)) {
            dfs(g, i, reachableVertices);
        }
    }
}
