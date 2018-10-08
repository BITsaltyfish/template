// HDU 5314 点权路径极差小于D的对数
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 5;
struct Edge { int to, next; } e[maxn << 1];
int head[maxn], cnt;
inline void init() { memset(head, -1, sizeof head); cnt = 0; }
inline void addedge(int u, int v) {
    e[cnt].to = v;
    e[cnt].next = head[u];
    head[u] = cnt++;
}
int son[maxn], f[maxn], vis[maxn], sum, rt;
int p[maxn], n, d, sz;
ll ans;
pair<int, int> v[maxn];
void dfs1(int u, int fa) { // for son and root
    son[u] = 1, f[u] = 0;
    for (int i = head[u]; ~i; i = e[i].next) {
        int v = e[i].to;
        if (v != fa && !vis[v]) {
            dfs1(v, u);
            son[u] += son[v];
            f[u] = max(f[u], son[v]);
        }
    }
    f[u] = max(f[u], sum - son[u]);
    if (f[u] < f[rt]) rt = u;
}
void dfs2(int u, int fa, int mi, int mx) { // calculate
    mi = min(mi, p[u]);
    mx = max(mx, p[u]);
    if (mi + d >= mx) v[++sz] = {mi, mx};
    for (int i = head[u]; ~i; i = e[i].next) {
        int v = e[i].to;
        if (!vis[v] && v != fa) dfs2(v, u, mi, mx);
    }
}
ll calc(int u, int mi, int mx) {
    sz = 0;
    dfs2(u, 0, mi, mx);
    sort(v +1, v + sz + 1);
    ll res = 0;
    for (int i = sz; i >= 1; i--) {
        int id = lower_bound(v + 1, v + i, make_pair(v[i].second - d, 0)) - v;
        res += (i - id);
    }
    return res;
}
void dfs(int u) {
    ans += calc(u, p[u], p[u]);
    vis[u] = 1;
    for (int i = head[u]; ~i; i = e[i].next) {
        int v = e[i].to;
        if (!vis[v]) {
            ans -= calc(v, p[u], p[u]);
            rt = 0;
            f[0] = sum = son[v];
            dfs1(v, 0);
            dfs(rt);
        }
    }
}
int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        init();
        scanf("%d%d", &n, &d);
        for (int i = 1; i <= n; i++) scanf("%d", &p[i]);
        for (int i = 1; i < n; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            addedge(u, v);
            addedge(v, u);
        }
        ans = 0; rt = 0;
        memset(vis, 0, sizeof vis);
        f[0] = sum = n;
        dfs1(1, 0);
        dfs(rt);
        printf("%lld\n", ans * 2);
    }
    return 0;
}


// BZOJ 2152 mod 3意义下路径点对计数
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e4 + 5;
struct Edge { int to, val, next; } e[maxn << 1];
int head[maxn], cnt;
inline void init() { memset(head, -1, sizeof head); cnt = 0; }
inline void addedge(int u, int v, int w) { e[cnt].to = v; e[cnt].next = head[u]; e[cnt].val = w; head[u] = cnt++; }
int son[maxn], f[maxn], d[maxn], t[5], sum, rt, ans;
bool vis[maxn];
void dfs1(int u, int fa) {  // root
    son[u] = 1, f[u] = 0;
    for (int i = head[u]; ~i; i = e[i].next) {
        int v = e[i].to;
        if (!vis[v] && v != fa) {
            dfs1(v, u);
            son[u] += son[v];
            f[u] = max(f[u], son[v]);
        }
    }
    f[u] = max(f[u], sum - son[u]);
    if (f[u] < f[rt]) rt = u;
}
void dfs2(int u, int fa) {  // deep
    t[d[u]]++;
    for (int i = head[u]; ~i; i = e[i].next) {
        int v = e[i].to, w = e[i].val;
        if (!vis[v] && v != fa) {
            d[v] = (d[u] + w) % 3;
            dfs2(v, u);
        }
    }
}
int calc(int u, int w) {
    t[0] = t[1] = t[2] = 0;
    d[u] = w;
    dfs2(u, 0);
    return t[1] * t[2] * 2 + t[0] * t[0];
}
void dfs3(int u) {
    ans += calc(u, 0);
    vis[u] = 1;
    for (int i = head[u]; ~i; i = e[i].next) {
        int  v = e[i].to, w = e[i].val;
        if (!vis[v]) {
            ans -= calc(v, w);
            rt = 0;
            sum = son[v];
            dfs1(v, 0);
            dfs3(rt);
        }
    }
}
int main() {
    int n;
    scanf("%d", &n);
    init();
    for (int i = 1; i < n; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        addedge(u, v, w % 3);
        addedge(v, u, w % 3);
    }
    f[0] = sum = n;
    dfs1(1, 0);
    ans = 0;
    dfs3(rt);
    int g = __gcd(ans, n * n);
    printf("%d/%d\n", ans / g, n * n / g);
    return 0;
}