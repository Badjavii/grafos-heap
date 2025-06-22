#ifndef HEAPSORT_H
#define HEAPSORT_H
#include <iostream>
using namespace std;
#include <vector>

// Heapify para Max Heap
void heapifyMax(vector<int> &arr, int n, int i)
{
    int largest = i;       // Inicializa el más grande como raíz
    int left = 2 * i + 1;  // hijo izquierdo
    int right = 2 * i + 2; // hijo derecho

    // Si el hijo izquierdo es mayor que la raíz
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // Si el hijo derecho es mayor que el más grande hasta ahora
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // Si el más grande no es la raíz
    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        // Recursivamente heapifica el subárbol afectado
        heapifyMax(arr, n, largest);
    }
}

// Heapify para Min Heap
void heapifyMin(vector<int> &arr, int n, int i)
{
    int smallest = i;      // Inicializa el más pequeño como raíz
    int left = 2 * i + 1;  // hijo izquierdo
    int right = 2 * i + 2; // hijo derecho

    // Si el hijo izquierdo es menor que la raíz
    if (left < n && arr[left] < arr[smallest])
        smallest = left;

    // Si el hijo derecho es menor que el más pequeño hasta ahora
    if (right < n && arr[right] < arr[smallest])
        smallest = right;

    // Si el más pequeño no es la raíz
    if (smallest != i)
    {
        swap(arr[i], arr[smallest]);
        // Recursivamente heapifica el subárbol afectado
        heapifyMin(arr, n, smallest);
    }
}

// Prototipo de la función heapsort
void heapsortMax(vector<int> &arr)
{
    int n = arr.size();

    // Construir el heap (Max Heap)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapifyMax(arr, n, i);

    // Extraer elementos del heap uno por uno
    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);  // Mover la raíz al final
        heapifyMax(arr, i, 0); // Llamar a heapify en el heap reducido
    }
}

void heapsortMin(vector<int> &arr)
{
    int n = arr.size();

    // Construir el heap (Min Heap)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapifyMin(arr, n, i);

    // Extraer elementos del heap uno por uno
    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);  // Mover la raíz al final
        heapifyMin(arr, i, 0); // Llamar a heapify en el heap reducido
    }
}

void printArray(const vector<int> &arr)
{
    for (int i : arr)
        cout << i << " ";
    cout << endl;
}

void printHeapsortMax(vector<int> &arr)
{
    cout << "Array ordenado (Max Heap): ";
    heapsortMax(arr);
    printArray(arr);
}

void printHeapsortMin(vector<int> &arr)
{
    cout << "Array ordenado (Min Heap): ";
    heapsortMin(arr);
    printArray(arr);
}

#endif // HEAPSORT_H