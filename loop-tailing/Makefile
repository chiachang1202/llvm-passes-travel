LLVM_CONFIG := /usr/local/opt/llvm/bin/llvm-config

CXX := `$(LLVM_CONFIG) --bindir`/clang
CXXFLAGS := -disable-O0-optnone -fno-discard-value-names
# C PreProcessor flag
CPPFLAGS := "-I/usr/local/opt/llvm/include" -fPIC -fno-rtti
LDFLAGS := "-L/usr/local/opt/llvm/lib"

all: LoopTailing.so

LoopTailing.so: LoopTailing.o
	$(CXX) -shared -undefined dynamic_lookup LoopTailing.o $(LDFLAGS) -fPIC -o LoopTailing.so

LoopTailing.o: LoopTailing.h LoopTailing.cpp
	$(CXX) -c LoopTailing.cpp $(CPPFLAGS) -o LoopTailing.o

inputs: test.c
	$(CXX) -O0 -Xclang $(CXXFLAGS) -S -emit-llvm -c test.c -o test.ll

clean:
	rm -f *.o *.ll *.so *.bin

.PHONY: all inputs