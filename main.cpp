/*
Autor: Gael Rodrígue Gómez
Matricula: A01639279

Este programa realiza resaltamiento sintáctico, en el que el usuario
carga un archivo .txt con las expresiones regulares según la notación
establecida en el documento de diseño, ademas se carga el texto a resaltar 
en el archivo text.txt. Finalmente, se arroja un documento html con los 
tokens resaltados según las expresiones establecidas

Requerimientos
    gcc version 6.3.0 en adelante
    flex versión 2.5.4

Instrucciones de compilación y ejecución:
    g++ main.cpp -o main
    ./main.exe

28 / Marzo / 2022
*/


#include "tokenHighlighter.h"
#include <ctime>




int main(){
    unsigned t0, t1;
    t0 = clock();
    
    expressionProcessor lex;
    //Creación del archivo de lex a partir de las expresiones
    lex.createLex("expressions.txt");
    //Ejecución del programa de lex
    lex.executeLex();    
    
    tokenHighlighter highlighter(lex);
    //Resaltamiento de los tokens identificados
    highlighter.highlight();
    
    t1 = clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "Tiempo de ejecucion: " << time << endl;
}