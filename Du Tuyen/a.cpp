//template for codeforces by ntannn_
//created in 22:41:29 - Thu 29/02/2024
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
typedef pair<ll, ll> pll;

const int N = 3e5 + 10;
const ll MOD = 1e9 + 7;

ll n;

bool check(ll x) {
    if(x < 2)
        return false;
    for(int i = 2; i <= sqrt(x); i++)
        if(x%i == 0)
            return false;
    return true;
}

void  solve() {
    while(!check(n--));
    cout << n + 1;
}

void init() {
    cin >> n;
}

signed main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int test_case;
    for(cin >> test_case;test_case--;cout << '\n') {
        init();
        solve();
    }
    // cerr << '\n' << "\x1b[31mtime is: " << TIME << "\e[39m";
}