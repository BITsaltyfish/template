//线性筛逆元
for(int i=2;i<p;i++)inv[i] = 1ll*(p-p/i)*inv[p%i]%p;
//
	int mrk[1000010],prime[1000001], phi[1000010];
//线性筛欧拉函数
void getphi(int N)  
{  
	int i,j;  
	phi[1]=1;
	int tot = 0;
	for(i=2;i<=N;i++)//相当于分解质因式的逆过程  
	{  
		if(!mrk[i])  
		{  
			prime[++tot]=i;//筛素数的时候首先会判断i是否是素数。  
			phi[i]=i-1;//当 i 是素数时 phi[i]=i-1  
		}  
		for(j=1;j<=tot;j++)  
		{  
			if(i*prime[j]>N)  break;  
			mrk[i*prime[j]]=1;//确定i*prime[j]不是素数  
			if(i%prime[j]==0)//接着我们会看prime[j]是否是i的约数  
			{  
				phi[i*prime[j]]=phi[i]*prime[j];break;  
			}  
			else
				phi[i*prime[j]]=phi[i]*(prime[j]-1);//其实这里prime[j]-1就是phi[prime[j]]，利用了欧拉函数的积性  
		}  
	}  
}
//线性筛莫比乌斯函数
int mu[1000010];
void getmu(int N)
{
	int cnt = 0;
	mu[1] = 1;
	for (int i = 2; i <= N ; ++i)
	{
		if(!vis[i])
		{
			prime[cnt++] = i;
			mu[i] = -1;
		}
		for (int j = 0; j < cnt&&i*prime[j]<=N ; ++j)
		{
			vis[i*prime[j]] = true;
			if(i%prime[j]) mu[i*prime[j]] = -mu[i];
			else
			{
				mu[i*prime[j]] = 0;
				break;
			}
		}
	}
}
//线性筛素数
#define MAXL 1299710
int prime[1000010];
int mrk[1000010];

void getprime(int N){
	int tot = 0;
	memset(mrk, 0, sizeof(mrk));
	for (int i = 2; i <= N; ++i)
	{
		if (!mrk[i])prime[++tot] = i;
		for (int j = 1; j <= tot; ++j)
		{
			if (i * prime[j] > N)break;
			mrk[i*prime[j]] = 1;
			if (i % prime[j] == 0)break;
		}
	}
}
//n sqrt(n) 拆分数
const int mod=1e9+7;
void inc(int &x,int y){x=x+y>=mod?x+y‐mod:x+y;}
void dec(int &x,int y){x=x‐y<0?x‐y+mod:x‐y;}
void getchaifen(int N){
	f[0]=1;
	for(int i=1;i<=N;i++)
	{
		for(int j=1,w=1;w<=i;w+=3*j+1,j++)
			if(j&1)inc(f[i],f[i‐w]);
			else dec(f[i],f[i‐w]); 
		for(int j=1,w=2;w<=i;w+=3*j+2,j++)
			if(j&1)inc(f[i],f[i‐w]);
			else dec(f[i],f[i‐w]);
	}
}