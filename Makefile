MAKE_TEMPLATE = 1.1;
BUILD_VERSION = 0.1.0

prefix = /usr/local
mandir = $(prefix)/share/man

CXX = g++
CXXFLAGS = -Wall -std=c++11

SHELL = /bin/bash
APP_NAME = scanpf
ROOT  = .
SRC = src
BUILD = build
OBJS = build

all: scanpf utility.o
debug: CXXFLAGS += -DDEBUG -g
debug: scanpf
debuggdb: CXXFLAGS += -DDEBUG -ggdb
debuggdb: scanpf

scanpf: scanpf.o
	$(CXX) $(CXXFLAGS) $(BUILD)/scanpf.o $(BUILD)/main.o -o $(BUILD)/scanpf 

scanpf.o: 
	$(CXX) $(CXXFLAGS) -c $(SRC)/scanpf.cpp -o $(BUILD)/scanpf.o
	$(CXX) $(CXXFLAGS) -c $(SRC)/main.cpp -o $(BUILD)/main.o

utility.o: 
	$(CXX) $(CXXFLAGS) -c $(SRC)/utility.cpp -o $(BUILD)/utility.o

.PHONY: man
man: 
	cp ../man/scanpf.1 /usr/local/share/man/man1
	gzip /usr/local/share/man/man1/scanpf.1
	mandblibtag.so.1.17.0
	
.PHONY: unman
unman:
	rm /usr/local/share/man/man1/scanpf.1.gz
	mandb

.PHONY: install
install: man scanpf
	cp $(BUILD)/scanpf /usr/local/bin/scanpf

.PHONY: uninstall
uninstall: unman
	rm /usr/local/bin/scanpf
	
# clean all build
.PHONY: test
test: regx unit_test
	$(BUILD)/unit_test

# just object files *.o
.PHONY: cleanobj
cleanobj:
	#rm $(BUILD)/*o

# clean all build
.PHONY: clean
clean:
	-rm -rf $(BUILD)/$(APP_NAME) $(BUILD)/*o

archive: all
	git archive master | gzip > $(BUILD)/scanpf.latest.tgz
