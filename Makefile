
all: *.c
	gcc -Wall -Wextra -Werror -o rush-01 *.c

test: all
	./rush-01 "4 3 2 1 1 2 2 3 4 3 2 1 1 2 2 2"

fail: all
	./rush-01 "4 3 2 1 1 2 2 3 4 3 2 1 1 2 2"

debug: all
	gdb ./rush-01

perm:
	gcc -Wall -Wextra -Werror -o main main.c
	./main