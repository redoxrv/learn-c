/*
 * Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

 An input string is valid if:

 1. Open brackets must be closed by the same type of brackets.
 2. Open brackets must be closed in the correct order.
 3. Every close bracket has a corresponding open bracket of the same type.
*/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isValid(char* s) {
    char stack[strlen(s)+1];
    int i_stack = 0;

    for(int i = 0; s[i] != 0; i++){
        if(s[i] == '(' || s[i] == '[' || s[i] == '{'){
            stack[i_stack] = s[i];
            i_stack++;
        }
        else if(s[i] == ')' || s[i] == ']' || s[i] == '}'){
            if(i_stack == 0) return 0;

            if ((s[i] == ')' && stack[i_stack-1] == '(') ||
                (s[i] == ']' && stack[i_stack-1] == '[') ||
                (s[i] == '}' && stack[i_stack-1] == '{')) { 
            
                i_stack--;
            }
            else{
                return 0;
            }
        }
    }

    return i_stack == 0;
}

int main(){
    char *testString[] = {
        "()", //true
        "()[]{}", //true
        "(]", //false
        "([])", //true
        "([)]", //false
        0
    };
    
    for(int i = 0; testString[i] != 0; i++){
        printf("%d\n", isValid(testString[i]));
    }

    return 0;
}
