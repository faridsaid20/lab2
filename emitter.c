/* emitter.c */

#include "global.h"

void emit (int token_type, int token_value)  /*  generates output  */
{
    switch(token_type) {
    case '+' : case '-' : case '*' : case '/':
        printf("%c\n", token_type); break;
    case DIV:
        printf("DIV\n"); break; 
    case MOD:
        printf("MOD\n"); break;
    case NUM:
        printf("%d\n", token_value); break;
    case ID:
        printf("%s\n", symtable[token_value].lexeme); break; 
    default:     
        printf("[Unknown token %d, with value %d]\n", token_type, token_value);
    }
}
