%{
    #include <stdio.h> 
    #include <stdlib.h>
    #include <string.h>
    #include "PolacaStack.h"


    #define ASCIINUMMIN 48
    #define MAX 300

    /* datos generales para operaciones: cantidad de variables, expresion y largo de expresion */

    char atoms[7];

    int expression[MAX];

    int variables[32]; 

    unsigned int numvariable;

    unsigned int i;

    unsigned int largev, auxatoms, auxatoms2, auxatoms3;




  


/* Funcion que consulta si esta en arreglo la variable que lee nuestro lexer, nos permitira contar la cantidad que hay sin repetir */

    int stayinarray (int arrayatms[32], int valor){
    
        int pivote, j;
    
        for(j=0; j < 32; j++){

            if (arrayatms[j] == valor){

                return 1;
            }
            else
                pivote = 0;

        }

        return pivote;  
    }
    


  /* Funcion que cambia a digito la variable v_{numero} */  

    int variablesatoms (char atoms[7]){
    

        auxatoms2 = (int)atoms[3] - ASCIINUMMIN;
        auxatoms3 = (int)atoms[4] - ASCIINUMMIN;
    
        if ( auxatoms3 <= 9 ){

            auxatoms3 = 10 * auxatoms3 + auxatoms2;

            return auxatoms3;

            }
        else

            return auxatoms2;

        }    

%}


subnumber   [0-9]+


%%


"v\_\{"{subnumber}"\}"    { strcpy(atoms,yytext);

                            //printf("guarda el siguiente caracter en atoms: %s\n", atoms);
                            
                            /* sacamos el numero de la variable v, para obtener la cantidad de variables que hay */

                            /* si v solo tiene un digito, entra aca */
                            if (stayinarray(variables,variablesatoms(atoms)) == 0 ){

                                variables[numvariable] = variablesatoms(atoms);
                                numvariable = numvariable + 1;
                                expression[i] = variablesatoms(atoms);
                                i = i + 1;

                                }
                                
                            else{

                                /* si v_{numero}* esta en variables, no se vuelv a contar */   

                                expression[i] = variablesatoms(atoms); 
                                i = i + 1;

                                }   
                            }

                            

            

"\\neg"    {expression[i] = 33;
            //printf("esto se guarda en expresion:  %i\n", expression[i]); 
            i = i + 1;
            }

"\\wedge"  {expression[i] = 34; 
            //printf("esto se guarda en expresion:  %i\n", expression[i]);
            i = i + 1;
            }

"\\vee"    {expression[i] = 35;
            //printf("esto se guarda en expresion:  %i\n", expression[i]) ; 
            i = i + 1;
            }

"\\rightarrow"     {expression[i] = 36; 
                    //printf("esto se guarda en expresion:  %i\n", expression[i]);
                    i = i + 1;
                    }

"\("   {expression[i] = 37;
        //printf("esto se guarda en expresion:  %i\n", expression[i]); 
        i = i + 1;}

"\)"   {expression[i] = 38;
        //printf("esto se guarda en expresion:  %i\n", expression[i]); 
        i = i + 1;}

.   ;

%%

int yywrap(){}




void defaultProgram(int modo){


    struct Stack *stk = NULL;
    int cantvariables = numvariable;

    yylex();

    //printf("Ejecuto default y leyo utilizo lex\n");
    
    polacainversa(stk, expression, variables, i, numvariable, modo);

    //printf("pase por polacainversa\n");
}



int main(int argc, char *argv[]){

    i = 0;
    numvariable = 0;
    int modo;

    //printf("entre a programa\n");

    if( strcmp(argv[1], "-V") == 0){

        //printf("entre -V\n");
        modo = 1;
        defaultProgram(modo);

        //printf("pase defaultProgram \n");
    
    }else if( strcmp(argv[1],"-S") == 0){

        //printf("entre -S\n");
        modo = 2;
        defaultProgram(modo);

        //printf("pase defaultProgram\n");

    }else{

        printf("-V (verboso) o -S (silencioso) \n");
    }


    return 0;
}