//质因子分解，小数据用筛法直接判，大数据用pollard_rho
//factor[i]是含有多少个质因子i
//map<ll,int>::iterator c,c->first表示质因子，c->second表示次方
//wrk.out(p+1,q+1,len)可以导出分解结果
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define maxn_for_division 1000001
#define rep_times 20
bool is_prime[maxn_for_division];
vector<int>prime;
inline void get_prime()
{
    for(int i=0;i<maxn_for_division;i++)is_prime[i]=1;
    is_prime[0]=is_prime[1]=0;
    for(int i=2;i<maxn_for_division;i++)
        if (is_prime[i])
        {
            prime.push_back(i);
            for (int j=i;j<maxn_for_division;j+=i)is_prime[j]=0;
        }
}

inline ll gcd(ll a,ll b){if (!b)return a;return gcd(b,a%b);}
inline ll mod_mul(ll a, ll b, ll p)
{
    ll ans=0ll;
    a%=p,b%=p;
    if (a>b)swap(a,b);
    while (b)
    {
        if (b&1)ans=(ans+a)%p;
        a=(a+a)%p;
        b>>=1;
    }
    return ans;
}
ll mod_pow(ll a,ll b,ll p)
{
    ll ans=1ll;
    a%=p;
    while (b)
    {
        if (b&1)ans=mod_mul(ans,a,p);
        a=mod_mul(a,a,p);
        b>>=1;
    }
    return ans;
}
struct get_factor{
    ll n;
    map<ll,int>factor;
    bool witness(ll a,ll n)
    {
        ll m=n-1;
        int j=0;
        while(!(m&1))j++,m>>=1;
        ll x=mod_pow(a,m,n);
        if (x==1||x==n-1)return 0;
        while(j--)
        {
            x=mod_mul(x,x,n);
            if(x==n-1)return 0;
        }
        return 1;
    }
    bool Miller_Rabin(ll n)//判断n是否为素数
    {
        srand(time(0));
        if(n<2)return 0;
        if(n==2)return 1;
        if (!(n&1))return 0;
        for(int i=0;i<rep_times;i++)
        {
            ll a=rand()%(n-1)+1;
            if (witness(a,n))return 0;
        }
        return 1;
    }
    #undef rep_times
    ll Pollard_Rho(ll n,int c)
    {
        ll x=2,y=2,d=1;
        while (d==1)
        {
            x=mod_mul(x,x,n)+c;
            y=mod_mul(y,y,n)+c;
            y=mod_mul(y,y,n)+c;
            d=gcd((x-y>=0?x-y:y-x),n);
        }
        if (d==n)return Pollard_Rho(n,c+1);
        return d;
    }
    bool Is_Prime(ll n){return n<maxn_for_division&&is_prime[n]||n>=maxn_for_division&&Miller_Rabin(n);}
    void Find_Factor(ll n)
    {
        if (n==1ll){factor[1ll]=1;return;}
        if (Is_Prime(n)){factor[n]++;return;}
        for (int i=0;i<prime.size()&&prime[i]<=n;i++)
            if (n%prime[i]==0)
            {
                while (n%prime[i]==0)
                {
                    factor[prime[i]]++;
                    n/=prime[i];
                }
            }
        if (n!=1)
        {
            if (Is_Prime(n))factor[n]++;
            else
            {
                ll p=Pollard_Rho(n,1);
                Find_Factor(p);
                Find_Factor(n/p);
            }
        }
    }
    inline void calc(){factor.clear();Find_Factor(n);}
    inline void out(ll* p,int* q,int &len)//导出质因子分解结果，p数组放质因子，q数组放次数，len从1开始
    {
        len=0;
        for(map<ll,int>::iterator c=factor.begin();c!=factor.end();)
        {
            p[++len]=c->first;q[len]=c->second;
            c++;
        }
    }
    inline void put()//for debug
    {
        printf("%lld = ",n);
        for(map<ll,int>::iterator c=factor.begin();c!=factor.end();)
        {
            printf("%lld^%d",c->first,c->second);
            if((++c)!=factor.end())printf("*");
        }
        puts("");
    }
}wrk;
int main()
{
    get_prime();
    while(~scanf("%lld",&wrk.n))
    {
        wrk.calc();
        wrk.put();
    }
}
