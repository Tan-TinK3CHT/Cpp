#include<bits/stdc++.h>
//#pragma GCC optimize("O3,unroll-loops,no-stack-protector")
//#pragma GCC target("sse4,avx2,fma")
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define all(x) x.begin(), x.end()

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<ii> vii;
typedef vector<vi> vvi;

const int N = 1e6+10;
const ll MOD = 1e9+7;

ll n, k, a[N];
map<ll, ll> M;

void solve() {
    ll res = 0;
    for(int i = 1; i <= n; i++) {
        res += M[k - a[i]];
        if(k - a[i] == a[i])
            res--;
        if(k == 0) continue;
        res += M[-k - a[i]];
        if(-k - a[i] == a[i])
            res--;
        //cout << res << " ";
    }
    cout << res/2;
}

// 

void init() {
    cin >> n >> k;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        M[a[i]]++;
    }
}

#define task "LUCKY"
signed main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    if(fopen(task".inp","r")) {
        freopen(task".inp","r",stdin);
        freopen(task".out","w",stdout);
    }
    int test_case = 1;
    //cin >> test_case;
    while(test_case--) {
        init();
        solve();
    }
}