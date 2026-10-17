/*
 * 拡張ユークリッドの互除法 (Extended GCD)
 *
 * ax + by = gcd(a, b) を満たす (x, y) を求める。
 * 戻り値は {x, y}（pair<ll, ll>）。
 * gcd(a, b) = a*ret.first + b*ret.second が成立する。
 *
 * 使い方:
 *   auto [x, y] = exgcd(a, b);   // ax + by = gcd(a,b) の解 (x,y) を返す
 *
 * 計算量:
 *   O(log(min(a, b)))
 */

#pragma once

#include <utility>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

pll exgcd(ll a, ll b){
    if(b == 0) return {1, 0};
    auto [y, x] = exgcd(b, a % b);
    y -= a / b * x;
    return {x, y};
}
