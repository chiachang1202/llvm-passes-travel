LLVM_CONFIG=/usr/local/opt/llvm/bin/llvm-config

CXX=`$(LLVM_CONFIG) --bindir`/clang
CPPFLAGS="-I/usr/local/opt/llvm/include"
LDFLAGS="-L/usr/local/opt/llvm/lib"

all: hw1.so test

hw1.so: hw1.o
	$(CXX) -shared -undefined dynamic_lookup hw1.o $(LDFLAGS) -fPIC -o hw1.so

hw1.o: hw1.cpp
	$(CXX) -c hw1.cpp $(CPPFLAGS) -o hw1.o

test: test.c
	$(CXX) -O0 -Xclang -disable-O0-optnone -S -emit-llvm test.c -o test.ll

.PHONY: clean
clean:
	rm -f *.o *.ll *.so
