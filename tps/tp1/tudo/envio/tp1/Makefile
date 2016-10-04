CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic -g

biblioteca: biblioteca.o main.o qsortExt.o
	gcc biblioteca.o main.o qsortExt.o -o biblioteca
main.o: main.c qsortExt.h biblioteca.h
	gcc -g -c main.c
biblioteca.o: biblioteca.h biblioteca.c
	gcc -g -c biblioteca.c
qsortExt.o: qsortExt.h qsortExt.c
	gcc -g -c qsortExt.c
clean:
	rm *.o *.gch
	rm biblioteca