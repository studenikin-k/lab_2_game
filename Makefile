CC=g++
CFLAGS=-Werror -Wpedantic -Wall -std=c++17
LDFLAGS=-lgtest -lgtest_main -lpthread
SOURCES=test.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=test

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) $(LDFLAGS) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS) *.mk
