int zhan[N],top;
int inset[N],dfn[N],low[N];
int belong[N],sz[N],cnt2,cnt3;
inline void dfs(int x,int fa)
{
	zhan[++top]=x;inset[x]=1;
	dfn[x]=low[x]=++cnt2;
	for(int i=head[x];i;i=e[i].next)
	if (e[i].to!=fa)
		if (!dfn[e[i].to])
		{
			dfs(e[i].to,x);
			low[x]=min(low[x],low[e[i].to]);
		}else if (inset[e[i].to])low[x]=min(low[x],dfn[e[i].to]);
	if (low[x]==dfn[x])
	{
		cnt3++;
		int p=-1;
		while (p!=x)
		{
			p=zhan[top--];
			belong[p]=cnt3;
			sz[cnt3]++;
			inset[p]=0;
		}
	}
}
inline void tarjan()
{
	for (int i=1;i<=n;i++)if (!dfn[i])dfs(i,0);
}