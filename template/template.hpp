#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
#ifdef LOCAL
#define debug(x) std::cerr << (x) << std::endl
#else
#define debug(x)
#endif
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pil = pair<int, ll>;
using pli = pair<ll, int>;
#define umap unordered_map
#define uset unordered_set
#define pque priority_queue
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
template<typename T> bool chmin(T& a, T b){if(a > b){a = b; return true;} return false;}
template<typename T> bool chmax(T& a, T b){if(a < b){a = b; return true;} return false;}
template<typename T> void addmod(T& a, T b, T mod){a = (a + mod) % mod, b = (b + mod) % mod; a += b; a %= mod; return;};
auto _ = []{ios::sync_with_stdio(false); cin.tie(nullptr); return 0;}();
const int dy[4] = {0, 1, 0, -1};
const int dx[4] = {1, 0, -1, 0};
const int ddy[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int ddx[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
const int inf = 1 << 30;
const ll INF = 1LL << 62;
const ll MOD = 998244353;
void retyn(bool flag){cout << (flag ? "Yes\n" : "No\n");}
int main(){
    
}