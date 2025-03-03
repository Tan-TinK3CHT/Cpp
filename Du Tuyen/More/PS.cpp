// Written by: ntannn_
// created in 10:27:02 - Mon 18/03/2024
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

const int N = 1e6 + 10;
const ll MOD = 1e9 + 7;

ll n, s[N], a[N], smin[N];
pll ans ;

void solve() {
    int i = n, k = smin[n];
    if(k == 0)
        ans.se = n;
    while(k >= 0) {
        while(k < i && s[k] >= s[i])
            i--;
        if(i - k > ans.se - ans.fi)
            ans = {k, i};
        if(k == 0)
            break;
        k = smin[k - 1];
    }
    cout << ans.fi + 1 << " " << ans.se;
}

void init() {
    cin >> n;
    s[0] = 0, smin[0] = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        s[i] = s[i - 1] + a[i];
        smin[i] = (s[i] < s[smin[i - 1]] ? i : smin[i - 1]);
    }
}

#define task "PS"
signed main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    if(fopen(task ".inp", "r")) {
        freopen(task ".inp", "r", stdin);
        freopen(task ".out", "w", stdout);
    }
    int test_case = 1;
    // cin >> test_case;
    while(test_case--) {
        init();
        solve();
    }
    // cerr << '\n' << "\x1b[31mtime is: " << TIME << "\e[39m";
}