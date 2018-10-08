#include <bits/stdc++.h>
using namespace std;
#define eps 1e-3
#define inf 1e17
const int maxn = 100100;
int tot = 0;
int stu[maxn], nxt[maxn << 1], vto[maxn << 1];
double w[maxn << 1];
int n, m;
int l[maxn], r[maxn];
double a[maxn], b[maxn];
double ll[maxn << 1], rr[maxn << 1];
void init() {
    memset(stu, -1, sizeof stu);
    tot = 0;
}
void added(int u, int v, double ww, double aa, double bb) {
    ll[tot] = aa, rr[tot] = bb;
    vto[tot] = v, w[tot] = ww, nxt[tot] = stu[u];
    stu[u] = tot++;
}
struct node {
    double u, d;
};
double dis[maxn];
bool vis[maxn];
int ped[maxn];
int pn[maxn];
node spfa() {
    for(int i = 1; i <= m + 1; i++) {
        dis[i] = inf;
        vis[i] = false;
    }
    deque<int> que;
    que.push_back(1);
    dis[1] = 0;
    while(!que.empty()) {
        int u = que.front();
        que.pop_front();
        vis[u] = false;
        for(int i = stu[u]; ~i; i = nxt[i]) {
            int v = vto[i];
            double ww = w[i];
            if(dis[u] + ww < dis[v]) {
                dis[v] = dis[u] + ww;
                ped[v] = i;
                pn[v] = u;
                if(vis[v])continue;
                vis[v] = true;
                if(!que.empty() && dis[v] >= dis[que.front()]) que.push_back(v);
                else que.push_front(v);
            }
        }
    }
    int u = m + 1;
    node ret;
    ret.u = ret.d = 0;
    while(u != 1) {
        ret.u += ll[ped[u]];
        ret.d += rr[ped[u]];
        u = pn[u];
    }
    return ret;
}
double check(double t) {
    init();
    for(int i = 1; i <= m; i++)added(i + 1, i, 0, 0, 0);
    double up = 0, dow = 0;
    for(int i = 1; i <= n; i++) {
        if(a[i] - b[i]*t < 0) {
            added(l[i], r[i] + 1, 0, 0, 0 );
            up += a[i];
            dow += b[i];
        } else {
            added(l[i], r[i] + 1, a[i] - b[i]*t, a[i], b[i]);
        }
    }
    node ans = spfa();
    //  printf("%f %f %f %f\n",ans.u,ans.d,up,dow );
    return (ans.u + up) / (ans.d + dow);
}
void solve() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++)scanf("%d%d%lf%lf", &l[i], &r[i], &a[i], &b[i]);
    double pre = 0, t = 1e5;
    while(fabs(pre - t) > eps) {
        pre = t;
        t = check(t);
    }
    printf("%.3f\n", t);
}
int main(int argc, char const *argv[]) {
    int t;
    scanf("%d", &t);
    while(t--) solve();
    return 0;
}