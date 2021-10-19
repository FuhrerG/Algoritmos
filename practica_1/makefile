main.out: main.c utilidades.o algoritmos.o test.o
	gcc -g main.c utilidades.o algoritmos.o test.o -o main.out -lm -Wall

utilidades.o: utilidades.c utilidades.h
	gcc -g -c utilidades.c -o utilidades.o -lm -Wall

test.o: test.c test.h
	gcc -g -c test.c -o test.o

algoritmos.o: algoritmos.c algoritmos.h
	gcc -g -c algoritmos.c -o algoritmos.o -Wall

clean:
	rm *.o main.out
