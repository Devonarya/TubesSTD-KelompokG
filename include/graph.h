#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <iostream>
#define firstVertex(G) G.firstVertex
#define nextVertex(v) v->nextVertex
#define firstEdge(v) v->firstEdge
#define idVertex(v) v->idVertex
#define destVertexID(e) e->destVertexID
#define weight(e) e->weight
#define nextEdge(e) e->nextEdge

using namespace std;

typedef struct vertex *adrVertex;
typedef struct edge *adrEdge;

struct vertex{
    string namaGedung;
    adrVertex nextVertex;
    adrEdge firstEdge;
};

struct edge{
    string destGedung;
    int weight;
    adrEdge nextEdge;
};

struct graph{
    adrVertex firstVertex;
};


void initGraph(graph &G);
void buildGraph(graph &G);
void createVertex(string namaGedung, adrVertex &V);
void createEdge(string destGedung, int weight);
void addVertex(graph &G, string namaGedung);
void addEdge(graph &G,string namaGedung,string destGedung, int weight);
void buildGraph(graph &G);
void showGraph(graph G);
adrVertex searchVertex(graph &G, string namaGedung);

#endif // GRAPH_H_INCLUDED
