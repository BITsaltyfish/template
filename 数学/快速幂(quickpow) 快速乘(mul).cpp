//===========================快速幂=============================================


ll quickpow(ll a,ll b,ll p)
{
    ll s=1;
    while (b)
    {
        if(b&1)s=mul(s,a,p);a=mul(a,a,p);
        //if(b&1)s=s*a%p;a=a*a%p;
        b>>=1;
    }
    return s;
}

//===========================快速乘 强板========================================

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

//===========================快速乘 黄板========================================

ll mul(ll x,ll n,ll MOD)
{
    ll res=x*n-(ll)((long double)x*n/MOD+0.5)*MOD;
    while(res<0)res+=MOD;
    while(res>=MOD) res-=MOD;
    return res;
}