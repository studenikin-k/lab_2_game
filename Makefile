CC=clang++
CFLAGS=-Werror -Wpedantic -Wall -std=c++20
LDFLAGS=-lpthread
TEST_LDFLAGS=$(LDFLAGS) -lgtest -lgtest_main


INVENTORY_DIRECTORIES = src/inventory src/inventory/bag src/inventory/equipment src/inventory/potion src/inventory/weapon
SOURCE_DIRECTORIES = src src/utils src/characters src/shop src/inventory/coins
TEST_DIRECTORY = tests

INVENTORY = $(wildcard $(patsubst %,%/*.cpp,$(INVENTORY_DIRECTORIES)))
SOURCES = $(wildcard $(patsubst %,%/*.cpp,$(SOURCE_DIRECTORIES)))
TESTS = $(wildcard $(TEST_DIRECTORY)/*.cpp)

MAIN_OBJECTS = $(SOURCES:.cpp=.o) $(INVENTORY:.cpp=.o) main.o
TEST_OBJECTS = $(SOURCES:.cpp=.o) $(INVENTORY:.cpp=.o) $(TESTS:.cpp=.o)

all: main test

main: $(MAIN_OBJECTS)
	$(CC) $(MAIN_OBJECTS) $(CFLAGS) $(LDFLAGS) -o $@

test: $(TEST_OBJECTS)
	$(CC) $(TEST_OBJECTS) $(CFLAGS) $(TEST_LDFLAGS) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean all

clean:
	rm -rf main test $(MAIN_OBJECTS) $(TEST_OBJECTS) *.mk