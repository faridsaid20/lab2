/* global.h */

#include <stdio.h>  /* include declarations for i/o routines */
#include <ctype.h>  /* ... and for character test routines */
#include <stdlib.h> /* ... and for some standard routines, such as exit */
#include <string.h> /* ... and for string routines */
#include <stdbool.h>

#define MAX_ID_LENGTH  128  /* for the buffer size */

#define NONE   -1
#define EOS    '\0'

#define NUM    256
#define DIV    257
#define MOD    258
#define ID     259
#define DONE   260
#define RESULT 261

extern int token_value;   /*  value of token attribute */  
extern int lineno;

struct symentry {  /*  form of symbol table entry  */
    char *lexeme;
    int  token_type;
    char *value;
};

extern struct symentry symtable[];  /* symbol table  */

extern void init();  /*  loads keywords into symtable  */
extern void error(char* message);  /*  generates all error messages  */
extern int lexan();  /*  lexical analyzer  */
extern void parse();  /*  parses and translates expression list  */
extern int insert(char *s, int token_type);    /*  returns position of entry for s */
extern int lookup(char *s);         /* returns position of entry for s, or -1 if not found */
extern void emit (int token_type, int token_value);  /*  generates output  */

extern int charToInt(char* str, bool* isOk);

extern bool isOperator(const char* str);

extern void printPostfix();

extern int calculateResult();
extern void printResult(int result);
extern void saveResultInSymtable(int result);
extern int performOperation(int a, int b, const char* op);
