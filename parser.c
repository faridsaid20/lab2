/* parser.c -- without the optimizations */

#include "global.h"
int lookahead;

void match(int);
void start(), list(), assignment(), expr(), moreterms(), term(), morefactors(),
   factor();

void parse() /*  parses and translates expression list  */
{
   lookahead = lexan();
   start();
}

void start()
{
   /* Just one production for start, so we don't need to check lookahead */
   list();
   match(DONE);
}

void list()
{
   if (lookahead == ID)
   {
      assignment();
      match(';');
      list();
   }
   else
   {
      /* Empty */
   }
}

void assignment()
{
   int expression_value_token = token_value;
   match(ID);
   emit(ID, expression_value_token);
   match('=');
   expr();
   emit('=', expression_value_token);
   emit(RESULT, expression_value_token);
}

void expr()
{
   /* Just one production for expr, so we don't need to check lookahead */
   term();
   moreterms();
}

void moreterms()
{
   if (lookahead == '+')
   {
      match('+');
      term();
      emit('+', token_value);
      moreterms();
   }
   else if (lookahead == '-')
   {
      match('-');
      term();
      emit('-', token_value);
      moreterms();
   }
   else
   {
      /* Empty */
   }
}

void term()
{
   /* Just one production for term, so we don't need to check lookahead */
   factor();
   morefactors();
}

void factor()
{
   if (lookahead == '(')
   {
      match('(');
      expr();
      match(')');
   }
   else if (lookahead == ID)
   {
      int id_number = token_value;
      match(ID);
      emit(ID, id_number);
   }
   else if (lookahead == NUM)
   {
      int num_value = token_value;
      match(NUM);
      emit(NUM, num_value);
   }
   else
   {
      error("syntax error in factor");
   }
}

void morefactors()
{
   if (lookahead == '*')
   {
      match('*');
      factor();
      emit('*', token_value);
      morefactors();
   }
   else if (lookahead == '/')
   {
      match('/');
      factor();
      emit('/', token_value);
      morefactors();
   }
   else if (lookahead == DIV)
   {
      match(DIV);
      factor();
      emit(DIV, token_value);
      morefactors();
   }
   else if (lookahead == MOD)
   {
      match(MOD);
      factor();
      emit(MOD, token_value);
      morefactors();
   }
   else
   {
      /* Empty */
   }
}

void match(int t)
{
   if (lookahead == t)
   {
      lookahead = lexan();
   }
   else
   {
      error("syntax error in match");
   }
}
