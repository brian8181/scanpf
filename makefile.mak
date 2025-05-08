# File Name:  scanpf/makefile
# Build Date: Mon Mar  4 09:11:39 AM CST 2024
# Version:    0.1.0

APP?=scanpf
CXX=g++
CXXFLAGS=-Wall -std=c++20
CXXCPP?=
LDFLAGS?=
LIBS?=

SRC=src
BLD?=build
OBJ?=build

ifndef RELEASE
	CXXFLAGS +=-g -DDEBUG
endif

ifdef CYGWIN
	CXXFLAGS += -DCYGWIN
endif

all: $(BLD)/$(APP) $(BLD)/$(APP)_test

rebuild: clean all

$(BLD)/$(APP): $(OBJ)/$(APP).o $(OBJ)/main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BLD)/$(APP)_test: $(OBJ)/$(APP).o $(OBJ)/$(APP)_test.o
	$(CXX) $(CXXFLAGS) $^ -lcppunit -o $@

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
