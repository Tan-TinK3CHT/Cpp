//template for some simple code by ntannn_
//created in 19:43:51 - Sun 28/01/2024
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

string s;
map<char, int> m;

void sub12() {
    m.clear();
    ll d = 0, ans = 0;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == 'a') 
            d++;
        else if(s[i] == 'b')
            d--;
        else 
            m.clear();
        ans += m[d];
        m[d]++;
    }
    cout << ans;
}

void sub3() {
    ll ans = 0;
    for(int i = 0; i < s.size(); i++) {
        ll a = 0, b = 0;
        if(s[i] == 'a') a++;
        else if(s[i] == 'b') b++;
        else if(s[i] != 'c') continue;
        for(int j = i+1; j < s.size(); j++) {
            if(s[j] == 'a') a++;
            else if(s[i] == 'b') b++;
            else if(s[i] != 'c') break;
            if(a == b)
                ans++;
        }
    }
    cout << ans;
}

void init() {
    cin >> s;
    for(auto i : s) 
        m[i]++;
    if(m['a'] + m['b'] + m['d'] == s.size()) {
        sub12();
        cerr << "sub12";
    }
    else if(s.size() <= 1e3)
        sub3();
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
        // solve();
    }
    // cerr << '\n' << "\x1b[31mtime is: " << TIME << "\e[39m";
}