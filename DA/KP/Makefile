CC = g++
FLAGS = -std=c++11 -O3 -g -pedantic -Wall -Wno-sign-compare -Wno-long-long -lm
FILES =  main.cpp Query.cpp Index.cpp
PROG = kp

kp:
	$(CC) $(FLAGS) -o $(PROG) $(FILES)

clean:
	rm -f *.o kp
