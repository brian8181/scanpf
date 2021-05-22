MAKE_TEMPLATE = 1.1;
# RUN BEFORE autoreconf -ivfm
BUILD_VERSION = 0.1.0

prefix = /usr/local
mandir = $(prefix)/share/man
man1dir = $(mandir)/man1

# Compiler settings - Can be customized.
CXX = g++
CXXFLAGS = -Wall -std=c++11

# lib settings
# LDFLAGS =
# INCLUDES= 
# add addtional libs here

# Makefile settings - Can be customized.
APP_NAME = scanpf
EXT = cpp
SHELL = /bin/bash
SRC_DIR = ~/src/scanpf/src
BUILD_DIR = ~/src/scanpf/build

all: scanpf utility.o

debug: CXXFLAGS += -DDEBUG -g
debug: scanpf

debuggdb: CXXFLAGS += -DDEBUG -ggdb
debuggdb: scanpf

scanpf: scanpf.o
	$(CXX) $(CXXFLAGS) $(BUILD_DIR)/scanpf.o $(BUILD_DIR)/main.o -o $(BUILD_DIR)/scanpf 

scanpf.o: 
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/scanpf.cpp -o $(BUILD_DIR)/scanpf.o
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o

# unit_test: unit_test.o 000-CatchMain.o 
#  	$(CXX) $(CXXFLAGS) $(BUILD_DIR)/unit_test.o $(BUILD_DIR)/000-CatchMain.o $(BUILD_DIR)/utility.o -o $(BUILD_DIR)/unit_test

# unit_test.o: 
#  	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/unit_test.cpp -o $(BUILD_DIR)/unit_test.o

# 000-CatchMain.o: 
#  	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/000-CatchMain.cpp -o $(BUILD_DIR)/000-CatchMain.o

utility.o: 
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/utility.cpp -o $(BUILD_DIR)/utility.o

# install man pages
.PHONY: man
man: 
	cp ../man/scanpf.1 /usr/local/share/man/man1
	gzip /usr/local/share/man/man1/scanpf.1
	mandblibtag.so.1.17.0
	
# uninstall man pages
.PHONY: unman
unman:
	rm /usr/local/share/man/man1/scanpf.1.gz
	mandb

# create_build_dir:
# 	if [ ! -d "./$BUILD_DIR)" ]; then 		\
# 			mkdir $BUILD_DIR);				\
# 	fi

.PHONY: install
install: man scanpf
	cp $(BUILD_DIR)/scanpf /usr/local/bin/scanpf

.PHONY: uninstall
uninstall: unman
	rm /usr/local/bin/scanpf
	
# clean all build
.PHONY: test
test: regx unit_test
	$(BUILD_DIR)/unit_test

# just object files *.o
.PHONY: cleanobj
cleanobj:
	#rm $(BUILD_DIR)/*o

# clean all build
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)/$(APP_NAME) $(BUILD_DIR)/*o

archive: all
	git archive master | gzip > $(BUILD_DIR)/scanpf.latest.tgz
