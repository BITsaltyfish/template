void RMQ() {
	for (int j = 1; (1 << j) <= n; j++)
		for (int i = 1; i <= n; i++)
			if (~pa[i][j - 1])
				pa[i][j] = pa[pa[i][j - 1]][j - 1];
}
int LCA(int x, int y) {
	if (deep[x] < deep[y]) swap(x, y);
	int i, j;
	for (i = 0; (1 << i) <= deep[x]; i++); i--;
	for (j = i; j >= 0; j--) // 把深度统一
		if (deep[x] - (1 << j) >= deep[y])
			 x = pa[x][j];
	if (x == y) return x;
	for (j = i; j >= 0; j--) //去找LCA
		if (pa[x][j] != -1 && pa[x][j] != pa[y][j]) {
			x = pa[x][j];
			y = pa[y][j];
		}
	return pa[x][0];
}
/* 例题：Codeforces - 832D - 给3个点任选一个作为终点其他两个为起始点，求两条路径相交的最大值。
 */
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
vector<int> g[maxn];
bool vis[maxn];
int pa[maxn][21], d[maxn];
void dfs(int u, int fa) {
    pa[u][0] = fa; // dfs 先预处理出该点向上爬的倍增结果
    for (int i = 1; i <= 20; i++) pa[u][i] = pa[pa[u][i-1]][i-1];
    for (auto v: g[u]) {
        if (v != fa) {
            d[v] = d[u] + 1;
            dfs(v, u);
        }
    }
}
int LCA(int u, int v) {
    if (d[u] < d[v]) swap(u, v);
    for (int i = 20; i >= 0; i--) {
        if (d[pa[u][i]] >= d[v]) u = pa[u][i];
    }
    if (u == v) return u;
    for (int i = 20; i >= 0; i--) {
        if (pa[u][i] != pa[v][i]) u = pa[u][i], v = pa[v][i];
    }
    return pa[u][0];
}
int dis(int u, int v) {
    int lca = LCA(u, v);
    return d[u] + d[v] - 2 * d[lca];
}

int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    for (int i = 2; i <= n; i++) {
        int to;
        scanf("%d", &to);
        g[i].push_back(to);
        g[to].push_back(i);
    }
    memset(pa, 0, sizeof pa);
    memset(d, 0, sizeof d);
    dfs(1, 1);
    while (q--) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        int ab = dis(a, b), bc = dis(b, c), ac = dis(a, c);
        int len1 = (ab + bc - ac) / 2 + 1, len2 = (ab + ac - bc) / 2 + 1, len3 = (ac + bc - ab) / 2 + 1;
        printf("%d\n", max(len1, max(len2, len3)));
    }
    return 0;
}
