#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long 
const long long R = 1e9+7;
const long long N = 1e6+9;
ll n, a[N], res = 0;
void slove(){
    sort(a+1, a+1+n);
    ll i = n;
    while((a[i]-(n-i)) != 0){
        res += a[i] - (n-i);
        i--;
    }
    cout<<res;
}
int main()
{
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin>>n;
    for(int i = 1; i <= n; i++){
        cin>>a[i];
    }
    slove();
}