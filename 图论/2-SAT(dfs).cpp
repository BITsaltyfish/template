struct twoSAT {
#define max_V 505
    struct Edge {
        int to, next;
    } E[max_V * max_V];
    int n;
    bool vis[max_V << 1];
    int head[max_V << 1], cnt;
    int S[max_V << 1], c;

    void init(int n) {
        this->n = n;
        for (int i = 0; i < n * 2; i++) {
            head[i] = -1;
            vis[i] = 0;
        }
        cnt = 0;
    }

    void addedge(int u, int v) {
        E[cnt].to = v;
        E[cnt].next = head[u];
        head[u] = cnt++;
    }

    bool dfs(int u) {
        if (vis[u ^ 1]) return 0;
        if (vis[u]) return 1;
        vis[u] = 1;
        S[c++] = u;
        for (int i = head[u]; ~i; i = E[i].next) {
            int v = E[i].to;
            if (!dfs(v)) return 0;
        }
        return 1;
    }

    bool solve() {
        for (int i = 0; i < n * 2; i += 2) {
            if (!vis[i] && !vis[i ^ 1]) {
                c = 0;
                if (!dfs(i)) {
                    while (c) vis[S[--c]] = 0;
                    if (!dfs(i + 1)) return 0;
                }
            }
        }
        return 1;
    }
#undef max_V
};