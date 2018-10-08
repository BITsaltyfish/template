//一般图的最大加权匹配模板
//注意G 的初始化, 需要偶数个点，刚好可以形成n/2 个匹配
//如果要求最小权匹配，可以取相反数，或者稍加修改就可以了
//点的编号从0 开始的
const int MAXN = 110;
const int INF = 0x3f3f3f3f;
int G[MAXN][MAXN];
int cnt_node;//点的个数
int dis[MAXN];
int match[MAXN];
bool vis[MAXN];
int sta[MAXN], top; //堆栈
bool dfs(int u) {
    sta[top++] = u;
    if(vis[u])return true;
    vis[u] = true;
    for(int i = 0; i < cnt_node; i++)
        if(i != u && i != match[u] && !vis[i]) {
            int t = match[i];
            if(dis[t] < dis[u] + G[u][i] − G[i][t]) {
                dis[t] = dis[u] + G[u][i] − G[i][t];
                if(dfs(t))return true;
            }
        }
    top−−;
    vis[u] = false;
    return false;
}
int P[MAXN];
//返回最大匹配权值
int get_Match(int N) {
    cnt_node = N;
    for(int i = 0; i < cnt_node; i++)P[i] = i;
    for(int i = 0; i < cnt_node; i += 2) {
        match[i] = i + 1;
        match[i + 1] = i;
    }
    int cnt = 0;
    while(1) {
        memset(dis, 0, sizeof(dis));
        memset(vis, false, sizeof(vis));
        top = 0;
        bool update = false;
        for(int i = 0; i < cnt_node; i++)
            if(dfs(P[i])) {
                update = true;
                int tmp = match[sta[top−1]];
                int j = top−2;
                while(sta[j] != sta[top−1]) {
                    match[tmp] = sta[j];
                    swap(tmp, match[sta[j]]);
                    j−−;
                }
                match[tmp] = sta[j];
                match[sta[j]] = tmp;
                break;
            }
        if(!update) {
            cnt++;
            if(cnt >= 3)break;
            random_shuffle(P, P + cnt_node);
        }
    }
    int ans = 0;
    for(int i = 0; i < cnt_node; i++) {
        int v = match[i];
        if(i < v)ans += G[i][v];
    }
    return ans;
}