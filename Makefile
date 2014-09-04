CFLAGS	= -Wall -Wextra -pedantic -std=c++11 -g -ggdb
PROG	= maze
OBJ	= squaremaze.o main.o cell.o pathway.o svgsave.o binarysave.o \
depthfirstsearchsave.o binaryload.o depthfirstsearchgenerator.o

%.o: %.cpp
	@echo "Compiling........"
	g++ $(CFLAGS) -c $< -o $@

all: $(OBJ)
	@echo "Linking........"
	g++ -o $(PROG) $(OBJ)

clean: 
	@echo "Cleaning.........."
	rm -f $(OBJ) $(PROG)

.PHONY:prep
prep:
	@echo "Preparing........."
	source /opt/rh/devtoolset-2/enable
