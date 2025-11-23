#include <stdio.h>

int main(void){
    int i = 0;
    
    repeat:
        printf("%d\n", i);
        i++;
        if(i < 10) goto repeat;
    return 0;
}
