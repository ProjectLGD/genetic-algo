
CC=g++
CFLAGS:=-O2 -g
CPPFLAGS:=$(CFLAGS) -std=c++11

AR=ar

SRC_DIR=./
OBJ_DIR=./

INCLUDES=-I ./classes

LIBRARY=libgenetic-algo.a

SRC=$(shell find . -name "*.cpp")

OBJ=$(patsubst $(SRC_DIR)%.cpp,$(OBJ_DIR)%.o,$(SRC))

EXECUTABLE=genetic-algo

%.cpp%.o:
	$(CC) -c -o $@ $< $(CPPFLAGS)
%.hpp%.o:
	$(CC) -c -o $@ $< $(CPPFLAGS)

all: $(EXECUTABLE)

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
