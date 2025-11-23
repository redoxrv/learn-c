#include <stdio.h>

void scambia(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

int main(void){
    int a = 10;
    int b = 15;
    int *pa = &a;
    int *pb = &b;

    printf("Il puntatore 1 si trova in: %p\n", pa);
    printf("Il puntatore 2 si trova in: %p\n", pb);

    scambia(pa, pb);

    printf("Il puntatore 1 si trova in: %p\n", pa);
    printf("Il puntatore 2 si trova in: %p\n", pb);

    return 0;
}
