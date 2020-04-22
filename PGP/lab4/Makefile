CC = nvcc 

FLAGS = --std=c++11 -Werror cross-execution-space-call -lm
FILES = lab4.cu

PROG = lab4

all:
	$(CC) $(FLAGS) -o $(PROG) $(FILES)

clean:
	rm -f *.o $(PROG)