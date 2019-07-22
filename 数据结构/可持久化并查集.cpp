/* 可持久化线段树维护fa数组即可，按秩合并必需，可以同时加上路径压缩，但是效果未必更好
 * f=1 合并a,b所在集合
 * f=2 回到第k次操作之后状态（查询也算操作）
 * f=3 询问(bool)ab属于一个集合？
 * 注意内存，可能要开大点或者开小点
*/
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
struct segtree {
    int lson, rson, fa, dep; //左右儿子，并查集的fa，并查集集合内深度上限
} t[200010 << 6];
int root[200010], n, m, treesize;
inline void modify(int &k, int old, int x, int y, int pos, int newfa) {
    if (!k) t[k = ++treesize] = (segtree) {0, 0, 0, 0};
    if (x == y) {
        t[k].fa = newfa;
        t[k].dep = t[old].dep;
        return;
    }
    int mid = (x + y) >> 1;
    if (pos <= mid) modify(t[k].lson, t[old].lson, x, mid, pos, newfa);
    else modify(t[k].rson, t[old].rson, mid + 1, y, pos, newfa);
    if (!t[k].lson) t[k].lson = t[old].lson;
    if (!t[k].rson) t[k].rson = t[old].rson;
}
inline void force_modify(int &k, int old, int x, int y, int pos, int newfa) { //区别在于强制新加一条链，没有路径压缩不用写
    t[k = ++treesize] = (segtree) {0, 0, 0, 0};//就这一行改了
    if (x == y) {
        t[k].fa = newfa;
        t[k].dep = t[old].dep;
        return;
    }
    int mid = (x + y) >> 1;
    if (pos <= mid) modify(t[k].lson, t[old].lson, x, mid, pos, newfa);
    else modify(t[k].rson, t[old].rson, mid + 1, y, pos, newfa);
    if (!t[k].lson) t[k].lson = t[old].lson;
    if (!t[k].rson) t[k].rson = t[old].rson;
}
inline int askpos(int &k, int x, int y, int pos) { //返回的是树上的点编号而不是fa的值
    if (x == y) return k;
    int mid = (x + y) >> 1;
    if (pos <= mid) return askpos(t[k].lson, x, mid, pos);
    else return askpos(t[k].rson, mid + 1, y, pos);
}
inline void adddep(int &k, int x, int y, int pos) {
    if (x == y) {
        t[k].dep++;
        return;
    }
    int mid = (x + y) >> 1;
    if (pos <= mid) adddep(t[k].lson, x, mid, pos);
    else adddep(t[k].rson, mid + 1, y, pos);
}
inline int getfa(int &nowroot, int x) { //返回的还是树上的点编号而不是祖先编号
    register int pos = askpos(nowroot, 1, n, x);
    if (t[pos].fa == x) return pos;
    /* 路径压缩
    register int newfa=getfa(nowroot,t[pos].fa);
    force_modify(nowroot,nowroot,1,n,t[pos].fa,t[newfa].fa);
    return newfa;
    */
    return getfa(nowroot, t[pos].fa);
}
inline void merge(int x, int y, int &newroot, int old) {
    int px = getfa(old, x);
    int py = getfa(old, y);
    if (t[px].fa == t[py].fa) {
        newroot = old;
        return;
    }
    if (t[px].dep > t[py].dep) swap(px, py); //按秩合并 px -> py
    modify(newroot, old, 1, n, t[px].fa, t[py].fa);
    if (t[px].dep == t[py].dep) adddep(newroot, 1, n, py);
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) modify(root[0], 0, 1, n, i, i);
    int lastans = 0;
    for (int i = 1; i <= m; i++) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int x, y;
            scanf("%d%d", &x, &y);
            x ^= lastans, y ^= lastans;
            merge(x, y, root[i], root[i - 1]);
        } else if (op == 2) {
            int k;
            scanf("%d", &k);
            k ^= lastans;
            root[i] = root[k];
        } else if (op == 3) {
            root[i] = root[i - 1];
            int x, y;
            scanf("%d%d", &x, &y);
            x ^= lastans, y ^= lastans;
            printf("%d\n", lastans = t[getfa(root[i], x)].fa == t[getfa(root[i], y)].fa);
        }
    }
    return 0;
}