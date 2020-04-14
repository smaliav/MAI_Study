CC = nvcc 

FLAGS = --std=c++11 -Werror cross-execution-space-call -lm
FILES = lab3.cu

PROG = lab3

all:
	$(CC) $(FLAGS) -o $(PROG) $(FILES)

clean:
	rm -f *.o $(PROG)