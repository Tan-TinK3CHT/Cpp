#include<bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops,no-stack-protector")
#pragma GCC target("sse4,avx2,fma")
using namespace std;
#define el inp<<'\n'
#define pb push_back
#define all(x) x.begin(), x.end()
#define	f0(i,n) for(int i=0;i<n;i++)
#define f1(i,n) for(int i=1;i<=n;i++)
typedef long long ll;
const int btest = 2;
const int etest = 300;

ll Rand(ll l, ll h)
{
    return l + ((ll)rand() * (RAND_MAX + 1) * (RAND_MAX + 1) * (RAND_MAX + 1) +
                (ll)rand() * (RAND_MAX + 1) * (RAND_MAX + 1) +
                (ll)rand() * (RAND_MAX + 1) +
                rand()) % (h - l + 1);
}
#define maxn 2003
//#define A 1000000000
const ll A = 1e18;
const ll H = 1e12;
const ll N = 1e3;
const ll Q = 1e5;
const ll X = 2e9;
const ll K = 1e9;
const ll W = 1e6;
const ll T = 10;
map<ll, ll> M;
// vector<long long> vt;
mt19937 rd(20092007);


void sub1(int x) {
    ofstream os;
    ofstream inp((to_string(x) + ".inp").c_str());
    ll t, n, l, r, m, a, b, q, k;
    
    vector<int> vt(4);

    for(auto &i : vt) 
        i = Rand(1, 1e4);

    sort(all(vt));

    for(auto i : vt)
        inp << i << " "; inp << '\n';
    
    k = Rand(1, 201);

    inp << k;
}

void sub2(int x) {
    ofstream os;
    ofstream inp((to_string(x) + ".inp").c_str());
    ll t, n, l, r, m, a, q, k;
    vector<int> vt(4);

    for(auto &i : vt) 
        i = Rand(1, 1e4);

    sort(all(vt));

    for(auto i : vt)
        inp << i << " "; inp << '\n';
    
    k = Rand(1, Q);

    inp << k;
}

void sub3(int x) {
    ofstream os;
    ofstream inp((to_string(x) + ".inp").c_str());
    ll t, n, l, r, m, a, b, q, k;
    vector<int> vt(4);

    for(auto &i : vt) 
        i = Rand(1, 1e4);

    sort(all(vt));

    for(auto i : vt)
        inp << i << " "; inp << '\n';
    
    k = Rand(1e8, 1e9);

    inp << k;
}
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //srand(time(NULL));
    srand(static_cast<unsigned int>(std::time(nullptr)));
    M[1] = 1;
    for (int i = btest; i <= etest; i++)
    {
        if(i <= 20)
            sub1(i);
        else if(i <= 150)
            sub2(i);
        else 
            sub3(i);
    }
    return 0;
}
