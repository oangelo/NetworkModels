# Generic Makefile for compiling a simple executable.

CC := g++ 
SRCDIR := src
BUILDDIR := build
CFLAGS := -g -Wall -std=c++0x  -Weffc++ -Wextra -pedantic
LDFLAGS=  -lm
TARGET := netmodels 
LIB := libnetmodels.so 
SRCEXT := cpp
INCDIR := /usr/include/network_models
LIBDIR := /usr/lib
BINDIR := /usr/bin

SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
DIRS = $(shell find $(SRCDIR) -type d)

HEADERS := $(shell find $(SRCDIR) -type f -name *.h)
INCLUDE = $(patsubst $(SRCDIR)/%,$(INCDIR)/%,$(HEADERS))

.PHONY: all 
all:bin lib

.PHONY: install 
vpath %.h $(DIRS)
install: $(INCLUDE)
	@cp $(LIB) $(LIBDIR)
	@cp $(TARGET) $(BINDIR)
$(INCDIR)/%.h: %.h 
	@mkdir -p  $(shell dirname $@)
	@cp $< $@
 
.PHONY: lib 
lib:$(LIB)
$(LIB):$(OBJECTS)
	$(CC)  -shared -Wl,-soname,$(LIB) -o $(LIB) $? 
vpath %.$(SRCEXT) $(DIRS)
$(BUILDDIR)/%.o: %.$(SRCEXT) 
	@mkdir -p  $(shell dirname $@)
	$(CC) $(CFLAGS) $< -o $@  -c -fPIC

.PHONY: bin 
bin:$(TARGET)
$(TARGET):$(LIB)
	$(CC) -L. -lnetmodels $(LDFLAGS) -o $(TARGET)

.PHONY: clean
clean:
	@echo " Cleaning..."; $(RM) -r $(BUILDDIR) $(TARGET) $(LIB)
