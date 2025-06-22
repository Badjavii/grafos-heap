#include <iostream>
#include <vector>
#include "heapsort.h"
using namespace std;

int main()
{
    vector<int> vecMin = {14, 18, 9, 25, 6, 11, 10};
    vector<int> vecMax = {14, 18, 9, 25, 6, 11, 10};

    cout << "Vector original: ";
    printArray(vecMin);

    printHeapsortMax(vecMax);

    printHeapsortMin(vecMin);

    return 0;
}