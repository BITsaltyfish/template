/* 动态开点类似于主席树，每次开点需要记录每个点的儿子是谁
 * 例题：hdu6183 - 二维矩形，4种操作，每次可以清除所有点、给点(x,y)添加一种颜色c、查询在(0,y1)与(x,y2)所围成的矩形里有多少种颜色
 * 解法：因为每次查询的矩阵都是从x=0开始到x，因此只需要维护1颗关于y轴值域的50颗关于颜色的线段树即可，对于每个y_i，存这个颜色下出现的最小的 x ，查询是否mi[rt] <= x即可 ，但是因为数据范围较大，但实际上点数不多，需要动态开点或者离线以后离散化
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;
int up = 1e6;
int col[52], ls[maxn << 5], rs[maxn << 5], mi[maxn << 5], idx;
void insert(int &o, int x, int y, int l, int r) {
    if (o == 0) { o = ++idx; mi[o] = x; }
	if (mi[o] == 0 || mi[o] > x) mi[o] = x;
	if (l == r) return;
	int m = (l + r) / 2;
	if (y <= m) insert(ls[o], x, y, l, m);
	else insert(rs[o], x, y, m+1, r);
}
bool query(int o, int x, int y1, int y2, int l, int r) {
    if (!o) return 0;
    if (y1 <= l && r <= y2) return mi[o] <= x;
    int m = (l + r) / 2;
    bool ok = 0;
    if (y1 <= m) ok = query(ls[o], x, y1, y2, l, m);
    if (!ok && y2 > m) ok = query(rs[o], x, y1, y2, m+1, r);
    return ok;
}
int main() {
    int op;
    idx = 0;
    while (~scanf("%d", &op) && op != 3) {
        if (op == 0) {
            memset(col, 0, sizeof col);
            memset(ls, 0, sizeof ls);
            memset(rs, 0, sizeof rs);
            memset(mi, 0, sizeof mi);
        } else if (op == 1) {
            int x, y, c;
            scanf("%d%d%d", &x, &y, &c);
            insert(col[c], x, y, 1, up);
        } else if (op == 2) {
            int x, y1, y2;
            scanf("%d%d%d", &x, &y1, &y2);
            int ans = 0;
            for (int i = 0; i <= 50; i++) ans += query(col[i], x, y1, y2, 1, up);
            printf("%d\n", ans);
        }
    }
    return 0;
}
/* 例题2：Codeforces 915E - 区间修改、区间查询
 * 解法：n很大，但是q很小，用到的点很少，因此线段树动态开点，注意内存10倍以上？
 */
 #include <bits/stdc++.h>
using namespace std;
const int maxn = 1e7 + 5e6 + 5;
int ls[(maxn], rs[maxn], sum[maxn], tag[maxn], idx, rt;
void init() {
    memset(ls, 0, sizeof ls);
    memset(rs, 0, sizeof rs);
    memset(sum, 0, sizeof sum);
    memset(tag, 0, sizeof tag);
    rt = idx = 0;
}
void push_up(int o) {
    sum[o] = sum[ls[o]] + sum[rs[o]];
}
void push_down(int l, int r, int o) {
    if (tag[o] != -1) {
        int m = (l + r) / 2;
        if (l != r) {
            if (!ls[o]) ls[o] = ++idx;
            if (!rs[o]) rs[o] = ++idx;
            tag[ls[o]] = tag[o];
            tag[rs[o]] = tag[o];
            sum[ls[o]] = (m - l + 1) * tag[o];
            sum[rs[o]] = (r - m) * tag[o];
        }
        tag[o] = -1;
    }
}
void update(int ql, int qr, int v, int l, int r, int &o) {
    if (!o) o = ++idx;
    if (ql <= l && r <= qr) {
        if (l != r) tag[o] = v;
        sum[o] = v * (r - l + 1);
        return;
    }
    push_down(l, r, o);
    int m = (l + r) / 2;
    if (ql <= m) update(ql, qr, v, l, m, ls[o]);
    if (qr > m) update(ql, qr, v, m + 1, r, rs[o]);
    push_up(o);
}
int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    init();
    while (q--) {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        if (k == 1) update(l, r, 1, 1, n, rt);
        else if (k == 2) update(l, r, 0, 1, n, rt);
        printf("%d\n", n - sum[rt]);
    }
    return 0;
}