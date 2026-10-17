/*
 * 最小素因数篩 (Smallest Prime Factor Sieve, Osa_k 法)
 *
 * 使い方:
 *   o_sak sk(n);              // [0, n] の最小素因数を前計算
 *   auto fac = sk.get(x);     // x を素因数分解。{素因数, 指数} の vector<pii> を返す
 *   // 例: sk.get(12) → {{2,2},{3,1}}
 *
 * 計算量:
 *   コンストラクタ : O(N log log N)
 *   get(x)         : O(log x)
 */

#pragma once

#include <vector>
#include <utility>
#include <numeric>
using namespace std;
#define all(v) v.begin(), v.end()
using ll = long long;
using pii = pair<int, int>;

class o_sak{
    public:
    vector<int> spf;
    o_sak(int n){
        spf.resize(n + 1);
        iota(all(spf), 0);
        for(int i = 2; i * i <= n; i++){
            if(spf[i] != i) continue;
            for(int j = i * i; j <= n; j += i){
                if(spf[j] == j) spf[j] = i;
            }
        }
    }
    vector<pii> get(int x) const{
        vector<pii> res;
        while(x != 1){
            if(res.empty() || res.back().first != spf[x]){
                res.push_back({spf[x], 1});
            }else{
                res.back().second++;
            }
            x /= spf[x];
        }
        return res;
    }
};
