struct edge{int to,next,v,c,from;}e[100*N];
int head[N],dist[N],q[N],from[N];
bool mrk[N];
int n,m,cnt=1,ans;
inline void ins(int u,int v,int w,int c)
{
    e[++cnt].to=v;
    e[cnt].v=w;
    e[cnt].c=c;
    e[cnt].from=u;
    e[cnt].next=head[u];
    head[u]=cnt;
}
inline void insert(int u,int v,int w,int c)
{
    ins(u,v,w,c);
    ins(v,u,0,-c);
}
inline bool spfa()
{
    for (int i=0;i<=T;i++)dist[i]=inf;
    int t=0,w=1;
    dist[S]=0;q[0]=S;mrk[S]=1;
    while (t!=w)
    {
        int now=q[t++];if (t==N-1)t=0;
        for (int i=head[now];i;i=e[i].next)
            if (e[i].v&&dist[now]+e[i].c<dist[e[i].to])
            {
                dist[e[i].to]=dist[now]+e[i].c;
                from[e[i].to]=i;
                if (!mrk[e[i].to])
                {
                    mrk[e[i].to]=1;
                    q[w++]=e[i].to;
                    if (w==N-1)w=0;
                }
            }
        mrk[now]=0;
    }
    return dist[T]!=inf;
}
inline void mcf()
{
    int x=inf;
    for (int i=from[T];i;i=from[e[i].from])
        x=min(x,e[i].v);
    for (int i=from[T];i;i=from[e[i].from])
    {
        e[i].v-=x;
        e[i^1].v+=x;
        ans+=x*e[i].c;
    }
}
while (spfa())mcf();
printf("%d\n",ans);