#include "graph.h"

int main() {

    graph G;
    initGraph(G);

    // Menambahkan gedung (vertex)
    addVertex(G, "TULT");
    addVertex(G, "Sport-Center");
    addVertex(G, "GKU");
    addVertex(G, "TUCH");
    addVertex(G, "CaCuk");
    addVertex(G, "Lapangan-Tenis");

    // Menambahkan jalan (edge) dengan label dan jarak acak
    addEdge(G,"TelRoad1", "TULT", "Sport-Center", 100); // A
    addEdge(G, "TelRoad2", "TULT", "GKU", 200);          // B
    addEdge(G, "TelRoad3","Sport-Center", "GKU", 300);         // C
    addEdge(G, "TelRoad4","Sport-Center", "CaCuk", 400);     // D
    addEdge(G, "TelRoad5","GKU", "TUCH", 500);          // E
    addEdge(G, "TelRoad6","GKU", "CaCuk", 600);              // F
    addEdge(G, "TelRoad7","CaCuk", "Lapangan-Tenis", 700);   // G
    addEdge(G, "TelRoad8","Lapangan-Tenis", "TUCH", 800); // H


    menu(G);

    return 0;
}
