#include <stdio.h>

char* longestCommonPrefix(char** strs, int strsSize) {
    char *prefix = malloc(255);

    int i;
    for(i = 0; strs[0][i] != 0; i++){
        for(int j = 1; j < strsSize; j++){
            if(strs[j][i] == '\0' || strs[j][i] != strs[0][i]){
                prefix[i] = '\0';
                return prefix;
            }
        }

        prefix[i] = strs[0][i];
    }
    prefix[i] = '\0';

    return prefix;
}

int main(void){
    //char *str[] = {"flower","flow","flight"};
    char *str[] = {"dog","racecar","car"}; 
    printf("%s", longestCommonPrefix(str, 2));
}
