#include <stdio.h>
#include <stdlib.h>

struct frazione{
    int numeratore;
    int denominatore;
};

struct frazione create_frazione(int numeratore, int denumeratore){
    struct frazione f;
    f.numeratore = numeratore;
    f.denominatore = denumeratore;
    return f;
}

void print_frazione(struct frazione *f){
    printf("%d/%d\n", f->numeratore, f->denominatore);
}

void semplifica_frazione(struct frazione *f){
    for(int i = 0; i <= f->numeratore && i <= f->denominatore; i++){
        if(f->numeratore % i == 0 && f->denominatore % i == 0){
            f->numeratore /= i;
            f->denominatore /= i;
        }
    }
}

int main(void){
    struct frazione f = create_frazione(10, 20); //fa una copia della struttura e diventa inefficiente
    semplifica_frazione(&f);    
    print_frazione(&f);

    return 0;
}
