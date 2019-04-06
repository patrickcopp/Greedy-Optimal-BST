all: Q1 Q2

Q1: Q1.c
	gcc -Wall -pedantic -std=c99 Q1.c -o Q1

Q2: Q2.c
	gcc -Wall -pedantic -std=c99 Q2.c -o Q2
