HEADERS=
CXXFLAGS+=-std=c++17 -Wall -pedantic -DDEBUG -ggdb3
LDFLAGS=
SRC=$(wildcard *.cpp)
OBJ=$(SRC:%.cpp=%.o)

all: $(OBJ)
	g++ -o unittest $^ ${LDFLAGS}

%.o: %.cpp
	g++ ${CXXFLAGS} -c $<

clean:
	rm -f *.o unittest
