#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<set>
#include<ctime>
#include<vector>
#include<cmath>
#include<algorithm>
#include<map>
#include<ext/pb_ds/priority_queue.hpp>
#define pa pair<int,int>
#define inf 2000000000
using namespace std;
using namespace __gnu_pbds;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
typedef __gnu_pbds::priority_queue<pa,greater<pa> > heap;
int n,m,K,cnt,cnt2;
int ans[105];
int d[10005],g[10005],tim[10005];
int last[10005],last2[10005];
heap q;
heap::point_iterator id[10005];
struct edge{int to,next,v;}e[10005],ed[10005];
void insert(int u,int v,int w)
{
	e[++cnt].to=v;e[cnt].next=last[u];last[u]=cnt;e[cnt].v=w;
	ed[++cnt2].to=u;ed[cnt].next=last2[v];last2[v]=cnt2;ed[cnt2].v=w;
}
void dijkstra()
{
	for(int i=1;i<=n;i++)d[i]=inf;
	d[1]=0;
	id[1]=q.push(make_pair(0,1));
	while(!q.empty())
	{
		int now=q.top().second;q.pop();
		for(int i=last2[now];i;i=ed[i].next)
			if(ed[i].v+d[now]<d[ed[i].to])
			{
				d[ed[i].to]=d[now]+ed[i].v;
				if(id[ed[i].to]!=0)
					q.modify(id[ed[i].to],make_pair(d[ed[i].to],ed[i].to));
				else id[ed[i].to]=q.push(make_pair(d[ed[i].to],ed[i].to));
			}
	}
}
void astar()
{
    if(d[n]==inf)return;
    q.push(make_pair(d[n],n));
	while(!q.empty())
	{
		int now=q.top().second,dis=q.top().first;q.pop();
		tim[now]++;
		if(now==1)ans[tim[now]]=dis;
		if(tim[now]<=K)
			for(int i=last[now];i;i=e[i].next)
				q.push(make_pair(dis-d[now]+d[e[i].to]+e[i].v,e[i].to));
	}
}
int main()
{
	n=read();m=read();K=read();
	for(int i=1;i<=m;i++)
	{
		int u=read(),v=read(),w=read();
		insert(u,v,w);
	}
	dijkstra();
	astar();
	for(int i=1;i<=K;i++)
		if(ans[i])printf("%d\n",ans[i]);
		else puts("-1");
	return 0;
}