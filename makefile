# File Name:  scanpf/makefile
# Build Date: Mon Mar  4 09:11:39 AM CST 2024
# Version:    0.1.0

APP=scanpf
CXX=g++
<<<<<<< HEAD
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

all: $(BLD)/scanpf $(BLD)/scanpf_test

debug: CXXFLAGS += -DDEBUG -g
debug: scanpf
debuggdb: CXXFLAGS += -DDEBUG -ggdb
debuggdb: scanpf

$(BLD)/scanpf: $(BLD)/scanpf.o $(BLD)/main.o
	$(CXX) $(CXXFLAGS) $(OBJ)/scanpf.o $(OBJ)/main.o -o $(BLD)/scanpf
=======
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
>>>>>>> ec728969389dd3d4fdb47b62ad8b746373516d06

ifdef CYGWIN
	CXXFLAGS += -DCYGWIN
endif

<<<<<<< HEAD
$(BLD)/$(APP)_test: $(OBJ)/$(APP).o $(OBJ)/$(APP)_test.o
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

$(BLD)/unit_test: $(BLD)/unit_test.o $(BLD)/000-CatchMain.o
	$(CXX) $(CXXFLAGS) $(BLD)/unit_test.o $(BLD)/000-CatchMain.o $(BLD)/utility.o -o $(BLD)/unit_test
=======
all: $(BLD)/$(APP) $(BLD)/$(APP)_test
>>>>>>> ec728969389dd3d4fdb47b62ad8b746373516d06

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
