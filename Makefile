
CC=g++
CFLAGS=-pedantic -Wextra -Wall
CPPFLAGS=$(CFLAGS) -std=c++11

AR=ar

SRC_DIR=./
OBJ_DIR=./

INCLUDES=-I ./include

LIBRARY=libgenetic-algo.a

SRC=$(shell find . -name "*.cpp")

OBJ=$(patsubst $(SRC_DIR)%.cpp,$(OBJ_DIR)%.o,$(SRC))

EXECUTABLE=genetic-algo

release: all

all: CFLAGS+=-O2
all: $(EXECUTABLE)

debug: CFLAGS+=-O0 -g
debug: $(EXECUTABLE)

%.cpp%.o:
	$(CC) -c -o $@ $< $(CPPFLAGS)

# Make the executable named EXECUTABLE using CC
$(EXECUTABLE): $(OBJ)
	$(CC) -o $@ $(CPPFLAGS) $(OBJ) $(INCLUDES)

# Generate the static library
# TODO: Get this working.
$(LIBRARY): $(OBJ)
	$(AR) rcs $@ $(OBJ)

clean:
	rm -rf $(OBJ)
	rm -f $(EXECUTABLE)
	rm -f $(LIBRARY)
