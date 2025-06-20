#include <iostream>
using namespace std;

int main() {
    cout << "Numbers from 200 to 500 with exactly 6 divisors:\n";

    for (int num = 200; num <= 500; ++num) {
        int count = 0;

        for (int i = 1; i <= num; ++i) {
            int result;
            __asm {
                mov eax, num; dividend
                cdq; sign extend EAX into EDX : EAX
                idiv i; divide by i
                mov result, edx; remainder in EDX
            }

            if (result == 0) {
                ++count;
            }
        }

        if (count == 6) {
            cout << num << " ";
        }
    }

    cout << endl;
    return 0;
}
