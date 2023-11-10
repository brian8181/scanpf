# Fri Nov 10 05:58:41 AM CST 2023
MAKE_TEMPLATE = 1.1;
BUILD_VERSION = 0.1.0
prefix = /usr/local

CXX = g++
CXXFLAGS = -Wall -std=c++11
APP_NAME = scanpf
ROOT  = .
SRC = src
BLD = build
OBJ = build

all: scanpf utility.o
debug: CXXFLAGS += -DDEBUG -g
debug: scanpf
debuggdb: CXXFLAGS += -DDEBUG -ggdb
debuggdb: scanpf

scanpf: scanpf.o
	$(CXX) $(CXXFLAGS) $(OBJ)/scanpf.o $(OBJ)/main.o -o $(BLD)/scanpf 

scanpf.o: 
	$(CXX) $(CXXFLAGS) -c $(SRC)/scanpf.cpp -o $(OBJ)/scanpf.o
	$(CXX) $(CXXFLAGS) -c $(SRC)/main.cpp -o $(OBJ)/main.o

utility.o: 
	$(CXX) $(CXXFLAGS) -c $(SRC)/utility.cpp -o $(OBJ)/utility.o

# clean all build
.PHONY: clean
clean:
	-rm -rf $(BLD)/$(APP_NAME) $(BLD)/*o

archive: all
	git archive master | gzip > $(BLD)/scanpf.latest.tgz
