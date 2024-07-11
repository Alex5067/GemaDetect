CC = g++
FLAGS = -Werror -Wextra -Wall
FILE = lib
LIB_DIR = lib
EXEC_FILE = run

all: clean Neu.a test

*.o: $(LIB_DIR)/Neu.cpp $(LIB_DIR)/Neu.h
	@$(CC) $(FLAGS) -c $(LIB_DIR)/Neu.cpp

Neu.a: *.o
	@ar crs Neu.a Neu.o
	@ranlib Neu.a

test.o:
	@$(CC) $(FLAGS) -c testRun.cpp

test: test.o Neu.a
	@$(CC) $(FLAGS) testRun.o -L. Neu.a -o $@
	./test

clean:
	@rm -rf $(LIB_DIR)/data.json
	@rm -rf Neu.a Neu.o test testRun.o

rebuild: clean all