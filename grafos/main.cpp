#include <iostream>
#include "extras.h"
#include "djikstra.h"
#include <vector>
using namespace std;

int main()
{
    Vertice *grafo = nullptr;

    llenarGrafo(&grafo);
    imprimirGrafo(grafo);

    int origen;
    cout << "Ingrese el vertice de origen para Dijkstra: ";
    cin >> origen;

    pair<vector<pair<int, int>>, int> arbol_caminos_minimos = dijkstra(grafo, origen);

    vector<pair<int, int>> caminos = arbol_caminos_minimos.first;
    int k = arbol_caminos_minimos.second;
    imprimirDijkstra(caminos, k);

    Vertice *origenVertice = buscarVertice(grafo, origen);

    cout << "Ingrese el vertice de destino para Dijkstra: ";
    cin >> origen;

    Vertice *destinoVertice = buscarVertice(grafo, origen);

    if (origenVertice && destinoVertice)
    {
        seguirCamino(origenVertice, destinoVertice, grafo, arbol_caminos_minimos);
    }
    else
    {
        cout << "Origen o destino no encontrado en el grafo.\n";
    }

    liberarMemoria(&grafo);

    return 0;
}