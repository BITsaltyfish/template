#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9+7;
int f[100010];
void inc(int &x,int y){x = x+y>=mod?x+y-mod:x+y;}
void dec(int &x,int y){x = x-y<0?x-y+mod:x-y;}
void solve()
{
    int n;scanf("%d",&n);
    printf("%d\n",f[n] );
}
int main(int argc, char const *argv[])
{
    f[0]=1;
    for(int i=1;i<=100000;i++)
    {
        for(int j=1,w=1;w<=i;w+=3*j+1,j++)
            if(j&1)inc(f[i],f[i-w]);
            else dec(f[i],f[i-w]);
        for(int j=1,w=2;w<=i;w+=3*j+2,j++)
            if(j&1)inc(f[i],f[i-w]);
            else dec(f[i],f[i-w]);
    }
    int t;scanf("%d",&t);
    while(t--)solve();
    return 0;
}