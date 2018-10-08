// codeforces - 406D
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define rep(i,a,n) for (int i=a;i<n;i++)
typedef long long ll;
const int maxn = 1e5 + 10;
/* head */
vector<int> g[maxn];
struct Query {
	int to, next, id;
} q[maxn << 1];
int head[maxn], fa[maxn], ans[maxn], cnt;
bool vis[maxn];
void addedge(int u, int v, int id) {
	q[cnt].id = id, q[cnt].to = v, q[cnt].next = head[u], head[u] = cnt++;
	q[cnt].id = id, q[cnt].to = u, q[cnt].next = head[v], head[v] = cnt++;
}
int pa[maxn];
inline void init(int n) {
	cnt = 0;
	memset(head, -1, sizeof head);
	memset(vis, 0, sizeof vis);
	rep(i, 1, n + 1) pa[i] = i;
}
int find(int x) {
	if (pa[x] == x) return x;
	return pa[x] = find(pa[x]);
}
inline void merge(int u, int v) {
	int fu = find(u);
	int fv = find(v);
	if (fu != fv) pa[fu] = fv;
}
void dfs(int u) {
	fa[u] = u;
	vis[u] = 1;
	for (auto v: g[u]) {
		if (!vis[v]) {
			dfs(v);
			merge(u, v);
			fa[find(v)] = u;
		}
	}
	for (int i = head[u]; ~i; i = q[i].next) {
		int v = q[i].to;
		if (vis[v]) ans[q[i].id] = fa[find(v)];
	}
}
struct Point {
	ll x, y;
	Point operator- (const Point& rhs) const {
		return { x - rhs.x, y - rhs.y };
	}
} p[maxn];
inline bool cross(const Point& A, const Point& B) { return A.x * B.y - A.y * B.x > 0; }
int s[maxn], top;
inline void solve() {
	int n, m;
	scanf("%d", &n);
	rep(i, 1, n + 1) scanf("%lld%lld", &p[i].x, &p[i].y);
	init(n);
	top = 0;
	for (int i = n; i >= 1; i--) {
		while (top > 1 && cross(p[s[top]] - p[i], p[s[top - 1]] - p[i])) top--;
		s[++top] = i;
		if (top > 1) g[s[top - 1]].pb(s[top]);
	}
	scanf("%d", &m);
	rep(i, 1, m + 1) {
		int u, v;
		scanf("%d%d", &u, &v);
		addedge(u, v, i);
	}
	dfs(n); // 应该要找入度为0的点作为根dfs下去，这题建树特点可以看出n是根，所以省去了找根的步骤
	rep(i, 1, m + 1) {
		if (i == 1) printf("%d", ans[i]);
		else printf(" %d", ans[i]);
	}
	puts("");
}
int main() {
	solve();
	return 0;
}