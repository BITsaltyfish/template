// 点权式 - 配合线段树的单点修改+区间查询
struct Edge {
	int to, next;
	Edge() {}
	Edge(int a, int b) { to = a; next = b; }
} E[maxn << 1];
int head[maxn], cnt, tot;
int top[maxn], son[maxn], size[maxn], deep[maxn], pa[maxn], id[maxn];
int a[maxn];
void init() {
	memset(head, -1, sizeof head);
	tot = cnt = 0;
}
void addedge(int u, int v) {
	E[cnt].to = v;
	E[cnt].next = head[u];
	head[u] = cnt++;
}
void dfs1(int u, int fa, int d) { // 处理出重链
	size[u] = 1; deep[u] = d; son[u] = 0;
	for (int i = head[u]; ~i; i = E[i].next) {
		int v = E[i].to;
		if (v != fa) {
			dfs1(v, u, d + 1);
			pa[v] = u;
			size[u] += size[v];
			if (size[v] > size[son[u]]) son[u] = v;
		}
	}
}
void dfs2(int u, int first) {
	top[u] = first;
	id[u] = ++tot;
	if (son[u]) dfs2(son[u], first);
	for (int i = head[u]; ~i; i = E[i].next) {
		int v = E[i].to;
		if (v != pa[u] && v != son[u]) dfs2(v, v);
	}
}
void solve(int u, int v) { // 跑LCA同时计算答案
	int x = top[u], y = top[v], res = 0;
	while (x != y) {
		if (deep[x] < deep[y]) {
			swap(u, v);
			swap(x, y);
		}
		res += T.query(id[x], id[u], 1);
		u = pa[x];
		x = top[u];
	}
	if (deep[u] > deep[v]) swap(u, v);
	res += T.query(id[u], id[v], 1);
	printf("%d\n", res);
}
// 边权式：把边权偏移到深度较大的点，化成点权式
struct Point {
	int from, to, val;
} p[maxn];
struct Edge {
	int to, next;
} E[maxn << 1];
int head[maxn], cnt, tot;
int top[maxn], son[maxn], size[maxn], deep[maxn], pa[maxn], id[maxn];
int a[maxn];
void init() {
	memset(head, -1, sizeof head);
	tot = cnt = 0;
}
void addedge(int u, int v) {
	E[cnt].to = v;
	E[cnt].next = head[u];
	head[u] = cnt++;
}
void dfs1(int u, int fa, int d) {
	size[u] = 1; deep[u] = d; son[u] = 0;
	for (int i = head[u]; ~i; i = E[i].next) {
		int v = E[i].to;
		if (v != fa) {
			dfs1(v, u, d + 1);
			pa[v] = u;
			size[u] += size[v];
			if (size[v] > size[son[u]]) son[u] = v;
		}
	}
}
void dfs2(int u, int first) {
	top[u] = first;
	id[u] = ++tot;
	if (son[u]) dfs2(son[u], first);
	for (int i = head[u]; ~i; i = E[i].next) {
		int v = E[i].to;
		if (v != pa[u] && v != son[u]) dfs2(v, v);
	}
}
int solve(int u, int v) {
	int x = top[u], y = top[v];
	int ans = 0;
	while (x != y) {
		if (deep[x] < deep[y]) {
			swap(u, v);
			swap(x, y);
		}
		ans += T.query(id[x], id[u], 1);
		u = pa[x];
		x = top[u];
	}
	//	printf("%d : %d - %d : ", ans, u, v);
	if (deep[u] > deep[v])
		swap(u, v);
	if (u != v) ans += T.query(id[son[u]], id[v], 1);
	return ans;
}
/* 例题：POJ 2763 - 给一颗树，边之间有权值，两种操作
 *     第一种：求任意两点的权值和，第二，修改树上两点的权值。
 */
 #include <bits/stdc++.h>
using namespace std;
#define maxn 100010
/* head */
class SegmentTree {
public:
#define lson root << 1
#define rson root << 1 | 1
#define lent (t[root].r - t[root].l + 1)
#define lenl (t[lson].r - t[lson].l + 1)
#define lenr (t[rson].r - t[rson].l + 1)
    struct Tree {
        int l, r, val;
    } t[maxn << 4];

    void pushup(int root) {
        t[root].val = t[lson].val + t[rson].val;
    }
    
    void build(int l, int r, int root) {
        t[root].l = l;
        t[root].r = r;
        if (l == r) {
            t[root].val = 0;
            return;
        }
        int mid = l + r >> 1;
        build(l, mid, lson);
        build(mid + 1, r, rson);
        pushup(root);
    }
    
    void update(int l, int r, int val, int root) {
        if (l <= t[root].l && t[root].r <= r) {
            t[root].val = val;
            return;
        }
        int mid = t[root].l + t[root].r >> 1;
        if (l <= mid) update(l, r, val, lson);
        if (r > mid) update(l, r, val, rson);
        pushup(root);
    }

    int query(int l, int r, int root) {
        if (l <= t[root].l && t[root].r <= r) return t[root].val;
        int mid = t[root].l + t[root].r >> 1;
        int ans = 0;
        if (l <= mid) ans += query(l, r, lson);
        if (r > mid) ans += query(l, r, rson);
        return ans;
    }
#undef lenr
#undef lenl
#undef lent
#undef rson
#undef lson
} T;
struct Point {
    int from, to, val;
} p[maxn];
struct Edge {
    int to, next;
} E[maxn << 1];
int head[maxn], cnt, tot;
int top[maxn], son[maxn], size[maxn], deep[maxn], pa[maxn], id[maxn];
int a[maxn];
void init() {
    memset(head, -1, sizeof head);
    tot = cnt = 0;
}
void addedge(int u, int v) {
    E[cnt].to = v;
    E[cnt].next = head[u];
    head[u] = cnt++;
}
void dfs1(int u, int fa, int d) {
    size[u] = 1; deep[u] = d; son[u] = 0;
    for (int i = head[u]; ~i; i = E[i].next) {
        int v = E[i].to;
        if (v != fa) {
            dfs1(v, u, d + 1);
            pa[v] = u;
            size[u] += size[v];
            if (size[v] > size[son[u]]) son[u] = v;
        }
    }
}
void dfs2(int u, int first) {
    top[u] = first;
    id[u] = ++tot;
    if (son[u]) dfs2(son[u], first);
    for (int i = head[u]; ~i; i = E[i].next) {
        int v = E[i].to;
        if (v != pa[u] && v != son[u]) dfs2(v, v);
    }
}
int solve(int u, int v) {
    int x = top[u], y = top[v];
    int ans = 0;
    while (x != y) {
        if (deep[x] < deep[y]) {
            swap(u, v);
            swap(x, y);
        }
        ans += T.query(id[x], id[u], 1);
        u = pa[x];
        x = top[u];
    }
    if (deep[u] > deep[v]) swap(u, v);
    if (u != v) ans += T.query(id[son[u]], id[v], 1);
    return ans;
}
int main() {
    int n, m, q;
    while (~scanf("%d%d%d", &n, &q, &m)) {
        init();
        for (int i = 1; i < n; i++) {
            scanf("%d%d%d", &p[i].from, &p[i].to, &p[i].val);
            addedge(p[i].from, p[i].to);
            addedge(p[i].to, p[i].from);
        }
        dfs1(1, 0, 1);
        dfs2(1, 1);
        T.build(1, tot, 1);
        for (int i = 1; i < n; i++) {
            if (deep[p[i].from] < deep[p[i].to]) swap(p[i].from, p[i].to);
            T.update(id[p[i].from], id[p[i].from], p[i].val, 1);
        }
        while (q--) {
            int op, x, y;
            scanf("%d%d", &op, &x);
            if (op) {
                scanf("%d", &y);
                T.update(id[p[x].from], id[p[x].from], y, 1);
            } else {
                printf("%d\n", solve(m, x));
                m = x;
            }
        }
    }
    return 0;
}