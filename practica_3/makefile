main.out: main.c datain.o abb.o utils.o measuretime.o
	gcc main.c datain.o abb.o utils.o measuretime.o -o main.out -lm -Wall

datain.o: datain.c datain.h
	gcc -c datain.c -o datain.o -Wall

measuretime.o: measuretime.c measuretime.h
	gcc -c measuretime.c -o measuretime.o -lm -Wall

abb.o: abb.c abb.h
	gcc -c abb.c -o abb.o -Wall

utils.o: utils.c utils.h
	gcc -c utils.c -o utils.o -Wall

clean:
	rm *.o main.out
