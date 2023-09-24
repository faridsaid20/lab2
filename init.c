/* init.c */

#include "global.h"

struct symentry keywords[] = {
    { "div", DIV },
    { "mod", MOD, }
};

void init()  /*  loads keywords into symtable  */
{
    int nr_keywords = sizeof(keywords) / sizeof(keywords[0]);
    for (int i = 0; i < nr_keywords; ++i)
        insert(keywords[i].lexeme, keywords[i].token_type);
}
