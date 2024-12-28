#include "graph.h"

int main() {

    graph G;
    initGraph(G);

    addVertex(G, "TULT");
    addVertex(G, "Sport Center");
    addVertex(G, "GKU");
    addVertex(G, "TUCH");
    addVertex(G, "CaCuk");
    addVertex(G, "Lapangan Tenis");


    addEdge(G,"TelRoad1", "TULT", "Sport Center", 100, true);
    addEdge(G, "TelRoad2", "TULT", "TUCH", 200, false);
    addEdge(G, "TelRoad3","Sport Center", "GKU", 150, true);
    addEdge(G, "TelRoad4","Sport Center", "TUCH", 250, false);
    addEdge(G, "TelRoad5","GKU", "TUCH", 180, false);
    addEdge(G, "TelRoad6","GKU", "CaCuk", 100, true);
    addEdge(G, "TelRoad7","CaCuk", "Lapangan Tenis", 150, true);
    addEdge(G, "TelRoad8","CaCuk", "TUCH", 250, true);
    addEdge(G, "TelRoad9","Lapangan Tenis", "GKU", 300, true);


    menu(G);

    return 0;
}
