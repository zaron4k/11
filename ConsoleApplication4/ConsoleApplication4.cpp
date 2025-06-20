#include <iostream>
using namespace std;

int main() {
    int arr[10] = { 3, 0, 5, 0, 2, 7, 0, 9, 1, 0 };
    int result[10] = { 0 };  // инициализируем нулями

    int zeroIndex = 0;

    // Первый проход: кладем нули в начало
    for (int i = 0; i < 10; ++i) {
        int val = arr[i];

        __asm {
            mov eax, val; загружаем val в eax
            cmp eax, 0
            jne skip_zero

            mov ebx, zeroIndex
            lea edi, result
            mov dword ptr[edi + ebx * 4], 0
            inc zeroIndex

            skip_zero :
        }
    }

    // Второй проход: кладем ненулевые после нулей
    int nonZeroIndex = zeroIndex;

    for (int i = 0; i < 10; ++i) {
        int val = arr[i];
        if (val != 0) {
            __asm {
                mov eax, val
                mov ebx, nonZeroIndex
                lea edi, result
                mov dword ptr[edi + ebx * 4], eax
            }
            ++nonZeroIndex;
        }
    }

    // Вывод результата
    cout << "Rearranged array: ";
    for (int i = 0; i < 10; ++i) {
        cout << result[i] << " ";
    }
    cout << endl;

    return 0;
}
