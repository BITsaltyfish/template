#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
class XORbase {
#define HIGH 62
public:
    ll b[HIGH], nb[HIGH]
    int tot;

    void Init() {
        memset(b, 0, sizeof b);
        memset(nb, 0, sizeof nb);
    }

    void Insert(ll x) {
        per(i, 0, HIGH) {
            if (x & (1LL << i)) {
                if (!b[i]) {
                    b[i] = x;
                    break;
                } else x ^= b[i];
            }
        }
    }

    void Init(ll x) {
        memset(b, 0, sizeof b);
        Insert(x);
        tot = 0;
    }

    ll Query_max(ll x = 0) {
        ll res = x;
        per(i, 0, HIGH) res = max(res, res ^ b[i]);
        return res;
    }

    ll Query_min(ll x = 0) {
        ll res = x;
        rep(i, 0, HIGH) {
            if (b[i]) res ^= b[i];
        }
        return res;
    }

    void Rebuild() {
        tot = 0;
        per(i, 0, HIGH) {
            per(j, 0, i) {
                if (b[i] & (1LL << j)) b[i] ^= b[j];
            }
        }
        rep(i, 0, HIGH) {
            if (b[i]) nb[tot++] = b[i];
        }
    }

    ll Query_Kth(ll k) { // 需要先rebuild
        ll res = 0;
        per(i, 0, HIGH) {
            if (k & (1LL << i)) res ^= nb[i];
        }
        return res;
    }

    friend XORbase operator+ (const XORbase &x, const XORbase &y) { // 两个线性向量合并
        XORbase res = x;
        per(i, 0, HIGH) if (y.b[i]) res.Insert(y.b[i]);
        return res;
    }
#undef HIGH
};

/*
 * 例题1：K大异或和
 * 解法：那么就从高位到低位贪心，每碰到一位，看看需不需要异或上它就好了。
 *      其中若这n个数都是线性无关的，那么k要加1，因为不能表示出0。
 */
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define Close() ios::sync_with_stdio(0),cin.tie(0)
typedef long long ll;
/* head */
class XORbase {
#define HIGH 64
public:
    ll b[HIGH];
    int sz, n;

    void Init() {
        memset(b, 0, sizeof b);
    }

    void Insert(ll x) {
        per(i, 0, HIGH) {
            if (x & (1LL << i)) {
                if (!b[i]) {
                    b[i] = x;
                    break;
                } else x ^= b[i];
            }
        }
    }

    void Init(ll x) {
        memset(b, 0, sizeof b);
        Insert(x);
    }

    void Init(int _n) {
        n = _n;
        sz = 0;
        rep(i, 0, HIGH) {
            rep(j, i + 1, HIGH) {
                if ((b[j] >> i) & 1) b[j] ^= b[i];
            }
        }
        rep(i, 0, HIGH) if (b[i]) b[sz++] = b[i];
    }

    ll Calc(ll k) {
        if (sz != n) k--;
        if (k > (1LL << sz) - 1) return -1;
        ll res = 0;
        rep(i, 0, HIGH) if (k & (1LL << i)) res ^= b[i];
        return res;
    }

    friend XORbase operator+ (const XORbase &x, const XORbase &y) {
        XORbase res = x;
        per(i, 0, HIGH) if (y.b[i]) res.Insert(y.b[i]);
        return res;
    }
#undef HIGH
} e;
int main() {
    Close();
    int n, q;
    ll k;
    cin >> n;
    e.Init();
    rep(i, 1, n + 1) {
        ll x;
        cin >> x;
        e.Insert(x);
    }
    e.Init(n);
    cin >> q;
    while (q--) {
        cin >> k;
        cout << e.Calc(k) << endl;
    }
    return 0;
}

/*
 * 例题2：「SCOI2016」幸运数字 - 树上查询u,v路径上选一些点异或起来最大
 * 解法：树链剖分维护一段路径的线性基，暴力合并
 */
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
typedef long long ll;
const int maxn = 4e4 + 10;
/* head */
class XORbase {
public:
    ll b[62];

    void Init() {
        memset(b, 0, sizeof b);
    }

    void Insert(ll x) {
        per(i, 0, 61) {
            if (x & (1LL << i)) {
                if (!b[i]) {
                    b[i] = x;
                    break;
                } else x ^= b[i];
            }
        }
    }

    void Init(ll x) {
        memset(b, 0, sizeof b);
        Insert(x);
    }

    ll Calc() {
        ll res = 0;
        per(i, 0, 61) res = max(res, res ^ b[i]);
        return res;
    }

    friend XORbase operator+ (const XORbase &x, const XORbase &y) {
        XORbase res = x;
        per(i, 0, 61) if (y.b[i]) res.Insert(y.b[i]);
        return res;
    }

};
ll a[maxn];
class SegmentTree {
public:
#define lson (root << 1)
#define rson (root << 1 | 1)
#define lent (t[root].r - t[root].l + 1)
#define lenl (t[lson].r - t[lson].l + 1)
#define lenr (t[rson].r - t[rson].l + 1)
    struct Tree {
        int l, r;
        XORbase v;
    } t[maxn << 2];

    void pushup(int root) {
        t[root].v = t[lson].v + t[rson].v;
    }

    void build(int l, int r, int root) {
        t[root].l = l;
        t[root].r = r;
        t[root].v.Init();
        if (l == r) {
            return;
        }
        int mid = l + r >> 1;
        build(l, mid, lson);
        build(mid + 1, r, rson);
        pushup(root);
    }

    void update(int l, int r, ll x, int root) {
        if (l <= t[root].l && t[root].r <= r) {
            t[root].v.Insert(x);
            return;
        }
        int mid = t[root].l + t[root].r >> 1;
        if (l <= mid) update(l, r, x, lson);
        if (r > mid) update(l, r, x, rson);
        pushup(root);
    }

    XORbase query(int l, int r, int root) {
        if (l <= t[root].l && t[root].r <= r)
            return t[root].v;
        int mid = t[root].l + t[root].r >> 1;
        XORbase ans;
        ans.Init();
        if (l <= mid) ans = ans + query(l, r, lson);
        if (r > mid) ans = ans + query(l, r, rson);
        return ans;
    }
#undef lenr
#undef lenl
#undef lent
#undef rson
#undef lson
} T;
struct Edge {
    int to, next;
    Edge() {}
    Edge(int a, int b) {
        to = a;
        next = b;
    }
} E[maxn << 1];
int head[maxn], cnt, tot;
int top[maxn], son[maxn], size[maxn], deep[maxn], pa[maxn], id[maxn];
inline void init() {
    memset(head, -1, sizeof head);
    tot = cnt = 0;
}
inline void addedge(int u, int v) {
    E[cnt].to = v;
    E[cnt].next = head[u];
    head[u] = cnt++;
}
inline void dfs1(int u, int fa, int d) {
    size[u] = 1;
    deep[u] = d;
    son[u] = 0;
    for (int i = head[u]; ~i; i = E[i].next) {
        int v = E[i].to;
        if (v != fa) {
            dfs1(v, u, d + 1);
            pa[v] = u;
            size[u] += size[v];
            if (size[v] > size[son[u]]) son[u] = v;
        }
    }
}
void dfs2(int u, int first) {
    top[u] = first;
    id[u] = ++tot;
    if (son[u]) dfs2(son[u], first);
    for (int i = head[u]; ~i; i = E[i].next) {
        int v = E[i].to;
        if (v != pa[u] && v != son[u]) dfs2(v, v);
    }
}
XORbase calc(int u, int v) {
    int x = top[u], y = top[v];
    XORbase res;
    res.Init();
    while (x != y) {
        if (deep[x] < deep[y]) {
            swap(u, v);
            swap(x, y);
        }
        res = res + T.query(id[x], id[u], 1);
        u = pa[x];
        x = top[u];
    }
    if (deep[u] > deep[v]) swap(u, v);
    res = res + T.query(id[u], id[v], 1);
    return res;
}
int main() {
    int n, q;
    init();
    scanf("%d%d", &n, &q);
    rep(i, 1, n + 1) scanf("%lld", &a[i]);
    rep(i, 1, n) {
        int u, v;
        scanf("%d%d", &u, &v);
        addedge(u, v);
        addedge(v, u);
    }
    dfs1(1, 0, 1);
    dfs2(1, 1);
    T.build(1, tot, 1);
    rep(i, 1, n + 1) T.update(id[i], id[i], a[i], 1);
    while (q--) {
        int x, y;
        ll ans = 0;
        scanf("%d%d", &x, &y);
        XORbase res = calc(x, y);
        per(i, 0, 61) ans = max(ans, ans ^ res.b[i]);
        printf("%lld\n", ans);
    }
    return 0;
}
/*
 * 例题3：BZOJ - 2115 - 边权图求1-n的最大Xor和路径，存在重边，允许经过重复点、重复边。
 * 解法：路径一定是由许多的环和一条从1到n的路径组成。因此预处理所有环的Xor，维护线性基取Max即可
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int>P;
const int INF = 0x3f3f3f3f, maxn = 50005;
int n, m, vis[maxn], tot, head[maxn];
ll dis[maxn], base[66];
vector<ll>a;
struct node {
    int v, next;
    ll w;
} g[200005];
void add(int u, int v, ll w) {
    g[tot].v = v, g[tot].next = head[u], g[tot].w = w, head[u] = tot++;
}
void dfs(int u, ll d) {
    dis[u] = d, vis[u] = 1;
    for(int i = head[u]; ~i; i = g[i].next) {
        int v = g[i].v;
        ll w = g[i].w;
        if(vis[v])a.push_back(dis[u]^dis[v]^w);
        else dfs(v, dis[u]^w);
    }
}
int main() {
    while(~scanf("%d%d", &n, &m)) {
        a.clear();
        tot = 0;
        for(int i = 1; i <= n; i++)vis[i] = 0, head[i] = -1;
        while(m--) {
            int u, v;
            ll w;
            scanf("%d%d%lld", &u, &v, &w);
            add(u, v, w), add(v, u, w);
        }
        dfs(1, 0);
        ll ans = dis[n];
        memset(base, 0, sizeof(base));
        for(int i = 0; i < a.size(); i++)
            for(int j = 62; j >= 0; j--)
                if((a[i] >> j) & 1) {
                    if(!base[j]) {
                        base[j] = a[i];
                        break;
                    } else a[i] ^= base[j];
                }
        for(int i = 62; i >= 0; i--)ans = max(ans, ans ^ base[i]);
        printf("%lld\n", ans);
    }
    return 0;
}