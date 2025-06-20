#include <iostream>
using namespace std;

int main() {
    int a = 3, b = 4, x = 2;
    int y;

    __asm {
        mov eax, x; загружаем x в eax
        imul eax, eax; eax = x * x = x ^ 2
        cdq; расширяем знак из eax в edx(для деления знаковых чисел)
        idiv b; eax = (edx:eax) / b, делим x ^ 2 на b, результат в eax, остаток в edx

        mov ebx, eax; сохраняем результат деления(x ^ 2 / b) в ebx

        mov eax, a; загружаем a в eax
        imul eax, x; eax = a * x

        sub ebx, eax; ebx = (x ^ 2 / b) - (a * x)

        mov eax, ebx; eax = ebx, подготовка к возведению в квадрат
        imul eax, ebx; eax = ebx * ebx = ((x ^ 2 / b) - a * x) ^ 2

        mov y, eax; сохраняем результат в переменную y
    }

    cout << "y = " << y << endl;
    return 0;
}
