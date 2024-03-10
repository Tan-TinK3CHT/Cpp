#include <bits/stdc++.h>
using namespace std;
struct ii //Th�ng tin di k�m v?i m?i d?u m�t i
{
    int val; //Toa do
    int kind; //��ng/mo {1/0}
    int conf; //So hieu cuoc hop
};
ii ID[1000001];
int n,u,v;
int m; //Luu so luong ph�ng can d�ng, cung ch�nh l� so hieu ph�ng max
int meet[1000001];
vector <int> room[1000001]; //V� 1 ph�ng c� the to chuc nhieu cuoc hop, n�n d�ng Vector
stack <int> s;

bool cmp(const ii&x, const ii &y)
{
    if (x.val==y.val) return x.kind>y.kind;
    else return x.val<y.val;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    freopen("ROOMS.inp","r",stdin);
    freopen("ROOMS.out","w",stdout);
    cin>>n;
    for (int i=1;i<=n;i++)
    {
        cin>>u>>v;
        ID[i*2-1].val=u;
        ID[i*2].kind=0;
        ID[i*2-1].conf=i;

        ID[i*2].val=v;
        ID[i*2].kind=1;
        ID[i*2].conf=i;

    }
   for (int i=n;i>=1;i--) s.push(i);//�ay n ph�ng v�o Stack

    sort (ID+1,ID+2*n+1,cmp);

    for (int i=1;i<=2*n;i++)
    {
        if (ID[i].kind==0) //Neu gap toa do l� diem bat dau 1 cuoc hop
        {
            int meetNum=s.top(); s.pop(); //Lay 1 ph�ng trong Stack
            meet[ID[i].conf]=meetNum; // G�n cho cuoc hop conf

            room[meetNum].push_back(ID[i].conf); //Bo sung cuoc hop v�o ph�ng meetNum, ch� � 1 ph�ng c� the d�ng cho nhieu cuoc hop
            m=max(m,meetNum);//X�c dinh so hieu ph�ng max
        }
        else s.push(meet[ID[i].conf]); //Neu gap toa do l� diem ket th�c 1 cuoc hop, th� tra ph�ng lai cho Stack
    }
    cout<<m<<'\n';
    for (int i=1;i<=m;i++)
    {
        for (int j=0;j<room[i].size();j++) cout<<room[i][j]<<" ";
        cout<<'\n';
    }
}
