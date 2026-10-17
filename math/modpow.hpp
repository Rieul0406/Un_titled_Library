/*
 * 繰り返し二乗法 (Fast Exponentiation)
 *
 * base^exp mod を高速に計算する。
 *
 * 使い方:
 *   ll res = modpow(base, exp, mod);
 *
 * 計算量:
 *   O(log exp)
 */

#pragma once

using namespace std;
using ll = long long;
const ll MOD = 998244353;

ll modpow(ll base, ll exp){
    ll res = 1LL;
    while(exp){
        if(exp & 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return res;
}