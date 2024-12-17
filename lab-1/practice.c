// При помощи команд печати языка C вывести на экран адреса переменных x и y.

#include <stdio.h>

int main() {
    int x = 10;
    int y = 20;

    printf("Pointer to x: %p\n", (void*)&x);
    printf("Pointer to y: %p\n", (void*)&y);

    return 0;
}
