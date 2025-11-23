#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct line{
    char *s;
    struct line *next;
};

int main(int argc, char **argv){
    if(argc < 2){
        printf("Missing path file\n");
        return 1;
    }
    else if(argc > 2){
        printf("Too many argument\n");
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if(fp == NULL){
        printf("File not exist\n");
        return 1;
    }

    char buff[1024];
    struct line *head = NULL;
    while(fgets(buff, sizeof(buff), fp)){
        struct line *l = malloc(sizeof(*l));
        size_t bufflen = strlen(buff);

        l->s = malloc(bufflen + 1);
        for(int i = 0; i <= bufflen; i++){
            l->s[i] = buff[i];
        }

        l->next = head;
        head = l;
    }
    
    fclose(fp);

    while(head){
        printf("%s", head->s);
        head = head->next;
    }
    return 0;
}
