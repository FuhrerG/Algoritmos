main.out: main.c utilidades.o algoritmos.o
	gcc -g main.c utilidades.o algoritmos.o -o main.out -lm -Wall

utilidades.o: utilidades.c utilidades.h
	gcc -g -c utilidades.c -o utilidades.o -lm -Wall

algoritmos.o: algoritmos.c algoritmos.h
	gcc -g -c algoritmos.c -o algoritmos.o -Wall

clean:
	rm *.o main.out
