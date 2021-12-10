LLVM_CONFIG := /usr/local/opt/llvm/bin/llvm-config

CXX := `$(LLVM_CONFIG) --bindir`/clang
CXXFLAGS := ""
# C PreProcessor flag
CPPFLAGS := "-I/usr/local/opt/llvm/include"
LDFLAGS := "-L/usr/local/opt/llvm/lib"

all: inject_func_call.so test.ll

inject_func_call.so: inject_func_call.o
	$(CXX) -shared -undefined dynamic_lookup inject_func_call.o $(LDFLAGS) -fPIC -o inject_func_call.so

inject_func.o: inject_func_call.h inject_func_call.cpp
	$(CXX) -c inject_func_call.cpp $(CPPFLAGS) -o inject_func_call.o

test.ll: test.c test.h
	$(CXX) -O0 -Xclang -disable-O0-optnone -S -emit-llvm -include test.h -c test.c -o test.ll

clean:
	rm -f *.o *.ll *.so *.bin

.PHONY: all