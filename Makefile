CC=g++
CFLAGS=-Werror -Wpedantic -Wall -std=c++17
LDFLAGS=-lgtest -lgtest_main -lpthread
SOURCE_DIRECTORIES = src src/characters src/inventory
TEST_DIRECTORY = tests
SOURCES=$(wildcard $(patsubst %,%/*.cpp,$(SOURCE_DIRECTORIES))) main.cpp
TESTS = $(wildcard $(TEST_DIRECTORY)/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o) $(TESTS:.cpp=.o)
EXECUTABLE=test

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) $(LDFLAGS) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS) *.mk

