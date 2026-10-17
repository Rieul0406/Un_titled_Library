/*
 * Segment Tree（モノイド上の区間クエリ）
 *
 * デフォルトは区間和。op() と val を書き換えることで区間最大・最小などに対応。
 *
 * 使い方:
 *   segmenttree seg(n);              // サイズ n で初期化
 *   segmenttree seg(vec);            // vector で初期化
 *   seg.update(pos, value);          // a[pos] = value にセット (0-indexed)
 *   seg.add(pos, value);             // a[pos] += value
 *   ll v = seg.query(l, r);          // op(a[l], ..., a[r-1]) を返す  [l, r)
 *
 * 計算量:
 *   コンストラクタ : O(N)
 *   update / add   : O(log N)
 *   query          : O(log N)
 */

#pragma once

#include <vector>
using namespace std;
using ll = long long;

class segmenttree{
    public:
    vector<ll> data;
    ll siz;
    ll val = 0; // 区間和
    // ll val = -INF; // 区間最大値
    // ll val = INF; // 区間最小値

    ll op(ll a, ll b){
        return a + b; // 区間和
        // return max(a, b); // 区間最大値
        // return min(a, b); // 区間最小値
    }

    segmenttree(){}

    segmenttree(int n){
        init(n);
    }

    segmenttree(vector<ll> vec){
        int n = vec.size();
        init(n);
        for(int i = 0; i < n; i++) data[siz + i] = vec[i];
        for(int i = siz - 1; i >= 1; i--) data[i] = op(data[i * 2], data[i * 2 + 1]);
    }

    void init(ll n){
        siz = 1LL;
        while(n > siz) siz <<= 1;
        data.resize(siz * 2, val);
    }

    void update(ll pos, ll value){
        pos += siz;
        data[pos] = value;
        while(pos >= 2){
            pos /= 2;
            data[pos] = op(data[pos * 2], data[pos * 2 + 1]);
        }
    }

    void add(ll pos, ll value){
        pos += siz;
        data[pos] += value;
        while(pos >= 2){
            pos /= 2;
            data[pos] = op(data[pos * 2], data[pos * 2 + 1]);
        }
    }

    // [left, right) の区間クエリ
    ll query(ll left, ll right){
        return _query(left, right, 0, siz, 1);
    }

    private:
    ll _query(ll left, ll right, ll open, ll close, ll now){
        if(right <= open || close <= left) return val;
        if(left <= open && close <= right) return data[now];
        ll middle = (open + close) / 2;
        ll ansl = _query(left, right, open, middle, now * 2);
        ll ansr = _query(left, right, middle, close, now * 2 + 1);
        return op(ansl, ansr);
    }
};