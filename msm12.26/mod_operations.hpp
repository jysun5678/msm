#pragma once
#include <cstdint>  // for uint64_t
#include"bigintegerlibrary.hpp"
using namespace std;
// Function declarations
BigInteger mod_add(BigInteger a, BigInteger b, BigInteger modulus);
BigInteger mod_sub(BigInteger a, BigInteger b, BigInteger modulus);
BigInteger mod_mul(BigInteger a, BigInteger b, BigInteger modulus);
BigInteger mod_inv(BigInteger a, BigInteger modulus, BigInteger* u, BigInteger* v);
//extern BigInteger q= BigInteger("4002409555221667393417789825735904156556882819939007885332058136124031650490837864442687629129015664037894272559787");
//extern BigInteger q;