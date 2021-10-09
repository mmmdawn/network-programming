CFLAGS = -c -Wall
CC = gcc
LIBS = -lm

all: main.o account.o utils.o functions.o
	${CC} main.o account.o utils.o functions.o -o week1

main.o: main.c
	${CC} ${CFLAGS} main.c

account.o: account.c
	${CC} ${CFLAGS} account.c

utils.o: utils.c
	${CC} ${CFLAGS} utils.c

functions.o: functions.c
	${CC} ${CFLAGS} functions.c

clean:
	rm -f *.o *~
