// URAL 1099
#include <bits/stdc++.h>
using namespace std;
const int maxn = 230;
int nxt[maxn], spouse[maxn];
int pa[maxn];
int find(int x) {
    if (x == pa[x]) return x;
    return pa[x] = find(pa[x]);
}
inline void merge(int u, int v) {
    int fu = find(u);
    int fv = find(v);
    if (fu != fv) pa[fu] = fv;
}
vector<int> g[maxn];
int mark[maxn], vis[maxn];
int Q[maxn], l, r;
int n, t = 0; //点的个数，点的编号从1到n
inline int LCA(int x, int y) {
    ++t;
    while (1) {
        if (x != -1) {
            x = find(x);
            if (vis[x]== t) return x;
            vis[x] = t;
            if (spouse[x] != -1) x = nxt[spouse[x]];
            else x = -1;
        }
        swap(x, y);
    }
}
inline void group(int a, int p) {
    while (a != p) {
        int b = spouse[a], c = nxt[b];
        if (find(c) != p) nxt[c] = b;
        if (mark[b] == 2) mark[Q[r++] = b] = 1;
        if (mark[c] == 2) mark[Q[r++] = c] = 1;
        merge(a, b); merge(b, c);
        a = c;
    }
}
inline void Augment(int s) {
    for (int i = 0; i < n; i++) {
        nxt[i] = -1;
        vis[i] = -1;
        pa[i] = i;
        mark[i] = 0;
    }
    Q[l = 0] = s; r = 1; mark[s] = 1;
    while (l < r && spouse[s] == -1) {
        int u = Q[l++];
        for (int i = 0; i < g[u].size(); i++) {
            int v = g[u][i];
            int fu = find(u);
            int fv = find(v);
            if (spouse[u] != v && fu != fv && mark[v] != 2) {
                if (mark[v] == 1) {
                    int p = LCA(u, v);
                    if (fu != p) nxt[u] = v;
                    if (fv != p) nxt[v] = u;
                    group(u, p); group(v, p);
                } else if (spouse[v] == -1) {
                    nxt[v] = u;
                    int now = v;
                    while (now != -1) {
                        int p = nxt[now];
                        int tmp = spouse[p];
                        spouse[now] = p; spouse[p] = now;
                        now = tmp;
                    }
                    break;
                } else {
                    nxt[v] = u;
                    mark[Q[r++] = spouse[v]] = 1;
                    mark[v] = 2;
                }
            }
        }
    }
}
bool m[maxn][maxn];
int main() {
    int x, y;
    scanf("%d", &n); 
    memset(m, 0, sizeof m);
    while (~scanf("%d%d", &x, &y)) {
        x--; y--;
        if (x != y && !m[x][y]) {
            g[x].push_back(y);
            g[y].push_back(x);
            m[x][y] = m[y][x] = 1;
        }
    }
    for (int i = 0; i < n; i++) spouse[i] = -1;
    for (int i = 0; i < n; i++) {
        if (spouse[i] == -1) Augment(i);
    }
    int res = 0; //匹配数，匹配对数是Count/2
    for (int i = 0; i < n; i++) {
        if (spouse[i] != -1) res++;
    }
    printf("%d\n", res);
    for (int i = 0; i < n; i++) {
        if (spouse[i] != -1 && spouse[i] > i) {
            printf("%d %d\n", i + 1, spouse[i] + 1);
        }
    }
    return 0;
}
