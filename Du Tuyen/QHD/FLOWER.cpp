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

const int N = 1e6+10;
const ll MOD = 1e9+7;

ll n, k, a[N], lmin[N], dp[N];
deque<ll> dq;

void mintinhtien() {
    for(int i = 1; i <= n; i++) {
        while(!dq.empty() && dq.back() >= a[i])
            dq.pop_back();
        dq.pb(i);
        if(dq.front() + k <= i)
            dq.pop_front();
        if(i >= k)  
            lmin[i] = a[dq.front()];
        else 
            lmin[i] = 0;
    }
}

void solve() {
    dp[0] = 0; lmin[0] = 0; a[0] = 0;
    lmin[1] = 0; dp[1] = 0;   
    for(int i = 2; i <= n+1; i++) {
        dp[i] = lmin[i-2] + a[i];
        while(!dq.empty() && dp[dq.back()] > dp[i])
            dq.pop_back();
        dq.pb(i);
        if(dq.front() + k <= i)
            dq.pop_front();
        lmin[i] = dp[dq.front()];
    }
}

void init() {
    cin >> n >> k;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    a[n+1] = 0;
}
int32_t main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    if(fopen("FLOWER.inp","r")) {
        freopen("FLOWER.inp","r",stdin);
        freopen("FLOWER.out","w",stdout);
    }
    int test_case = 1;
    //cin >> test_case;
    while(test_case--) {
        init();
        solve();
    }
}