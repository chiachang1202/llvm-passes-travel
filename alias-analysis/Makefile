LLVM_CONFIG := /usr/local/opt/llvm/bin/llvm-config

CXX := `$(LLVM_CONFIG) --bindir`/clang
CXXFLAGS := -disable-O0-optnone -fno-discard-value-names
# C PreProcessor flag
CPPFLAGS := "-I/usr/local/opt/llvm/include" -fPIC -fno-rtti
LDFLAGS := "-L/usr/local/opt/llvm/lib"

all: alias_analysis.so

alias_analysis.so: alias_analysis.o
	$(CXX) -shared -undefined dynamic_lookup alias_analysis.o $(LDFLAGS) -fPIC -o alias_analysis.so

alias_analysis.o: alias_analysis.h alias_analysis.cpp
	$(CXX) -c alias_analysis.cpp $(CPPFLAGS) -o alias_analysis.o

inputs: foo.c icpp.c icpp2.c icpp3.c
	$(CXX) -O0 -Xclang $(CXXFLAGS) -S -emit-llvm -c foo.c -o foo.ll
	$(CXX) -O0 -Xclang $(CXXFLAGS) -S -emit-llvm -c icpp.c -o icpp.ll
	$(CXX) -O0 -Xclang $(CXXFLAGS) -S -emit-llvm -c icpp2.c -o icpp2.ll
	$(CXX) -O0 -Xclang $(CXXFLAGS) -S -emit-llvm -c icpp3.c -o icpp3.ll

clean:
	rm -f *.o *.ll *.so *.bin

.PHONY: all inputs