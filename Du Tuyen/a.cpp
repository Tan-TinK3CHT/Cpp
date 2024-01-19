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

ll n, a[N], ans, cnt;

void solve() {
    // if(n < 3)
    //     return cout << 0, void();
    a[0] = LLONG_MAX - 222;
    a[n + 1] = LLONG_MAX - 222;
    sort(a + 1, a + 1 + n);
    ans = 0, cnt = 0;
    for(int i = 1; i <= n + 1; i++) {
        if(a[i] != a[i - 1]) {
            ans += cnt * (cnt - 2) * (cnt - 1) / 6;
            cnt = 1;
            continue;
        }
        cnt += 1;
        ans += (cnt - 1) * (i - cnt);
    }
    cout << ans << '\n';
}

void init() {
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
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
    cin >> test_case;
    while(test_case--) {
        init();
        solve();
    }
    // cerr << '\n' << "\x1b[31mtime is: " << TIME << "\e[39m";
}