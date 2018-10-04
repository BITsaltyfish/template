inline void dijkstra(int S)
{
    for (int i=1;i<=n;i++)dis[i]=-1,vis[i]=0;
    dis[S]=0;q.push(mkp(0,S));
    while (!q.empty())
    {
        int now=q.top().second;q.pop();
        if (vis[now])continue;vis[now]=1;
        for(int i=head[now];i;i=e[i].next)
        if(dis[e[i].to]==-1||dis[now]+e[i].v<dis[e[i].to])
        {
            dis[e[i].to]=dis[now]+e[i].v;
            q.push(mkp(dis[e[i].to],e[i].to));
        }
    }
}