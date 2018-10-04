#include <bits/stdc++.h>
using namespace std;
const int maxn = 1000010;
struct Sam
{
	int n,tot,last,ans,l;
	int nxt[maxn<<1][26],pa[maxn<<1],dep[maxn<<1];
	int root;
	char s[maxn];
	inline void init()
	{
		memset(vis,0,sizeof vis);
		root = tot = last = 1;
		memset(nxt,-1,sizeof nxt);
		memset(pa,-1,sizeof pa);
		memset(dep,0,sizeof dep);
	}
	inline void extend(int x)
	{
		int c = s[x] - 'a',p = last,np = ++tot;last = np;
		dep[np] = x;
		for(;p!=-1 && nxt[p][c]==-1;p = pa[p])nxt[p][c] = np;
		if(p == -1)pa[np] = 1;
		else
		{
			int q = nxt[p][c];
			if(dep[p]+1 == dep[q])pa[np] = q;
			else
			{
				int nq = ++tot;dep[nq] = dep[p]+1;
				memcpy(nxt[nq],nxt[q],sizeof nxt[q]);
				pa[nq] = pa[q];pa[np] = pa[q] = nq;
				for(;nxt[p][c] == q;p = pa[p])nxt[p][c] = nq;		
			}
		}
	}
	int res[maxn<<1];
	int w[maxn<<1],b[maxn<<1],r[maxn<<1];
	void topo()
	{
		memset(w,0,sizeof w);
		memset(r,0,sizeof r);
		//拓扑排序
		for(int i = 1;i<= tot;i++)w[dep[i]]++;
		for(int i = 1;i<= l;i++) w[i] += w[i-1];
		for(int i = 1;i<= tot;i++)b[w[dep[i]]--] = i;
		//拓扑排序

		//计算每个状态right的size
		int p = root;
		for(int i = 1;i <= l;i++)p = nxt[p][s[i]-'a'],r[p]++;
		for(int i = tot; i>= 1;i--) if( pa[b[i]] != -1 ) r[ pa[b[i]] ] += r[b[i]];
	}

	int vis[maxn<<1];
	/*CodeForces 235C*/
	void query(char a[],int len,int now)
	{
		int p = root;
		int ans = 0;
		int t = 0;
		p = root;
		for(int i=0;i<len;i++)if(nxt[p][a[i]-'a'] == -1){printf("0\n");return ;}
		for(int i=0;i<len;i++)
		{
			while( p > 1 && nxt[p][a[i]-'a'] == -1){p = pa[p]; t = dep[p];}
			p = nxt[p][a[i]-'a'];t++;
			if(t >= len/2)
			{
				while(pa[p]!=-1 && dep[pa[p]]>=len/2 )p = pa[p],t = dep[p];
				if(vis[p]!=now)vis[p] = now,ans+=r[p];
			}
		}
		printf("%d\n",ans);
	}
	//查询子串第k大
	inline void query(int k)
	{
		int p = root;
		while(k)
		{
			for(int i = 0;i<26;i++)
			{
				if(nxt[p][i]==-1)continue;
				if(k > r[nxt[p][i]]) k-=r[nxt[p][i]];
				else if(k <= r[nxt[p][i]]){printf("%c",i+'a');p = nxt[p][i];break;}
			}
		}
		printf("\n");
	}
}S;
int main(int argc, char const *argv[])
{
	scanf("%s",S.s+1);int len = strlen(S.s+1);S.l = len;
	S.init();
	for(int i = 1;i<= len;i++) S.extend(i);
	S.topo();
	int k;
	scanf("%d",&k),S.query(k);
	return 0;
}
