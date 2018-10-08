/* 例题1：Codeforces 617E - 对每个查询区间，计算有多少个子区间异或为k
 * 解法：预处理异或前缀，一个区间[L,R]的异或值=sum[R]^sum[L-1]
 *     接下来发现如果已知一个区间很容易推到相邻区间信息，因此可以用莫队维护
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 5;
const int maxk = 2e6 + 5;
struct Query {
    int l, r, id;
    ll ans;
} q[maxn];
int pos[maxn], BLOCK;
inline bool cmp1(const Query& x, const Query& y) { return pos[x.l] < pos[y.l]|| (pos[x.l] == pos[y.l] && x.r < y.r); }
inline bool cmp2(const Query& x, const Query& y) { return x.id < y.id; }
int pre[maxn], vis[maxk];
ll res;
int n, m, k;
void modify(int p, bool op) {
    if (op == 0) {
        vis[pre[p]]--;
        res -= vis[pre[p] ^ k];
    } else if (op == 1) {
        res += vis[pre[p] ^ k];
        vis[pre[p]]++;
    }
}
int main() {
    scanf("%d%d%d", &n, &m, &k);
    BLOCK = sqrt(n + 0.5);
    pre[0] = 0;
    for (int i = 1; i <= n; i++) {
        int a;
        scanf("%d", &a);
        pre[i] = pre[i - 1] ^ a;
        pos[i] = (i - 1) / BLOCK + 1;
    }
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &q[i].l, &q[i].r);
        q[i].id = i;
    }
    sort(q, q + m, cmp1);
    int L = 0, R = 0; // 维护左区间
    memset(vis, 0, sizeof vis);
    res = 0;
    for (int i = 0; i < m; i++) {
        int l = q[i].l, r = q[i].r;
        while (L < l - 1) modify(L, 0), L++;
        while (L >= l) modify(L - 1, 1), L--;
        while (R <= r) modify(R, 1), R++;
        while (R > r + 1) modify(R - 1, 0), R--;
        q[i].ans = res;
    }
    sort(q, q + m, cmp2);
    for (int i = 0; i < m; i++) printf("%lld\n", q[i].ans);
    return 0;
}
/* 例题2：Codeforces 940F - n个整数，m次操作
 *      一种是查询[l,r]的mex{c1,...,c109}，c_x指 x 出现的次数，另一种是修改某个整数的值
 * 解法：把查询分块，按顺序暴力修改，即带修改的莫队
 */
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
const int maxn = 1e5 + 10;
/* head */
struct Change { // origin y, now x
    int p, x, y;
} c[maxn];
struct Query {
    int l, r, t, ans, id;
} q[maxn];
int pos[maxn];
bool cmp1(const Query& x, const Query& y) {
    if (pos[x.l] == pos[y.l]) {
        if (pos[x.r] == pos[y.r]) return x.t < y.t;
        return pos[x.r] < pos[y.r];
    }
    return pos[x.l] < pos[y.l];
}
bool cmp2(const Query& x, const Query& y) {
    return x.id < y.id;
}
map<int, int> M;
int a[maxn], b[maxn];
int num[maxn << 1], cnt[maxn];
void update(int x, int v) {
    if (num[x] > 0) cnt[num[x]]--;
    num[x] += v;
    if (num[x] > 0) cnt[num[x]]++;
}
void modify(int p, int x, int l, int r) {
    if (l <= p && p <= r) {
        update(a[p], -1);
        update(x, 1);
    }
    a[p] = x;
}
int calc() {
    int i = 1;
    while (i) {
        if (!cnt[i]) return i;
        i++;
    }
}
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int block = pow(n, 2.0 / 3.0); // 带修改莫队一般块大小取 n^{2/3)
    int idx = 0;
    rep(i, 1, n + 1) {
        scanf("%d", &a[i]);
        if (!M.count(a[i])) M[a[i]] = ++idx;
        int tmp = M[a[i]];
        b[i] = a[i] = tmp;
        pos[i] = i / block + 1;
    }
    int q_cnt = 0, c_cnt = 0;
    rep(i, 1, m + 1) {
        int op, x, y;
        scanf("%d%d%d", &op, &x, &y);
        if (op == 1) q[++q_cnt] = { x, y, c_cnt, 0, q_cnt };
        else if (op == 2) {
            if (!M.count(y)) M[y] = ++idx;
            int tmp = M[y];
            c[++c_cnt] = { x, tmp, b[x] };
            b[x] = tmp;
        }
    }
    sort(q + 1, q + q_cnt + 1, cmp1);
    int v = 0, l = 1, r = 0;
    rep(i, 1, q_cnt + 1) {
        int T = q[i].t, L = q[i].l, R = q[i].r;
        while (v < T) modify(c[v + 1].p, c[v + 1].x, l, r), v++;
        while (v > T) modify(c[v].p, c[v].y, l, r), v--;
        while (l < L) update(a[l], -1), l++;
        while (l > L) update(a[l - 1], 1), l--;
        while (r < R) update(a[r + 1], 1), r++;
        while (r > R) update(a[r], -1), r--;
        q[i].ans = calc();
    }
    sort(q + 1, q + q_cnt + 1, cmp2);
    rep(i, 1, q_cnt + 1) printf("%d\n", q[i].ans);
    return 0;
}