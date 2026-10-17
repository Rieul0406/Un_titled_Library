/*
 * 多角形の面積（Shoelace Formula）
 *
 * 整数座標で与えられた多角形の頂点リストから面積を求める（符号付き面積の絶対値 / 2）。
 * 頂点は時計回り・反時計回りどちらでも正しく動作する。
 *
 * 使い方:
 *   vector<pii> poly;
 *   ld area = quad(poly);   // 面積を返す（long double）
 *
 * 計算量:
 *   O(N)
 */

#pragma once

#include <vector>
#include <utility>
#include <cstdlib>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;

ld quad (vector<pii> xy){
    int siz = xy.size();
    ll sum = 0;
    for(int i = 0; i < siz; i++){
        sum += (ll)xy[i].first * xy[(i + 1) % siz].second;
        sum -= (ll)xy[(i + 1) % siz].first * xy[i].second;
    }
    if(sum < 0) sum = llabs(sum);
    ld res = sum; res /= 2.0;
    return res;
}
