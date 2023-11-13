#include<bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops,no-stack-protector")
#pragma GCC target("sse4,avx2,fma")
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

const int N = 2e4+10;
const ll MOD = 1e9;

int m, n, a[201][N];
ll ans = 0;

void solve(){
    for(int i = 1; i < m; i++) {
        for(int j = i+1; j <= m; j++) {
            int l = 0, r = 0, pos = 0;
            while(l <= n && r <= n) {
                if(a[i][l+1] <= a[j][r+1]){
                    l++;
                    pos++;
                    if(pos == n) {
                        ans += a[i][l];
                        //cout << i << " " << j << " " << l << " " << r << '\n';
                        break;
                    }
                }
                else {
                    r++;
                    pos++;
                    if(pos == n) {
                        ans += a[j][r];
                        break;
                    }
                }
            }
        }
    }
    cout << ans%MOD ;
}

void init(){
    read(m), read(n);
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++)
            read(a[i][j]);
    }
}
#define task "TV"
int32_t main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    if(fopen(task".inp","r")){
        freopen(task".inp","r",stdin);
        freopen(task".out","w",stdout);
    }
    int test_case = 1;
    //cin >> test_case;
    while(test_case--){
        init();
        solve();
    }
}