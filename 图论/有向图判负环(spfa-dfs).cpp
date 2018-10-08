#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct edge {
    int to, next;
    double v;
} e[4010];
int head[810], cnt;
inline void ins(int u, int v, double w) {
    e[++cnt].to = v;
    e[cnt].next = head[u];
    e[cnt].v = w;
    head[u] = cnt;
}
inline void insert(int u, int v, double w) {
    ins(u, v, w);
    ins(v, u, w);
}
int n, m, ans;
double dis[810];
bool vis[810];
inline void dfs(int x) {
    vis[x] = 1;
    for(int i = head[x]; i; i = e[i].next) {
        if (dis[x] + e[i].v < dis[e[i].to]) {
            if (vis[e[i].to]) {
                ans = 1;
                return;
            }
            dis[e[i].to] = dis[x] + e[i].v;
            dfs(e[i].to);
        }
    }
    vis[x] = 0;
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int x, y;
        double z;
        scanf("%d%d%lf", &x, &y, &z);
        z = -log(z);
        ins(x, y, z);
    }
    for (int i = 1; i <= n; i++) {
        memset(vis, 0, sizeof vis);
        memset(dis, 0, sizeof dis);
        dfs(i);
        if (ans)break;
    }
    puts(ans ? "inadmissible" : "admissible");
    return 0;
}
