/* parser.c */

#include "global.h"

int lookahead;

void match(int);
void factor(), term(), expr();

void parse()  /*  parses and translates expression list  */
{
  lookahead = lexan();
  while (lookahead != DONE) {
    expr (); match (';');
  }
}

void expr()
{
  int t;
  term();
  while(1)
    switch (lookahead) {
    case '+' : case '-' :
      t = lookahead;
      match(lookahead); term(); emit (t, NONE);
      continue;
    default:
      return;
    }
}

void term ()
{
  int t;
  factor ();
  while(1)
    switch (lookahead) {
    case '*' : case '/' : case DIV: case MOD:
      t= lookahead;
      match(lookahead); factor(); emit (t, NONE);
      continue;
    default:
      return;
    }
}

void factor ()
{
  switch(lookahead) {
  case '(' :
    match('('); expr(); match(')'); break;
  case NUM:
    emit(NUM, token_value); match(NUM); break;
  case ID:
    emit(ID, token_value); match(ID); break;
  default:
    error("syntax error in factor");
  }
}

void match(int t)
{
  if (lookahead == t)
    lookahead = lexan();
  else error ("syntax error in match");
}
