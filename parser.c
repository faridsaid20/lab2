/* parser.c -- without the optimizations */

#include "global.h"

int lookahead;

void match(int);
void start(), list(), expr(), moreterms(), term(), morefactors(), factor();

void parse()  /*  parses and translates expression list  */
{
    lookahead = lexan();
    start();
}

void start ()
{
    /* Just one production for start, so we don't need to check lookahead */
    list(); match(DONE);
}

void list()
{
    if (lookahead == '(' || lookahead == ID || lookahead == NUM) {
        expr(); match(';'); list();
    }
    else {
        /* Empty */
    }
}

void expr ()
{
    /* Just one production for expr, so we don't need to check lookahead */
    term(); moreterms();
}

void moreterms()
{
    if (lookahead == '+') {
        match('+'); term(); emit('+', token_value); moreterms();
    }
    else if (lookahead == '-') {
        match('-'); term(); emit('-', token_value); moreterms();
    }
    else {
        /* Empty */
    }
}

void term ()
{
    /* Just one production for term, so we don't need to check lookahead */
    factor(); morefactors();
}

void morefactors ()
{
    if (lookahead == '*') {
        match('*'); factor(); emit('*', token_value); morefactors();
    }
    else if (lookahead == '/') {
        match('/'); factor(); emit('/', token_value); morefactors();
    }
    else if (lookahead == DIV) {
        match(DIV); factor(); emit(DIV, token_value); morefactors();
    }
    else if (lookahead == MOD) {
        match(MOD); factor(); emit(MOD, token_value); morefactors();
    }
    else {
        /* Empty */
    }
}

void factor ()
{
    if (lookahead == '(') {
        match('('); expr(); match(')');
    }
    else if (lookahead == ID) {
        int id_number = token_value;
        match(ID);
        emit(ID, id_number);
    }
    else if (lookahead == NUM) {
        int num_value = token_value;
        match(NUM);
        emit(NUM, num_value);
    }
    else
        error("syntax error in factor");
}

void match(int t)
{
    if (lookahead == t)
        lookahead = lexan();
    else
        error ("syntax error in match");
}
