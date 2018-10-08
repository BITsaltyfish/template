/*
 * 最大权完美匹配：一个两边各n个点的二分图，中间边的权值由g[i][j]给出，
                 要求找出一个包含n条边的完美匹配，使得权值和最大。
 * 最小权完美匹配的做法是把边取反跑一遍，然后答案再取反
 */
#define N 310
#define inf 0x3f3f3f3f
int g[N][N];
int lx[N], ly[N];
int match[N];
bool vis_x[N], vis_y[N];
int slack[N];
int n;
bool dfs(int cur) {
    vis_x[cur] = 1;
    int t;
    for(int y = 1; y <= n; y++) {
        if(vis_y[y])continue;
        t = lx[cur] + ly[y] - g[cur][y];
        if(!t) {
            vis_y[y] = 1;
            if(match[y] == -1 || dfs(match[y])) {
                match[y] = cur;
                return 1;
            }
        } else if(slack[y] > t)slack[y] = t;
    }
    return 0;
}
int KM() {
    memset(match, -1, sizeof(match));
    memset(ly, 0, sizeof(ly));
    for(int i = 1; i <= n; i++) {
        lx[i] = -inf;
        for(int j = 1; j <= n; j++)
            if(g[i][j] > lx[i])lx[i] = g[i][j];
    }
    for(int x = 1; x <= n; x++) {
        for(int i = 1; i <= n; i++)slack[i] = inf;
        int d;
        while(1) {
            memset(vis_x, 0, sizeof(vis_x));
            memset(vis_y, 0, sizeof(vis_y));
            if(dfs(x))break;
            d = inf;
            for(int i = 1; i <= n; i++)
                if(!vis_y[i] && d > slack[i])d = slack[i];
            for(int i = 1; i <= n; i++)
                if(vis_x[i])lx[i] -= d;
            for(int i = 1; i <= n; i++)
                if(vis_y[i])ly[i] += d;
                else slack[i] -= d;
        }
    }
    int res = 0;
    for(int i = 1; i <= n; i++)
        if(match[i] > -1)res += g[match[i]][i];
    return res;
}