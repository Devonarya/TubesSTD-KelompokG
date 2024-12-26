#include "graph.h"
#include <iostream>
#define firstVertex(G) G.firstVertex
#define nextVertex(v) v->nextVertex
#define firstEdge(v) v->firstEdge
#define idVertex(v) v->idVertex
#define destVertexID(e) e->destVertexID
#define weight(e) e->weight
#define nextEdge(e) e->nextEdge
#include <set>

void menu(graph &G) {
    int pilihan;
    string namaGedung, tujuanGedung, namaJalan;
    int jarak;

    do {
        cout << "\nMENU:\n";
        cout << "1. Lihat gedung yang ada\n";
        cout << "2. Lihat jalan yang ada\n";
        cout << "3. Lihat gedung beserta jalan yang dimiliki\n";
        cout << "4. Tambah gedung\n";
        cout << "5. Tambah jalan antar gedung\n";
        cout << "6. Cari jarak terpendek antar gedung\n";
        cout << "7. Hapus Jalan antar gedung\n";
        cout << "8. Hapus gedung\n";
        cout << "9. Quit menu\n";
        cout << "Masukkan pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                showVertex(G);
                break;
            case 2:
                showEdge(G);
                break;
            case 3:
                showGraph(G);
                break;
            case 4:
                cout << "Masukkan nama gedung: ";
                cin >> namaGedung;
                addVertex(G, namaGedung);
                break;
            case 5:
                cout << "Masukkan nama jalan: ";
                cin >> namaJalan;
                cout << "Masukkan nama gedung asal: ";
                cin >> namaGedung;
                cout << "Masukkan nama gedung tujuan: ";
                cin >> tujuanGedung;
                cout << "Masukkan jarak antar gedung: ";
                cin >> jarak;
                addEdge(G, namaJalan, namaGedung, tujuanGedung, jarak);
                break;
                case 7:
                    cout << "Masukkan nama jalan: ";
                    cin >> namaJalan;
                    cout << "Masukkan nama gedung asal: ";
                    cin >> namaGedung;
                    cout << "Masukkan nama gedung tujuan: ";
                    cin >> tujuanGedung;
                    removeJalan(G, namaJalan, namaGedung, tujuanGedung, true);
                break;
                case 8:
                    cout << "Masukkan nama gedung yang ingin dihapus: ";
                    cin >> namaGedung;
                    removeGedung(G, namaGedung);
                break;
            case 9:
                cout << "Keluar dari menu." << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
                break;
        }

    } while (pilihan != 9);
}

void initGraph(graph &G) {
    G.firstVertex = nullptr;
}

void buildGraph(graph &G) {
    string gedung;
    cout << "Masukkan Nama Gedung (0 untuk berhenti): ";
    while (cin >> gedung && gedung != "0") {
        if (searchVertex(G, gedung) != nullptr) {
            cout << "Gedung " << gedung << " sudah ada dalam graf." << endl;
        } else {
            addVertex(G, gedung);
        }
        cout << "Masukkan Nama Gedung (0 untuk berhenti): ";
    }
}

void createVertex(string namaGedung, adrVertex &V) {
    V = new vertex;
    V->namaGedung = namaGedung;
    V->nextVertex = nullptr;
    V->firstEdge = nullptr;
}

void createEdge(string namaJalan,string destGedung, int weight, adrEdge &E) {
    E = new edge;
    E->namaJalan = namaJalan;
    E->destGedung = destGedung;
    E->weight = weight;
    E->nextEdge = nullptr;
}

void addVertex(graph &G, string namaGedung) {
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
    cout << "Gedung baru telah ditambahkan." << endl;
}

void addEdge(graph &G, string namaJalan, string namaGedung, string destGedung, int weight) {
    if (weight <= 0) {
        cout << "Jarak harus bernilai positif." << endl;
        return;
    }
    adrVertex V = searchVertex(G, namaGedung);
    adrVertex D = searchVertex(G, destGedung);
    if (V == nullptr) {
        cout << "Gedung " << namaGedung << " tidak ditemukan." << endl;
        return;
    } else if (D == nullptr) {
        cout << "Gedung " << destGedung << " tidak ditemukan." << endl;
        return;
    }

    adrEdge temp = V->firstEdge;
    bool roadExists = false;

    // Cek apakah jalan sudah ada pada gedung asal
    while (temp != nullptr) {
        if (temp->namaJalan == namaJalan && temp->destGedung == destGedung) {
            roadExists = true;
            break;
        }
        temp = temp->nextEdge;
    }

    if (roadExists) {
        cout << "Nama jalan sudah ada, silahkan masukkan nama jalan lain." << endl;
        return;
    }

    // Jika jalan tidak ditemukan, buat jalan baru
    adrEdge E;
    createEdge(namaJalan, destGedung, weight, E);

    if (V->firstEdge == nullptr) {
        V->firstEdge = E;
    } else {
        temp = V->firstEdge;
        while (temp->nextEdge != nullptr) {
            temp = temp->nextEdge;
        }
        temp->nextEdge = E;
    }

    cout << "Jalan baru bernama " << namaJalan << " ditambahkan dengan rute dari " << namaGedung << " ke " << destGedung << " dengan jarak " << weight << " meter." << endl;

    // Tambahkan juga edge pada gedung tujuan agar rute dua arah
    createEdge(namaJalan, namaGedung, weight, E);  // Membuat edge yang mengarah kembali
    if (D->firstEdge == nullptr) {
        D->firstEdge = E;
    } else {
        temp = D->firstEdge;
        while (temp->nextEdge != nullptr) {
            temp = temp->nextEdge;
        }
        temp->nextEdge = E;
    }
}

void removeGedung(graph &G, string idVertex) {
    adrVertex prevVertex = nullptr;
    adrVertex currentVertex = G.firstVertex;

    while (currentVertex != nullptr && currentVertex->namaGedung != idVertex) {
        prevVertex = currentVertex;
        currentVertex = currentVertex->nextVertex;
    }

    if (currentVertex == nullptr) {
        cout << "Gedung " << idVertex << " tidak ditemukan." << endl;
        return;
    }

    // Hapus semua edge yang terhubung ke vertex ini
    adrVertex temp = G.firstVertex;
    while (temp != nullptr) {
        adrEdge edge = temp->firstEdge;
        while (edge != nullptr) {
            removeJalan(G, edge->namaJalan, temp->namaGedung, idVertex, false);
            edge = edge->nextEdge;
        }
        temp = temp->nextVertex;
    }

    // Hapus vertex dari graf
    if (prevVertex == nullptr) {
        G.firstVertex = currentVertex->nextVertex;
    } else {
        prevVertex->nextVertex = currentVertex->nextVertex;
    }

    // Hapus semua edge yang berasal dari vertex ini
    while (currentVertex->firstEdge != nullptr) {
        adrEdge tempEdge = currentVertex->firstEdge;
        currentVertex->firstEdge = tempEdge->nextEdge;
        delete tempEdge;
    }

    delete currentVertex;
    cout << "Gedung " << idVertex << " berhasil dihapus." << endl;
}


void removeJalan(graph &G, string namaJalan, string namaGedung, string destGedung, bool stringOutput = true) {
    // Cari vertex untuk gedung asal
    adrVertex startVertex = searchVertex(G, namaGedung);
    if (startVertex == nullptr) {
        cout << "Gedung " << namaGedung << " tidak ditemukan." << endl;
        return;
    }

    // Cari vertex untuk gedung tujuan
    adrVertex endVertex = searchVertex(G, destGedung);
    if (endVertex == nullptr) {
        cout << "Gedung " << destGedung << " tidak ditemukan." << endl;
        return;
    }

    // Hapus jalan dari gedung asal ke gedung tujuan berdasarkan nama jalan
    adrEdge prevEdge = nullptr;
    adrEdge currentEdge = startVertex->firstEdge;

    while (currentEdge != nullptr && (currentEdge->destGedung != destGedung || currentEdge->namaJalan != namaJalan)) {
        prevEdge = currentEdge;
        currentEdge = currentEdge->nextEdge;
    }

    if (currentEdge != nullptr) {
        if (prevEdge == nullptr) {
            startVertex->firstEdge = currentEdge->nextEdge;
        } else {
            prevEdge->nextEdge = currentEdge->nextEdge;
        }

        delete currentEdge;
        if (stringOutput) cout << "Jalan " << namaJalan << " dari " << namaGedung << " ke " << destGedung << " berhasil dihapus." << endl;
    } else {
        if (stringOutput) cout << "Jalan " << namaJalan << " dari " << namaGedung << " ke " << destGedung << " tidak ditemukan." << endl;
    }

    // Hapus jalan dari gedung tujuan ke gedung asal berdasarkan nama jalan (jika ada)
    prevEdge = nullptr;
    currentEdge = endVertex->firstEdge;

    while (currentEdge != nullptr && (currentEdge->destGedung != namaGedung || currentEdge->namaJalan != namaJalan)) {
        prevEdge = currentEdge;
        currentEdge = currentEdge->nextEdge;
    }

    if (currentEdge != nullptr) {
        if (prevEdge == nullptr) {
            endVertex->firstEdge = currentEdge->nextEdge;
        } else {
            prevEdge->nextEdge = currentEdge->nextEdge;
        }

        delete currentEdge;
        if (stringOutput) cout << "Jalan " << namaJalan << " dari " << destGedung << " ke " << namaGedung << " berhasil dihapus." << endl;
    } else {
        if (stringOutput) cout << "Jalan " << namaJalan << " dari " << destGedung << " ke " << namaGedung << " tidak ditemukan." << endl;
    }
}


void showGraph(graph G) {
    adrVertex v = G.firstVertex;
    while (v != nullptr) {
        cout << "Gedung: " << v->namaGedung << endl;
        adrEdge e = v->firstEdge;
        if (e == nullptr) {
            cout << "  ** tidak ada jalan yang menghubungkan antar gedung ini **" << endl;
        }
        while (e != nullptr) {
            cout << "  - Jalan " << e->namaJalan << " menuju " << e->destGedung << " dengan jarak " << e->weight << " meter"<< endl;
            e = e->nextEdge;
        }
        v = v->nextVertex;
    }
}
void showEdge(graph G) {
    adrVertex temp = G.firstVertex;
    cout << "Daftar Jalan:\n";
    set<string> jalanSet;  // Set untuk menyimpan nama jalan agar tidak ada yang duplikat

    while (temp != nullptr) {
        adrEdge edge = temp->firstEdge;
        while (edge != nullptr) {
            // Tambahkan nama jalan ke set, sehingga hanya jalan yang unik yang ditampilkan
            jalanSet.insert(edge->namaJalan);
            edge = edge->nextEdge;
        }
        temp = temp->nextVertex;
    }

    // Tampilkan nama jalan yang unik
    for (const string& jalan : jalanSet) {
        cout << "- jalan " << jalan << endl;
    }
}


void showVertex(graph G) {
    adrVertex temp = G.firstVertex;
    cout << "Daftar Gedung:\n";
    while (temp != nullptr) {
        cout << "- " << temp->namaGedung << endl;
        temp = temp->nextVertex;
    }
}

adrVertex searchVertex(graph &G, string namaGedung) {
    adrVertex temp = G.firstVertex;
    while (temp != nullptr) {
        if (temp->namaGedung == namaGedung) {
            return temp;
        }
        temp = temp->nextVertex;
    }
    return nullptr;
}

