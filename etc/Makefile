# Output setting
SHELL = /bin/sh
SRC=../src
BUILD=../build

# Compiler settings - Can be customized.
CXX = g++
CXXFLAGS = -std=c++11 -Wall
# LDFLAGS
# CPPFLAGS

all: scanpf unit_test

debug: CXXFLAGS += -DDEBUG -g
debug: scanpf

debuggdb: CXXFLAGS += -DDEBUG -ggdb
debuggdb: scanpf

scanpf: scanpf.o
	#$(CXX) $(CXXFLAGS) $(BUILD)/$< -o $(BUILD)/$@
	$(CXX) $(CXXFLAGS) $(BUILD)/scanpf.o -o $(BUILD)/scanpf 

scanpf.o: $(BUILD)
	#$(CXX) $(CXXFLAGS) -c $(SRC)/$< -o $(BUILD)/$@
	$(CXX) $(CXXFLAGS) -c $(SRC)/scanpf.cpp -o $(BUILD)/scanpf.o

unit_test: unit_test.o 000-CatchMain.o utility.o
	$(CXX) $(CXXFLAGS) $(BUILD)/unit_test.o $(BUILD)/000-CatchMain.o $(BUILD)/utility.o -o $(BUILD)/unit_test

unit_test.o: $(BUILD) $(SRC)/unit_test.cpp 000-CatchMain.o utility.o
	$(CXX) $(CXXFLAGS) -c $(SRC)/unit_test.cpp -o $(BUILD)/unit_test.o

000-CatchMain.o: $(BUILD) $(SRC)/000-CatchMain.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/000-CatchMain.cpp -o $(BUILD)/000-CatchMain.o

utility.o: $(BUILD) $(SRC)/utility.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/utility.cpp -o $(BUILD)/utility.o

# install man pages
.PHONY: man
man: 
	cp ../man/scanpf.1 /usr/local/share/man/man1
	gzip /usr/local/share/man/man1/scanpf.1
	mandb
	
# uninstall man pages
.PHONY: unman
unman:
	rm /usr/local/share/man/man1/scanpf.1.gz
	mandb

$(BUILD):
	if [ ! -d "./$(BUILD)" ]; then 		\
			mkdir $(BUILD);				\
	fi

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
	rm $(BUILD)/*o

# clean all build
.PHONY: clean
clean:
	rm -rf $(BUILD) 

archive: all
	git archive master | gzip > $(BUILD)/scanpf.latest.tgz