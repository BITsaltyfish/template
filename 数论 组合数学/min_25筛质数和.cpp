/*必须先调用init(),注意mx要开够
 *G(x,plen)返回1~x的所有质数之和
 */
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int mx=1e6+5;//这里mx=sqrt(n),1e6不够的话还要开大
int prime[mx/10],plen;
bool isprime[mx];
int psum[mx],pcount[mx],psum2[mx];
const static int mod=1e9+7;
inline ll quickpow(ll a,int b,int md=mod)
{
    ll s=1;
    while (b)
	{
		if (b&1)s=s*a%md;
        a=a*a%md;
        b>>=1;
	}
	return s;
}
inline void init()
{
    for (int i=2;i<mx;i++)
	{
		if (!isprime[i])prime[++plen]=i,psum[i]=i,pcount[i]=1,psum2[plen]=(psum2[plen-1]+i)%mod;
		psum[i]+=psum[i-1];if (psum[i]>=mod)psum[i]-=mod;
		pcount[i]+=pcount[i-1];
        for (int j=1,p=prime[j]*i;j<=plen&&p<mx;j++,p=prime[j]*i)
		{
			isprime[p]=1;
			if (i%prime[j]==0)break;
		}
	}
}
ll inv2=quickpow(2,mod-2,mod);
ll Sum(ll t){return (t+1)%mod*t%mod*inv2%mod;}// (t+1)*t/2
ll G(ll n,int m)
{
    if(n<mx&&n<(ll)prime[m]*prime[m])return psum[n];
    if(!m)return Sum(n);
    for(;n<(ll)prime[m]*prime[m];--m);
    ll ans=0;
    for(;m;--m)ans=((ans-(G(n/prime[m],m-1)-psum[m-1])*prime[m])%mod+mod)%mod;
    return (ans+Sum(n))%mod;
}
int main()
{
	init();
	ll n;
    while(~scanf("%lld",&n))printf("%lld\n",G(n,plen));
	return 0;
}
