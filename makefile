CC := g++
CFLAGS := -c -g -save-temps=obj -std=c++11 -O3 
AR := ar
LIB := -pthread
INC := -I include
TARGET := lib/libclas.a
build/products.o : src/products.cxx
	@mkdir -p build
	$(CC) $(CFLAGS) src/products.cxx -o build/products.o $(INC) $(LIB) 
	@ar cr lib/libclas.a build/products.o
	@echo "ar cr lib/libclas.a build/products.o";
