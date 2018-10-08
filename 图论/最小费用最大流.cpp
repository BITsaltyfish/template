struct Edge {
	int from, to, cap, flow, cost;
	Edge(int a, int b, int c, int d, int E) { from = a; to = b; cap = c; flow = d; cost = E; }
};
class MCMF {
public:
#define max_V 202
	int n, m, s, t;
	vector<Edge> edges;
	vector<int> g[max_V];
	bool vis[max_V];
	int d[max_V], p[max_V], a[max_V];

	void Init(int n) {
		this->n = n;
		rep(i, 0, n) g[i].clear();
		edges.clear();
	}

	void Addedge(int u, int v, int c, int w) {
		edges.pb(Edge(u, v, c, 0, w));
		edges.pb(Edge(v, u, 0, 0, -w));
		int m = SZ(edges);
		g[u].pb(m - 2);
		g[v].pb(m - 1);
	}

	bool Spfa(int s, int t, int &flow, int &cost) {
		fill(d, d + n, INF);
		memset(vis, 0, sizeof vis);
		d[s] = 0; vis[s] = 1; p[s] = 0; a[s] = INF;
		queue<int> q;
		q.push(s);
		while (!q.empty()) {
			int u = q.front(); q.pop();
			vis[u] = 0;
			int sz = SZ(g[u]);
			rep(i, 0, sz) {
				Edge& E = edges[g[u][i]];
				if (E.cap > E.flow && d[E.to] > d[u] + E.cost) {
					d[E.to] = d[u] + E.cost;
					p[E.to] = g[u][i];
					a[E.to] = min(a[u], E.cap - E.flow);
					if (!vis[E.to]) {
						vis[E.to] = 1;
						q.push(E.to);
					}
				}
			}
		}
		if (d[t] == INF) return 0;
		flow += a[t];
		cost += d[t] * a[t];
		int u = t;
		while (u != s) {
			edges[p[u]].flow += a[t];
			edges[p[u] ^ 1].flow -= a[t];
			u = edges[p[u]].from;
		}
		return 1;
	}

	int MincostMaxflow(int s, int t) {
		int flow = 0, cost = 0;
		while (Spfa(s, t, flow, cost));
		return cost;
	}
#undef max_V
};