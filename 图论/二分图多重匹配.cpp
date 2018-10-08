/* 例题：POJ-2289 有一个通讯录,里面有n个人,现在要把他们分成m组,给出每个人的名字,和想要把他们分在的组号.求怎么分组,能使人数最多的那个组的人最少.
 * 解法：二分这个人数,看最大匹配是否为n,最后输出这个人数.
 */
#include <bits/srdc++.h>
using namespace std;
const int maxn = 1005;
const int maxm = 505;
vector<int> g[maxn];
int match[maxn][maxm], a[maxn];
bool vis[maxn];
bool dfs(int u) {
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (!vis[v]) {
            vis[v] = 1;
            if (match[v][0] < a[v]) {
                match[v][++match[v][0]] = u;
                return 1;
            }
            for (int j = 1; j <= match[v][0]; j++) {
                if (dfs(match[v][j])) {
                    match[v][j] = u;
                    return 1;
                }
            }
        }
    }
    return 0;
}
inline bool check(int x, int n) {
    memset(match, -1, sizeof match);
    for (int i = 0; i < n; i++) {
        a[i] = x;
        match[i][0] = 0;
    }
    int res = 0;
    for (int i = 0; i < n; i++) {
        memset(vis, 0, sizeof vis);
        if (dfs(i)) res++;
    }
    return res == n;
}
char s[maxn][maxm];
int main() {
    int n, m;
    while (~scanf("%d%d", &n, &m), n + m) {
        for (int i = 0; i < n; i++) g[i].clear();
        for (int i = 0; i < n; i++) {
            scanf("%s", s[i]);
            while (getchar() != '\n') {
                int v;
                scanf("%d", &v);
                g[i].push_back(v);
            }
        }
        int l = 0, r = n, ans = 0;
        while (l <= r) {
            int mid = l + r >> 1;
            if (check(mid, n)) {
                ans = mid;
                r = mid - 1;
            } else l = mid + 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}
