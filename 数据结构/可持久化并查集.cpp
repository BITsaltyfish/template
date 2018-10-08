/*
 * �ɳ־û��߶���ά��fa���鼴�ɣ����Ⱥϲ����裬����ͬʱ����·��ѹ��������Ч��δ�ظ���
 * f=1 �ϲ�a,b���ڼ���
 * f=2 �ص���k�β���֮��״̬����ѯҲ�������
 * f=3 ѯ��(bool)ab����һ�����ϣ�
 * ע���ڴ棬����Ҫ�������߿�С��
*/
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
struct segtree {
    int lson, rson, fa, dep; //���Ҷ��ӣ����鼯��fa�����鼯�������������
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
inline void force_modify(int &k, int old, int x, int y, int pos, int newfa) { //��������ǿ���¼�һ������û��·��ѹ������д
    t[k = ++treesize] = (segtree) {0, 0, 0, 0};//����һ�и���
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
inline int askpos(int &k, int x, int y, int pos) { //���ص������ϵĵ��Ŷ�����fa��ֵ
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
inline int getfa(int &nowroot, int x) { //���صĻ������ϵĵ��Ŷ��������ȱ��
    register int pos = askpos(nowroot, 1, n, x);
    if (t[pos].fa == x) return pos;
    /* ·��ѹ��
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
    if (t[px].dep > t[py].dep) swap(px, py); //���Ⱥϲ� px -> py
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