HEADERS=
CXXFLAGS+=-std=c++17 -Wall -pedantic -DDEBUG -ggdb3
LDFLAGS= -pthread -lpthread
SRC=$(wildcard *.cpp)
OBJ=$(SRC:%.cpp=%.o)

TEST_DIR=test
TEST_SRC=$(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJ=$(TEST_SRC:$(TEST_DIR)/%.cpp=$(TEST_DIR)/%.o)

all: unittest

unittest: $(OBJ) $(TEST_OBJ)
	g++ -o $@ $^ ${LDFLAGS}

%.o: %.cpp
	g++ ${CXXFLAGS} -c $< -o $@

$(TEST_DIR)/%.o: $(TEST_DIR)/%.cpp
	g++ ${CXXFLAGS} -c $< -o $@

clean:
	rm -f *.o unittest $(TEST_DIR)/*.o
