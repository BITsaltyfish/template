/*
[LightOJ-1356] - 最大点独立集+素数筛
Hopcroft-Carp算法适用于点集稠密的二分图，相较于匈牙利更有优势
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn = 4e4 + 5;
const int maxm = 5e5 + 5;
vector<int> prime, g[maxn], v[maxn];
int a[maxn], p[2][maxm], mx[maxn], my[maxn], dx[maxn], dy[maxn];
bool vis[maxm], used[maxn];
int n, dis;
inline void init() {
    memset(vis, 0, sizeof vis);
    for (int i = 2; i <= maxm - 5; i++) {
        if (!vis[i]) {
            prime.push_back(i);
            for (int j = 2*i; j <= maxm - 5; j += i) vis[j] = 1;
        }
    }
}
bool find() {
    queue<int> q;
    dis = 1e9;
    memset(dx, -1, sizeof dx);
    memset(dy, -1, sizeof dy);
    for (int i = 0; i < n; i++) {
        if (mx[i] == -1) {
            q.push(i);
            dx[i] = 0;
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (dx[u] > dis) break;
        for (int i = 0; i < g[u].size(); i++) {
            int v = g[u][i];
            if (dy[v] == -1) {
                dy[v] = dx[u] + 1;
                if (my[v] == -1) dis = dy[v];
                else {
                    dx[my[v]] = dy[v] + 1;
                    q.push(my[v]);
                }
            }

        }
    }
    return dis != 1e9;
}
bool dfs(int u) {
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (!used[v] && dy[v] == dx[u] + 1) {
            used[v] = 1;
            if (my[v] != -1 && dy[v] == dis) continue;
            if (my[v] == -1 || dfs(my[v])) {
                my[v] = u;
                mx[u] = v;
                return 1;
            }
        }
    }
    return 0;
}
inline void solve(int kase) {
    scanf("%d", &n);
    for (int i = 0; i <= n; i++) {
        g[i].clear();
        v[i].clear();
    }
    memset(p, 0, sizeof p);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        int tmp = a[i], cnt= 0;;
        for (int j = 0; prime[j] * prime[j] <= tmp; j++) {
            if (tmp % prime[j] == 0) {
                v[i].push_back(prime[j]);
                while (tmp % prime[j] == 0) {
                    cnt++;
                    tmp /= prime[j];
                }
            }
        }
        if (tmp > 1) {
            v[i].push_back(tmp);
            cnt++;
        }
        p[cnt&1][a[i]] = i;
    }
    for (int i = 1; i<= n; i++) {
        if (p[0][a[i]]) {
            for (int j = 0; j < v[i].size(); j++) {
                int tmp = a[i] / v[i][j];
                if (!p[1][tmp]) continue;
                g[i-1].push_back(p[1][tmp]-1);
            }
        } else {
            for (int j = 0;  j < v[i].size(); j++) {
                int tmp = a[i] / v[i][j];
                if (!p[0][tmp]) continue;
                g[p[0][tmp]-1].push_back(i-1);
            }
        }
    }
    int cnt = 0;
    memset(mx, -1, sizeof mx);
    memset(my, -1, sizeof my);
    while (find()) {
        memset(used, 0, sizeof used);
        for (int i = 0; i < n; i++) {
            if (mx[i] == -1 && dfs(i)) cnt++;
        }
    }
    printf("Case %d: %d\n", kase, n-cnt);
}
int main() {
    init();
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++) solve(i);
    return 0;
}
