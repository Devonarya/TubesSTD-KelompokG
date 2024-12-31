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
    bool antiHujan;
    string kanopiInput;

    do {
        cout << "\n=================== MENU ===================\n";
        cout << "1. Lihat gedung yang ada\n";
        cout << "2. Lihat jalan yang ada\n";
        cout << "3. Lihat gedung beserta jalan yang dimiliki\n";
        cout << "4. Tambah gedung\n";
        cout << "5. Tambah jalan antar gedung\n";
        cout << "6. Cari jarak terpendek antar gedung\n";
        cout << "7. Jalur anti hujan\n";
        cout << "8. Hapus Jalan antar gedung\n";
        cout << "9. Hapus gedung\n";
        cout << "0. Quit menu\n";
        cout << "============================================";
        cout << "\nMasukkan pilihan: ";

        while (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Input tidak valid. Silakan coba lagi.\n";
            cout << "\nMasukkan pilihan: ";
        }

        cin.ignore();

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
                getline(cin, namaGedung);
                addVertex(G, namaGedung);
                break;
            case 5:
                cout << "Masukkan nama jalan: ";
                getline(cin, namaJalan);
                cout << "Masukkan nama gedung asal: ";
                getline(cin, namaGedung);
                cout << "Masukkan nama gedung tujuan: ";
                getline(cin, tujuanGedung);
                cout << "Masukkan jarak antar gedung (meter): ";
                if (!(cin >> jarak)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Input jarak tidak valid.\n";
                    break;
                }
                cin.ignore();

                do {
                    cout << "Apakah terdapat kanopi (ya/tidak)? ";
                    getline(cin, kanopiInput);
                    if (kanopiInput == "ya") {
                        antiHujan = true;
                        break;
                    } else if (kanopiInput == "tidak") {
                        antiHujan = false;
                        break;
                    } else {
                        cout << "Input tidak valid. Masukkan 'true' atau 'false'\n";
                    }
                } while (true);

                addEdge(G, namaJalan, namaGedung, tujuanGedung, jarak, antiHujan);
                break;
            case 6:
                cout << "Masukan Gedung awal: ";
                getline(cin, namaGedung);
                cout << "Masukan Tujuan Gedung: ";
                getline(cin, tujuanGedung);
                jalurTerpendek(G, namaGedung, tujuanGedung);
                break;
            case 7:
                cout << "Masukkan gedung awal: ";
                getline(cin, namaGedung);
                cout << "Masukkan gedung tujuan: ";
                getline(cin, tujuanGedung);
                jalurAntiHujan(G, namaGedung, tujuanGedung);
                break;
            case 8:
                cout << "Masukkan nama jalan: ";
                getline(cin, namaJalan);
                cout << "Masukkan nama gedung asal: ";
                getline(cin, namaGedung);
                cout << "Masukkan nama gedung tujuan: ";
                getline(cin, tujuanGedung);
                removeJalan(G, namaJalan, namaGedung, tujuanGedung, true);
                break;
            case 9:
                cout << "Masukkan nama gedung yang ingin dihapus: ";
                getline(cin, namaGedung);
                removeGedung(G, namaGedung);
                break;
            case 0:
                cout << "Keluar dari menu." << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
                break;
        }

    } while (pilihan != 0);
}

void initGraph(graph &G) {
    firstVertex(G) = nullptr;
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
    nextVertex(V) = nullptr;
    firstEdge(V) = nullptr;
}

void createEdge(string namaJalan,string destGedung, int weight, bool kanopi, adrEdge &E) {
    E = new edge;
    E->namaJalan = namaJalan;
    E->destGedung = destGedung;
    weight(E) = weight;
    E->kanopi = kanopi;
    nextEdge(E) = nullptr;
}

void addVertex(graph &G, string namaGedung) {
    adrVertex V;
    createVertex(namaGedung, V);

    if (firstVertex(G) == nullptr) {
        firstVertex(G) = V;
    } else {
        adrVertex temp = firstVertex(G);
        while (nextVertex(temp) != nullptr) {
            temp = nextVertex(temp);
        }
        nextVertex(temp) = V;
    }
    cout << "Gedung baru telah ditambahkan." << endl;
}

void addEdge(graph &G, string namaJalan, string namaGedung, string destGedung, int weight, bool kanopi) {
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

    adrEdge temp = firstEdge(V);
    while (temp != nullptr) {
        if (temp->namaJalan == namaJalan) {
            cout << "Nama jalan sudah ada, silahkan masukkan nama jalan lain." << endl;
            return;
        }
        temp = nextEdge(temp);
    }

    temp = firstEdge(D);
    while (temp != nullptr) {
        if (temp->namaJalan == namaJalan) {
            cout << "Nama jalan sudah ada, silahkan masukkan nama jalan lain." << endl;
            return;
        }
        temp = nextEdge(temp);
    }

    adrEdge E1;
    createEdge(namaJalan, destGedung, weight, kanopi, E1);

    if (firstEdge(V) == nullptr) {
        firstEdge(V) = E1;
    } else {
        temp = firstEdge(V);
        while (nextEdge(temp) != nullptr) {
            temp = nextEdge(temp);
        }
        nextEdge(temp) = E1;
    }

    adrEdge E2;
    createEdge(namaJalan, namaGedung, weight, kanopi, E2);

    if (firstEdge(D) == nullptr) {
        firstEdge(D) = E2;
    } else {
        temp = firstEdge(D);
        while (nextEdge(temp) != nullptr) {
            temp = nextEdge(temp);
        }
        nextEdge(temp) = E2;
    }

    cout << "Jalan baru bernama " << namaJalan << " ditambahkan dari " << namaGedung
         << " ke " << destGedung << " dengan jarak " << weight << " meter dan "
         << (kanopi ? "berkanopi." : "tidak berkanopi.") << endl;
}

void removeGedung(graph &G, string idVertex) {
    adrVertex prevVertex = nullptr;
    adrVertex currentVertex = firstVertex(G);

    while (currentVertex != nullptr && currentVertex->namaGedung != idVertex) {
        prevVertex = currentVertex;
        currentVertex = nextVertex(currentVertex);
    }

    if (currentVertex == nullptr) {
        cout << "Gedung " << idVertex << " tidak ditemukan." << endl;
        return;
    }

    adrVertex temp = G.firstVertex;
    while (temp != nullptr) {
        adrEdge edge = firstEdge(temp);
        while (edge != nullptr) {
            removeJalan(G, edge->namaJalan, temp->namaGedung, idVertex, false);
            edge = nextEdge(edge);
        }
        temp = temp->nextVertex;
    }

    if (prevVertex == nullptr) {
        firstVertex(G) = nextVertex(currentVertex);
    } else {
        nextVertex(prevVertex) = nextVertex(currentVertex);
    }

    while (firstEdge(currentVertex) != nullptr) {
        adrEdge tempEdge = firstEdge(currentVertex);
        firstEdge(currentVertex) = nextEdge(tempEdge);
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

    adrVertex endVertex = searchVertex(G, destGedung);
    if (endVertex == nullptr) {
        cout << "Gedung " << destGedung << " tidak ditemukan." << endl;
        return;
    }

    adrEdge prevEdge = nullptr;
    adrEdge currentEdge = firstEdge(startVertex);

    while (currentEdge != nullptr && (currentEdge->destGedung != destGedung || currentEdge->namaJalan != namaJalan)) {
        prevEdge = currentEdge;
        currentEdge = nextEdge(currentEdge);
    }

    if (currentEdge != nullptr) {
        if (prevEdge == nullptr) {
            firstEdge(startVertex) = nextEdge(currentEdge);
        } else {
            nextEdge(prevEdge) = nextEdge(currentEdge);
        }

        delete currentEdge;
        if (stringOutput) cout << "Jalan " << namaJalan << " dari " << namaGedung << " ke " << destGedung << " berhasil dihapus." << endl;
    } else {
        if (stringOutput) cout << "Jalan " << namaJalan << " dari " << namaGedung << " ke " << destGedung << " tidak ditemukan." << endl;
    }

    prevEdge = nullptr;
    currentEdge = firstEdge(endVertex);

    while (currentEdge != nullptr && (currentEdge->destGedung != namaGedung || currentEdge->namaJalan != namaJalan)) {
        prevEdge = currentEdge;
        currentEdge = nextEdge(currentEdge);
    }

    if (currentEdge != nullptr) {
        if (prevEdge == nullptr) {
            firstEdge(endVertex) = nextEdge(currentEdge);
        } else {
            nextEdge(prevEdge) = nextEdge(currentEdge);
        }

        delete currentEdge;
        if (stringOutput) cout << "Jalan " << namaJalan << " dari " << destGedung << " ke " << namaGedung << " berhasil dihapus." << endl;
    } else {
        if (stringOutput) cout << "Jalan " << namaJalan << " dari " << destGedung << " ke " << namaGedung << " tidak ditemukan." << endl;
    }
}


void showGraph(graph G) {
    adrVertex v = firstVertex(G);
    if (v == nullptr) {
        cout << "\n**Tidak ada data dalam graph**" << endl;
    }
    while (v != nullptr) {
        cout << "Gedung: " << v->namaGedung << endl;
        adrEdge e = firstEdge(v);
        if (e == nullptr) {
            cout << "  ** tidak ada jalan yang menghubungkan antar gedung ini **" << endl;
        }
        while (e != nullptr) {
            cout << "  - Jalan " << e->namaJalan << " menuju " << e->destGedung << " dengan jarak " << e->weight << " meter"<< endl;
            e = nextEdge(e);
        }
        v = nextVertex(v);
    }
}
void showEdge(graph G) {
    adrVertex temp = firstVertex(G);
    bool hasJalan = false;
    adrVertex checkTemp = firstVertex(G);
    while (checkTemp != nullptr) {
        if (firstEdge(checkTemp) != nullptr) {
            hasJalan = true;
            break;
        }
        checkTemp = nextVertex(checkTemp);
    }
    if (temp == nullptr || !hasJalan) {
        cout << "\n**Tidak ada data dalam terkait jalan graph**\n";
        return;
    }

    cout << "Daftar Jalan:\n";
    set<string> jalanSet;

    while (temp != nullptr) {
        adrEdge edge = firstEdge(temp);
        while (edge != nullptr) {
            jalanSet.insert(edge->namaJalan);
            edge = nextEdge(edge);
        }
        temp = nextVertex(temp);
    }

    for (const string& jalan : jalanSet) {
        cout << "- jalan " << jalan << endl;
    }
}


void showVertex(graph G) {
    adrVertex temp = firstVertex(G);
    if (temp == nullptr){
        cout << "\n**Tidak ada data terkait gedung dalam graph**\n";
    }else {
        cout << "Daftar Gedung:\n";
    }
    while (temp != nullptr) {
        cout << "- " << temp->namaGedung << endl;
        temp = nextVertex(temp);
    }
}

adrVertex searchVertex(graph &G, string namaGedung) {
    adrVertex temp = firstVertex(G);
    while (temp != nullptr) {
        if (temp->namaGedung == namaGedung) {
            return temp;
        }
        temp = nextVertex(temp);
    }
    return nullptr;
}


void jalurAntiHujan(graph G, string namaGedung, string tujuanGedung) {
    const int MAX_VERTEX = 100;
    int jarak[MAX_VERTEX];
    bool visited[MAX_VERTEX];
    adrVertex vertexArray[MAX_VERTEX];
    int idxAwal = -1, idxAkhir = -1;
    string path[MAX_VERTEX];

    int jumlahVertex = 0;
    adrVertex current = firstVertex(G);

    while (current != NULL) {
        vertexArray[jumlahVertex] = current;
        jarak[jumlahVertex] = INT_MAX;
        visited[jumlahVertex] = false;
        path[jumlahVertex] = "";

        if (current->namaGedung == namaGedung) idxAwal = jumlahVertex;
        if (current->namaGedung == tujuanGedung) idxAkhir = jumlahVertex;
        jumlahVertex++;
        current = nextVertex(current);
    }

    if (idxAwal == -1 || idxAkhir == -1) {
        cout << "Error: Gedung awal atau tujuan tidak ditemukan." << endl;
        return;
    }

    jarak[idxAwal] = 0;
    path[idxAwal] = vertexArray[idxAwal]->namaGedung;

    for (int i = 0; i < jumlahVertex; ++i) {
        int minJarak = INT_MAX;
        int idxMin = -1;

        for (int j = 0; j < jumlahVertex; ++j) {
            if (!visited[j] && jarak[j] < minJarak) {
                minJarak = jarak[j];
                idxMin = j;
            }
        }

        if (idxMin == -1) break;
        visited[idxMin] = true;

        adrEdge edge = firstEdge(vertexArray[idxMin]);
        while (edge != NULL) {
            if (!edge->kanopi) {
                edge = nextEdge(edge);
                continue;
            }

            int idxTetangga = -1;
            for (int k = 0; k < jumlahVertex; ++k) {
                if (vertexArray[k]->namaGedung == edge->destGedung) {
                    idxTetangga = k;
                    break;
                }
            }

            if (idxTetangga != -1 && !visited[idxTetangga]) {
                int jarakBaru = jarak[idxMin] + edge->weight;
                if (jarakBaru < jarak[idxTetangga]) {
                    jarak[idxTetangga] = jarakBaru;
                    path[idxTetangga] = path[idxMin] + " -> " + edge->namaJalan +
                                      " -> " + vertexArray[idxTetangga]->namaGedung;
                }
            }
            edge = nextEdge(edge);
        }
    }

    // Output hasil
    if (jarak[idxAkhir] == INT_MAX) {
        cout << "Tidak ada jalur anti hujan dari " << namaGedung
             << " ke " << tujuanGedung << "." << endl;
    } else {
        cout << "Jalur anti hujan terpendek dari " << namaGedung
             << " ke " << tujuanGedung << " adalah:" << endl;
        cout << path[idxAkhir] << endl;
        cout << "Dengan total jarak: " << jarak[idxAkhir] << endl;
    }
}

void jalurTerpendek(graph G, string namaGedung, string tujuanGedung) {
    const int MAX_VERTEX = 100;
    int jarak[MAX_VERTEX];
    bool visited[MAX_VERTEX];
    adrVertex vertexArray[MAX_VERTEX];
    int idxAwal = -1, idxAkhir = -1;
    string path[MAX_VERTEX];

    int jumlahVertex = 0;
    adrVertex current = firstVertex(G);

    while (current != NULL) {
        vertexArray[jumlahVertex] = current;
        jarak[jumlahVertex] = INT_MAX;
        visited[jumlahVertex] = false;
        path[jumlahVertex] = "";

        if (current->namaGedung == namaGedung) idxAwal = jumlahVertex;
        if (current->namaGedung == tujuanGedung) idxAkhir = jumlahVertex;
        jumlahVertex++;
        current = nextVertex(current);
    }

    if (idxAwal == -1 || idxAkhir == -1) {
        cout << "Gedung awal atau tujuan tidak ditemukan." << endl;
        return;
    }

    jarak[idxAwal] = 0;
    path[idxAwal] = vertexArray[idxAwal]->namaGedung;

    for (int i = 0; i < jumlahVertex; ++i) {
        int minJarak = INT_MAX;
        int idxMin = -1;

        for (int j = 0; j < jumlahVertex; ++j) {
            if (!visited[j] && jarak[j] < minJarak) {
                minJarak = jarak[j];
                idxMin = j;
            }
        }

        if (idxMin == -1) break;
        visited[idxMin] = true;

        adrEdge edge = firstEdge(vertexArray[idxMin]);
        while (edge != NULL) {
            int idxTetangga = -1;
            for (int k = 0; k < jumlahVertex; ++k) {
                if (vertexArray[k]->namaGedung == edge->destGedung) {
                    idxTetangga = k;
                    break;
                }
            }

            if (idxTetangga != -1 && !visited[idxTetangga]) {
                int jarakBaru = jarak[idxMin] + edge->weight;
                if (jarakBaru < jarak[idxTetangga]) {
                    jarak[idxTetangga] = jarakBaru;
                    path[idxTetangga] = path[idxMin] + " -> " + edge->namaJalan +
                                      " -> " + vertexArray[idxTetangga]->namaGedung;
                }
            }
            edge = nextEdge(edge);
        }
    }

    if (jarak[idxAkhir] == INT_MAX) {
        cout << "Tidak ada jalur dari " << namaGedung
             << " ke " << tujuanGedung << "." << endl;
    } else {
        cout << "Jalur terpendek dari " << namaGedung
             << " ke " << tujuanGedung << " adalah:" << endl;
        cout << path[idxAkhir] << endl;
        cout << "Dengan total jarak: " << jarak[idxAkhir] << " meter" << endl;
    }
}
