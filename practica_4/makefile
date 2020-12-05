main.out: main.c datain.o algoritmos.o utils.o measuretime.o
	gcc -g main.c datain.o algoritmos.o utils.o measuretime.o -o main.out -lm -Wall
	
datain.o: datain.c datain.h
	gcc -g -c datain.c -o datain.o -Wall

measuretime.o: measuretime.c measuretime.h
	gcc -g -c measuretime.c -o measuretime.o -lm -Wall

algoritmos.o: algoritmos.c algoritmos.h
	gcc -g -c algoritmos.c -o algoritmos.o -Wall

utils.o: utils.c utils.h
	gcc -g -c utils.c -o utils.o -Wall

clean:
	rm *.o main.out
