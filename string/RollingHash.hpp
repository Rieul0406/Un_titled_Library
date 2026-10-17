/*
 * ローリングハッシュ（更新可能・2重ハッシュ）
 *
 * 使い方:
 *   RollingHash rh(s);                // 文字列 s で初期化  O(N log N)
 *   pll h = rh.get(l, r);             // s[l..r) のハッシュ値  O(log N)
 *   pll ha = rh.get_all();            // s 全体のハッシュ値  O(1)
 *   pll hm = rh.merge(h1, h2, len2);  // 長さ len2 の h2 を h1 の後ろに連結したハッシュ  O(1)
 *   pll hc = rh.change(i, c, update); // s[i] を c に変えた場合のハッシュ  O(log N)
 *   pll hc = rh.change(i, c);         // update=false なら文字列を実際には変更しない  O(1)
 *
 * 計算量:
 *   コンストラクタ : O(N log N)
 *   get(l, r)      : O(log N)
 *   get_all()      : O(1)
 *   merge()        : O(1)
 *   change()       : update=true で O(log N), update=false で O(1)
 */

#pragma once

#include <array>
#include <vector>
#include <utility>
#include <string>
#include <chrono>
#include <random>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

class RollingHash{
private:
    const array<ll, 2> mods = {1000000007LL, 1000000009LL};

    struct BIT{
        int n;
        vector<ll> bit;

        BIT() {}

        BIT(int n) : n(n), bit(n + 1, 0) {}

        // O(log N)
        void add(int idx, ll val){
            for(++idx; idx <= n; idx += idx & -idx){
                bit[idx] += val;
            }
        }

        // O(log N)
        ll sum(int r) const {
            ll ret = 0;
            for(; r > 0; r -= r & -r){
                ret += bit[r];
            }
            return ret;
        }

        // O(log N)
        ll sum(int l, int r) const {
            return sum(r) - sum(l);
        }
    };

    array<ll, 2> base;
    int n;
    string s;
    array<BIT, 2> bit;
    array<vector<ll>, 2> p;
    array<vector<ll>, 2> invp;
    pll all_h;

public:
    // O(N log N)
    RollingHash(const string& s) : n(s.size()), s(s){
        ll seed = std::chrono::steady_clock::now().time_since_epoch().count();
        std::mt19937_64 rng(seed);
        for(int k = 0; k < 2; k++){
            std::uniform_int_distribution<ll> dist(256, mods[k] - 2);
            base[k] = dist(rng);
            bit[k] = BIT(n);
            p[k].assign(n + 1, 1);
            invp[k].assign(n + 1, 1);
            for(int i = 0; i < n; i++){
                p[k][i + 1] = p[k][i] * base[k] % mods[k];
            }
            ll inv_base = 1;
            ll a = base[k];
            ll b = mods[k] - 2;
            while(b){
                if(b & 1){
                    inv_base = inv_base * a % mods[k];
                }
                a = a * a % mods[k];
                b >>= 1;
            }
            for(int i = 0; i < n; i++){
                invp[k][i + 1] = invp[k][i] * inv_base % mods[k];
            }
            for(int i = 0; i < n; i++){
                ll val = static_cast<ll>(s[i]);
                ll contribution = val * p[k][n - 1 - i] % mods[k];
                bit[k].add(i, contribution);
            }
        }
        // 全体ハッシュを正しく計算（get_all() は all_h を返すだけなのでここで初期化）
        all_h = get(0, n);
    }

    // O(log N)
    pll get(int l, int r) const {
        array<ll, 2> ret;
        for(int k = 0; k < 2; k++){
            ll h = bit[k].sum(l, r) % mods[k];
            if(h < 0){
                h += mods[k];
            }
            // h = substring_hash * base^(n-r)
            // → substring_hash = h * base^(-(n-r))
            ret[k] = h * invp[k][n - r] % mods[k];
        }
        return make_pair(ret[0], ret[1]);
    }

    // O(1)
    pll merge(pll h1, pll h2, int h2_len) const {
        array<ll, 2> ret;
        array<ll, 2> h1_arr = {h1.first, h1.second};
        array<ll, 2> h2_arr = {h2.first, h2.second};
        for(int k = 0; k < 2; k++){
            ret[k] = (h1_arr[k] * p[k][h2_len] + h2_arr[k]) % mods[k];
        }
        return make_pair(ret[0], ret[1]);
    }
    // update = true  : 実際に文字列を変更する   O(log N)
    // update = false : 変更した場合のハッシュだけ返す O(1)
    pll change(int idx, char new_char, bool update = true){
        char old_char = s[idx];
        array<ll, 2> ret = {all_h.first, all_h.second};
        for(int k = 0; k < 2; k++){
            ll diff = static_cast<ll>(new_char) - static_cast<ll>(old_char);
            ll change = diff * p[k][n - 1 - idx] % mods[k];
            ret[k] += change;
            ret[k] %= mods[k];
            if(ret[k] < 0){
                ret[k] += mods[k];
            }
            if(update){
                bit[k].add(idx, change);
            }
        }
        if(update){
            s[idx] = new_char;
            all_h = make_pair(ret[0], ret[1]);
        }
        return make_pair(ret[0], ret[1]);
    }

    // O(1)
    pll get_all() const {
        return all_h;
    }
};