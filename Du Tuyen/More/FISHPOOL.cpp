//template simple for codeforces by ntannn_
//created in 19:07:59 - Sun 17/03/2024
#include <bits/stdc++.h>
#define int int64_t

using namespace std;

void solve() {
    int n, m, k;
    cin >> n >> k >> m;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) 
        cin >> a[i];
    for(int i = 2; i <= n; i++) {
        
    }
}

int32_t main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    #define task "FISHPOOL"
    if(fopen(task ".inp", "r")) {
        freopen(task ".inp", "r", stdin);
        freopen(task ".out", "w", stdout);
    }
    int test_case;
    for(cin >> test_case;test_case--;cout << '\n') 
        solve();
}