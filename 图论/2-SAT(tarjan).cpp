/* 强连通缩点法、
 * 连边、跑tarjan
 * 判可行性，即同一集合中的两个点是否同属一个强连通块
 * 缩点建新图，连反边、拓扑序，若当前点没有被访问过，则选择该点，不选择其另外的点
 * 连边：
     a->b即选a必选b
     a、b不能同时选：选了a就要选b'，选了b就要选a'
     a、b必须同时选：选了a就要选b，选了b就要选a，选了a'就要选b'，选了b'就要选a'
     a、b必须选一个：选了a就要选b'，选了b就要选a'，选了a'就要选b，选了b'就要选a
     a必须选：a'->a。
 */
#include <bits/stdc++.h>
#define ll long long
#define inf 0x3f3f3f3f
#define pa pair<int,int>
#define mkp make_pair
#define N 2010
#define M 200100
#define p(x) ((x)*2)
#define q(x) ((x)*2-1)
using namespace std;
//===============================================
struct edge {
    int to, next;
} e[M];
int head[N], cnt;
inline void ins(int u, int v) {
    e[++cnt].to = v;
    e[cnt].next = head[u];
    head[u] = cnt;
}
//===============================================
int n;
int dfn[N], low[N], belong[N], cnt2, scc;
int zhan[N], top;
bool instack[N];
void dfs(int x) {
    dfn[x] = low[x] = ++scc;
    zhan[++top] = x;
    instack[x] = 1;
    for (int i = head[x]; i; i = e[i].next) {
        if (!dfn[e[i].to]) {
            dfs(e[i].to);
            low[x] = min(low[x], low[e[i].to]);
        } else if (instack[e[i].to])low[x] = min(low[x], dfn[e[i].to]);
    }
    if (low[x] == dfn[x]) {
        cnt2++;
        int tmp;
        do {
            tmp = zhan[top--];
            belong[tmp] = cnt2;
            instack[tmp] = 0;
        } while (x != tmp);
    }
}
inline bool solve() {
    scc = cnt2 = top = 0;
    memset(belong, 0, sizeof belong);
    memset(dfn, 0, sizeof dfn);
    memset(low, 0, sizeof low);
    memset(instack, 0, sizeof instack);
    for (int i = 1; i <= 2 * n; i++)if(!dfn[i])dfs(i);
    for (int i = 1; i <= 2 * n; i += 2)if (belong[i] == belong[i + 1])return 0;
    return 1;
}
int l, r;
struct pnt {
    int x, y;
} p[1010];
inline void build() {
    memset(head, 0, sizeof head);
    cnt = 0;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (p[i].x == p[j].x && abs(p[i].y - p[j].y) < 2 * r - 1) {
                ins(p(j), q(i));
                ins(p(i), q(j));
            } else if (p[i].y == p[j].y && abs(p[i].x - p[j].x) < 2 * r - 1) {
                ins(q(i), p(j));
                ins(q(j), p(i));
            }
}
int main() {
    scanf("%d%d%d", &l, &r, &n);
    for (int i = 1; i <= n; i++)scanf("%d%d", &p[i].x, &p[i].y);
    build();
    if(solve())puts("YES");
    else puts("NO");
}
