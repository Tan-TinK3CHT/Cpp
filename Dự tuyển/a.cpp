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

template <typename T> inline void read (T &x) {
    bool b = 0;
    char c;
    while (!isdigit (c = getchar()) && c != '-');
    if (c == '-') {
        c = getchar();
        b = 1;
    }
    x = c - 48;
    while (isdigit(c = getchar())) {
        x = (x << 3) + (x << 1) + (c - 48);
    }
    if (b) {
        x=-x;
    }
}

typedef long long ll;
typedef pair<int,int> ii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<ii> vii;
typedef unordered_map<int, int> umii;
typedef unordered_map<int, bool> umib;
typedef unordered_map<ll, ll> umll;

const int N = 1e6+10;
const ll MOD = 1e9+7;

ll n, k;
ll f[N];
vector<vi> vt;

bool cmp(vi x, vi y) {
    return x[x.size()-1] < y[y.size()-1]; 
}

void solve() {
    sort(all(vt), cmp);
    f[0] = INT_MIN;
    f[1] = vt[0][0];
    int ans = 1;
    for(int i = 0; i < vt.size(); i++) {
        for(int j = 0; j < vt[i].size(); j++) {
            if(f[1] > vt[i][j])
                f[1] = vt[i][j];
            else if(vt[i][j] > f[ans])
                f[++ans] = vt[i][j];
            else {
                ll t = lower_bound(f+1, f+1+ans, vt[i][j]) - f;
                f[t] = vt[i][j];
            }
        }
    }
}

void init() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> k;
        vi a;
        ll t, gmax = 0;
        for(int j = 1; j <= k; j++) {
            cin >> t;
            if(t > gmax) {
                t = gmax;
                a.eb(t);
            }
        }
        vt.eb(a);
    }
}

#define task "a"
int32_t main() {
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