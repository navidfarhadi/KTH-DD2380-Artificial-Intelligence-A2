CC = g++-7

uname_S=$(shell sh -c 'uname -s 2>/dev/null || echo not')

ifeq ($(uname_S),Linux)
	CC = g++
endif

all:
	$(CC) *.cpp -g -O2 -Wall -o TTT -std=gnu++14

clean:
	rm TTT
