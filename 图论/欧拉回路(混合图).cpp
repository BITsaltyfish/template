// 最大流部分SAP
const int MAXN = 210;
const int MAXM = 20100;
const int INF = 0x3f3f3f3f;
struct Edge {
    int to, next, cap, flow;
} edge[MAXM];
int tol;
int head[MAXN];
int gap[MAXN], dep[MAXN], pre[MAXN], cur[MAXN];
void init() {
    tol = 0;
    memset(head, −1, sizeof(head));
}
void addedge(int u, int v, int w, int rw = 0) {
    edge[tol].to = v;
    edge[tol].cap = w;
    edge[tol].next = head[u];
    edge[tol].flow = 0;
    head[u] = tol++;
    edge[tol].to = u;
    edge[tol].cap = rw;
    edge[tol].next = head[v];
    edge[tol].flow = 0;
    head[v] = tol++;
}
int sap(int start, int end, int N) {
    memset(gap, 0, sizeof(gap));
    memset(dep, 0, sizeof(dep));
    memcpy(cur, head, sizeof(head));
    int u = start;
    pre[u] = −1;
    gap[0] = N;
    int ans = 0;
    while(dep[start] < N) {
        if(u == end) {
            int Min = INF;
            for(int i = pre[u]; i != −1; i = pre[edge[i ^ 1].to])
                if(Min > edge[i].cap − edge[i].flow)
                    Min = edge[i].cap − edge[i].flow;
            for(int i = pre[u]; i != −1; i = pre[edge[i ^ 1].to]) {
                edge[i].flow += Min;
                edge[i ^ 1].flow − = Min;
            }
            u = start;
            ans += Min;
            continue;
        }
        bool flag = false;
        int v;
        for(int i = cur[u]; i != −1; i = edge[i].next) {
            v = edge[i].to;
            if(edge[i].cap − edge[i].flow && dep[v] + 1 == dep[u]) {
                flag = true;
                cur[u] = pre[v] = i;
                break;
            }
        }
        if(flag) {
            u = v;
            continue;
        }
        int Min = N;
        for(int i = head[u]; i != −1; i = edge[i].next)
            if(edge[i].cap − edge[i].flow && dep[edge[i].to] < Min) {
                Min = dep[edge[i].to];
                cur[u] = i;
            }
        gap[dep[u]]−−;
        if(!gap[dep[u]])return ans;
        dep[u] = Min + 1;
        gap[dep[u]]++;
        if(u != start)u = edge[pre[u] ^ 1].to;
    }
    return ans;
}
//the end of 最大流部分
int in[MAXN], out[MAXN]; //每个点的出度和入度
int main() {
    int T;
    int n, m;
    scanf("%d", &T);
    while(T−−) {
        scanf("%d%d", &n, &m);
        init();
        int u, v, w;
        memset(in, 0, sizeof(in));
        memset(out, 0, sizeof(out));
        while(m−−) {
            scanf("%d%d%d", &u, &v, &w);
            out[u]++;
            in[v]++;
            if(w == 0)//双向
                addedge(u, v, 1);
        }
        bool flag = true;
        for(int i = 1; i <= n; i++) {
            if(out[i] − in[i] > 0)
                addedge(0, i, (out[i] − in[i]) / 2);
            else if(in[i] − out[i] > 0)
                addedge(i, n + 1, (in[i] − out[i]) / 2);
            if((out[i] − in[i]) & 1)
                flag = false;
        }
        if(!flag) {
            printf("impossible\n");
            continue;
        }
        sap(0, n + 1, n + 2);
        for(int i = head[0]; i != −1; i = edge[i].next)
            if(edge[i].cap > 0 && edge[i].cap > edge[i].flow) {
                flag = false;
                break;
            }
        if(flag) printf("possible\n");
        else printf("impossible\n");
    }
    return 0;
}