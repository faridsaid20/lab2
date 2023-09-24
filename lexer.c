/* lexer.c */

#include "global.h"

char lexeme[MAX_ID_LENGTH + 1];
int  lineno = 1;
int  token_value = NONE;

int lexan()  /*  lexical analyzer  */
{
    int c;
    while(1) {
        c = getchar();
        if (c == ' ' || c == '\t')
            ;  /*  strip out white space  */
        else if (c == '\n')
            lineno = lineno + 1;
        else if (isdigit(c)) {  /*  c is a digit  */
            ungetc(c, stdin);
            scanf("%d", &token_value);
            return NUM;
        }
        else if (isalpha(c)) {  /*  c is a letter */
            int id_number, chars = 0;
            while (isalnum(c)) {  /* c is alphanumeric  */
                lexeme[chars++] = c; 
                if (chars > MAX_ID_LENGTH)
                    error("identifier too long");
                c = getchar();
            }
            lexeme[chars] = EOS;
            if (c != EOF)
                ungetc(c, stdin);
            id_number = lookup(lexeme);
            if (id_number == -1)
                id_number = insert(lexeme, ID);
            token_value = id_number;
            return symtable[id_number].token_type;
        }
        else if (c == EOF)
            return DONE;
        else {
            token_value = NONE;
            return c;
        }
    }
}
