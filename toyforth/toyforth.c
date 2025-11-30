#define TFOBJ_TYPE_INT 0
#define TFOBJ_TYPE_STR 1
#define TFOBJ_TYPE_BOOL 2
#define TFOBJ_TYPE_LIST 3
#define TFOBJ_TYPE_SYMBOL 4

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

typedef struct tfObj {
    int refCount;
    int type;
    union{
        int i;
        struct {
            char *ptr;
            size_t len;
        } str;
        struct {
            struct tfObj **elements;
            size_t len;
        } list;
    };
} tfObj;

typedef struct tfParser{
    char *program;
    char *token;
} tfParser;

typedef struct tfContext{
    tfObj *stack;
} tfContext;


void *xmalloc(size_t size){
    void *ptr = malloc(size);
    
    if(ptr == NULL){
        fprintf(stderr, "Out of memory allocating %zu bytes\n", size);
        exit(1); 
    }
    return ptr;
}

void *xrealloc(void *oldPtr, size_t size){
    void *ptr = realloc(oldPtr, size);

    if(ptr == NULL){
        fprintf(stderr, "Out of memory allocating %zu bytes\n", size);
        exit(1); 
    }
    return ptr;
}

tfObj *createObject(int type){
    tfObj *o = xmalloc(sizeof(tfObj));
    o->type = type;
    o->refCount++;

    return o;
}

tfObj *createIntObject(int i){
    tfObj *o = createObject(TFOBJ_TYPE_INT);
    o->i = i;

    return o;
}

tfObj *createStringObject(char *s, size_t len){
    tfObj *o = createObject(TFOBJ_TYPE_STR);
    o->str.ptr = xmalloc(len + 1);
    o->str.len = len;

    memcpy(o->str.ptr, s, len);
    o->str.ptr[len] = 0;

    return o;
}

tfObj *createSymbolObject(char *s, size_t len){
    tfObj *o = createStringObject(s, len);
    o->type = TFOBJ_TYPE_SYMBOL;

    return o;
}

tfObj *createBoolObject(int i){
    tfObj *o = createObject(TFOBJ_TYPE_BOOL);
    o->i = i;

    return o;
}

tfObj *createListObject(void){
    tfObj *o = createObject(TFOBJ_TYPE_LIST);
    o->list.elements = NULL;
    o->list.len = 0;

    return o;
}

void pushListObject(tfObj *rootObj, tfObj *element){
    rootObj->list.elements = xrealloc(rootObj->list.elements, sizeof(tfObj*) * rootObj->list.len + 1);
    rootObj->list.elements[rootObj->list.len] = element;
    rootObj->list.len++;
}

int isSymbol(int c){
    char simboli[] = "+-*/%";
    return isalpha(c) || strchr(simboli, c) != NULL;
}

void parserSpaces(tfParser *parser){
    while(isspace(parser->token[0])) parser->token++;
}

#define MAX_NUM_LEN 128
tfObj *parseNumber(tfParser *parser){
    char buffer[MAX_NUM_LEN];
    char *start = parser->token;
    char *end = NULL;
    
    if(parser->token[0] == '-') parser->token++;
    
    while(parser->token[0] && isdigit(parser->token[0])) parser->token++;
   
    end = parser->token;
    int numLen = end-start;
    memcpy(buffer, start, numLen);
    buffer[numLen] = 0;

    tfObj *o = createIntObject(atoi(buffer));
    return o;
}

tfObj *parseSymbol(tfParser *parser){
    char *start = parser->token;
    while(parser->token[0] && isSymbol(parser->token[0])) parser->token++;

    tfObj *o = createSymbolObject(start, parser->token - start);
    return o;
}

tfObj *compile(char *programText){
    tfParser parser;
    parser.program = programText;
    parser.token = programText;

    tfObj *rootObj = createListObject();
    while(parser.token){
        tfObj *o;
        parserSpaces(&parser);
       
        if(parser.token[0] == 0) break;

        if(isdigit(parser.token[0]) || (parser.token[0] == '-' && isdigit(parser.token[1]))){
            o = parseNumber(&parser);
        }
        else if(isSymbol(parser.token[0])){
            o = parseSymbol(&parser);
        }
        else{
            printf("Syntax errore near: %32s ...\n", parser.token);
            return NULL;
        }

        pushListObject(rootObj, o);
    }

    return rootObj;
}

void printObj(tfObj *program){
    switch(program->type){
        case TFOBJ_TYPE_LIST:
            printf("[");
            for(size_t i = 0; i < program->list.len; i++){
                printObj(program->list.elements[i]);
                if(i != program->list.len - 1){
                    printf(" ");
                }
            }
            printf("]");

        break;
        case TFOBJ_TYPE_INT:
            printf("%d", program->i);
        break;
        case TFOBJ_TYPE_SYMBOL:
            printf("%s", program->str.ptr);
        break;
        default:
            printf("?");
    }
}

tfContext *createContext(void){
    tfContext *ctx = malloc(sizeof(*ctx));
    ctx->stack = createListObject();
    return ctx;
}

void exec(tfContext *ctx, tfObj *program){
    assert(program->type == TFOBJ_TYPE_LIST);

    for(size_t i = 0; i < program->list.len; i++){
        switch(program->list.elements[i]->type){
            case TFOBJ_TYPE_SYMBOL:
            break;
            default:
                pushListObject(ctx->stack, program->list.elements[i]);
        }
    }
}

int main(int argc, char **argv){
    if(argc != 2){
        fprintf(stderr, "Usage: %s <filename>\n", *argv);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if(fp == NULL){
        perror("Opening Toy Forth program");
        return 1;
    }

    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *programText = xmalloc(fileSize + 1);
    
    fread(programText, fileSize, 1, fp);
    programText[fileSize] = 0;

    fclose(fp);

    tfObj *program = compile(programText);
    if(program == NULL) return 1;
    
    printObj(program);
    printf("\n");

    tfContext *ctx = createContext();
    exec(ctx, program);
    
    printf("My stack: ");
    printObj(ctx->stack);
    printf("\n");

    return 0;
}
