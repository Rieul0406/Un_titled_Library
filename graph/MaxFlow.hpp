#pragma once

#include <vector>
using namespace std;

struct edge{
    int to, cap, rev;
};

class maximumflow{
    public:
    int siz = 0;
    vector<bool> used;
    vector<vector<edge>> g;
    
    // 1 - index
    void init(int n){
        siz = n;
        used.resize(n + 1);
        g.resize(n + 1);
    }

    // 辺、辺、重み
    void add_edge(int a, int b, int c){
        int curg_a = g[a].size();
        int curg_b = g[b].size();
        g[a].push_back({b, c, curg_b});
        g[b].push_back({a, 0, curg_a});
    }

    int dfs (int pos, int goal, int f){
        if(pos == goal) return f;
        used[pos] = true;
        for(auto& [g_to, g_cap, g_rev] : g[pos]){
            if(g_cap == 0) continue;
            if(used[g_to]) continue;
            int flow = dfs(g_to, goal, min(f, g_cap));
            if(flow >= 1){
                g_cap -= flow;
                g[g_to][g_rev].cap += flow;
                return flow;
            }
        }
        return 0;
    }

    int max_flow(int s, int t){
        int total_flow = 0;
        while(true){
            used.assign(siz + 1, false);
            int f = dfs(s, t, 1e9);
            if(f == 0) break;
            total_flow += f;
        }
        return total_flow;
    }
};