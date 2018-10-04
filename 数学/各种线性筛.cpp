//线性筛逆元/阶乘逆元 上限多大才开多大，别MLE了

const static int mx=2e7+10;
int inv[mx];//[0,mx)逆元
int jc[mx],invjc[mx];// 0!~(mx-1)!逆元
void init()
{
    //[0,mx)逆元
    inv[0]=inv[1]=1;
    int p,q;
    for (int i=2;i<mx;i++)
    {
        p=mod/i,q=mod-p*i;
        inv[i]=1ll*(mod-p)*inv[q]%mod;
    }
    //0!~(mx-1)!及逆元
    jc[0]=1;
    for (int i=1;i<mx;i++)jc[i]=1ll*jc[i-1]*i%mod;
    invjc[mx-1]=quickpow(jc[mx-1],mod-2,mod);
    for (int i=mx-2;i>=0;i--)invjc[i]=1ll*invjc[i+1]*(i+1)%mod;
}

//线性筛素数

const static int mx=2e7+10;
int prime[mx],len;
bool isprime[mx];
void init()
{
    len=0;memset(isprime,0,sizeof isprime);
    for (int i=2;i<mx;i++)
	{
        if (!isprime[i])isprime[i]=1,prime[++len]=i;
        else isprime[i]=0;
        for (int j=1;j<=len&&prime[j]*i<mx;j++)
		{
            isprime[prime[j]*i]=1;
            if (i%prime[j]==0)break;
		}
	}
}

//线性筛欧拉函数phi

const static int mx=2e7+10;
int prime[mx],phi[mx],len;
void init()
{
    len=0;memset(phi,0,sizeof phi);phi[1]=1;
    for (int i=2;i<mx;i++)
	{
        if (!phi[i])phi[i]=i-1,prime[++len]=i;
        for (int j=1;j<=len&&prime[j]*i<mx;j++)
		{
            if (i%prime[j]==0){phi[prime[j]*i]=phi[i]*prime[j];break;}
            else phi[prime[j]*i]=phi[i]*(prime[j]-1);
		}
	}
}

//线性筛莫比乌斯函数mu

const static int mx=2e7+10;
int prime[mx],mu[mx],len;
bool mrk[mx];
void init()
{
    len=0;memset(mu,127/3,sizeof mu);mu[1]=1;
    for (int i=2;i<mx;i++)
	{
        if (mu[i]>1)mu[i]=-1,prime[++len]=i;
        for (int j=1;j<=len&&prime[j]*i<mx;j++)
		{
            if (i%prime[j]==0){mu[prime[j]*i]=0;break;}
            else mu[prime[j]*i]=-mu[i];
		}
	}
}

//线性筛任意积性函数（需要能够快速求出素数幂的函数值f[p^k]）

const static int mx=2e7+10;
int prime[mx],dprime[mx],f[mx],len;
//dprime[i]是i的最小质因子部分，可能不是最小质因子p，而是p^k
void init()
{
    f[0]=0;f[1]=1;
    for (int i=2;i<mx;i++)
    {
        if(!dprime[i])dprime[i]=prime[++len]=i,f[i]=;
        //f取值自己算，这里i是质数
        for (int j=1;j<=len&&i*prime[j]<mx;j++)
        {
            if (i%prime[j]==0)
            {
                dprime[i*prime[j]]=dprime[i]*prime[j];
                if(dprime[i]==i)f[i*prime[j]]=;
                //这里i*prime[j]是prime[j]^k,i=prime[j]^(k-1)
                else f[i*prime[j]]=f[i/dprime[i]]*f[dprime[i]*prime[j]];
                break;
            }
            dprime[i*prime[j]]=prime[j];
            f[i*prime[j]]=f[i]*f[prime[j]];
        }
    }
}