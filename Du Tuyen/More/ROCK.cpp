//Written by: ntannn_
//created in 14:38:01 - Fri 26/04/2024
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

const int N = 5e5 + 10;
const ll MOD = 1e9 + 7;

ll n, m, L, a[N], ans = INT_MAX;
priority_queue<pll> q;
map<ll, bool> M;

struct cmp {
    bool operator() (pair<int, int> x, pair<int, int> y) {
        return (x.fi < y.fi || (x.fi == y.fi && a[y.se + 1] - a[y.se] > a[x.se + 1] - a[x.se]));  
    }
};

void solve() {
    sort(a + 1, a + 1 + n);

    for(int i = 1; i <= n; i++) {
        q.push(mp(a[i] - a[i - 1], i));
        if(q.size() > m)
            q.pop();
    }
    
    while(!q.empty()) {
        M[q.top().se] = 1;
        // cout << q.top().fi << " " << q.top().se << '\n';
        q.pop();    
    }
    // for(int i = 1; i <= n; i++) 
    //     cout << a[i] << " " ; cout << '\n';
    for(int i = 1; i <= n; i++) {
        if(M[i])
            a[i] = a[i - 1];
        else {
            ans = min(ans, a[i] - a[i - 1]);
            // cout << i << " " << a[i] - a[i - 1] << " " << ans << '\n';
        }
    }

    cout << ans;
}

void init() {
    cin >> L >> n >> m;
    a[0] = 0;
    a[n + 1] = L;
    for(int i = 1; i <= n; i++) 
        cin >> a[i];
}

#define task "ROCK"
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