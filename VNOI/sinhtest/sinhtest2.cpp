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
const int btest = 1; 
const int etest = 200; // so luong test
const int test_for_sub1 = 20; //% so luong test theo tung sub
const int test_for_sub2 = 20;
const int test_for_sub3 = 60;
const int s1 = double(etest) / 100.0 * test_for_sub1 * 1.0;
const int s2 = s1 + double(etest) / 100.0 * test_for_sub2 * 1.0;


ll Rand(ll l, ll h)
{
    return l + ((ll)rand() * (RAND_MAX + 1) * (RAND_MAX + 1) * (RAND_MAX + 1) +
                (ll)rand() * (RAND_MAX + 1) * (RAND_MAX + 1) +
                (ll)rand() * (RAND_MAX + 1) +
                rand()) % (h - l + 1);
}

mt19937_64 rd(static_cast<unsigned int>(std::time(nullptr)));
ll Randd(ll l, ll r) {
    return uniform_int_distribution<ll>(l,r) (rd);
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
vector<long long> vt;

int cal(int x, int n) {
    return double(n / 100.0) * x;
}

void sub1(int x) {
    ofstream os;
    ofstream inp((to_string(x) + ".inp").c_str());
    ll t, n, l, r, m, a, b, q, k;
    
    t = Rand(1, 30);
    if(x >= cal(80, s1))
        t = Rand(20, 30);
    inp << t << '\n';
    for(int i = 1; i <= t; i++) {
        l = Randd(1, A - W);
        if(i <= cal(60, t))
            l = Randd(1, W);
        r = Rand(l, l + W);
        inp << l << " " << r << '\n';
    }
}

void sub2(int x) {
    ofstream os;
    ofstream inp((to_string(x) + ".inp").c_str());
    ll t, n, l, r, m, a, q, k, b;
    
    t = Rand(1, 100);
    if(x >= cal(80, s2))
        t = Rand(80, 100);
    inp << t << '\n';
    for(int i = 1; i <= t; i++) {
        r = Rand(1, K);
        l = Randd(1, r - 10 * W);
        inp << l << " " << r << '\n';
    }
}

void sub3(int x) {
    ofstream os;
    ofstream inp((to_string(x) + ".inp").c_str());
    ll t, n, l, r, m, a, b, q, k;
    t = Rand(1, 100);
    inp << t << '\n';
    for(int i = 1; i <= t; i++) {
        r = Rand(1, A);
        l = Randd(1, r - 5e7);
        inp << l << " " << r << '\n';
    }
}
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //srand(time(NULL));
    srand(static_cast<unsigned int>(std::time(nullptr)));
    M[1] = 1;
    for (int i = btest; i <= etest; i++)
    {
        if(i <= s1)
            sub1(i);
        else if(i <= s2)
            sub2(i);
        else 
            sub3(i);
    }
    return 0;
}
