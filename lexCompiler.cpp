#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

extern int yylex();
extern int yylineno;
extern char* yytext;

int main(){
    extern FILE *yyin, *yyout;
    yyin = fopen("text.txt", "r");
    yyout = fopen("output.txt", "w");

    yylex();
    return 0;
}