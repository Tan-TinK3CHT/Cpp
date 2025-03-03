//Written by: ntannn_
//created in 17:54:03 - Tue 11/06/2024
#include <bits/stdc++.h>
// #pragma GCC optimize("O3,unroll-loops,no-stack-protector")
// #pragma GCC target("sse4,avx2,fma")
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define all(x) x.begin(), x.end()
#define TIME (1.0 * clock() / CLOCKS_PER_SEC)

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<ii> vii;
typedef vector<vi> vvi;

const int N = 2e5 + 10;
const ll MOD = 1e9 + 7;

struct pt {
    int a, b, p;
};

pt f[N];
int n;
ll dp[2 * N];
map<int, int> M;
vector<vector<pair<int, int>>> c;

void solve() {
    int d = 0;
    for(auto &i : M) 
        i.se = ++d;
    
    c.resize(d + 2, vector<pair<int, int>>());

    for(int i = 1; i <= n; i++) {
        f[i].a = M[f[i].a];
        f[i].b = M[f[i].b];
        c[f[i].b].push_back({f[i].a, f[i].p});
    }

    for(int i = 1; i <= d; i++) {
        dp[i] = dp[i - 1];
        for(auto j : c[i]) 
            dp[i] = max(dp[i], dp[j.fi - 1] + j.se);
    }

    cout << dp[d];
}

void init() {
    cin >> n;
    for(int i = 1; i <= n; i++) 
        cin >> f[i].a >> f[i].b >> f[i].p,
        M[f[i].a] = 1, M[f[i].b] = 1;
}

#define task "1140"
signed main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    if(fopen(task ".inp", "r")) {
        freopen(task ".inp", "r", stdin);
        freopen(task ".out", "w", stdout);
    }
    int test_case = 1;
    //cin >> test_case;
    while(test_case--) {
        init();
        solve();
    }
    // cerr << '\n' << "\x1b[31mtime is: " << TIME << "\e[39m";
}