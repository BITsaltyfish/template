#define inf 0x3fffffff
#define M 1005  //最大点数
struct edge {
    int v, w, next;
} e[10005];     //估计好有多少条边
int pre[M], cnt, dist[M], n;
bool inq[M];
//注意初始化
void init () {
    cnt = 0;
    memset (pre, -1, sizeof(pre));
}
//注意双向加边
void addedge (int u, int v, int w) {  //加边函数，慢慢模拟就会明白的
    e[cnt].v = v;
    e[cnt].w = w;
    e[cnt].next = pre[u];       //接替已有边
    pre[u] = cnt++;             //自己前插成为u派生的第一条边
}
void spfa (int u) {
    int v, w, i;
    for (i = 1; i <= n; i++) dist[i] = inf, inq[i] = false;
    dist[u] = 0;
    deque<int> q; // 双端队列优化
    q.push_back(u);
    inq[u] = true;
    while (!q.empty()) {
        u = q.front();
        q.pop_front();
        inq[u] = false;
        for (i = pre[u]; i != -1; i = e[i].next) {
            w = e[i].w;
            v = e[i].v;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (!inq[v]) { // 判断负环的方法是看进入队列是否超过n次
                    inq[v] = true;
                    if (!q.empty() || dist[v] < dist[q.front()]) q.push_front(v);
                    else q.push_back(v);
                }
            }
        }
    }
}