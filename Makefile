
all:
	gcc -Wall -Wextra -Werror -o rush-01 rush-01.c map.c

test: all
	./rush-01 "2 2 1 2 1 3 3 1 2 1 2 2"

# ./rush-01 "4 3 2 1 1 2 2 3 4 3 2 1 1 2 2 2"
#./rush-01 "3 2 1 2 3 1 3 3 4 2 3 2 2 4 1 3 2 3 1 2"

fail: all
	./rush-01 "4 3 2 1 1 2 2 3 4 3 2 1 1 2 2"

debug: all
	gdb ./rush-01

perm:
	gcc -Wall -Wextra -Werror -o main main.c
	./main

tcgen:
	gcc -Wall -Wextra -Werror -o tcgen tcgen.c map.c
	./tcgen 3
