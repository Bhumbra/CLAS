XX := g++
CC := gcc
SS := gcc
AR := ar
XFLAGS := -c -g -save-temps=obj -std=c++11 -O3 -msse4.1
CFLAGS := -c -g -save-temps=obj -O3 -msse4.1
SFLAGS := -c -g -save-temps=obj
AFLAGS := cr
LIB := -pthread
INC := -I include -I src
lib/libclas.a:
	@mkdir -p build
	$(SS) $(SFLAGS) src/vmdot_product_double_1.S -o build/products_s.o $(INC) $(LIB)
	$(CC) $(CFLAGS) src/vmdot_product_double.c -o build/products_c.o $(INC) $(LIB)
	$(XX) $(XFLAGS) src/products.cxx -o build/products_x.o $(INC) $(LIB) 
	@mkdir -p lib
	$(AR) $(AFLAGS) lib/libclas.a build/products_s.o build/products_c.o build/products_x.o
