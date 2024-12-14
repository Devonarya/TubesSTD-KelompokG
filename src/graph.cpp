#include "graph.h"
#include <iostream>
#define firstVertex(G) G.firstVertex
#define nextVertex(v) v->nextVertex
#define firstEdge(v) v->firstEdge
#define idVertex(v) v->idVertex
#define destVertexID(e) e->destVertexID
#define weight(e) e->weight
#define nextEdge(e) e->nextEdge

void initGraph(graph &G){
    G.firstVertex = nullptr;
}

void buildGraph(graph &G){
    string gedung;
    cout << "Masukkan Nama Gedung (0 untuk berhenti): ";
    while (cin >> gedung && != 0) {
        addVertex(G, gedung);
        cout << "Masukkan Nama Gedung (0 untuk berhenti): ";
    }
}

void createVertex(string namaGedung, adrVertex &V){
    V = new vertex;
    V->namaGedung = namaGedung;
    V->nextVertex = nullptr;
    V->firstEdge = nullptr;
}
void createEdge(string destGedung, int weight){
    E = new edge;
    E->destGedung = destGedung;
    E->weight = weight;
    E->nextEdge = nullptr;
}
void addVertex(graph &G, string namaGedung){
    adrVertex V;
    createVertex(namaGedung, V);

    if (G.firstVertex == nullptr) {
        G.firstVertex = V;
    } else {
        adrVertex temp = G.firstVertex;
        while (temp->nextVertex != nullptr) {
            temp = temp->nextVertex;
        }
        temp->nextVertex = V;
    }
}
void addEdge(graph &G,string namaGedung,string destGedung, int weight){
    adrVertex V = searchVertex(G, namaGedung);
    if (V != nullptr) {
        adrEdge E;
        createEdge(destGedung, weight, E);

        if (V->firstEdge == nullptr) {
            V->firstEdge = E;
        } else {
            adrEdge temp = V->firstEdge;
            while (temp->nextEdge != nullptr) {
                temp = temp->nextEdge;
            }
            temp->nextEdge = E;
        }
    }
}

void showGraph(graph G){
    adrVertex v = G.firstVertex;
    while (v != nullptr) {
        cout << "Vertex: " << v->namaGedung << endl;
        adrEdge e = v->firstEdge;
        while (e != nullptr) {
            cout << "  - Edge to " << e->destGedung << " with weight " << e->weight << endl;
            e = e->nextEdge;
        }
        v = v->nextVertex;
    }
}
adrVertex searchVertex(graph &G, string namaGedung){
    adrVertex temp = G.firstVertex;
    while (temp != nullptr) {
        if (temp->namaGedung == namaGedung) {
            return temp;
        }
        temp = temp->nextVertex;
    }
    return nullptr;
}
