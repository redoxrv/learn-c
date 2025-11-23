#include <stdio.h>

int romanValue(char c){
    switch(c){
        case 'I':
            return 1;
        case 'V':
            return 5;
        case 'X':
            return 10;
        case 'L':
            return 50;
        case 'C':
            return 100;
        case 'D':
            return 500;
        case 'M':
            return 1000;
    }
    return -1;
}

int romanToInt(char *s){
    int numero = 0;
    for(int i = 0; s[i] != 0; i++){
        if(s[i+1] != 0){
            if(romanValue(s[i]) >= romanValue(s[i+1])){
                numero += romanValue(s[i]);
            }
            else{
                numero += romanValue(s[i+1]) - romanValue(s[i]);
                i++;
            }
        }
        else{
            numero += romanValue(s[i]);
        }
    }
    return numero;
}

int main(void){
    char s[] = "IX";
    printf("%d\n", romanToInt(s));
}
