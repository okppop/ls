.PHONY: build run

build:
	@ gcc -Wall -Wextra -o ./ls ls.c

run: build
	@ ./ls

clean:
	rm -f ./ls
