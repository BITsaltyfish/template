//r:余数,d:模数,n:方程数,下标0开始，无解返回-1
ll mul(ll a,ll b,ll p)
{
    if(b<0)b=(b%p+p)%p;
    a%=p;
    if(a<b)swap(a,b);
    ll ans=0;
    while(b)
    {
        if(b&1)ans=(ans+a)%p;
        a=(a+a)%p;
        b>>=1;
    }
    return ans;
}
ll exgcd(ll a,ll b,ll &x,ll &y)
{
    ll d=a;
    if(b!=0)d=exgcd(b,a%b,y,x),y-=(a/b)*x;
    else x=1,y=0;
    return d;
}
ll CRT(ll d[],ll r[],int n)
{
    ll M=1,Mi,ans=0;
    ll x,y,t;
    for(int i=0;i<n;i++)M*=d[i];
    for(int i=0;i<n;i++)
    {
        Mi=M/d[i];
        t=exgcd(Mi,d[i],x,y);
        ans=(ans+mul(mul(Mi,x,M),d[i],M))%M;
        //ans=(ans+Mi*x%M*d[i]%M)%M;
    }
    if(ans<0)ans+=M;
    return ans;
}
