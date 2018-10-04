//r:余数,d:模数,n:方程数,下标0开始，无解返回-1
ll exgcd(ll a,ll b,ll &x,ll &y)
{
    ll d=a;
    if(b!=0)d=exgcd(b,a%b,y,x),y-=(a/b)*x;
    else x=1,y=0;
    return d;
}
ll CRT(ll* d,ll* r,int n)
{
    ll M=d[0],R=r[0],x,y,g,c,t;
    for(int i=1;i<n;i++)
    {
        g=exgcd(M,d[i],x,y);
        c=r[i]-R;t=d[i]/g;
        if(c%g!=0)return -1;
        x=(x*(c/g)%t+t)%t;
        R+=x*M;
        M=M/g*d[i];
    }
    R=(R%M+M)%M;
    return R;
}
