/*
 * 二項係数 / 組み合わせ (mod 998244353)
 *
 * 使い方:
 *   ll f   = fact(n);        // n! mod MOD を返す
 *   ll inv = inv_fact(n);    // (n!)^{-1} mod MOD を返す
 *   ll c   = binom(n, k);    // C(n, k) mod MOD を返す（k<0 or k>n なら 0）
 *
 * 計算量:
 *   fact(n) / inv_fact(n) : 初回は O(n)、キャッシュ済みなら O(1)
 *   binom(n, k)            : O(n)（未キャッシュ分の計算のみ）
 */

#pragma once

#include <vector>
using namespace std;
using ll = long long;
const ll MOD = 998244353;

ll fact(const int n){
    static vector<ll> v = {1};
    while((int)v.size() <= n){
        v.push_back((v.back() * (ll)v.size()) % MOD);
    }
    return v[n];
}

ll inv_fact(const int n){
    static vector<ll> u = {0, 1}, v = {1, 1};
    for(int i = (int)u.size(); i <= n; i++){
        ll nex_inv = MOD - (u[MOD % i] * (MOD / i) % MOD);
        u.push_back(nex_inv);
        v.push_back((v.back() * u.back()) % MOD);
    }
    return v[n];
}

ll binom(const int n, const int k){
    if(k < 0 || k > n) return 0;
    ll res = fact(n);
    res = (res * inv_fact(k)) % MOD;
    res = (res * inv_fact(n - k)) % MOD;
    return res;
}
