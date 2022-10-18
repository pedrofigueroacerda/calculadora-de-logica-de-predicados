Compilado con:

gcc (Ubuntu 9.2.1-9ubuntu2) 9.2.1 20191008
flex 2.6.4

Considerar que es necesario:

Tener compilador gcc instalado.
Tener compilador flex instalado.

Compilar en linux con:

$ flex logicproblem.lex
$ gcc -o tarea1.exe lex.yy.c -ll


Para ejecutar:

Donde entrega la tabla de verdad: 

./tarea1.exe -V < expresion.txt

Donde soloe ntrega el valor de verdad: 

./tarea1.exe -S < expresion.txt

Considerar que es necesario:

Tener compilador gcc instalado.
Tener compilador flex instalado.

Que es esto:

Es una computadora de expresiones logicas.

Una expresion logica consta de operadores y variables

Un operador puede ser unario (negacio) o binario (and, or, etc)

Una variable se denota por v_{xy}, donde x y y son digito d eun número que llega hasta 32

y toda oepración debe estar en paréntesis, (unaria o binaria) esto quiere decir:

$$ ((( v_{1} \rightarrow v_{2}) \ wedge) ( v_{2} \rightarrow v_{3} ) \rightarrow (v_{1} \rightarrow v_{3})) $$

puesto que así operará nuestra polaca.





