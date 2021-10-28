CFLAGS = -c -Wall
CC = gcc
LIBS = -lm

all: main.o account.o utils.o functions.o resolver.o validator.o
	${CC} main.o account.o utils.o functions.o resolver.o validator.o -o week3; 	rm -f *.o *~;

main.o: main.c
	${CC} ${CFLAGS} main.c

account.o: account.c
	${CC} ${CFLAGS} account.c

utils.o: utils.c
	${CC} ${CFLAGS} utils.c

functions.o: functions.c
	${CC} ${CFLAGS} functions.c

resolver.o: resolver.c
	${CC} ${CFLAGS} resolver.c

validator.o: validator.c
	${CC} ${CFLAGS} validator.c

clean:
	rm -f *.o *~
