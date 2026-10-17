/*
 * Union-Find
 *
 * パスの圧縮とサイズによるマージを実装。
 *
 * 使い方:
 *   UnionFind uf(n);        // n 要素で初期化
 *   uf.unite(u, v);         // u と v の属する集合を合併
 *   bool b = uf.same(u, v); // u と v が同じ集合に属するか（true/false）
 *   int r = uf.root(x);      // x の根（代表元）を返す
 *
 * 計算量:
 *   コンストラクタ : O(N)
 *   unite          : O(α(N)) ≈ O(1)
 *   same / root    : O(α(N)) ≈ O(1)
 */

#pragma once

#include <vector>
using namespace std;

class UnionFind{
    public:
    vector<int> former;
    vector<int> siz;
    
    UnionFind(int n){init(n);}

    void init(int n){
        former.resize(n, -1);
        siz.resize(n, 1);
    }

    int root(int x){
        if(former[x] == -1) return x;
        else return former[x] = root(former[x]);
    }

    void unite(int u, int v){
        int rootu = root(u);
        int rootv = root(v);
        if(rootu == rootv) return;
        if(siz[rootu] > siz[rootv]) swap(rootu, rootv);
        former[rootu] = rootv;
        siz[rootv] += siz[rootu];
    }

    [[nodiscard]]bool same(int u, int v){
        return root(u) == root(v);
    }
};