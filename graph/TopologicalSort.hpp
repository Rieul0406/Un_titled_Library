/*
 * トポロジカルソート（Kahn 法）
 *
 * DAG（有向非巡回グラフ）のトポロジカル順序を返す。
 * グラフにサイクルが存在する場合、返り値のサイズが N 未満になる。
 *
 * 使い方:
 *   vector<vector<int>> g(n); // 有向辺グラフ
 *   vector<int> order = toposort(g);
 *
 * 戻り値: トポロジカル順序の頂点番号列 vector<int>
 *
 * 計算量:
 *   O(V + E)
 */

#pragma once

#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define all(v) v.begin(), v.end()

vector<int> toposort(vector<vector<int>> g){
    int n = g.size();
    vector<int> deg(n);
    for(int from = 0; from < n; from++) for(auto& to : g[from]){
        deg[to]++;
    }
    queue<int> q;
    for(int i = 0; i < n; i++) if(deg[i] == 0) q.push(i);
    vector<int> res;
    while(!q.empty()){
        int v = q.front(); q.pop();
        res.push_back(v);
        for(auto& nex : g[v]){
            deg[nex]--;
            if(deg[nex] == 0) q.push(nex);
        }
    }
    return res;
};

