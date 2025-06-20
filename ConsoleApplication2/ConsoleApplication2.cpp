#include <iostream>
using namespace std;

int main() {
    int numbers[5] = { 12, 7, 20, 3, 15 };  // any 5 different integers
    int maxVal = numbers[0];
    int sum = 0;
    int average = 0;
    int result = 0;

    __asm {
        xor eax, eax; eax = 0 (sum)
        mov ecx, 5; counter for 5 elements
        lea esi, numbers; esi->start of array
        mov ebx, [esi]; initial max value

        loop_start :
        mov edx, [esi]; edx = numbers[i]
            add eax, edx; sum += numbers[i]
            cmp edx, ebx
            jle skip_max
            mov ebx, edx; maxVal = numbers[i]
            skip_max:
        add esi, 4; move to next int(4 bytes)
            loop loop_start; decrement ecx, repeat if not 0

            mov sum, eax; store sum
            mov maxVal, ebx; store max
    }

    average = sum / 5;                  // average in C++
    result = maxVal - average;          // difference

    cout << "Maximum value: " << maxVal << endl;
    cout << "Average value: " << average << endl;
    cout << "Difference: " << result << endl;

    return 0;
}
