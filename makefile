all : prog

prog : src/main.o src/fct.o src/IA.o 
	gcc -o prog src/main.o src/fct.o src/IA.o -lTableauNoir


src/main.o : main.c 
	gcc -o src/main.o -c main.c 

src/fct.o : src/fct.c 
	gcc -o src/fct.o -c src/fct.c 

src/IA.o : src/IA.c 
	gcc -o src/IA.o -c src/IA.c 




