/*
 * 点数 N，边数 maxn，INF=0x3f3f3f3f，注意图是单向边还是双向边
 * 小数流量记得加eps
 */
struct Edge {
	int to, cap, next;
} E[maxn];
int head[N], pa[N], vis[N], cnt;
void init() {
	memset(head, -1, sizeof head);
	cnt = 0;
}
void addedge(int u, int v, int w) {
	E[cnt].to = v; E[cnt].cap = w; E[cnt].next = head[u]; head[u] = cnt++;
	E[cnt].to = u; E[cnt].cap = 0; E[cnt].next = head[v]; head[v] = cnt++; // 0 or w
}
bool bfs(int s, int t) {
	memset(vis, -1, sizeof vis);
	queue<int> q;
	vis[s] = 0;
	q.push(s);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int i = head[u]; i != -1; i = E[i].next) {
			int v = E[i].to;
			if (E[i].cap && vis[v] == -1) {
				vis[v] = vis[u] + 1;
				q.push(v);
			}
		}
	}
	return vis[t] != -1;
}
int dfs(int u, int t, int flow) {
	if (u == t) return flow;
	for (int &i = pa[u]; i != -1; i = E[i].next) {
		int v = E[i].to;
		if (E[i].cap && vis[v] == vis[u] + 1) {
			int res = dfs(v, t, min(flow, E[i].cap));
			if (res) {
				E[i].cap -= res;
				E[i ^ 1].cap += res;
				return res;
			} 
		}
	}
	return 0;
}
int Dinic(int s, int t) {
	int max_flow = 0;
	while (bfs(s, t)) {
		memcpy(pa, head, sizeof head);
		int res;
		do {
			res = dfs(s, t, INF);
			max_flow += res;
		} while (res);
	}
	return max_flow;
}