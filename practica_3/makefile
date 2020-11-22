main.out: main.c datain.o abb.o utils.o measuretime.o
	gcc -g main.c datain.o abb.o utils.o measuretime.o -o main.out -lm -Wall

datain.o: datain.c datain.h
	gcc -g -c datain.c -o datain.o -Wall

measuretime.o: measuretime.c measuretime.h
	gcc -g -c measuretime.c -o measuretime.o -lm -Wall

abb.o: abb.c abb.h
	gcc -g -c abb.c -o abb.o -Wall

utils.o: utils.c utils.h
	gcc -g -c utils.c -o utils.o -Wall

clean:
	rm *.o main.out
