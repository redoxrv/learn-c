#include <stdio.h>
#include <unistd.h>

#define COLONNE 25
#define RIGHE 75
#define VIVO '*'
#define MORTO ' '
#define SLEEP_USEC 100000

int convertiOffsetRiga(int offset){
    if(offset < 0) return RIGHE - 1;
    if(offset >= RIGHE) return 0;
    return offset;
}

int convertiOffsetColonna(int offset){
    if(offset < 0) return COLONNE - 1;
    if(offset >= COLONNE) return 0;
    return offset;
}

void inizializzaTabella(char tabella[COLONNE][RIGHE], char stato){
    for(int i = 0; i < COLONNE; i++){
        for(int j = 0; j < RIGHE; j++){
            tabella[i][j] = stato;
        }
    }
}

void setCella(char tabella[COLONNE][RIGHE], int colonna, int riga, char stato){
    tabella[convertiOffsetColonna(colonna)][convertiOffsetRiga(riga)] = stato;
}

char getCella(char tabella[COLONNE][RIGHE], int colonna, int riga){
    return tabella[convertiOffsetColonna(colonna)][convertiOffsetRiga(riga)];
}

void clearScreen(){
    printf("\033[2J\033[H");
}

void stampaTabella(char tabella[COLONNE][RIGHE]){
    clearScreen();
    for(int i = 0; i < COLONNE; i++){
        for(int j = 0; j < RIGHE; j++){
            printf("%c", getCella(tabella, i, j)); 
        }
        printf("\n");
    }
}

int contaCelleVicine(char tabella[COLONNE][RIGHE], int colonna, int riga){
    int conta = 0;

    for(int i = -1; i < 2; i++){
        for(int j = -1; j < 2; j++){
            if (i == 0 && j == 0) continue;
        
            if(getCella(tabella, colonna+i, riga+j) == VIVO) conta++;
        }
    }

    return conta;
}

void gameOfLife(char tabella[COLONNE][RIGHE], char temp[COLONNE][RIGHE]){
    for(int i = 0; i < COLONNE; i++){
        for(int j = 0; j < RIGHE; j++){
            int numero_celle_vive = contaCelleVicine(tabella, i, j);
            int stato_cella = getCella(tabella, i, j);
            int nuovo_stato = MORTO;
            
            if(stato_cella == VIVO){
                if(numero_celle_vive == 2 || numero_celle_vive == 3){
                    nuovo_stato = VIVO;
                }
            }
            else{
                if(numero_celle_vive == 3){
                    nuovo_stato = VIVO;
                }
            }

            setCella(temp, i, j, nuovo_stato);
        }
    }
}

void glider(char tabella[COLONNE][RIGHE]){
    setCella(tabella, 1, 0, VIVO);
    setCella(tabella, 2, 1, VIVO);
    setCella(tabella, 0, 2, VIVO);
    setCella(tabella, 1, 2, VIVO);
    setCella(tabella, 2, 2, VIVO);
}

void croce(char tabella[COLONNE][RIGHE]){
    setCella(tabella, 0, 1, VIVO);
    setCella(tabella, 1, 1, VIVO);
    setCella(tabella, 2, 1, VIVO);
}

int main(void){
    char tabella[COLONNE][RIGHE];
    char temp[COLONNE][RIGHE];

    inizializzaTabella(tabella, MORTO);
    glider(tabella);

    while(1){
        stampaTabella(tabella);
        gameOfLife(tabella, temp);
        usleep(SLEEP_USEC);
        stampaTabella(temp);
        gameOfLife(temp, tabella);
        usleep(SLEEP_USEC);
    }
    return 0;
}
