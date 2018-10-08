// 对于二分图类型的比较高效
const int MAXN = 100;
const int MAXM = 20000;
const int INF = 0x3f3f3f3f;
struct Edge {
    int to, next, cap, flow, cost;
    Edge(int _to = 0, int _next = 0, int _cap = 0, int _flow = 0, int _cost = 0): to(_to), next(_next), cap(_cap), flow(_flow), cost(_cost) {}
} edge[MAXM];
struct ZKW_MinCostMaxFlow {
    int head[MAXN], tot;
    int cur[MAXN];
    int dis[MAXN];
    bool vis[MAXN];
    int ss, tt, N; //源点、汇点和点的总个数（编号是0∼N-1）, 不需要额外赋值，调用会直接赋值
    int min_cost, max_flow;
    void init() {
        tot = 0;
        memset(head, −1, sizeof(head));
    }
    void addedge(int u, int v, int cap, int cost) {
        edge[tot] = Edge(v, head[u], cap, 0, cost);
        head[u] = tot++;
        edge[tot] = Edge(u, head[v], 0, 0, −cost);
        head[v] = tot++;
    }
    int aug(int u, int flow) {
        if(u == tt)return flow;
        vis[u] = true;
        for(int i = cur[u]; i != −1; i = edge[i].next) {
            int v = edge[i].to;
            if(edge[i].cap > edge[i].flow && !vis[v] && dis[u] == dis[v] + edge[i].cost) {
                int tmp = aug(v, min(flow, edge[i].cap−edge[i].flow));
                edge[i].flow += tmp;
                edge[i ^ 1].flow − = tmp;
                cur[u] = i;
                if(tmp)return tmp;
            }
        }
        return 0;
    }
    bool modify_label() {
        int d = INF;
        for(int u = 0; u < N; u++)
            if(vis[u])
                for(int i = head[u]; i != −1; i = edge[i].next) {
                    int v = edge[i].to;
                    if(edge[i].cap > edge[i].flow && !vis[v])
                        d = min(d, dis[v] + edge[i].cost−dis[u]);
                }
        if(d == INF)return false;
        for(int i = 0; i < N; i++)
            if(vis[i]) {
                vis[i] = false;
                dis[i] += d;

            }
        return true;
    }
    /*
    * 直接调用获取最小费用和最大流
    * 输入: start-源点，end-汇点，n-点的总个数（编号从0 开始）
    * 返回值: pair<int,int> 第一个是最小费用，第二个是最大流
    */
    pair<int, int> mincostmaxflow(int start, int end, int n) {
        ss = start, tt = end, N = n;
        min_cost = max_flow = 0;
        for(int i = 0; i < n; i++)dis[i] = 0;
        while(1) {
            for(int i = 0; i < n; i++)cur[i] = head[i];
            while(1) {
                for(int i = 0; i < n; i++)vis[i] = false;
                int tmp = aug(ss, INF);
                if(tmp == 0)break;
                max_flow += tmp;
                min_cost += tmp * dis[ss];
            }
            if(!modify_label())break;
        }
        return make_pair(min_cost, max_flow);
    }
} solve;