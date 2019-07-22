/* 先求出dfs序，要求每个点进入In_i和退出Out_i计算2次
 * 对于路径(a,b)
 * 若lca(a,b)==a或b，那么[In_a,Out_b]或[In_b,Out_a]中*只出现1次*的点都是路径上的点
 * 若lca(a,b)!=a或b，那么" [In_a,Out_b]并上lca(a,b) "或" [In_b,Out_a]并上lca(a,b) "中*只出现1次*的点都是路径上的点
 * 区别在于如果lca不是它们中的一个那么在集合中还要加上一个lca
 * 注意在当前区间中的一个点出现次数如果是奇->偶，要消除点的影响。如果是偶->奇，要加入点的影响。
 * spoj COT2 查询树上x-y路径上有多少不同的数字出现过
 */
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int maxn=100010,maxm=100010;
int v[maxn];
struct edge{int to,next;}e[maxn<<1];
int head[maxn],cnt;
inline void ins(int u,int v)
{
	e[++cnt].to=v;
	e[cnt].next=head[u];
	head[u]=cnt;
}
inline void insert(int u,int v)
{
    ins(u,v);
    ins(v,u);
}
struct query{int x,y,lca,ans,id;}q[maxm];
int belong[maxn<<1],block;
bool operator<(query a,query b){return belong[a.x]==belong[b.x]?a.y<b.y:belong[a.x]<belong[b.x];}
bool cmp(query a,query b){return a.id<b.id;}
int fa[maxn][20];
int l[maxn],r[maxn],dep[maxn],dfn[maxn<<1],cnt2;
void dfs(int x,int f,int d)
{
	fa[x][0]=f;dep[x]=d;dfn[l[x]=++cnt2]=x;
	for (int i=1;i<20;i++)fa[x][i]=fa[fa[x][i-1]][i-1];
	for (int i=head[x];i;i=e[i].next)if(e[i].to!=f)dfs(e[i].to,x,d+1);
	dfn[r[x]=++cnt2]=x;
}
inline int LCA(int x,int y)
{
    if (dep[x]<dep[y])swap(x,y);
    int dif=dep[x]-dep[y];
	for (int i=19;i>=0;i--)if (dif&(1<<i))x=fa[x][i];
    for (int i=19;i>=0;i--)if (fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
    return x==y?x:fa[x][0];
}
int n,m;
int col[maxn],ans;
inline void add(int x,int d)
{
    if (d==-1){col[x]--;if (!col[x])ans--;}
    else if (d==1){if (!col[x])ans++;col[x]++;}
}
int main()
{
	scanf("%d%d",&n,&m);
	map<int,int>mp;int cr=0;
	for (int i=1;i<=n;i++)scanf("%d",v+i),mp[v[i]]=1;
	for (auto i=mp.begin();i!=mp.end();i++)i->second=++cr;
	for (int i=1;i<=n;i++)v[i]=mp[v[i]];
	for (int i=1;i<n;i++)
	{
        int x,y;scanf("%d%d",&x,&y);
        insert(x,y);
	}
	dfs(1,0,0);
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d",&q[i].x,&q[i].y);
		if (l[q[i].x]>l[q[i].y])swap(q[i].x,q[i].y);
		q[i].lca=LCA(q[i].x,q[i].y);
		if (q[i].lca==q[i].x)
		{
            q[i].lca=0;
			q[i].x=l[q[i].x];q[i].y=l[q[i].y];
		}else
		{
            q[i].x=r[q[i].x];q[i].y=l[q[i].y];
		}
		q[i].id=i;
	}
    block=sqrt(n*2);if (block*block!=n*2)block++;
    for (int i=1;i<=n*2;i++)belong[i]=(i-1)/block+1;
	sort(q+1,q+m+1);
	memset(col,0,sizeof col);ans=0;
	int L=1,R=0;
    for (int i=1;i<=m;i++)
	{
        while (L>q[i].x)
		{
            L--;
            if (L==l[dfn[L]])if (R>=r[dfn[L]])add(v[dfn[L]],-1);else add(v[dfn[L]],1);
            else add(v[dfn[L]],1);
		}
		while (R<q[i].y)
		{
            R++;
            if (R==r[dfn[R]])if (L<=l[dfn[R]])add(v[dfn[R]],-1);else add(v[dfn[R]],1);
            else add(v[dfn[R]],1);
		}
        while (L<q[i].x)
		{
            if (L==l[dfn[L]])if (R>=r[dfn[L]])add(v[dfn[L]],1);else add(v[dfn[L]],-1);
            else add(v[dfn[L]],-1);
            L++;
		}
		while (R>q[i].y)
		{
            if (R==r[dfn[R]])if (L<=l[dfn[R]])add(v[dfn[R]],1);else add(v[dfn[R]],-1);
            else add(v[dfn[R]],-1);
            R--;
		}
		if (q[i].lca)
		{
            add(v[q[i].lca],1);
            q[i].ans=ans;
            add(v[q[i].lca],-1);
		}else q[i].ans=ans;
	}
	sort(q+1,q+m+1,cmp);
    for(int i=1;i<=m;i++)printf("%d\n",q[i].ans);
	return 0;
}
