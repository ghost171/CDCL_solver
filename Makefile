CC = g++
FLAGS = --std=c++11 -Wall
EXEC = ./bin/solver
FILES = solver.cpp CDCL.cpp prop.cpp filling_literals.cpp polarity.cpp backtrack.cpp conflict_solve.cpp result.cpp choosevariable.cpp

all:
	$(CC) $(FLAGS) $(FILES) -o $(EXEC)

clean:
	rm $(EXEC)