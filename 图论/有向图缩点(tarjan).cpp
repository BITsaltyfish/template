/* tarjan缩点找出度为0点 
 */
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
const int maxn = 1e4 + 10;
/* head */
int low[maxn], dfn[maxn];
bool vis[maxn];
int belong[maxn], son[maxn], scc, cnt;
vector<int> g[maxn];
stack<int> s;
int out[maxn];
inline void init() {
    memset(dfn, 0, sizeof dfn);
    memset(low, 0, sizeof low);
    memset(son, 0, sizeof son);
    memset(vis, 0, sizeof vis);
    cnt = scc = 0;
    memset(out, 0, sizeof out);
}
void tarjan(int u) {
    low[u] = dfn[u] = ++cnt;
    s.push(u);
    vis[u] = 1;
    for (int v: g[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (vis[v]) low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) {
        ++scc;
        int v;
        do {
            v = s.top();
            s.pop();
            vis[v] = 0;
            belong[v] = scc;
            son[scc]++;
        } while (u != v);
    }
}
inline void rebuild(int n) {
    rep(u, 1, n + 1) {
        for (int v: g[u]) {
            if (belong[v] != belong[u]) {
                ++out[belong[u]];
            }
        }
    }
}
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    init();
    while (m--) {
        int a, b;
        scanf("%d%d", &a, &b);
        g[a].push_back(b);
    }
    rep(i, 1, n + 1) if (!dfn[i]) tarjan(i);
    rebuild(n);
    int ans = 0;
    rep(i, 1, scc + 1) {
        if (!out[i]) {
            ans = son[i];
            break;
        }
    }
    printf("%d\n", ans);
    return 0;
}
/* 例题：codeforces - 962F 找简单边双连通分量 并输出
 */
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
const int maxn = 1e5 + 5;
struct Edge {
    int to, id, next;
} e[maxn << 1];
int head[maxn], cnt;
int low[maxn], dfn[maxn];
bool vis[maxn];
int belong[maxn], block, dep;
stack<int> s;
vector<int> ans;
inline void init() {
    memset(head, -1, sizeof head);
    memset(dfn, 0, sizeof dfn);
    memset(low, 0, sizeof low);
    memset(vis, 0, sizeof vis);
    memset(belong, 0, sizeof belong);
    block = cnt = dep = 0;
    while (!s.empty()) s.pop();
}
inline void addedge(int u, int v, int t) {
    e[cnt].to = v;
    e[cnt].id = t;
    e[cnt].next = head[u];
    head[u] = cnt++;
}
void tarjan(int u, int fa) {
    dfn[u] = low[u] = ++dep;
    for (int i = head[u]; ~i; i = e[i].next) {
        int v = e[i].to;
        if (v == fa) continue;
        if (!dfn[v]) {
            s.push(i);
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                block++;
                bool ok = 1;
                vector<int> a;
                int tmp;
                do {
                    tmp = s.top(); s.pop();
                    int x = e[tmp].to;
                    a.push_back(e[tmp].id);
                    if (belong[x] != block) belong[x] = block;
                    else ok = 0;
                } while (tmp != i);
                if (ok && a.size() > 1) {
                    for (int j: a) ans.push_back(j);
                }
            }
        } else if (dfn[v] < dfn[u]) {
            low[u] = min(low[u], dfn[v]);
            s.push(i);
        }
    }
}
int main() {
    int n, m;
    init();
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        addedge(u, v, i);
        addedge(v, u, i);
    }
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) tarjan(i, -1);
    }
//    for (int i = 1; i <= n; i++) printf("%d\n", belong[i]);
//    puts("");
    sort(ans.begin(), ans.end());
    unique(ans.begin(), ans.end());
    printf("%d\n", ans.size());
    for (int i = 0; i < ans.size(); i++) {
        if (i == 0) printf("%d", ans[i]);
        else printf(" %d", ans[i]);
    }
    puts("");
    return 0;
}