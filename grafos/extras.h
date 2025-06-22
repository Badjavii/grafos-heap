#ifndef EXTRAS_H
#define EXTRAS_H
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Arista;

struct Vertice
{
    int valor;
    Vertice *siguiente;
    Arista *lista_adyacencias;
};

struct Arista
{
    Vertice *destino;
    Arista *siguiente;
    int peso;
};

Vertice *crearVertice(int valor)
{
    Vertice *nuevo = new Vertice;
    nuevo->valor = valor;
    nuevo->siguiente = nullptr;
    nuevo->lista_adyacencias = nullptr;
    return nuevo;
}

Vertice *buscarVertice(Vertice *cabeza, int valor)
{
    Vertice *actual = cabeza;
    while (actual != nullptr)
    {
        if (actual->valor == valor)
        {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

// Modificada para buscar por destino y peso
Arista *buscarArista(Vertice *origen, Vertice *destino, int peso)
{
    Arista *actual = origen->lista_adyacencias;
    while (actual != nullptr)
    {
        if (actual->destino == destino && actual->peso == peso)
        {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

bool existeVertice(Vertice *cabeza, int valor)
{
    return buscarVertice(cabeza, valor) != nullptr;
}

// Modificada para buscar por destino y peso
bool existeArista(Vertice *origen, Vertice *destino, int peso)
{
    return buscarArista(origen, destino, peso) != nullptr;
}

Arista *crearArista(Vertice *destino, int peso)
{
    Arista *nueva = new Arista;
    nueva->destino = destino;
    nueva->siguiente = nullptr;
    nueva->peso = peso;
    return nueva;
}

void insertarVertice(Vertice **cabeza, int valor)
{
    Vertice *nuevo = crearVertice(valor);
    nuevo->siguiente = *cabeza;
    *cabeza = nuevo;
}

void insertarArista(Vertice *origen, Vertice *destino, int peso)
{
    Arista *nueva = crearArista(destino, peso);
    nueva->siguiente = origen->lista_adyacencias;
    origen->lista_adyacencias = nueva;
}

void agregarVertice(Vertice **cabeza)
{
    int valor;
    cout << "Ingrese el valor del nuevo vertice: ";
    cin >> valor;
    insertarVertice(cabeza, valor);
}

// Modificada para pedir el peso y pasarlo a las funciones correspondientes
void agregarArista(Vertice *cabeza)
{
    int valorOrigen, valorDestino, peso;
    cout << "Ingrese el valor del vertice origen: ";
    cin >> valorOrigen;
    cout << "Ingrese el valor del vertice destino: ";
    cin >> valorDestino;
    cout << "Ingrese el peso de la arista: ";
    cin >> peso;

    // Buscar los vértices
    Vertice *origen = buscarVertice(cabeza, valorOrigen);
    Vertice *destino = buscarVertice(cabeza, valorDestino);

    if (!origen || !destino)
    {
        cout << "Uno o ambos vertices no existen." << endl;
        return;
    }

    if (existeArista(origen, destino, peso))
    {
        cout << "La arista ya existe." << endl;
        return;
    }

    insertarArista(origen, destino, peso);
    cout << "Arista agregada exitosamente." << endl;
}

void llenarGrafo(Vertice **cabeza)
{
    int n;
    cout << "Ingrese el numero de vertices: ";
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        agregarVertice(cabeza);
    }

    int m;
    cout << "Ingrese el numero de aristas: ";
    cin >> m;

    for (int i = 0; i < m; i++)
    {
        agregarArista(*cabeza);
    }
}

void imprimirGrafo(Vertice *cabeza)
{
    Vertice *actual = cabeza;
    while (actual != nullptr)
    {
        cout << "Vertice: " << actual->valor << " -> ";
        Arista *adyacente = actual->lista_adyacencias;
        while (adyacente != nullptr)
        {
            cout << adyacente->destino->valor << "(" << adyacente->peso << ") ";
            adyacente = adyacente->siguiente;
        }
        cout << endl;
        actual = actual->siguiente;
    }
}

// Modificada para eliminar por destino y peso
void eliminarArista(Vertice *origen, Vertice *destino, int peso)
{
    if (!existeArista(origen, destino, peso))
    {
        cout << "Arista no encontrada." << endl;
        return;
    }

    Arista *actual = origen->lista_adyacencias;
    Arista *anterior = nullptr;

    while (actual != nullptr && !(actual->destino == destino && actual->peso == peso))
    {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == nullptr)
        return; // Por seguridad

    if (anterior == nullptr)
    {
        origen->lista_adyacencias = actual->siguiente; // Eliminar la primera arista
    }
    else
    {
        anterior->siguiente = actual->siguiente; // Eliminar una arista intermedia o final
    }

    delete actual; // Liberar memoria de la arista eliminada
}

// Modificada para pedir el peso de la arista a eliminar
void eliminarVertice(Vertice **cabeza, int valor)
{
    if (!existeVertice(*cabeza, valor))
    {
        cout << "Vertice no encontrado." << endl;
        return;
    }

    Vertice *actual = buscarVertice(*cabeza, valor);

    Vertice *anterior = nullptr;
    Vertice *temp = *cabeza;
    while (temp != nullptr && temp != actual)
    {
        anterior = temp;
        temp = temp->siguiente;
    }

    // Eliminar todas las aristas que apunten a este vértice desde otros vértices
    Vertice *v = *cabeza;
    while (v != nullptr)
    {
        if (v != actual)
        {
            Arista *arista = v->lista_adyacencias;
            while (arista != nullptr)
            {
                // Si la arista apunta al vértice a eliminar, la eliminamos
                if (arista->destino == actual)
                {
                    // Guardar el siguiente antes de eliminar
                    Arista *siguiente = arista->siguiente;
                    eliminarArista(v, actual, arista->peso);
                    arista = siguiente;
                }
                else
                {
                    arista = arista->siguiente;
                }
            }
        }
        v = v->siguiente;
    }

    // Eliminar todas las aristas asociadas al vértice (adyacencias)
    while (actual->lista_adyacencias != nullptr)
    {
        Arista *adyacente = actual->lista_adyacencias;
        eliminarArista(actual, adyacente->destino, adyacente->peso);
    }

    // Eliminar el vértice de la lista
    if (anterior == nullptr)
    {
        *cabeza = actual->siguiente; // Eliminar el primer vértice
    }
    else
    {
        anterior->siguiente = actual->siguiente; // Eliminar un vértice intermedio o final
    }

    delete actual; // Liberar memoria del vértice eliminado
}

void liberarMemoria(Vertice **cabeza)
{
    while (*cabeza != nullptr)
    {
        int valor = (*cabeza)->valor;
        eliminarVertice(cabeza, valor);
    }
}

int cantidadVertices(Vertice *cabeza)
{
    int contador = 0;
    Vertice *actual = cabeza;
    while (actual != nullptr)
    {
        contador++;
        actual = actual->siguiente;
    }
    return contador;
}

// Modificada para buscar por peso
int pesoArista(Vertice *origen, Vertice *destino, int peso)
{
    Arista *arista = buscarArista(origen, destino, peso);
    if (arista != nullptr)
    {
        return arista->peso;
    }
    return -1; // Indica que la arista no existe
}

// Modificada para buscar por peso
void moverte(Vertice *&actual, Vertice *destino, int peso)
{
    Arista *arista = buscarArista(actual, destino, peso);
    if (arista && arista->peso == peso)
    {
        actual = destino;
        cout << "Te has movido al vertice " << actual->valor << endl;
    }
    else
    {
        cout << "No existe una arista con ese peso hacia el vertice destino." << endl;
    }
}

// Busca el índice del hijo adecuado en el árbol de caminos mínimos serializado.
// Retorna el índice del hijo cuyo valor coincide con el destino, o -1 si no lo encuentra.
int buscarIndiceHijo(const vector<pair<int, int>> &nodos, int idx, int k, int valorDestino)
{
    // Hijos de idx: k*idx + 1 hasta k*idx + k
    for (int j = 1; j <= k; ++j)
    {
        int hijo = k * idx + j;
        if (hijo >= static_cast<int>(nodos.size()))
            break;
        if (nodos[hijo].first == valorDestino)
            return hijo;
    }
    return -1; // No se encontró el hijo con el valor destino
}

// Busca recursivamente la ruta desde idx hasta valorDestino en el árbol serializado.
bool buscarRuta(const vector<pair<int, int>> &nodos, int idx, int k, int valorDestino, vector<int> &ruta)
{
    if (idx >= (int)nodos.size() || nodos[idx].first == -1)
        return false;

    if (nodos[idx].first == valorDestino)
    {
        ruta.push_back(idx);
        return true;
    }

    for (int j = 1; j <= k; ++j)
    {
        int hijo = k * idx + j;
        if (hijo >= (int)nodos.size())
            break;
        if (nodos[hijo].first != -1)
        {
            if (buscarRuta(nodos, hijo, k, valorDestino, ruta))
            {
                ruta.push_back(idx);
                return true;
            }
        }
    }
    return false;
}

// Recorre paso a paso desde 'origen' hasta 'destino' usando el árbol de caminos mínimos serializado.
void seguirCamino(Vertice *&origen, Vertice *destino, Vertice *grafo, const pair<vector<pair<int, int>>, int> &arbol)
{
    const vector<pair<int, int>> &nodos = arbol.first;
    int k = arbol.second;

    // Buscar índice inicial (origen) en el arreglo serializado
    int idxInicio = -1;
    for (size_t i = 0; i < nodos.size(); ++i)
    {
        if (nodos[i].first == origen->valor)
        {
            idxInicio = static_cast<int>(i);
            break;
        }
    }

    if (idxInicio == -1)
    {
        cout << "Origen no encontrado en el árbol.\n";
        return;
    }

    // Construir ruta desde origen hasta destino
    vector<int> rutaIndices;
    if (!buscarRuta(nodos, idxInicio, k, destino->valor, rutaIndices))
    {
        cout << "No se encontró una ruta desde el origen hasta el destino.\n";
        return;
    }

    reverse(rutaIndices.begin(), rutaIndices.end());

    for (size_t i = 1; i < rutaIndices.size(); ++i)
    {
        int idxSiguiente = rutaIndices[i];
        int valorSiguiente = nodos[idxSiguiente].first;
        int peso = nodos[idxSiguiente].second - nodos[rutaIndices[i - 1]].second;
        Vertice *siguiente = buscarVertice(grafo, valorSiguiente); // desde origen hacia adelante

        if (siguiente)
        {
            moverte(origen, siguiente, peso);
        }
        else
        {
            cout << "No se encontró el vértice con valor " << valorSiguiente << " en el grafo.\n";
            break;
        }
    }
}

#endif // EXTRAS_H