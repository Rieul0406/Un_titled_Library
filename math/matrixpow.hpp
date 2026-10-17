/*
 * 行列累乗 (Matrix Exponentiation, mod 998244353)
 *
 * 行列の積は operator* で定義
 * 使い方:
 *   mat A;
 *   mat An = matpow(A, n);
 *   ll val = An[0][1];
 *
 * 計算量:
 *   operator*  : O(N^3)  （N は行列サイズ）
 *   matpow     : O(N^3 log n)
 */

#pragma once

#include <vector>
using namespace std;
using ll = long long;

const ll MOD = 998244353;
template<typename T> void addmod(T& a, T b){a += b; a %= MOD; return;};

using mat = vector<vector<ll>>;
mat operator * (const mat& a, const mat& b){
    mat c(a.size(), vector<ll>(b[0].size()));
    for(int i = 0; i < (int)c.size(); i++){
        for(int j = 0; j < (int)c[0].size(); j++){
            for(int k = 0; k < (int)a[0].size(); k++){
                addmod(c[i][j], a[i][k] * b[k][j]);
            }
        }
    }
    return c;
}
mat matpow(mat a, ll n){
    mat res(a.size(), vector<ll>(a[0].size()));
    for(int i = 0; i < (int)res.size(); i++) res[i][i] = 1;
    while(n){
        if(n & 1) res = res * a;
        a = a * a;
        n >>= 1;
    }
    return res;
}
