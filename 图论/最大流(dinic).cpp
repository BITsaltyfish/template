/*
    务必牢记：重新建图的时候cnt=1！！！不是0！
*/
#define S 0
#define T (n+1)
#define N 1010
#define M 100010
#define inf 0x3f3f3f3f		//如果重复定义可注释
struct edge{int to,next,v;}e[M];
int head[N],cnt;
inline void ins(int u,int v,int w)
{
    e[++cnt].to=v;
    e[cnt].next=head[u];
    e[cnt].v=w;
    head[u]=cnt;
}
inline void insert(int u,int v,int w)
{
    ins(u,v,w);
    ins(v,u,0);
}
int h[N],q[N],tot;
inline bool bfs()
{
    memset(h,-1,sizeof(h));
    int t=0,w=1;
    q[0]=S;h[S]=0;
    while (t!=w)
    {
        int now=q[t++];if (t==N)t=0;
        for (int i=head[now];i;i=e[i].next)
            if (e[i].v&&h[e[i].to]==-1)
            {
                h[e[i].to]=h[now]+1;
                q[w++]=e[i].to;
                if (w==N)w=0;
            }
    }
    return h[T]!=-1;
}
inline int dfs(int x,int f)
{
    if (x==T||!f)return f;
    int w,used=0;
    for (int i=head[x];i;i=e[i].next)
        if (h[e[i].to]==h[x]+1&&e[i].v)
        {
            w=dfs(e[i].to,min(e[i].v,f-used));
            e[i].v-=w;
            e[i^1].v+=w;
            used+=w;
            if (used==f)return f;
        }
    if (!used)h[x]=-1;
    return used;
}
inline void dinic(){tot=0;while (bfs())tot+=dfs(S,inf);}