//使用is_prime(x)
//切记：一定要用快速乘不能用普通乘,基本上是一定会爆ll

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
ll quickpow(ll a,ll b,ll p)
{
    ll s=1;
    while (b)
    {
        if(b&1)s=mul(s,a,p);a=mul(a,a,p);
        b>>=1;
    }
    return s;
}
bool witness(ll a,ll b)
{
    if(a==b)return 1;
    ll s=b-1;
    int t=0;
    while(!(s&1))s>>=1,t++;
    ll x=quickpow(a,s,b);
    if(x==1)return 1;
    while(t--)
    {
        if(x==b-1)return 1;
        x=mul(x,x,b);
        if(x==1)return 0;
    }
    return 0;
}
bool is_prime(ll x)
{
    if(x<2)return 0;
    static int p[]={2,3,5,7,11,13,17,19,23,29,31};
    for(int i=0;i<=10;i++)if(!witness(p[i],x))return 0;
    return 1;
}
