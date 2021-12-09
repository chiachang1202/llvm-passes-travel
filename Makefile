LLVM_CONFIG := /usr/local/opt/llvm/bin/llvm-config

SO := inject_func.so
OBJ := inject_func.o
SRC := inject_func.cpp

SRC_DIR := lib
INPUT_DIR := inputs
BUILD_DIR := build

CXX := `$(LLVM_CONFIG) --bindir`/clang
CXXFLAGS := ""
# C PreProcessor flag
CPPFLAGS := "-I/usr/local/opt/llvm/include"
LDFLAGS := "-L/usr/local/opt/llvm/lib"

.PHONY: all input clean

all: $(SO) input

$(SO): $(OBJ)
	$(CXX) -shared -undefined dynamic_lookup $(BUILD_DIR)/$(OBJ) $(LDFLAGS) -fPIC -o $(BUILD_DIR)/$(SO)

$(OBJ): $(SRC_DIR)/inject_func.h $(SRC_DIR)/$(SRC)
	$(CXX) -c $(SRC_DIR)/$(SRC) $(CPPFLAGS) -o $(BUILD_DIR)/$(OBJ)

input: $(INPUT_DIR)/test.c
	$(CXX) -O0 -Xclang -disable-O0-optnone -S -emit-llvm $(INPUT_DIR)/test.c -o $(INPUT_DIR)/test.ll

clean:
	rm -f *.o *.ll *.so
