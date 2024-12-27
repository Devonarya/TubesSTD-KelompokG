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
    string namaJalan;
    string destGedung;
    int weight;
    bool kanopi;
    adrEdge nextEdge;
};

struct graph{
    adrVertex firstVertex;
};

void menu(graph &G);
void initGraph(graph &G);
void buildGraph(graph &G);
void createVertex(string namaGedung, adrVertex &V);
void createEdge(string namaJalan, string destGedung, int weight);
void addVertex(graph &G, string namaGedung);
void addEdge(graph &G, string namaJalan, string namaGedung,string destGedung, int weight, bool kanopi);
void removeGedung(graph &G, string idVertex);
void removeJalan(graph &G, string namaJalan, string namaGedung, string destGedung, bool stringOutput);
void buildGraph(graph &G);
void showGraph(graph G);
void showEdge(graph G);
void showVertex(graph G);
adrVertex searchVertex(graph &G, string namaGedung);
void jalurAntiHujan(graph G, string namaGedung, string tujuanGedung);
int shortPathSearching(graph &G, string namaGedung, string tujuanGedung);

#endif // GRAPH_H_INCLUDED
