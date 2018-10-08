/* 记得初始化 T+1 个点*/
struct Edge {
	int from, to, cap, flow;
};
class ISAP {
public:
#define max_V 202
	int n, m, s, t;
	vector<Edge> edges;
	vector<int> g[max_V];
	bool vis[max_V];
	int d[max_V], cur[max_V], p[max_V], num[max_V];

	void Addedge(int u, int v, int w) {
		edges.pb((Edge) {
			u, v, w, 0
		});
		edges.pb((Edge) {
			v, u, 0, 0
		});
		m = SZ(edges);
		g[u].pb(m - 2);
		g[v].pb(m - 1);
	}

	bool Bfs() {
		memset(vis, 0, sizeof vis);
		queue<int> q;
		q.push(t);
		vis[t] = 1;
		d[t] = 0;
		while (!q.empty()) {
			int u = q.front(); q.pop();
			int sz = SZ(g[u]);
			rep(i, 0, sz) {
				Edge &E = edges[g[u][i] ^ 1];
				if (!vis[E.from] && E.cap > E.flow) {
					vis[E.from] = 1;
					d[E.from] = d[u] + 1;
					q.push(E.from);
				}
			}
		}
		return vis[s];
	}

	void ClearAll(int n) {
		this->n = n;
		rep(i, 0, n) g[i].clear();
		edges.clear();
	}

	void ClearFlow() {
		int sz = SZ(edges);
		rep(i, 0, sz) edges[i].flow = 0;
	}

	int Augment() {
		int x = t, a = INF;
		while (x != s) {
			Edge &E = edges[p[x]];
			a = min(a, E.cap - E.flow);
			x = edges[p[x]].from;
		}
		x = t;
		while (x != s) {
			edges[p[x]].flow += a;
			edges[p[x] ^ 1].flow -= a;
			x = edges[p[x]].from;
		}
		return a;
	}

	int MaxFlow(int s, int t) {
		this->s = s; this->t = t;
		int flow = 0;
		Bfs();
		memset(num, 0, sizeof num);
		rep(i, 0, n) num[d[i]]++;
		int x = s;
		memset(cur, 0, sizeof cur);
		while (d[s] < n) {
			if (x == t) {
				flow += Augment();
				x = s;
			}
			bool ok = 0;
			int sz = SZ(g[x]);
			rep(i, cur[x], sz) {
				Edge &E = edges[g[x][i]];
				if (E.cap > E.flow && d[x] == d[E.to] + 1) {
					ok = 1;
					p[E.to] = g[x][i];
					cur[x] = i;
					x = E.to;
					break;
				}
			}
			if (!ok) {
				int m = n - 1;
				rep(i, 0, sz) {
					Edge &E = edges[g[x][i]];
					if (E.cap > E.flow)
						m = min(m, d[E.to]);
				}
				if (--num[d[x]] == 0) break; // gap
				num[d[x] = m + 1]++;
				cur[x] = 0;
				if (x != s) x = edges[p[x]].from;
			}
		}
		return flow;
	}

	vector<int> Mincut() {
		Bfs();
		vector<int> ans;
		int sz = SZ(edges);
		rep(i, 0, sz) {
			Edge &E = edges[i];
			if (!vis[E.from] && vis[E.to] && E.cap > 0)
				ans.pb(i);
		}
		return ans;
	}

	void Reduce() {
		int sz = SZ(edges);
		rep(i, 0, sz) {
			edges[i].cap -= edges[i].flow;
		}
	}

	void Print() {
		puts("Graph:");
		int sz = SZ(edges);
		rep(i, 0, sz) {
			printf("%d->%d, %d, %d\n", edges[i].from, edges[i].to, edges[i].cap, edges[i].flow);
		}
	}
#undef max_V
};