CC := gcc
CC_FLAGS := -g -Wall -O0
LD_FLAGS := -lodbc

TARGET := mariadb-odbc-test
SRCS := $(wildcard *.c)
OBJS := $(patsubst %.c, %.o, ${SRCS})

%.o: %.c
	${CC} ${CC_FLAGS} -c $< -o $@

${TARGET}: ${OBJS}
	${CC} ${CC_FLAGS} $^ -o $@ ${LD_FLAGS}

all: ${TARGET}

clean:
	rm -f ${OBJS} ${TARGET}

test:
	echo ${SRCS}
	echo ${OBJS}

.phony: test clean