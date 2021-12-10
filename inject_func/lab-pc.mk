LLVM_CONFIG := /home/chiachang/Advanced-Compiler/llvm_build/bin/llvm-config

CXX := `$(LLVM_CONFIG) --bindir`/clang
CXXFLAGS := ""
# C PreProcessor flag
CPPFLAGS := `$(LLVM_CONFIG) --cppflags` -fPIC -fno-rtti
LDFLAGS := `$(LLVM_CONFIG) --ldflags`

all: inject_func_call.so test.ll

inject_func_call.so: inject_func_call.o
	$(CXX) -shared inject_func_call.o $(LDFLAGS) -o inject_func_call.so

inject_func.o: inject_func_call.h inject_func_call.cpp
	$(CXX) -c inject_func_call.cpp $(CPPFLAGS) -o inject_func_call.o

test.ll: test.c test.h
	$(CXX) -O0 -Xclang -disable-O0-optnone -S -emit-llvm -include test.h -c test.c -o test.ll

clean:
	rm -f *.o *.ll *.so

.PHONY: all