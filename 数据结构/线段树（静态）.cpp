//这是一个区间加和RMQ
class SegmentTree {
public:
#define lson (root << 1)
#define rson (root << 1 | 1)
#define lent (t[root].r - t[root].l + 1)
#define lenl (t[lson].r - t[lson].l + 1)
#define lenr (t[rson].r - t[rson].l + 1)
	struct Tree {
		int l, r, val, lazy;
	} t[maxn << 4];

	void pushup(int root) {
		t[root].val = t[lson].val + t[rson].val;
	}

	void pushdown(int root) {
		if (t[root].lazy) {
			t[lson].lazy += t[root].lazy;
			t[rson].lazy += t[root].lazy;
			t[lson].val += lenl * t[root].lazy;
			t[rson].val += lenr * t[root].lazy;
			t[root].lazy = 0;		
		}
	}
	
	void build(int l, int r, int root) {
		t[root].l = l;
		t[root].r = r;
		t[root].lazy = 0;
		if (l == r) {
			t[root].val = 0;
			return;
		}
		int mid = l + r >> 1;
		build(l, mid, lson);
		build(mid + 1, r, rson);
		pushup(root);
	}
	
	void update(int l, int r, int val, int root) {
		if (l <= t[root].l && t[root].r <= r) {
			t[root].val += lent * val;
			t[root].lazy += val;
			return;
		}
		pushdown(root);
		int mid = t[root].l + t[root].r >> 1;
		if (l <= mid) update(l, r, val, lson);
		if (r > mid) update(l, r, val, rson);
		pushup(root);
	}

	int query(int l, int r, int root) {
		if (l <= t[root].l && t[root].r <= r)
			return t[root].val;
		pushdown(root);
		int mid = t[root].l + t[root].r >> 1;
		int ans = 0;
		if (l <= mid) ans += query(l, r, lson);
		if (r > mid) ans += query(l, r, rson);
		return ans;
	}
#undef lenr
#undef lenl
#undef lent
#undef rson
#undef lson
};
// new HDU-5828
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 5;
int a[maxn];
class SegmentTree {
public:
#define ls (rt<<1)
#define rs (rt<<1|1)
    struct Tree {
        int l, r;
        ll mi, mx, tag, sum;
    } t[maxn << 2];

    inline int treelen(int rt) { return t[rt].r - t[rt].l + 1; }

    inline void push_up(int rt) {
        t[rt].mi = min(t[ls].mi, t[rs].mi);
        t[rt].mx = max(t[ls].mx, t[rs].mx);
        t[rt].sum = t[ls].sum + t[rs].sum;
    }

    inline void push_down(int rt) {
        if (t[rt].tag) {
            t[ls].tag += t[rt].tag;
            t[rs].tag += t[rt].tag;
            t[ls].mi += t[rt].tag;
            t[rs].mi += t[rt].tag;
            t[ls].mx += t[rt].tag;
            t[rs].mx += t[rt].tag;
            t[ls].sum += treelen(ls) * t[rt].tag;
            t[rs].sum += treelen(rs) * t[rt].tag;
            t[rt].tag = 0;
        }
    }

    void build(int l, int r, int rt) {
        t[rt].l = l,  t[rt].r = r, t[rt].tag = 0;
        if (l == r) {
            t[rt].mi = t[rt].mx = t[rt].sum = a[l];
            return;
        }
        int m = l + r >> 1;
        build(l, m, ls);
        build(m + 1, r, rs);
        push_up(rt);
    }

    void update(int l, int r, int rt) {
        if (l <= t[rt].l && t[rt].r <= r) {
            if (t[rt].mi == t[rt].mx) {
                ll tmp = sqrt(t[rt].mx + 0.5);
                ll sub = t[rt].mx - tmp;
                t[rt].sum -= sub * treelen(rt);
                t[rt].tag -= sub;
                t[rt].mi = t[rt].mx = tmp;
                return;
            } else if (t[rt].mi == t[rt].mx - 1) {
                ll tmp1 = sqrt(t[rt].mx + 0.5);
                ll tmp2 = sqrt(t[rt].mi + 0.5);
                if (tmp2 == tmp1 - 1) {
                    ll sub = t[rt].mx - tmp1;
                    t[rt].sum -= sub * treelen(rt);
                    t[rt].tag -= sub;
                    t[rt].mx = tmp1, t[rt].mi = tmp2;
                    return;
                }
            }
        }
        push_down(rt);
        int m = t[rt].l + t[rt].r >> 1;
        if (l <= m) update(l, r, ls);
        if (r > m) update(l, r, rs);
        push_up(rt);
    }

    void update(int l, int r, int x, int rt) {
        if (l <= t[rt].l && t[rt].r <= r) {
            t[rt].sum +=  1LL * treelen(rt) * x;
            t[rt].mi += x;
            t[rt].mx += x;
            t[rt].tag += x;
            return;
        }
        push_down(rt);
        int m = t[rt].l + t[rt].r >> 1;
        if (l <= m) update(l, r, x, ls);
        if (r > m) update(l, r, x, rs);
        push_up(rt);
    }

    ll query(int l, int r, int rt) {
        if (l <= t[rt].l && t[rt].r <= r) return t[rt].sum;
        push_down(rt);
        int m = t[rt].l + t[rt].r >> 1;
        ll ans = 0;
        if (l <= m) ans += query(l, r, ls);
        if (r > m) ans += query(l, r, rs);
        return ans;
    }
#undef ls
#undef rs
#undef lt
#undef ll
#undef lr
} T;
int main() {
    int t, n, m;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        T.build(1, n, 1);
        while (m--) {
            int op, l, r, x;
            scanf("%d%d%d", &op, &l, &r);
            if (op == 1) {
                scanf("%d", &x);
                T.update(l, r, x, 1);
            } else if (op == 2) T.update(l, r, 1);
            else printf("%lld\n", T.query(l, r, 1));
        }
    }
    return 0;
}