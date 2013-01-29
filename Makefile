# neste template de Makefile so muda a lista
# dos SOURCES e o nome do EXECUTABLE.

CC = g++
CFLAGS = -c -Wall -Weffc++ -pedantic -std=c++0x  
LDFLAGS = -lgsl -lgslcblas -lm -lpthread
SOURCES =   src/main.cpp src/solicitation_model.cpp src/statistics/histogram.cpp src/statistics/statistics.cpp
 
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = networks


all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC)  $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

 
