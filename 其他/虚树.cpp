#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mx=5e5+10;
int n,m;
vector<int>ed[mx];
int fa[mx][20],dfn[mx],dep[mx],cnt;
inline void dfs1(int x,int f,int d)
{
    fa[x][0]=f;
    dfn[x]=++cnt;
    dep[x]=d;
    for (int i=1;i<20;i++)fa[x][i]=fa[fa[x][i-1]][i-1];
    for (auto y:ed[x])if (y!=fa[x][0])dfs1(y,x,d+1);
}
inline int LCA(int x,int y)
{
    if (dep[x]<dep[y])swap(x,y);
    int res=dep[x]-dep[y];
    for (int i=19;i>=0;i--)if (res&(1<<i))x=fa[x][i];
    for (int i=19;i>=0;i--)if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
    return x==y?x:fa[x][0];
}
bool cmp(const int &x,const int &y){return dfn[x]<dfn[y];}
int fa2[mx],dep2[mx],fa2_edge_sz[mx];
vector<int>ed2[mx];
inline void addEdge(int u,int v)
{
    if (u==v)return;
    if (dep[u]<dep[v])swap(u,v);
    fa2[u]=v;
    ed2[v].push_back(u);
    fa2_edge_sz[u]=dep[u]-dep[v]-1;
}
inline void dfs2(int x,int d)
{
    dep2[x]=d;
    for (auto y:ed2[x])if (y!=fa2[x])
        dfs2(y,d+1);
}
int op[2010],u[2010],v[2010],w[2010],d[10010];
ll a[500010],b[500010];
int zhan[10010],top;
inline void work()
{
    for (int i=1;i<=n;i++)ed[i].clear(),ed2[i].clear(),a[i]=0,b[i]=0;
    cnt=0;
    scanf("%d%d",&n,&m);
    for (int i=1;i<n;i++)
    {
        int x,y;scanf("%d%d",&x,&y);
        ed[x].push_back(y);ed[y].push_back(x);
    }
    dfs1(1,0,1);
    int tot=0;
    for (int i=1;i<=m;i++)
    {
        scanf("%d%d%d",op+i,u+i,v+i);
        if (op[i]==1||op[i]==2||op[i]==3||op[i]==7)scanf("%d",w+i);
        d[++tot]=u[i];d[++tot]=v[i];
    }
    sort(d+1,d+2*m+1,cmp);
    tot=1;
    for (int i=2;i<=2*m;i++)if (d[tot]!=d[i])d[++tot]=d[i];
    zhan[top=1]=1;
    for (int i=1;i<=tot;i++)
    {
        int now=d[i],f=LCA(now,zhan[top]);
        while (top>1)
        {
            if (dep[f]>=dep[zhan[top-1]])
            {
                addEdge(f,zhan[top--]);
                if (zhan[top]!=f)zhan[++top]=f;
                break;
            }
            addEdge(zhan[top-1],zhan[top]);top--;
        }
        if (zhan[top]!=now)zhan[++top]=now;
    }
    while (--top)addEdge(zhan[top],zhan[top+1]);
    dfs2(1,1);
}
int main()
{
    int T;scanf("%d",&T);
    while (T--)work();
    return 0;
}