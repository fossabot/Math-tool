#pragma once
#ifndef FUNKCIE_H
#define FUNKCIE_H
#include <fstream>
#include <NTL/ZZX.h>
#include <NTL/mat_ZZ_p.h>
#include <NTL/ZZ_pXFactoring.h>
#include <sal.h>

NTL_CLIENT
int ord(ZZ A, ZZ M, ZZ result = to_ZZ(1));
vec_ZZ factorize_number(ZZ n);
int cancer(vec_ZZ& list);
void vec_to_lambda(vec_ZZ& list);
int lcm(vec_ZZ& list);

void (*RAL[])();
void (*ZKRY1[])();
void (*ZKRY2[])();
#endif