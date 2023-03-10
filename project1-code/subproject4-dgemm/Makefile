K=128

# TODO
# Adjust these values
M=32
N=32
ALIGNMENT=32
# END TODO


CXX=icpc
CXXFLAGS= -O3 -funroll-loops -mavx2 -march=core-avx2 -fma -ftz -fomit-frame-pointer -std=c++11

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
