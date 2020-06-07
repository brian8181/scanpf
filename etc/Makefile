# Output setting
SRC=../src
BUILD=../build

# Compiler settings - Can be customized.
CXX = g++
CXXFLAGS = -std=c++11 -Wall
# LDFLAGS
# CPPFLAGS

all: scanpf unit_test regx

debug: CXXFLAGS += -DDEBUG -g
debug: scanpf regx

debuggdb: CXXFLAGS += -DDEBUG -ggdb
debuggdb: scanpf regx


scanpf: scanpf.o
	#g++ $(CXXFLAGS) $(BUILD)/$< -o $(BUILD)/$@
	g++ $(CXXFLAGS) $(BUILD)/scanpf.o -o $(BUILD)/scanpf 

scanpf.o: 
	g++ $(CXXFLAGS) -c $(SRC)/scanpf.cpp -o $(BUILD)/scanpf.o

# regx: regx.o
# 	g++ $(CXXFLAGS) $(BUILD)/regx.o -o $(BUILD)/regx

# regx.o: 
# 	g++ $(CXXFLAGS) -c $(SRC)/regx.cpp -o $(BUILD)/regx.o

unit_test: unit_test.o 000-CatchMain.o utility.o
	g++ $(CXXFLAGS) $(BUILD)/unit_test.o $(BUILD)/000-CatchMain.o $(BUILD)/utility.o -o $(BUILD)/unit_test

unit_test.o: $(SRC)/unit_test.cpp 000-CatchMain.o utility.o
	g++ $(CXXFLAGS) -c $(SRC)/unit_test.cpp -o $(BUILD)/unit_test.o

000-CatchMain.o: $(SRC)/000-CatchMain.cpp
	g++ $(CXXFLAGS) -c $(SRC)/000-CatchMain.cpp -o $(BUILD)/000-CatchMain.o

utility.o: $(SRC)/utility.cpp
	g++ $(CXXFLAGS) -c $(SRC)/utility.cpp -o $(BUILD)/utility.o

man: 
	cp ../man/scanpf.1 /usr/local/share/man/man1
	gzip /usr/local/share/man/man1/scanpf.1
	mandb

# build:
# 	if [ -d "$(BUILD)/"]; then
# 		#mkdir $(BUILD)
# 		echo "TESTING"
# 	fi

.PHONY: install
install: scanpf
	cp $(BUILD)/scanpf /usr/local/bin/scanpf

.PHONY: uninstall
uninstall: 
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