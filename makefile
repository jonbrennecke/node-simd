cc = g++
cflags = -std=c11 -Wall -msse4
cxx = g++
cxxflags = -std=c++11 -Wall -msse4 -march=core-avx-i 
# -O3

# vector
src = test.cpp
target = 

# assembler
assembler = asm.cpp

all: test
	
test:
	$(cxx) $(cxxflags) $(src) $(target)

assembler:
	$(cxx) $(cxxflags) $(assembler)
