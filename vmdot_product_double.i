# 1 "src/vmdot_product_double.c"
# 1 "/home/admin/code/cxx/clas//"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "src/vmdot_product_double.c"

# 1 "include/vmdot_product_double.h" 1



# 1 "/usr/lib/gcc/x86_64-pc-linux-gnu/5.4.0/include/stdint.h" 1 3 4
# 9 "/usr/lib/gcc/x86_64-pc-linux-gnu/5.4.0/include/stdint.h" 3 4
# 1 "/usr/include/stdint.h" 1 3 4
# 25 "/usr/include/stdint.h" 3 4
# 1 "/usr/include/features.h" 1 3 4
# 368 "/usr/include/features.h" 3 4
# 1 "/usr/include/sys/cdefs.h" 1 3 4
# 410 "/usr/include/sys/cdefs.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 411 "/usr/include/sys/cdefs.h" 2 3 4
# 369 "/usr/include/features.h" 2 3 4
# 392 "/usr/include/features.h" 3 4
# 1 "/usr/include/gnu/stubs.h" 1 3 4
# 10 "/usr/include/gnu/stubs.h" 3 4
# 1 "/usr/include/gnu/stubs-64.h" 1 3 4
# 11 "/usr/include/gnu/stubs.h" 2 3 4
# 393 "/usr/include/features.h" 2 3 4
# 26 "/usr/include/stdint.h" 2 3 4
# 1 "/usr/include/bits/wchar.h" 1 3 4
# 27 "/usr/include/stdint.h" 2 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 28 "/usr/include/stdint.h" 2 3 4
# 36 "/usr/include/stdint.h" 3 4

# 36 "/usr/include/stdint.h" 3 4
typedef signed char int8_t;
typedef short int int16_t;
typedef int int32_t;

typedef long int int64_t;







typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;

typedef unsigned int uint32_t;



typedef unsigned long int uint64_t;
# 65 "/usr/include/stdint.h" 3 4
typedef signed char int_least8_t;
typedef short int int_least16_t;
typedef int int_least32_t;

typedef long int int_least64_t;






typedef unsigned char uint_least8_t;
typedef unsigned short int uint_least16_t;
typedef unsigned int uint_least32_t;

typedef unsigned long int uint_least64_t;
# 90 "/usr/include/stdint.h" 3 4
typedef signed char int_fast8_t;

typedef long int int_fast16_t;
typedef long int int_fast32_t;
typedef long int int_fast64_t;
# 103 "/usr/include/stdint.h" 3 4
typedef unsigned char uint_fast8_t;

typedef unsigned long int uint_fast16_t;
typedef unsigned long int uint_fast32_t;
typedef unsigned long int uint_fast64_t;
# 119 "/usr/include/stdint.h" 3 4
typedef long int intptr_t;


typedef unsigned long int uintptr_t;
# 134 "/usr/include/stdint.h" 3 4
typedef long int intmax_t;
typedef unsigned long int uintmax_t;
# 10 "/usr/lib/gcc/x86_64-pc-linux-gnu/5.4.0/include/stdint.h" 2 3 4
# 5 "include/vmdot_product_double.h" 2
# 15 "include/vmdot_product_double.h"

# 15 "include/vmdot_product_double.h"
void vmdot_product_double_1x1 (double* Out, double* In0, double* _In1, uint64_t k, uint64_t n, uint64_t In0s, uint64_t In1s);
void vmdot_product_double_1x2 (double* Out, double* In0, double* _In1, uint64_t k, uint64_t n, uint64_t In0s, uint64_t In1s);
void vmdot_product_double_1x4 (double* Out, double* In0, double* _In1, uint64_t k, uint64_t n, uint64_t In0s, uint64_t In1s);
void vmdot_product_double_1x8 (double* Out, double* In0, double* _In1, uint64_t k, uint64_t n, uint64_t In0s, uint64_t In1s);
void vmdot_product_double_1x16(double* Out, double* In0, double* _In1, uint64_t k, uint64_t n, uint64_t In0s, uint64_t In1s);
void vmdot_product_double_1x32(double* Out, double* In0, double* _In1, uint64_t k, uint64_t n, uint64_t In0s, uint64_t In1s);



static void vmdot_product_double_1 (double* Out,
                  double* In0,
                  double* In1,
                  volatile const uint64_t m,
                  volatile const uint64_t k,
                  volatile const uint64_t n,
                  volatile uint64_t OutS,
                  volatile uint64_t In0S,
                  volatile uint64_t In0s,
                  volatile uint64_t In1s,
                  volatile uint64_t U1);


static void vmdot_product_double_2 (double* Out,
                  double* In0,
                  double* In1,
                  volatile const uint64_t m,
                  volatile const uint64_t k,
                  volatile const uint64_t n,
                  volatile uint64_t OutS,
                  volatile uint64_t In0S,
                  volatile uint64_t In0s,
                  volatile uint64_t In1s,
                  volatile uint64_t U1);


static void vmdot_product_double_4 (double* Out,
                  double* In0,
                  double* In1,
                  volatile const uint64_t m,
                  volatile const uint64_t k,
                  volatile const uint64_t n,
                  volatile uint64_t OutS,
                  volatile uint64_t In0S,
                  volatile uint64_t In0s,
                  volatile uint64_t In1s,
                  volatile uint64_t U1);


static void vmdot_product_double_8 (double* Out,
                  double* In0,
                  double* In1,
                  volatile const uint64_t m,
                  volatile const uint64_t k,
                  volatile const uint64_t n,
                  volatile uint64_t OutS,
                  volatile uint64_t In0S,
                  volatile uint64_t In0s,
                  volatile uint64_t In1s,
                  volatile uint64_t U1);
# 3 "src/vmdot_product_double.c" 2


static void vmdot_product_double_1 (double* Out, double* In0,
                  double* In1,
                  volatile const uint64_t m,
                  volatile const uint64_t k,
                  volatile const uint64_t n,
                  volatile uint64_t OutS,
                  volatile uint64_t In0S,
                  volatile uint64_t In0s,
                  volatile uint64_t In1s,
                  volatile uint64_t U1) {
 uint64_t h = m;
 switch (U1) {
  case 1: {
   for (; h; h--) {
    vmdot_product_double_1x1 (Out, In0, In1, k, n, In0s, In1s);
    Out += OutS;
    In0 += In0S;
   }
   return;
  }
  case 2: {
   for (; h; h--) {
    vmdot_product_double_1x2 (Out, In0, In1, k, n, In0s, In1s);
    Out += OutS;
    In0 += In0S;
   }
   return;
  }
  case 4: {
   for (; h; h--) {
    vmdot_product_double_1x4 (Out, In0, In1, k, n, In0s, In1s);
    Out += OutS;
    In0 += In0S;
   }
   return;
  }
  case 8: {
   for (; h; h--) {
    vmdot_product_double_1x8 (Out, In0, In1, k, n, In0s, In1s);
    Out += OutS;
    In0 += In0S;
   }
   return;
  }
  case 16: {
   for (; h; h--) {
    vmdot_product_double_1x16(Out, In0, In1, k, n, In0s, In1s);
    Out += OutS;
    In0 += In0S;
   }
   return;
  }
  default: { for (; h; h--) {
    vmdot_product_double_1x32(Out, In0, In1, k, n, In0s, In1s);
    Out += OutS;
    In0 += In0S;
   }
   return;
  }
 }
}
