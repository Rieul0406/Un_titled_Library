/*
 * Manacher のアルゴリズム（最長回文の半径を O(N) で計算）
 *
 * 使い方:
 *   vector<int> r = manacher(S);        // 各文字を中心とする最長回文の半径（奇数長回文のみ、サイズ |S|）
 *   vector<int> r = manacher(S, false); // ダミー文字を挿入して偶数長回文も考慮した半径（サイズ 2|S| + 1）
 *
 * 計算量:
 *   manacher(S, flag) : O(N) （N = |S|）
 */

#pragma once

#include <vector>
#include <string>
using namespace std;

string adddummy(const string &S){
    string res;
    res.push_back('#');
    for(auto& i : S){
        res.push_back(i);
        res.push_back('#');
    }
    return res;
}

vector<int> manacher(const string &S, bool flag = true){
    string str = flag ? S : adddummy(S);
    int siz = str.size();
    vector<int> res(siz);
    int left = 0, right = 0;
    while(right < siz){
        while(right - left >= 0 && right + left < siz && str[right - left] == str[right + left]){
            left++;
        }
        res[right] = left;
        int nex = 1;
        while(right - nex >= 0 && nex + res[right - nex] < left){
            res[right + nex] = res[right - nex];
            nex++;
        }
        right += nex;
        left -= nex;
    }
    return res;
}
