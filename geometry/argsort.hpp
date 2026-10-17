/*
 * 偏角ソート (Angle Sort)
 *
 * 原点を中心として、2次元整数座標ベクトルの集合を偏角順（[0, 2π) の順）にソートする。
 * 偏角が等しい場合は外積の符号で比較（正側が先）。
 *
 * 使い方:
 *   vector<pii> pts;
 *   angle_sort(pts);   // pts を偏角の昇順にソート（in-place）
 *
 * 計算量:
 *   O(N log N)
 */

#pragma once

#include <utility>
#include <algorithm>
#include <vector>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

ll cross (const pii& a, const pii& b){
    return (ll)a.first * b.second - (ll)a.second * b.first;
}
bool cmp(const pii& a, const pii& b){
    int ah = (a.second < 0 || (a.second == 0 && a.first < 0));
    int bh = (b.second < 0 || (b.second == 0 && b.first < 0));
    if(ah != bh) return ah < bh;
    return cross(a, b) > 0;
}
void angle_sort(vector<pii>& points){
    sort(points.begin(), points.end(), cmp);
    return;
}