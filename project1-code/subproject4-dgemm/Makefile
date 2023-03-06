K=128

# TODO
# Adjust these values
M=11
N=11
ALIGNMENT=8
# END TODO

CXX=icpc
CXXFLAGS=-O3 -std=c++11 -march=core-avx2
LDFLAGS=
DEFINES=-DALIGNMENT=$(ALIGNMENT) -DM=$(M) -DN=$(N) -DK=$(K)
SOURCES=dgemm.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=dgemm


%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@ $(DEFINES)

all: $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $(EXECUTABLE)

clean:
	rm *.o $(EXECUTABLE)
