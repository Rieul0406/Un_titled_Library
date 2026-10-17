/*
 * Fenwick Tree (Binary Indexed Tree)
 *
 * 使い方:
 *   fenwick fw(n);           // サイズ n で初期化（全要素 0）
 *   fw.update(pos, value);   // a[pos] += value  (0-indexed)
 *   ll v = fw.query(l, r);   // a[l] + ... + a[r-1] の総和を返す  [l, r)
 *
 * 計算量:
 *   コンストラクタ : O(N)
 *   update         : O(log N)
 *   query          : O(log N)
 */

#pragma once

#include <vector>
using namespace std;
using ll = long long;

class fenwick{
    public:
    vector<ll> dat;
    int siz;

    fenwick(int n){
        siz = n;
        dat.assign(siz + 1, 0);
    }

    void update(int pos, ll value){
        for(pos++; pos <= siz; pos += pos & (-pos)) dat[pos] += value;
    }

    // [left, right)
    ll query(int left, int right){
        return calc(right) - calc(left);
    }

    private :
    ll calc(int right){
        ll res = 0;
        for(; right > 0; right -= right & (-right)) res += dat[right];
        return res;
    }
};