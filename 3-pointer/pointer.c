#include <stdio.h>

int main(void){
    int a = 10;
    int *p = &a;

    printf("L'indirizzo di a:  %p\n", &a);
    printf("L'indirizzo di p: %p\n", p);

    printf("Il valore del puntatore: %d\n", *p);

    return 0;
}
