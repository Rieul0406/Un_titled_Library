/*
 * 最大流（Ford-Fulkerson 法、DFS ベース）
 * 有向グラフ上の最大流を求める。頂点番号は 1-indexed。
 *
 * 使い方:
 *   maximumflow mf;
 *   mf.init(n);             // 頂点数 n で初期化（頂点番号は 1〜n）
 *   mf.add_edge(a, b, c);  // a → b に容量 c の辺を追加
 *   ll flow = mf.max_flow(s, t);  // s から t への最大流を返す
 *
 * 注意:
 *   計算量は容量の大きさに依存する Ford-Fulkerson 法（O(EF)）。
 *   容量が大きい場合は Dinic 法等への切り替えを検討すること。
 *
 * 計算量:
 *   init      : O(N)
 *   add_edge  : O(1)
 *   max_flow  : O(E × F)  （E: 辺数, F: 最大流量）
 */

#pragma once

#include <vector>
using namespace std;
using ll = long long;
const ll INF = 1LL << 62;

struct edge{
    int to, rev;
    ll cap;
};

class maximumflow{
    public:
    int siz = 0;
    vector<bool> used;
    vector<vector<edge>> g;

    // 1-index
    void init(int n){
        siz = n;
        used.resize(n + 1);
        g.resize(n + 1);
    }

    void add_edge(int a, int b, ll c){
        int curg_a = g[a].size();
        int curg_b = g[b].size();
        g[a].push_back({b, curg_b, c});
        g[b].push_back({a, curg_a, 0});
    }

    ll dfs(int pos, int goal, ll f){
        if(pos == goal) return f;
        used[pos] = true;
        for(auto& [g_to, g_rev, g_cap] : g[pos]){
            if(g_cap == 0) continue;
            if(used[g_to]) continue;
            ll flow = dfs(g_to, goal, min(f, g_cap));
            if(flow >= 1){
                g_cap -= flow;
                g[g_to][g_rev].cap += flow;
                return flow;
            }
        }
        return 0;
    }

    ll max_flow(int s, int t){
        ll total_flow = 0;
        while(true){
            used.assign(siz + 1, false);
            ll f = dfs(s, t, INF);
            if(f == 0) break;
            total_flow += f;
        }
        return total_flow;
    }
};
