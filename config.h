#ifndef CONFIG_H
#define CONFIG_H
#include <fstream>
#include <sstream>
#include <iomanip>

#include <NTL/ZZX.h>

#include <NTL/mat_ZZ_p.h>
#include <NTL/ZZ_pXFactoring.h>

#include <NTL/vec_GF2E.h>
#include <NTL/GF2XFactoring.h>

NTL_CLIENT

typedef unsigned char u8;

int ord(ZZ A, ZZ M, ZZ result = to_ZZ(1));
vec_ZZ factorize_number(ZZ n);
int cancer(vec_ZZ& list);
void vec_to_lambda(vec_ZZ& list);
int lcm(vec_ZZ& list);
void napln_hodnoty(ZZ& M, ZZ& A, ZZ& N, ZZ& B);

void (*RAL[])();
void (*ZKRY1[])();
void (*ZKRY2[])();
void (*NKS[])();
#endif