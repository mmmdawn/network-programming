CFLAGS = -c -Wall
CC = gcc
LIBS = -lm

all: main.o validator.o resolver.o
	${CC} main.o validator.o resolver.o -o resolver; rm -f *.o *~

main.o: main.c
	${CC} ${CFLAGS} main.c

validator.o: validator.c
	${CC} ${CFLAGS} validator.c

resolver.o: resolver.c
	${CC} ${CFLAGS} resolver.c

clean:
	rm -f *.o *~
