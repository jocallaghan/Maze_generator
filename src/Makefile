CFLAGS	= -Wall -Wextra -pedantic -std=c++11 
DEBUG	= -g -ggdb
PROG	= maze
OBJ	= maze.o main.o cell.o pathway.o svgsave.o binarysave.o \
binaryload.o depthfirstsearchgenerator.o depthfirstsearchsolver.o \
solvingstrategy.o breadthfirstsearchsolver.o astarsolver.o time.o \
kruskalgenerator.o 

%.o: %.cpp
	@echo "##### Compiling........"
	g++ $(CFLAGS) $(DEBUG) -c $< -o $@

all: $(OBJ)
	@echo "##### Linking........"
	g++ -o $(PROG) $(OBJ)

clean: 
	@echo "##### Cleaning.........."
	rm -f $(OBJ) $(PROG)

.PHONY:prep
prep:
	@echo "##### Preparing........."
	source /opt/rh/devtoolset-2/enable
