/*
 * 強連結成分分解 (SCC, Kosaraju's algorithm)
 *
 * 有向グラフを強連結成分（SCC）に分解する。
 * 返り値はトポロジカル順序（DAG 上での順序）で SCC のリストを返す。
 * 各 SCC は頂点番号の集合（vector<int>）。
 *
 * 使い方:
 *   vector<vector<int>> g(n);
 *   auto sccs = scc(g);
 *   // sccs[i] : i 番目の SCC の頂点リスト（トポロジカル順）
 *
 * 戻り値: vector<vector<int>>（各要素が一つの SCC の頂点集合）
 *
 * 計算量:
 *   O(V + E)
 */

#pragma once

#include <vector>
#include <algorithm>
using namespace std;
#define all(v) v.begin(), v.end()

vector<vector<int>> scc(vector<vector<int>>& g){
    int n = g.size();
    vector<vector<int>> grev(n);
    for(int from = 0; from < n; from++) for(auto& to : g[from]){
        grev[to].push_back(from);
    }
    vector<bool> used(n, false);
    vector<int> record;
    auto dfs = [&](auto& self, int pos) -> void{
        used[pos] = true;
        for(auto& nex : g[pos]) if(!used[nex]) self(self, nex);
        record.push_back(pos);
    };
    for(int i = 0; i < n; i++) if(!used[i]) dfs(dfs, i);
    reverse(all(record));
    used.assign(n, false);
    vector<vector<int>> res;
    auto dfs2 = [&](auto& self, int pos) -> void{
        used[pos] = true;
        res.back().push_back(pos);
        for(auto& nex : grev[pos]) if(!used[nex]) self(self, nex);
    };
    for(auto& v : record) if(!used[v]){
        res.push_back({});
        dfs2(dfs2, v);
    }
    return res;
}
