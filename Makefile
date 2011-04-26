objects = main.o grid.o gridmap.o
flags = -Wall -DDEBUG
compiler = clang++

yyatd : main.o grid.o gridmap.o
	$(compiler) $(objects) -o yyatd

main.o : main.cpp grid.h gridmap.h
	$(compiler) $(flags) -c main.cpp

grid.o : grid.cpp grid.h
	$(compiler) $(flags) -c grid.cpp

gridmap.o : gridmap.cpp gridmap.h grid.h
	$(compiler) $(flags) -c gridmap.cpp

.PHONY : clean
clean :
	rm yyatd $(objects)
