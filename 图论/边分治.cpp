/* 例题：HDU 5039 一颗树，每条边的属性为0 或1，求有多少条路径经过奇数条属性为1 的边。一种是查询操作，一种是修改边的属性。
 */
const int MAXN = 30010;
const int INF = 0x3f3f3f3f;
struct Edge {
    int to, next;
    int f;
} edge[MAXN * 2];
int head[MAXN], tot;
void init() {
    tot = 0;
    memset(head, −1, sizeof(head));
}
void addedge(int u, int v, int f) {
    edge[tot].to = v;
    edge[tot].next = head[u];
    edge[tot].f = f;
    head[u] = tot++;
}
long long ans;
int num0[MAXN], num1[MAXN];
long long tnum[MAXN];
struct Node {
    int l0, l1;
    int r0, r1;
    int cc;
    long long sum;
    Node gao(int u) {
        l0 = r0 = num0[u];
        l1 = r1 = num1[u];
        sum = tnum[u];
        cc = 0;
        return *this;
    }
};
int pos[MAXN];
int val[MAXN];
int fa[MAXN];
int cnt[MAXN];
int col[MAXN];
int link[MAXN];
int CHANGEU;
struct chain {
    vector<int>uu;
    vector<Node>nde;
    int n;
    void init() {
        n = uu.size();
        nde.resize(n << 2);
        for(int i = 0; i < n; i++)pos[uu[i]] = i;
        build(0, n−1, 1);
    }
    void up(int l, int r, int p) {
        int mid = (l + r) >> 1;
        nde[p].cc = nde[p << 1].cc ^ nde[(p << 1) | 1].cc ^ val[uu[mid]];
        nde[p].l0 = nde[p << 1].l0;
        nde[p].l1 = nde[p << 1].l1;
        if(nde[p << 1].cc ^ val[uu[mid]]) {
            nde[p].l0 += nde[(p << 1) | 1].l1;
            nde[p].l1 += nde[(p << 1) | 1].l0;
        } else {
            nde[p].l0 += nde[(p << 1) | 1].l0;
            nde[p].l1 += nde[(p << 1) | 1].l1;
        }
        nde[p].r0 = nde[(p << 1) | 1].r0;
        nde[p].r1 = nde[(p << 1) | 1].r1;
        if(nde[(p << 1) | 1].cc ^ val[uu[mid]]) {
            nde[p].r0 += nde[p << 1].r1;
            nde[p].r1 += nde[p << 1].r0;
        } else {
            nde[p].r0 += nde[p << 1].r0;
            nde[p].r1 += nde[p << 1].r1;
        }
        if(val[uu[mid]] == 0) {
            nde[p].sum = nde[p << 1].sum + nde[(p << 1) | 1].sum +
                         (long long)nde[p << 1].r0 * nde[(p << 1) | 1].l1 +
                         (long long)nde[p << 1].r1 * nde[(p << 1) | 1].l0;
        } else {
            nde[p].sum = nde[p << 1].sum + nde[(p << 1) | 1].sum +
                         (long long)nde[p << 1].r0 * nde[(p << 1) | 1].l0 +
                         (long long)nde[p << 1].r1 * nde[(p << 1) | 1].l1;
        }
    }
    void build(int l, int r, int p) {
        if(l == r) {
            nde[p].gao(uu[l]);
            return;
        }
        int mid = (l + r) / 2;
        build(l, mid, p << 1);
        build(mid + 1, r, (p << 1) | 1);
        up(l, r, p);
    }
    void update(int k, int l, int r, int p) {
        if(l == r) {
            nde[p].gao(uu[k]);
            return;
        }
        int mid = (l + r) / 2;
        if(k <= mid)update(k, l, mid, p << 1);
        else update(k, mid + 1, r, (p << 1) | 1);
        up(l, r, p);
    }
    int change(int y) {
        int x = uu.back();
        int p = fa[x];
        if(p) {
            if(x == CHANGEU)val[x] ^= 1;
            if(val[x]) {
                tnum[p] − = (long long)nde[1].r0 * (num0[p]−nde[1].r1)
                              ;
                tnum[p] − = (long long)nde[1].r1 * (num1[p]−nde[1].r0)
                              ;
                num0[p] − = nde[1].r1;
                num1[p] − = nde[1].r0;
            } else {
                tnum[p] − = (long long)nde[1].r1 * (num0[p]−nde[1].r0)
                              ;
                tnum[p] − = (long long)nde[1].r0 * (num1[p]−nde[1].r1)
                              ;
                num0[p] − = nde[1].r0;
                num1[p] − = nde[1].r1;
            }
            if(x == CHANGEU)val[x] ^= 1;
        }
        ans − = nde[1].sum;
        update(pos[y], 0, n−1, 1);
        if(p) {
            if(val[x]) {
                tnum[p] += (long long)nde[1].r0 * num0[p];
                tnum[p] += (long long)nde[1].r1 * num1[p];
                num0[p] += nde[1].r1;
                num1[p] += nde[1].r0;
            } else {
                tnum[p] += (long long)nde[1].r0 * num1[p];
                tnum[p] += (long long)nde[1].r1 * num0[p];
                num0[p] += nde[1].r0;
                num1[p] += nde[1].r1;
            }
        }
        ans += nde[1].sum;
        return p;
    }
} ch[MAXN];
void dfs1(int u, int pre) {
    chain &c = ch[u];
    c.uu.clear();
    int v, x = 0;
    cnt[u] = 1;
    for(int i = head[u]; i != −1; i = edge[i].next) {
        v = edge[i].to;
        if(v == pre)continue;
        dfs1(v, u);
        link[i / 2] = v;
        val[v] = edge[i].f;
        cnt[u] += cnt[v];
        fa[v] = u;
        if(cnt[v] > cnt[x]) x = v;
    }
    if(!x)col[u] = u;
    else col[u] = col[x];
    ch[col[u]].uu.push_back(u);
    num0[u] = 1;
    num1[u] = 0;
    tnum[u] = 0;

}
void dfs2(int x) {
    x = col[x];
    chain &c = ch[x];
    int n = c.uu.size();
    int u, v;
    for(int i = 1; i < n; i++) {
        u = c.uu[i];
        for(int j = head[u]; j != −1; j = edge[j].next) {
            v = edge[j].to;
            if(v == c.uu[i−1] || fa[u] == v)continue;
            dfs2(v);
            if(val[v]) {
                tnum[u] += (long long)num0[u] * ch[col[v]].nde[1].r0 + (long long)num1[u] * ch[col[v]].nde[1].r1;
                num0[u] += ch[col[v]].nde[1].r1;
                num1[u] += ch[col[v]].nde[1].r0;
            } else {
                tnum[u] += (long long)num1[u] * ch[col[v]].nde[1].r0 + (long long)num0[u] * ch[col[v]].nde[1].r1;
                num0[u] += ch[col[v]].nde[1].r0;
                num1[u] += ch[col[v]].nde[1].r1;
            }
        }
    }
    c.init();
    ans += c.nde[1].sum;
}
char str[100];
char str1[100], str2[100];
int main() {
    int T;
    int iCase = 0;
    scanf("%d", &T);
    int n;
    while(T−−) {
        ans = 0;
        iCase++;
        scanf("%d", &n);
        map<string, int>mp;
        init();
        for(int i = 1; i <= n; i++) {
            scanf("%s", str);
            mp[str] = i;
        }
        int u, v, f;
        for(int i = 1; i < n; i++) {
            scanf("%s%s%d", str1, str2, &f);
            addedge(mp[str1], mp[str2], f);
            addedge(mp[str2], mp[str1], f);
        }
        int Q;
        char op[10];
        scanf("%d", &Q);
        printf("Case␣#%d:\n", iCase);
        val[1] = 0;
        fa[1] = 0;
        dfs1(1, 1);
        dfs2(1);
        while(Q−−) {
            scanf("%s", op);
            if(op[0] == 'Q') {
                printf("%I64d\n", ans * 2);
            } else {
                int id ;
                scanf("%d", &id);
                id−−;
                u = link[id];
                val[u] ^= 1;
                CHANGEU = u;
                while(u)
                    u = ch[col[u]].change(u);
            }
        }
    }
    return 0;
}