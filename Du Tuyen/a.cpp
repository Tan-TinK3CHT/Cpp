//template for some simple code by ntannn_
//created in 20:38:27 - Thu 15/02/2024
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

ll n, Q, tree[N], lz[N];

void update(int id, int l, int r, int u, int v) {
    if(lz[id] != 0) {
        lz[id] %= 2;
        if(lz[id])
            tree[id] = (r - l + 1) - tree[id];
        if(l != r) {
            lz[id * 2] += lz[id];
            lz[id * 2 + 1] += lz[id];
        }
        lz[id] = 0;
    }
    if(l > v || r < u)
        return;
    if(u <= l && r <= v) {
        tree[id] = (r - l + 1) - tree[id];
        lz[id * 2]++;
        lz[id * 2 + 1]++;
        return;
    }
    int mid = (l + r) / 2;
    update(id * 2, l, mid, u, v);
    update(id * 2 + 1, mid + 1, r, u, v);
    tree[id] = tree[id*2] + tree[id*2+1];
}

ll get(int id, int l, int r, int u, int v) {
    if(lz[id] != 0) {
        lz[id] %= 2;
        if(lz[id])
            tree[id] = (r - l + 1) - tree[id];
        if(l != r) {
            lz[id * 2] += lz[id];
            lz[id * 2 + 1] += lz[id];
        }
        lz[id] = 0;
    }
    if(l > v || r < u)
        return 0;
    if(u <= l && r <= v) 
        return tree[id];
    int mid = (l + r) / 2;
    return get(id * 2, l, mid, u, v) + get(id * 2 + 1, mid + 1, r, u, v);
}

void solve() {
    while(Q--) {
        int c, l, r;
        cin >> c >> l >> r;
        if(!c) 
            update(1, 1, n, l+1, r+1);
        else 
            cout << get(1, 1, n, l+1, r+1) << '\n';
    }
}

void init() {
    cin >> n >> Q;
}

#define task "a"
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
