C=gcc
CFLAGS=-Wall -Wextra -O3 -I include

main: main.c ./**/*.c
	${C} ${CFLAGS} $^ -o $@