struct node {
	int to, val;
	friend bool operator< (const node& a, const node& b) {
		return a.val > b.val;
	}
};
vector<node> g[maxn];
int dis[maxn];
int dijkstra(int s, int t, int n) {
	fill(dis, dis + n + 1, INF);
	priority_queue<node> q;
	dis[s] = 0;
	q.push({s, 0});
	while (!q.empty()) {
		int u = q.top().to; q.pop();
		int sz = SZ(g[u]);
		for (int i = 0; i < sz; i++) {
			int v = g[u][i].to, w = g[u][i].val;
			if (dis[v] > dis[u] + w)
				q.push({v, dis[v] = dis[u] + w});
		}
	}
	return dis[t];
}