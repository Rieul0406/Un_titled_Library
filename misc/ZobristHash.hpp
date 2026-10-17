/*
 * Zobrist Hash（カスタムハッシュ関数）
 *
 * 使い方:
 *   unordered_map<uint64_t, int, custom_hash> mp;
 *   unordered_set<uint64_t, custom_hash> st;
 *
 * 計算量:
 *   operator() : O(1)
 */

#pragma once

#include <cstdint>
#include <chrono>
#include <unordered_map>
#include <unordered_set>
using namespace std;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator() (uint64_t x) const {
        static const uint64_t FIXED_RANDOM =    
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
