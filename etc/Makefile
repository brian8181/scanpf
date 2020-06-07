# Output setting
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
	#g++ $(CXXFLAGS) $(BUILD)/$< -o $(BUILD)/$@
	g++ $(CXXFLAGS) $(BUILD)/scanpf.o -o $(BUILD)/scanpf 

scanpf.o: build
	g++ $(CXXFLAGS) -c $(SRC)/scanpf.cpp -o $(BUILD)/scanpf.o

unit_test: unit_test.o 000-CatchMain.o utility.o
	g++ $(CXXFLAGS) $(BUILD)/unit_test.o $(BUILD)/000-CatchMain.o $(BUILD)/utility.o -o $(BUILD)/unit_test

unit_test.o: build $(SRC)/unit_test.cpp 000-CatchMain.o utility.o
	g++ $(CXXFLAGS) -c $(SRC)/unit_test.cpp -o $(BUILD)/unit_test.o

000-CatchMain.o: build $(SRC)/000-CatchMain.cpp
	g++ $(CXXFLAGS) -c $(SRC)/000-CatchMain.cpp -o $(BUILD)/000-CatchMain.o

utility.o: build $(SRC)/utility.cpp
	g++ $(CXXFLAGS) -c $(SRC)/utility.cpp -o $(BUILD)/utility.o

man: 
	cp ../man/scanpf.1 /usr/local/share/man/man1
	gzip /usr/local/share/man/man1/scanpf.1
	mandb

unman:
	rm /usr/local/share/man/man1/scanpf.1.gz
	mandb

.PHONY: build
build:
	if test ! -d $(BUILD); then mkdir $(BUILD); fi

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
	rm -r $(BUILD) 

archive: all
	git archive master | gzip > $(BUILD)/scanpf.latest.tgz