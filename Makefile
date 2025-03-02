
WIDTH ?= 4

build: rush-01.c map.c map.h
	gcc -g -Wall -Wextra -Werror -Wno-unused-variable -Wno-unused-function -o rush-01 rush-01.c map.c

# Does not work for some reason. Probably the input is wrong
test4: build
	./rush-01 "4 3 2 1 1 2 2 3 4 3 2 1 1 2 2 3"

test3: build
	./rush-01 "2 2 1 2 1 3 3 1 2 1 2 2"

test5: build
	./rush-01 "3 2 1 2 3 1 3 3 4 2 3 2 2 4 1 3 2 3 1 2"

test6: build
	./rush-01 "3 3 2 3 1 3 3 1 5 4 5 2 4 3 4 1 2 2 2 2 3 4 1 2"

sky: build
	./rush-01 "2 1 2 3 1 2 3 2 2 2 4 1 3 2 1 3"

# ./rush-01 "1 3 3 2 3 2 1 3 1 2 2 3 2 1 3 2"

debug: build
	gdb ./rush-01

tcgen: tcgen.c map.c
	gcc -Wall -Wextra -Werror -o tcgen tcgen.c map.c
	./tcgen 9

rand: build
	./tcgen ${WIDTH} | xargs -I{} time ./rush-01 {}
