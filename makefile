CC = g++
CXXFLAGS = -std=c++17 -o 
OBJ0 = story
OBJ1 = main

all: clean ${OBJ0}

${OBJ0}:
	${CC} ${CXXFLAGS} $@ src/${OBJ0}.cpp src/${OBJ1}.cpp
clean:
	rm -f ${OBJ0}
	