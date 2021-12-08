LLVM_CONFIG := /usr/local/opt/llvm/bin/llvm-config

SO := hw1.so
OBJ := hw1.o
SRC := hw1.cpp

CXX := `$(LLVM_CONFIG) --bindir`/clang
CXXFLAGS := ""
# C PreProcessor flag
CPPFLAGS := "-I/usr/local/opt/llvm/include"
LDFLAGS := "-L/usr/local/opt/llvm/lib"

.PHONY: all input clean

all: $(SO) input

$(SO): $(OBJ)
	$(CXX) -shared -undefined dynamic_lookup $(OBJ) $(LDFLAGS) -fPIC -o $(SO)

$(OBJ): hw1.h $(SRC)
	$(CXX) -c $(SRC) $(CPPFLAGS) -o $(OBJ)

input: test.c
	$(CXX) -O0 -Xclang -disable-O0-optnone -S -emit-llvm test.c -o test.ll

clean:
	rm -f *.o *.ll *.so
