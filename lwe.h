#ifndef LWE_H
#define LWE_H

#include <stdint.h>

//not very important, but all the functions exported in the output library
//should use the C naming convention, for inter-compiler compatibility
//reasons, or to bind it with non C++ code.
#ifdef __cplusplus
#define EXPORT extern "C"
#else
#define EXPORT 
#endif

// Idea:
// we may want to represent an element x of the real torus by 
// the integer rint(2^32.x) modulo 2^32
//  -- addition, subtraction and integer combinations are native operation
//  -- modulo 1 is mapped to mod 2^32, which is also native!
// This looks much better than using float/doubles, where modulo 1 is not
// natural at all.
typedef uint32_t Torus32; 
typedef uint64_t Torus64; 

struct LWEParams;

struct LWEKey;

struct LWESample;

struct LWEKeySwitchKey;

struct RingLWEParams;

struct RingLWEKey;

struct RingLWESample;

struct RingGSWParams;

struct RingGSWKey;

struct RingGSWSample;

struct LWEBootstrappingKey;

struct IntPolynomial;

struct TorusPolynomial;

//this is for compatibility with C code, to be able to use
//"LWEParams" as a type and not "struct LWEParams"
typedef struct LWEParams           LWEParams;
typedef struct LWEKey              LWEKey;
typedef struct LWESample           LWESample;
typedef struct LWEKeySwitchKey     LWEKeySwitchKey;
typedef struct RingLWEParams       RingLWEParams;
typedef struct RingLWEKey          RingLWEKey;
typedef struct RingLWESample       RingLWESample;
typedef struct RingGSWParams       RingGSWParams;
typedef struct RingGSWKey          RingGSWKey;
typedef struct RingGSWSample       RingGSWSample;
typedef struct LWEBootstrappingKey LWEBootstrappingKey;
typedef struct IntPolynomial	   IntPolynomial;
typedef struct TorusPolynomial	   TorusPolynomial;

/**
 * This function generates a random LWE key for the given parameters.
 * The LWE key for the result must be allocated and initialized
 * (this means that the parameters are already in the result)
 */
EXPORT void lweKeyGen(LWEKey* result);
EXPORT void lweSymEncrypt(LWESample* result, double message, const LWEKey* key);
EXPORT double lweSymDecrypt(const LWESample* sample, const LWEKey* key);

EXPORT void lweLinearCombination(LWESample* result, const int* combi, const LWESample* samples, const LWEParams* params);

EXPORT void lweKeySwitch(LWESample* result, const LWEKeySwitchKey* ks, const LWESample sample);

// Ring
EXPORT void ringLweKeyGen(LWEKey* result);
EXPORT void ringLweSymEncrypt(LWESample* result, double message, const LWEKey* key);
EXPORT double ringLweSymDecrypt(const LWESample* sample, const LWEKey* key);

EXPORT void ringLwePolyCombination(LWESample* result, const int* combi, const LWESample* samples, const LWEParams* params);

// GSW
EXPORT void ringGswKeyGen(LWEKey* result);
EXPORT void ringGswSymEncrypt(LWESample* result, double message, const LWEKey* key);
EXPORT double ringGswSymDecrypt(const LWESample* sample, const LWEKey* key);

EXPORT void ringGswPolyCombination(LWESample* result, const int* combi, const LWESample* samples, const LWEParams* params);

//extractions Ring LWE -> LWE
EXPORT void keyExtract(LWEKey* result, const RingLWEKey*); //sans doute un param supplémentaire
EXPORT void sampleExtract(LWESample* result, const RingLWESample* x);

//extraction RingGSW -> GSW
EXPORT void gswKeyExtract(RingLWEKey* result, const RingGSWKey* key); //sans doute un param supplémentaire
EXPORT void gswSampleExtract(RingLWESample* result, const RingGSWSample* x);

//bootstrapping
EXPORT void bootstrap(LWESample* result, const LWEBootstrappingKey* bk, double mu1, double mu0, const LWESample* x);

//multiplication Karatsuba
EXPORT void Karatsuba_aux(Torus32* R, const int* A, const Torus32* B, const int size);
EXPORT void multKaratsuba(TorusPolynomial* result, const IntPolynomial* poly1, const TorusPolynomial* poly2);


#include "autogenerated.h"

#endif //LWE_H