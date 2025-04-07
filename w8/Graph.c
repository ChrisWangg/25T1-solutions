#include "Graph.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct graph {
	int nV;
	int nE;
	bool **edges;
};

static bool validVertex(Graph g, Vertex v);

Graph GraphNew(int nV) {
	Graph g = malloc(sizeof(struct graph));
	if (g == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}

	g->nV = nV;
	g->nE = 0;

	g->edges = malloc(nV * sizeof(bool *));
	for (int i = 0; i < g->nV; i++) {
		g->edges[i] = calloc(nV, sizeof(bool));
	}

	return g;
}

void GraphFree(Graph g) {
	for (int i = 0; i < g->nV; i++) {
		free(g->edges[i]);
	}
	free(g->edges);
	free(g);
}

int GraphNumVertices(Graph g) {
	return g->nV;
}

int GraphNumEdges(Graph g) {
	return g->nE;
}

bool GraphIsAdjacent(Graph g, Vertex v, Vertex w) {
	assert(validVertex(g, v));
	assert(validVertex(g, w));

	return g->edges[v][w];
}

void GraphInsertEdge(Graph g, Vertex v, Vertex w) {
	assert(validVertex(g, v));
	assert(validVertex(g, w));

	if (g->edges[v][w]) {
		return;
	}
	
	g->edges[v][w] = true;
	g->edges[w][v] = true;
	g->nE++;
}

void GraphRemoveEdge(Graph g, Vertex v, Vertex w) {
	assert(validVertex(g, v));
	assert(validVertex(g, w));

	if (!g->edges[v][w]) {
		return;
	}

	g->edges[v][w] = false;
	g->edges[w][v] = false;
	g->nE--;
}

void GraphShow(Graph g) {
	printf("Number of vertices: %d\n", g->nV);
	printf("Number of edges: %d\n", g->nE);
	printf("Edges:\n");
	for (int i = 0; i < g->nV; i++) {
		printf("%2d:", i);
		for (int j = 0; j < g->nV; j++) {
			if (g->edges[i][j]) {
				printf(" %d", j);
			}
		}
		printf("\n");
	}
	printf("\n");
}

static bool validVertex(Graph g, Vertex v) {
	return (v >= 0 && v < g->nV);
}