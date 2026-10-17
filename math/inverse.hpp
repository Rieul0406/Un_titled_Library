/*
 * モジュラ逆元・モジュラ除算
 *
 * 使い方:
 *   ll inv = modpow(b, mod - 2, mod);   // b の mod 逆元
 *   ll res = mod_div(a, b, mod);         // a / b mod MOD（= a * b^{-1} mod MOD）
 *
 * 計算量:
 *   modpow  : O(log exp)
 *   mod_div : O(log mod)
 */

#pragma once

#include "modpow.hpp"
using namespace std;
using ll = long long;
const ll MOD = 998244353;

ll moddiv(ll a, ll b){
    return (a * modpow(b, MOD - 2)) % MOD;
}