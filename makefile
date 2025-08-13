# File Name:  makefile
# Build Date: Tue, Aug 12, 2025  9:26:00 PM
# Version:    0.1.1

APP=scanpf
CXX=g++
CXXFLAGS=-Wall -std=c++20 -fPIC
CXXCPP?=
LDFLAGS?=
LIBS?=
SRC=src
BLD?=build
OBJ?=build

# lib settings
LIBS = -L/usr/local/lib/
INCLUDES = -I/usr/local/include/cppunit/
LDFLAGS = $(LIBS) $(INCLUDES)

# lib settings
LIBS=-L/usr/local/lib/
INCLUDES=-I/usr/local/include/cppunit/

ifndef RELEASE
	CXXFLAGS +=-g -DDEBUG
	LDFLAGS=$(INCLUDES) $(LIBS) /usr/local/libcppunit.a
endif

ifdef CYGWIN
	CXXFLAGS +=-DCYGWIN
	LDFLAGS=$(INCLUDES) $(LIBS) /usr/lib/libcppunit.dll.a
endif

all: $(BLD)/scanpf $(BLD)/scanpf_test $(BLD)/scanrf $(BLD)/scanrf_test

rebuild: clean all

debug: CXXFLAGS += -DDEBUG -g
debug: scanpf
debuggdb: CXXFLAGS += -DDEBUG -ggdb
debuggdb: scanpf

$(BLD)/scanpf: $(BLD)/scanpf.o $(BLD)/main.o
	$(CXX) $(CXXFLAGS) $(OBJ)/scanpf.o $(OBJ)/main.o -o $(BLD)/scanpf

$(BLD)/scanrf: $(BLD)/scanrf.o $(BLD)/main.o
	$(CXX) $(CXXFLAGS) $(OBJ)/scanrf.o $(OBJ)/main.o -o $(BLD)/scanrf

$(BLD)/$(APP)_test: $(OBJ)/$(APP).o $(OBJ)/$(APP)_test.o
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

$(BLD)/scanrf_test: $(OBJ)/scanrf.o $(OBJ)/scanrf_test.o
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

$(BLD)/unit_test: $(BLD)/unit_test.o $(BLD)/000-CatchMain.o
	$(CXX) $(CXXFLAGS) $(BLD)/unit_test.o $(BLD)/000-CatchMain.o $(BLD)/utility.o -o $(BLD)/unit_test

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

.PHONY: install
install:
	cp ./$(BLD)/$(APP) ./$(prefix)/bin/$(APP)

.PHONY: uninstall
uninstall:
	-rm ./$(prefix)/bin/$(APP)

.PHONY: clean
clean:
	-rm -f ./$(OBJ)/*.o
	-rm -f ./$(BLD)/*.o
	-rm -f ./$(BLD)/$(APP)*

.PHONY: help
help:
	@echo  '  all             - build all'
	@echo  '  clean           - remove all files from build dir'
	@echo  '  install         - copy files to usr/local'
	@echo  '  dist            - create distribution, tar.gz'
	@echo  '  $(APP)          - build $(APP) executable'
	@echo  '  $(APP).o        - build not link'
	@echo  '  $(APP)_test     - build cppunit test'
	@echo  '  $(APP)_test.o   - build cppunit test'
	@echo  '  scanrf          - build scanrf executable'
	@echo  '  scanrf.o        - build not link'
	@echo  '  scanrf_test     - build cppunit test'
	@echo  '  scanrf_test.o   - build cppunit test'
