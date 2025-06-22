#ifndef DJIKSTRA_H
#define DJIKSTRA_H
#include <vector>
#include <utility> // pair
#include <climits>
#include <queue>
#include "extras.h"

using namespace std;

int obtenerIndice(Vertice *cabeza, int valor)
{
    int idx = 0;
    while (cabeza != nullptr)
    {
        if (cabeza->valor == valor)
            return idx;
        cabeza = cabeza->siguiente;
        idx++;
    }
    return -1;
}

Vertice *obtenerPorIndice(Vertice *cabeza, int idx)
{
    while (cabeza != nullptr && idx--)
        cabeza = cabeza->siguiente;
    return cabeza;
}

pair<vector<pair<int, int>>, int> dijkstra(Vertice *cabeza, int origen_valor)
{
    int n = cantidadVertices(cabeza);
    vector<int> dist(n, INT_MAX);
    vector<int> previo(n, -1);
    vector<bool> visitado(n, false);
    vector<vector<int>> hijos(n);

    int origen_idx = obtenerIndice(cabeza, origen_valor);
    dist[origen_idx] = 0;

    // Dijkstra clásico sin heap
    for (int i = 0; i < n; ++i)
    {
        int u = -1, min_dist = INT_MAX;
        for (int j = 0; j < n; ++j)
            if (!visitado[j] && dist[j] < min_dist)
                min_dist = dist[u = j];

        if (u == -1)
            break;
        visitado[u] = true;

        Vertice *vu = obtenerPorIndice(cabeza, u);
        for (Arista *a = vu->lista_adyacencias; a; a = a->siguiente)
        {
            int v = obtenerIndice(cabeza, a->destino->valor);
            if (!visitado[v] && dist[u] + a->peso < dist[v])
            {
                dist[v] = dist[u] + a->peso;
                previo[v] = u;
            }
        }
    }

    // Construir árbol de caminos mínimos
    for (int i = 0; i < n; ++i)
        if (previo[i] != -1)
            hijos[previo[i]].push_back(i);

    // Calcular k (orden del árbol)
    int k = 0;
    for (const auto &lista : hijos)
        k = max(k, (int)lista.size());

    // Serialización del árbol k-ario con pares {valor, distancia}
    vector<pair<int, int>> serializado;
    vector<int> indice(n, -1);
    serializado.push_back({origen_valor, dist[origen_idx]});
    indice[origen_idx] = 0;

    queue<pair<int, int>> q;
    q.push({origen_idx, 0});

    while (!q.empty())
    {
        auto [nodo, pos] = q.front();
        q.pop();
        for (int j = 0; j < (int)hijos[nodo].size(); ++j)
        {
            int hijo = hijos[nodo][j];
            int pos_hijo = k * pos + j + 1;
            if (pos_hijo >= (int)serializado.size())
                serializado.resize(pos_hijo + 1, {-1, -1});
            Vertice *vh = obtenerPorIndice(cabeza, hijo);
            serializado[pos_hijo] = {vh->valor, dist[hijo]};
            indice[hijo] = pos_hijo;
            q.push({hijo, pos_hijo});
        }
    }

    return {serializado, k};
}

void imprimirDijkstra(const vector<pair<int, int>> &serializado, int k)
{
    cout << "Árbol de caminos mínimos (k-ario):" << endl;
    for (int i = 0; i < (int)serializado.size(); ++i)
    {
        if (serializado[i].first != -1)
            cout << "Posición " << i << ": Valor = " << serializado[i].first
                 << ", Distancia = " << serializado[i].second << endl;
    }
    cout << "Orden del árbol: " << k << endl;
}

#endif // DJIKSTRA_H