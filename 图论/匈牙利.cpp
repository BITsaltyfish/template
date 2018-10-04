int g[maxn][maxn];
int match[maxn];int vis[maxn];
int n,tot;
bool dfs(int u) {
    for(int i = 1; i<= n; i++) {
        int v = i;
        if(g[u][v] == 0||vis[v])continue;
        vis[v] = 1;
        if (match[v] == -1 || dfs(match[v])) {
            match[v] = u;
            return 1;
        }
    }
    return 0;
}
int bipartite_matching(){
    int ans = 0;
    memset(match, -1, sizeof match);
    for(int u = 1;u<= n;u++) {
        memset(vis, 0, sizeof vis);
        if (dfs(u))ans++;
    }
    return ans;
}