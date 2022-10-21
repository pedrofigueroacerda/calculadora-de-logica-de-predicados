
#include<stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define MAX 300
#define MAXVAR 32


    /*

        Logica Computacional, Mayo 2022. USACH, Licenciatura en Ciencia de la Computacion.

        Integrantes: Pedro Figueroa Cerda 
        
        Institucion: Universidad de Santiago de Chile

        arcivo que contiene lex de problema


    */


/* Estrucutra de Pila, contiene: cabeza, una lista, y apunta al siguiente, (FALTA LISTA)*/

struct Stack{
	
	struct Stack *next;
	int TOP;
	char *set;
	
};


struct Stack *stk;

/* funcion que da valores de 0's y 1's a una lista, son digitos hexadecimales donde tienen cierta representacion en binario*/

void prioridad(char * cc, int prioridad){

	char *aux;

	aux = malloc(sizeof(char));

	char set1rep = 0xF0;    /*1111 0000*/
	char set2rep = 0xCC;    /*1100 1100*/
	char set3rep = 0xAA;   	/*1010 1010*/

	char zerorep = 0x00; 	/*0000 0000*/
	char onerep = 0xFF;  	/*1111 1111*/

	switch(prioridad){

		case 1: aux[0] = zerorep;
				 break;

		case 2: aux[0] = onerep;
				 break;

		case 3: aux[0] = set1rep;
		     break;

		case 4: aux[0] = set2rep;
			 	 break;

		case 5: aux[0] = set3rep;
			 	 break;			 	 

		}

	cc[0] = aux[0];			

}



/* funcion que calcula el largo del arreglo para el arreglo set en la píla que contiene el valor de verdad */


int largoarreglo(int numvariable){

	int j;
	int largo = 1;

	for(j=0; j < numvariable; j++){

		largo = 2*largo;
	}

	largo = (int)largo/8;

	return largo;
}



/* funcion que calcula el cuadrado de un numero */

int cuadrado(int numvariable){

	int j;
	int largo = 1;

	for(j=0; j < numvariable; j++){

		largo = 2*largo;
	}

	return largo;
}



/*Inicializacion de nodo pila. Se crea pila, se ingresa dato, (FALTA LISTA) */

struct Stack *createNode(struct Stack *node, int larreglo){

	node = malloc(sizeof(struct Stack*));
	node->TOP = 0;
	node->set = malloc(larreglo * sizeof(char));
	node->next = NULL;
	return node;
}


//Ingreso en la PILA, se ingrsa a la pila, se incerta dato, (FALTA LISTA)

void Push (struct Stack **stack, char lista01[MAX], int Data, int larreglo){

	struct Stack *node = createNode(node, larreglo);
	int j;
	node->TOP = Data;

	for(j=0; j<larreglo; j++){
		node->set[j] = lista01[j];
	}
	
	node->next = *stack;
	*stack = node;

}



/*Elimina la cabeza de la pila*/



struct Stack *Pop (struct Stack *stack){

	return stack->next;

}



/*Muestra la cabeza de la pila*/

void getTopSET(struct Stack *stack, char *lista02, int tam){

	int j;

	for (j=0; j < tam; j++){

		lista02[j] = stack->set[j];

	}

}



/* Funcion que calcula el valor de verdad */

void showStackTrue(struct Stack *stack, int larreglo){

	int k; 
	int verdad = 0;
	int falso = 0;
	int contingencia = 0;

	char *verd;
	char *fals;

	verd = malloc(sizeof(char));
	fals = malloc(sizeof(char));

	prioridad(verd,2);
	prioridad(fals,1);


	for(k=0; k < larreglo; k++){


		if(stack->set[k] == verd[0] ){

			verdad = verdad + 1;
		}

		else{

			if (stack->set[k] == fals[0] ){

				falso = falso + 1;
			}
			else{

				contingencia = contingencia + 1;
			}


		}

	}

	if(verdad != 0 && falso == 0){
		printf(": verdadero \n");
	}

	else{

		if( falso != 0 && verdad == 0){
			printf(": Falso  \n");
		}

		else{
			if (contingencia != 0){
				printf(": contingencia \n");
			}
		}
	}

}


void prinTOP(int TOP){

	switch(TOP){

		case 33: printf("¬\n");
				 break;

		case 34: printf("^\n");
				 break;

		case 35: printf("v\n");
				 break;

		case 36: printf("->\n");
				 break;

		default: printf("v_%i\n",TOP);
				 break;		 	 	 
	}
}

/******************    operaciones a nivel de bits      ******************/



/* funcion que traduce el hexadecimal a binario y lo muestra */

void showBitSet(struct Stack * stk, int tam){

	//printf("entre a show bit set\n");

	int l, r;
	printf(" ");
	prinTOP(stk->TOP);
	printf("\n");

	
	for(l = 0; l < tam; l++){
		
		for(r = 7; r >= 0; r--){
			putchar((stk->set[l] & (1u << r) ? '1' : '0'));
			printf("\n");
			//printf("valor de verdad\n");
		}
		
	}

}



/* funcion que incializa con 0's */

void setZeroBit(char *set, int tam){

	int j;
	char *aux;
	aux = malloc(sizeof(char)); 

	for(j = 0; j < tam; j++){

		prioridad(aux,1);
		set[j] = aux[0];
		free(aux);

	}

}



/* funcion not, calcula el valor de not de solo una primisa*/

struct Stack *operationNOT(struct Stack *stk, struct Stack *stkaux1, int larreglo){



	if(stk != NULL){
		
		int j;

		for(j = 0; j < larreglo; j++){

			stkaux1->set[j] = ~stk->set[j]; 

		}
	}

	return stkaux1;

}


/* calcula el valor de AND de dos primisas o dos operando, o un operando y primisa, o primisa y operando de derecha a izquierda (la cabeza y el anterior)  */

struct Stack *operationAND(struct Stack *stk1, struct Stack *stk2, struct Stack *stkaux1, int larreglo){



	if(stk1 != NULL && stk2!= NULL){
		
		int j;

		for(j = 0; j < larreglo; j++){

			stkaux1->set[j] = stk1->set[j] & stk2->set[j]; 

		}
	}

	return stkaux1;

}


/* calcula el valor de OR de dos primisas o dos operando, o un operando y primisa, o primisa y operando de derecha a izquierda (la cabeza y el anterior) */

struct Stack *operationOR(struct Stack *stk1, struct Stack *stk2, struct Stack *stkaux1, int larreglo){
	


	if(stk1 != NULL && stk2 != NULL){
		
		int j;

		for(j = 0; j < larreglo; j++){

			stkaux1->set[j] = stk1->set[j] | stk2->set[j]; 

		}
	}

	return stkaux1;

}


/* calcula el valor de IMPLICA de dos primisas o dos operando, o un operando y primisa, o primisa y operando de derecha a izquierda (la cabeza y el anterior) */

struct Stack *operationIMPL(struct Stack *stk1, struct Stack *stk2, struct Stack *stkaux1, int larreglo){

	return operationOR(operationNOT(stk1, stk1, larreglo), stk2, stkaux1, larreglo);

}



	/* funcion que hace primisas de solo las variables, recibe el char con las variables, recibe su largo, recibe el largo de arreglo 

		que corresponde a cada una. ciclo con grupos de 8 digitos binarios entre 1's y 0's representado en digitos exadecimales 
  */

void SETprimisa(char *lista01, int variables[MAXVAR], int cantvariables, int larreglo, int atomo){

	int j, k, l, limite, limite1;
	int largoMask; 

	limite = 0;
	largoMask = larreglo;
	char *primisaux;
	primisaux = malloc(sizeof(char));
	
	k = 0;

	if(cantvariables >= 4 && atomo < cantvariables - 2){ /* entra cuando las listas son mayores o igual a 64, para nuestro programa 64/8 */

		largoMask = larreglo / cuadrado(atomo);

		for (j = 0; j < larreglo; j++){ /* 111111111, 111111111, 0000000000, 0000000000 o 11111111, 0000000000, 11111111, 00000000*/

			if(k == 2*largoMask){ /* el valor de largoMask limita la cantidad de 0's o 1's que necesita, dependiendo tambien del atomo que entra */

				k=0;

				}

			if (k < largoMask){
				prioridad(primisaux, 2);
				lista01[j] = primisaux[0];
				
				}
	

			if (k >= largoMask){
				prioridad(primisaux, 1);
				lista01[j] = primisaux[0];
				if(k == 2*largoMask){
					k=0;
					}
				}
			k = k + 1; 	

			}
	
		}


	else{ /* esto es el caso base, para listas de largo 2^3 en adelante (para efectos de nuestro programa 2^3/8 */

		for (j = 0; j < larreglo; j++){

			if (atomo == cantvariables - 2){
				prioridad(primisaux, 3);
				lista01[j] = primisaux[0];
			}

			if (atomo == cantvariables - 1){
				prioridad(primisaux, 4);
				lista01[j] = primisaux[0];
			}

			if(atomo == cantvariables){
				prioridad(primisaux,5);
				lista01[j] = primisaux[0];
			}
		}
	}

} 





/* funcion que llena una pila de forma polaca inversa y calcula el valor de verdad a medida que se va llenando la pila */

void polacainversa(struct Stack *stk, int expression[MAX], int variables[MAXVAR], int i, int cantvariables, int verboso){

	/* recibimos: una pila vacia, un arreglo con la expresion, arreglo con variables, largo de expresion y largo de variable */ 
	struct Stack *stkaux1 = NULL;
	struct Stack *stkaux2 = NULL;
	struct Stack *stkaux3 = NULL;
	struct Stack *stkaux4 = NULL;
	int parentIZQ;
	int parentDER=0;
	int larreglo;
	int j, k;

	//printf("entre al archivo .h miauuu\n");
	
	larreglo = largoarreglo(cantvariables);

	//printf(" este es el largo del arreglo: %i\n", larreglo);

	char * lista01;
	lista01 = malloc(larreglo * sizeof(char));

	char * lista02;
	lista02 = malloc(larreglo * sizeof(char));

	for(j=0; j < i; j++){


		switch(expression[j]){

			/* caso: NOT */

			case 33: 
					 setZeroBit(lista02, larreglo);
					 Push(&stkaux1, lista02, expression[j], larreglo);		
					 //free(lista02);
					 break;		 

			case 34: 
					 setZeroBit(lista02, larreglo);
					 Push(&stkaux1, lista02, expression[j], larreglo);		
					 //free(lista02);
					 break;

			case 35: 
					 setZeroBit(lista02, larreglo);
					 Push(&stkaux1, lista02, expression[j], larreglo);		
					 //free(lista02);
					 break;

			case 36: 
					 setZeroBit(lista02, larreglo);
					 Push(&stkaux1, lista02, expression[j], larreglo);		
					 //free(lista02);
					 break;

			case 37: parentIZQ = parentIZQ + 1;
				 	 break;

			case 38: 
					 /* en el caso de que lea un parentesis concavo hacia la derecha, entra en este caso para obtener operadores y calcular verdad */

					  parentIZQ = parentIZQ - 1;

					 if (stkaux1!=NULL && parentIZQ != 0){


					 	switch(stkaux1->TOP){

					 		case 33: 
					 				 stkaux4 = operationNOT(stk, stkaux1, larreglo);
					 				 getTopSET(stkaux4, lista01, larreglo);
					 				 Push(&stk, lista01, stkaux4->TOP, larreglo);

					 				 if (verboso == 1){
					 				 	showBitSet(stk, larreglo);
					 				 }
					 				 
					 				 stkaux4 = Pop(stkaux4);
					 				 stkaux1 = Pop(stkaux1);
					 				 break;

					 	 	case 34:
		
					 		 		 stkaux3 = stk;	
					 				 stkaux2 = Pop(stk);
					 				 stkaux4 = operationAND(stkaux2, stkaux3, stkaux1, larreglo);
					 		 		 getTopSET(stkaux4, lista01, larreglo);
					 				 Push(&stk, lista01, stkaux4->TOP, larreglo);

					 				 if (verboso == 1){
					 				 	showBitSet(stk, larreglo);
					 				 }

					 				 stkaux2 = Pop(stkaux2);
					 				 stkaux3 = Pop(stkaux3);
					 				 stkaux4 = Pop(stkaux4);
					 				 //free(lista01);
					 				 break; 

					 		case 35: 
					 	
					 				 stkaux3 = stk;	
					 				 stkaux2 = Pop(stk);
					 				 stkaux4 = operationOR(stkaux2, stkaux3, stkaux1, larreglo);
					 				 getTopSET(stkaux4, lista01, larreglo);
					 				 Push(&stk, lista01, stkaux4->TOP, larreglo);
					 				 
					 				 if (verboso == 1){
					 				 	showBitSet(stk, larreglo);
					 				 }

					 				 stkaux2 = Pop(stkaux2);
					 				 stkaux3 = Pop(stkaux3);
					 				 stkaux4 = Pop(stkaux4);
					 				 //free(lista01);
					 				 break;


					 	  	case 36:

				
					 				 stkaux3 = stk;	
					 				 stkaux2 = Pop(stk);
					 				 stkaux4 = operationIMPL(stkaux2, stkaux3, stkaux1, larreglo);
					 				 getTopSET(stkaux4, lista01, larreglo);
					 				 Push(&stk, lista01, stkaux4->TOP, larreglo);

					 				 if (verboso == 1){
					 				 	showBitSet(stk, larreglo);
					 				 }

					 				 stkaux2 = Pop(stkaux2);
					 				 stkaux3 = Pop(stkaux3);
					 				 stkaux4 = Pop(stkaux4);
					 		 		//free(lista01);
					 				 break;



					 	}

				 	 	break;	
					 
					 }

					 stkaux1 = Pop(stkaux1);

			/* caso: Primisa */	 	 

			default: SETprimisa(lista01, variables, cantvariables, larreglo, expression[j]);
					 Push(&stk, lista01, expression[j], larreglo);
	                 if (verboso == 1){
					 	showBitSet(stk, larreglo);
					 }

					 break; 			 	 

		}




		
	}


	showStackTrue(stk, larreglo);


}


