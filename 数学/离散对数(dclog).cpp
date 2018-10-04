//a^x==b(mod MOD),无解==-1

ll exgcd(ll a,ll b,ll &x,ll &y)
{
    ll d=a;
    if(b!=0)d=exgcd(b,a%b,y,x),y-=(a/b)*x;
    else x=1,y=0;
    return d;
}
ll inv(ll a,ll MOD)
{
    ll x,y,d=exgcd(a,MOD,x,y);
    return d==1?(x+MOD)%MOD:-1;
}
ll dclog(ll a,ll b,ll MOD)
{
    map<ll,ll>base;
    ll m=(ll)ceil(sqrt(MOD)+1),e=1,i,v;
    base[1]=0;
    for(i=0;i<m;i++,e=(e*a)%MOD)
    {
        if(!base.count(e))base[e]=i;
        if (b==e)return i;
    }
    v=inv(e,MOD);
    if (v==-1)return -1;
    for(i=0;i<=MOD/m;i++)
    {
        if(base[b])return (i*m+base[b])%(MOD-1);
        b=(b*v)%MOD;
    }
    return -1;
}
