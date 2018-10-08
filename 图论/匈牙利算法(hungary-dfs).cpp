/* 算二分图最大匹配，dfs版
 * 以下是二分图左右点已经分开的版本，往下翻还有左右点没分开的版本
 * 编号(1)~(n1)的点是第一个集合，编号(n1+1)~(n2)的点是第二个集合
*/
#define M 2010
#define N 1010
struct edge {
    int to, next;
} e[M];
int head[N], cnt;
bool hungary_mrk[N];
int match[N];
inline void ins(int u, int v) {
    e[++cnt].to = v;
    e[cnt].next = head[u];
    head[u] = cnt;
}
inline void insert(int u, int v) {
    ins(u, v);
    ins(v, u);
}
bool hungary_dfs(int x) {
    for (int i = head[x]; i; i = e[i].next)
        if (!hungary_mrk[e[i].to]) {
            int now = e[i].to;
            hungary_mrk[now] = 1;
            if (!match[now] || hungary_dfs(match[now])) {
                match[now] = x;
                match[x] = now;
                return 1;
            }
        }
    return 0;
}
inline int hungary(int n1, int n2) {
    int tot = 0;
    memset(match, 0, sizeof(match));
    for (int i = 1; i <= n1; i++) {
        if (!match[i])memset(hungary_mrk, 0, sizeof(hungary_mrk));
        if (hungary_dfs(i))tot++;
    }
    return tot;
}
//以上是二分图左右已经分开的版本
//以下是二分图左右编号打乱的版本
#define M 2010
#define N 1010
struct edge {
    int to, next;
} e[M];
int head[N], cnt;
bool hungary_mrk[N];
int hungary_left[N];
int match[N];
inline void ins(int u, int v) {
    e[++cnt].to = v;
    e[cnt].next = head[u];
    head[u] = cnt;
}
inline void insert(int u, int v) {
    ins(u, v);
    ins(v, u);
}
bool hungary_dfs(int x) {
    for (int i = head[x]; i; i = e[i].next)
        if (!hungary_mrk[e[i].to]) {
            int now = e[i].to;
            hungary_mrk[now] = 1;
            if (!match[now] || hungary_dfs(match[now])) {
                match[now] = x;
                match[x] = now;
                return 1;
            }
        }
    return 0;
}
inline void hungary_remark(int x, int op) {
    hungary_left[x] = op;
    for (int i = head[x]; i; i = e[i].next)
        if (hungary_left[e[i].to] == -1)hungary_remark(e[i].to, op ^ 1);
}
inline int hungary(int n) {
    memset(hungary_left, -1, sizeof(hungary_left));
    for (int i = 1; i <= n; i++)if (hungary_left[i] == -1)hungary_remark(i, 1);
    int tot = 0;
    memset(match, 0, sizeof(match));
    for (int i = 1; i <= n; i++)
        if(hungary_left[i]) {
            if (!match[i])memset(hungary_mrk, 0, sizeof(hungary_mrk));
            if (hungary_dfs(i))tot++;
        }
    return tot;
}