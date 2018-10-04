inline void tarjan(int x,int fa)
{
	if (mrk[x])return;mrk[x]=inset[x]=1;
	dfn[x]=low[x]=++cnt2;
	for (int i=head[x];i;i=e[i].next)
	{
		if (mrk[e[i].to])
		{
			if (inset[e[i].to]&&e[i].to!=fa)low[x]=min(low[x],dfn[e[i].to]);
		}else
		{
			tarjan(e[i].to,x);
			low[x]=min(low[x],low[e[i].to]);
			if (low[e[i].to]>dfn[x])
			{
				d[++ans].x=x,d[ans].y=e[i].to;//Ò»Ìõ±ß(x,e[i].to)ÊÇ¸î±ß
				if (x>e[i].to)swap(d[ans].x,d[ans].y);
			}
		}
	}
	inset[x]=0;
}
