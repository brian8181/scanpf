# Output setting
SRC=../src
BUILD=.

# Compiler settings - Can be customized.
CXXFLAGS = -std=c++11 -Wall

all: scanpf unit_test

debug: CXXFLAGS += -DDEBUG -g
debug: scanpf

debuggdb: CXXFLAGS += -DDEBUG -ggdb
debuggdb: scanpf

scanpf: scanpf.o
	g++ $(CXXFLAGS) $(BUILD)/scanpf.o -o $(BUILD)/scanpf

scanpf.o: 
	g++ $(CXXFLAGS) -c $(SRC)/scanpf.cpp -o $(BUILD)/scanpf.o

unit_test: unit_test.o 000-CatchMain.o 
	g++ $(CXXFLAGS) $(BUILD)/unit_test.o $(BUILD)/000-CatchMain.o -o $(BUILD)/unit_test

unit_test.o: $(SRC)/unit_test.cpp 000-CatchMain.o
	g++ $(CXXFLAGS) -c $(SRC)/unit_test.cpp -o $(BUILD)/unit_test.o

000-CatchMain.o: $(SRC)/000-CatchMain.cpp
	g++ $(CXXFLAGS) -c $(SRC)/000-CatchMain.cpp -o $(BUILD)/000-CatchMain.o

# clean all build
.PHONY: test
test: scanpf unit_test
	$(BUILD)/unit_test

# just object files *.o
.PHONY: cleanobj
cleanobj:
	rm $(BUILD)/*o

# clean all build
# .PHONY: clean
# clean:
# 	rm $(BUILD)/*