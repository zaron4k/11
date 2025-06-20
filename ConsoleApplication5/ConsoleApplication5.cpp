#include <iostream>
using namespace std;

int main() {
    const int n = 4;  // example size 4x4, you can change it
    int arr[n][n] = {
        {1, 5, 3, 4},
        {2, 9, 6, 7},
        {8, 1, 0, 2},
        {4, 3, 5, 8}
    };

    // Print the original array
    cout << "Original array:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            cout << arr[i][j] << " ";
        cout << endl;
    }

    // For each column find max and replace it with zero (asm block inside loop)
    for (int col = 0; col < n; ++col) {
        int maxVal = arr[0][col];
        int maxRow = 0;

        // Find the max element in the column (C++ code)
        for (int row = 1; row < n; ++row) {
            if (arr[row][col] > maxVal) {
                maxVal = arr[row][col];
                maxRow = row;
            }
        }

        // Replace the max element with zero via asm
        __asm {
            mov eax, maxRow        // row index with max value
            mov ebx, col           // column index
            mov ecx, n             // array size
            lea edx, arr           // address of the array

            // Calculate address: arr[maxRow][col] = edx + (eax * n + ebx) * 4
            mov esi, eax           // row
            imul esi, ecx          // row * n
            add esi, ebx           // row * n + col
            shl esi, 2             // multiply by 4 (size of int)

            mov dword ptr[edx + esi], 0   // arr[maxRow][col] = 0
        }
    }

    // Swap last and second-last columns (C++ code)
    for (int row = 0; row < n; ++row) {
        int temp = arr[row][n - 1];
        arr[row][n - 1] = arr[row][n - 2];
        arr[row][n - 2] = temp;
    }

    // Print the modified array
    cout << "\nModified array:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            cout << arr[i][j] << " ";
        cout << endl;
    }

    return 0;
}
