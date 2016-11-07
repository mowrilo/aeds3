CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic -g

mapa: mapa.o main.o heap.o
	gcc mapa.o main.o heap.o -o mapa
main.o: main.c heap.h mapa.h
	gcc -g -c main.c
mapa.o: mapa.h mapa.c
	gcc -g -c mapa.c
heap.o: heap.h heap.c
	gcc -g -c heap.c
clean:
	rm *.o *.gch
	rm mapa