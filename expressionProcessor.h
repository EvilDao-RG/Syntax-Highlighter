#ifndef EXPRESSIONPROCESSOR
#define EXPRESSIONPROCESSOR
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>


using namespace std;


class expressionProcessor {
    public:
        expressionProcessor();
        void executeLex();
        void createLex(string file);
        int getSize();
        string getToken(int i);
        string getColor(int i);
    private:
        vector<string> tokens;
        vector<string> colors;
        int size;
};


expressionProcessor::expressionProcessor(){
    tokens = {};
    colors = {};
    size = 0;
}


int expressionProcessor::getSize(){
    return size;
}

//Regresa el token de la posición solicitada
string expressionProcessor::getToken(int i){
    return tokens[i];
}

//Regresa el color de la posición solicitada
string expressionProcessor::getColor(int i){
    return colors[i];
}

//Ejecuta el programa que usa el lex para identificar los tokens
void expressionProcessor::executeLex(){
    system("flex regex.l");
    system("g++ lexCompiler.cpp lex.yy.c -o lexCompiler");
    system("lexCompiler.exe");
}

//Escribe el archivo de lex y guarda los tokens y colores
void expressionProcessor::createLex(string file){
    ofstream lex;
    ifstream expressions;
    string expression, token, color;
    
    try{
        lex.open("regex.l", ios::out);
        if(lex.fail()){
            throw "Path error. The address or filename is incorrect\n";
        }
    } catch(char const* message){
        std::cerr<<message<<std::endl;
        exit(0);
    }

    try{
        expressions.open(file, ios::in);
        if(expressions.fail()){
            throw "Path error. The address or filename is incorrect\n";
        }
    } catch(char const* message){
        std::cerr<<message<<std::endl;
        exit(0);
    }

    lex << "%{\n%}\n%%\n";
    while(!expressions.eof()){
        getline(expressions, expression, ' ');
        getline(expressions, token, ' ');
        getline(expressions, color);

        tokens.push_back(token);
        colors.push_back(color);
        size++;
        lex << expression << " {fprintf(yyout, \" &&" << token << "&& \"); fprintf(yyout, yytext); fprintf(yyout, \" &&end&&\");}\n";
    }
    lex << ". {fprintf(yyout, yytext);}\n";
    lex << "%%\nint yywrap(void){\n\treturn 1;\n}";

    lex.close();
    expressions.close();
}


#endif // __EXPRESSIONPROCESSOR_H_