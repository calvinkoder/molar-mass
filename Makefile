chem : main.o chem.o dict.o csv.o
	gcc main.o chem.o dict.o csv.o -o chem

main.o : main.c
	gcc -c main.c

chem.o : chem.c
	gcc -lm -c chem.c

dict.o : dict.c
	gcc -c dict.c

csv.o : csv.c
	gcc -c csv.c
