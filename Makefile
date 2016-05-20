CC=g++
CCFLAGS= -std=c++11
# the parameters to be passed to the linker
LIBRARIES= -lsimlib -lm
LIBDIRS=
LDFLAGS= $(LIBDIRS) $(LIBRARIES)

######################################

# names of binaries
BIN=simulation
# names of sources and objects
BIN_SRC=src/*.cpp
BIN_OBJ=$(BIN_SRC:.c=.o)
OBJ=$(BIN_OBJ)

######################################

all: $(BIN)

$(BIN): $(BIN_OBJ)
	$(CC) $(CCFLAGS) $(BIN_OBJ) -o $@ $(LDFLAGS)

######################################

# generating prerequsites automatically
%.d: %.cpp
	$(CC) -M -MF $@ $<
	-include $(OBJ:.o=.d)

######################################

.PHONY: clean run pack
clean:
	rm -f src/*.o $(BIN) 06_xgazdi03_xbaasa00.zip
pack:
	zip -r 06_xgazdi03_xbaasa00.zip src/*.cpp src/*.h timetable/ex124.csv timetable/ex3.csv prilohy/ Makefile doc.pdf
run:
	./simulation
