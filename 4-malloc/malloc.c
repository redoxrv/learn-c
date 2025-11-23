#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

char *create_prefix_string(char *init, int len){
    char *s = malloc(4+len+1);
    uint32_t *lenptr = (uint32_t*)s;
    *lenptr = len;
    
    s += 4;
    for(int i = 0; i < len; i++){
        s[i] = init[i];
    }

    s[len+1] = 0;

    return s;
}

void print_prefix_string(char *s){
    uint32_t *lenptr = (uint32_t*)(s-4);

    for(int i = 0; i < *lenptr; i++){
        putchar(s[i]);
    }
    printf("\n");
}

void ps_free(char *s){
    free(s-4);
}

uint32_t pslen(char *s){
    uint32_t *lenptr = (uint32_t*)(s-4);
    return *lenptr;
}

int main(){
    char *string = create_prefix_string("Hello World", 11);
    print_prefix_string(string);
    
    printf("%s\n", string);
    printf("La mia stringa è grande: %d\n", pslen(string));
    ps_free(string);

    return 0;
}
