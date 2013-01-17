# neste template de Makefile so muda a lista
# dos SOURCES e o nome do EXECUTABLE.

CC = g++
CFLAGS = -c -Wall -Weffc++ -pedantic -std=c++0x  
LDFLAGS = -lgtest -lgsl -lgslcblas -lm -lpthread
SOURCES =   src/main.cpp src/preferential_attachment.cpp src/statistics/histogram.cpp
 
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = networks


all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC)  $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

 
