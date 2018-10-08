// 区间加法，单点求值：
#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e4 + 5;
int a[maxn], b[maxn], pos[maxn], L[maxn], R[maxn];
int m;
void modify(int l, int r, int c) {
    for (int i = L[pos[l]]; i <= R[pos[l]]; i++) {
        if (l <= i && i <= r) a[i] += c;
    }
    if (pos[l] == pos[r]) return;
    for (int i = pos[l] + 1; i < pos[r]; i++) b[i] += c;
    for (int i = L[pos[r]]; i <= R[pos[r]]; i++) {
        if (l <= i && i <= r) a[i] += c;
    }
}
int main() {
    int n;
    scanf("%d", &n);
    m = sqrt(n + 0.5);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        pos[i] = (i - 1) / m + 1;
        b[i] = 0;
    }
    int tot = n / m;
    if (n % m) tot++;
    for (int i = 1; i <= tot; i++) {
        L[i] = (i - 1) * m + 1;
        R[i] = i * m;
    }
    R[tot] = n;
    for (int i = 1; i <= n; i++) {
        int op, l, r, c;
        scanf("%d%d%d%d", &op, &l, &r, &c);
        if (op == 0) modify(l, r, c);
        else if (op == 1) printf("%d\n", a[r] + b[pos[r]]);
    }
    return 0;
}
// 区间加法，区间小于某个值的元素之和：
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
const int maxn = 5e4 + 5;
int pos[maxn], L[maxn], R[maxn];
pii a[maxn];
int b[maxn];
int m;
void modify(int l, int r, int c) {
    for (int i = L[pos[l]]; i <= R[pos[l]]; i++) {
        if (l <= a[i].second && a[i].second <= r) a[i].first += c;
    }
    sort(a + L[pos[l]], a + R[pos[l]] + 1);
    if (pos[l] == pos[r]) return;
    for (int i = pos[l] + 1; i < pos[r]; i++) b[i] += c;
    for (int i = L[pos[r]]; i <= R[pos[r]]; i++) {
        if (l <= a[i].second && a[i].second <= r) a[i].first += c;
    }
    sort(a + L[pos[r]], a + R[pos[r]] + 1);
}
int calc(int left, int right, int c) {
    int l = left, r = right, res = 0;
    while (l <= r) {
        int m = (l + r) / 2;
        if (a[m].first < c) {
            res = m - left + 1;
            l = m + 1;
        } else r = m - 1;
    }
    return res;
}
int query(int l, int r, int c) {
    int cnt = 0;
    for (int i = L[pos[l]]; i <= R[pos[l]]; i++) {
        if (l <= a[i].second && a[i].second <= r && a[i].first < c - b[pos[l]]) cnt++;
    }
    if (pos[l] == pos[r]) return cnt;
    for (int i = pos[l] + 1; i < pos[r]; i++) cnt += calc(L[i], R[i], c - b[i]);
    for (int i = L[pos[r]]; i <= R[pos[r]]; i++) {
        if (l <= a[i].second && a[i].second <= r && a[i].first < c - b[pos[r]]) cnt++;
    }
    return cnt;
}
int main() {
    int n;
    scanf("%d", &n);
    m = sqrt(n + 0.5);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i].first);
        a[i].second = i;
        pos[i] = (i - 1) / m + 1;
        b[i] = 0;
    }
    int tot = n / m;
    if (n % m) tot++;
    for (int i = 1; i <= tot; i++) {
        L[i] = (i - 1) * m + 1;
        R[i] = i * m;
    }
    R[tot] = n;
    for (int i = 1; i <= tot; i++) sort(a + L[i], a + R[i] + 1);
    for (int i = 1; i <= n; i++) {
        int op, l, r, c;
        scanf("%d%d%d%d", &op, &l, &r, &c);
        if (op == 0) modify(l, r, c);
        else if (op == 1) printf("%d\n", query(l, r, c * c));
    }
    return 0;
}
// 区间加法，区间小于某个值x的前驱：
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
const int maxn = 1e5 + 5;
int pos[maxn], L[maxn], R[maxn];
pii a[maxn];
int b[maxn];
int m;
void modify(int l, int r, int c) {
    for (int i = L[pos[l]]; i <= R[pos[l]]; i++) {
        if (l <= a[i].second && a[i].second <= r) a[i].first += c;
    }
    sort(a + L[pos[l]], a + R[pos[l]] + 1);
    if (pos[l] == pos[r]) return;
    for (int i = pos[l] + 1; i < pos[r]; i++) b[i] += c;
    for (int i = L[pos[r]]; i <= R[pos[r]]; i++) {
        if (l <= a[i].second && a[i].second <= r) a[i].first += c;
    }
    sort(a + L[pos[r]], a + R[pos[r]] + 1);
}
int calc(int left, int right, int c, int d) {
    int l = left, r = right, res = -1 - d;
    while (l <= r) {
        int m = (l + r) / 2;
        if (a[m].first < c - d) {
            res = a[m].first;
            l = m + 1;
        } else r = m - 1;
    }
    return res;
}
int query(int l, int r, int c) {
    int mx = -1;
    for (int i = L[pos[l]]; i <= R[pos[l]]; i++) {
        if (l <= a[i].second && a[i].second <= r && a[i].first + b[pos[l]] < c) mx = max(mx, a[i].first + b[pos[l]]);
    }
    if (pos[l] == pos[r]) return mx;
    for (int i = pos[l] + 1; i < pos[r]; i++) mx = max(mx, calc(L[i], R[i], c, b[i]) + b[i]);
    for (int i = L[pos[r]]; i <= R[pos[r]]; i++) {
        if (l <= a[i].second && a[i].second <= r && a[i].first + b[pos[r]] < c) mx = max(mx, a[i].first + b[pos[r]]);
    }
    return mx;
}
int main() {
    int n;
    scanf("%d", &n);
    m = sqrt(n + 0.5);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i].first);
        a[i].second = i;
        pos[i] = (i - 1) / m + 1;
        b[i] = 0;
    }
    int tot = n / m;
    if (n % m) tot++;
    for (int i = 1; i <= tot; i++) {
        L[i] = (i - 1) * m + 1;
        R[i] = i * m;
    }
    R[tot] = n;
    for (int i = 1; i <= tot; i++) sort(a + L[i], a + R[i] + 1);
    for (int i = 1; i <= n; i++) {
        int op, l, r, c;
        scanf("%d%d%d%d", &op, &l, &r, &c);
        if (op == 0) modify(l, r, c);
        else if (op == 1) printf("%d\n", query(l, r, c));
    }
    return 0;
}
// 区间加法，区间求和：
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 5e4 + 5;
int pos[maxn], L[maxn], R[maxn];
ll a[maxn], b[maxn], c[maxn];
int n, m, k;
void modify(int l, int r, int d) {
    for (int i = L[pos[l]]; i <= R[pos[l]]; i++) {
        if (l <= i && i <= r) {
            a[i] += d;
            c[pos[l]] += d;
        }
    }
    if (pos[l] == pos[r]) return;
    for (int i = pos[l] + 1; i < pos[r]; i++) {
        b[i] += d;
        c[i] += 1LL * (R[i] - L[i] + 1) * d;
    }
    for (int i = L[pos[r]]; i <= R[pos[r]]; i++) {
        if (l <= i && i <= r) {
            a[i] += d;
            c[pos[r]] += d;
        }
    }
}
int query(int l, int r, int mod) {
    int res = 0;
    for (int i = L[pos[l]]; i <= R[pos[l]]; i++) {
        if (l <= i && i <= r) res = (res + a[i] + b[pos[l]]) % mod;
    }
    if (pos[l] == pos[r]) return res;
    for (int i = pos[l] + 1; i < pos[r]; i++) res = (res + c[i]) % mod;
    for (int i = L[pos[r]]; i <= R[pos[r]]; i++) {
        if (l <= i && i <= r) res = (res + a[i] + b[pos[r]]) % mod;
    }
    return res;
}
int main() {
    scanf("%d", &n);
    m = sqrt(n + 0.5);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        pos[i] = (i - 1) / m + 1;
        b[i] = 0;
        c[pos[i]] += a[i];
    }
    k = n / m;
    if (n % m) k++;
    for (int i = 1; i <= k; i++) {
        L[i] = (i - 1) * m + 1;
        R[i] = i * m;
    }
    R[k] = n;
    for (int i = 1; i <= n; i++) {
        int op, l, r, c;
        scanf("%d%d%d%d", &op, &l, &r, &c);
        if (op == 0) modify(l, r, c);
        else if (op == 1) printf("%d\n", query(l, r, c + 1));
    }
    return 0;
}
// 单点插入，单点询问（带块的分裂）：
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
const int maxn = 2e5 + 5;
int pos[maxn];
vector<int> v[maxn];
int n, m, k;
int s[maxn], top;
void rebuild() {
    top = 0;
    for (int i = 1; i <= k; i++) {
        for (int j = 0; j < v[i].size(); j++) s[++top] = v[i][j];
        v[i].clear();
    }
    m = sqrt(top + 0.5);
    for (int i = 1; i <= top; i++) {
        pos[i] = (i - 1) / m + 1;
        v[pos[i]].push_back(s[i]);
    }
    k = top / m;
    if (top % m) k++;
}
pii query(int x) {
    int id = 1;
    while (x > v[id].size()) x -= v[id].size(), id++;
    return {id, x - 1};
}
void insert(int l, int r) {
    pii res = query(l);
    v[res.first].insert(v[res.first].begin() + res.second, r);
    if (v[res.first].size() > 20 * m) rebuild();
}
int main() {
    scanf("%d", &n);
    m = sqrt(n + 0.5);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &s[i]);
        pos[i] = (i - 1) / m + 1;
        v[pos[i]].push_back(s[i]);
    }
    k = n / m;
    if (n % m) k++;
    for (int i = 1; i <= n; i++) {
        int op, l, r, c;
        scanf("%d%d%d%d", &op, &l, &r, &c);
        if (op == 0) insert(l, r);
        else {
            pii res = query(r);
            printf("%d\n", v[res.first][res.second]);
        }
    }
    return 0;
}
// 区间乘法，区间加法，单点询问：
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 5;
const int mod = 10007;
int pos[maxn], L[maxn], R[maxn];
ll a[maxn], b[maxn], c[maxn];
int n, m, k;
void modify1(int l, int r, int x) {
    for (int i = L[pos[l]]; i <= R[pos[l]] && c[pos[l]] != 1; i++) a[i] = a[i] * c[pos[l]] % mod;
    c[pos[l]] = 1;
    for (int i = L[pos[l]]; i <= R[pos[l]]; i++) {
        if (l <= i && i <= r) a[i] = (a[i] + x) % mod;
    }
    if (pos[l] == pos[r]) return;
    for (int i = pos[l] + 1; i < pos[r]; i++) b[i] = (b[i] + x) % mod;
    for (int i = L[pos[r]]; i <= R[pos[r]] && c[pos[r]] != 1; i++) a[i] = a[i] * c[pos[r]]  % mod;
    c[pos[r]] = 1;
    for (int i = L[pos[r]]; i <= R[pos[r]]; i++) {
        if (l <= i && i <= r) a[i] = (a[i] + x) % mod;
    }
}
void modify2(int l, int r, int x) {
    for (int i = L[pos[l]]; i <= R[pos[l]] && (b[pos[l]] || c[pos[l]] != 1); i++) a[i] = (a[i] * c[pos[l]] % mod + b[pos[l]]) % mod;
    b[pos[l]] = 0;
    c[pos[l]] = 1;
    for (int i = L[pos[l]]; i <= R[pos[l]]; i++) {
        if (l <= i && i <= r) a[i] = a[i] * x % mod;
    }
    if (pos[l] == pos[r]) return;
    for (int i = pos[l] + 1; i < pos[r]; i++) {
        c[i] = c[i] * x % mod;
        b[i] = b[i] * x % mod;
    }
    for (int i = L[pos[r]]; i <= R[pos[r]] && (b[pos[r]] || c[pos[r]] != 1); i++) a[i] = (a[i] * c[pos[r]] % mod + b[pos[r]]) % mod;
    b[pos[r]] = 0;
    c[pos[r]] = 1;
    for (int i = L[pos[r]]; i <= R[pos[r]]; i++) {
        if (l <= i && i <= r) a[i] = a[i] * x % mod;
    }
}
int main() {
    scanf("%d", &n);
    m = sqrt(n + 0.5);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        pos[i] = (i - 1) / m + 1;
    }
    k = n / m;
    if (n % m) k++;
    for (int i = 1; i <= k; i++) {
        b[i] = 0, c[i] = 1;
        L[i] = (i - 1) * m + 1;
        R[i] = i * m;
    }
    R[k] = n;
    for (int i = 1; i <= n; i++) {
        int op, l, r, x;
        scanf("%d%d%d%d", &op, &l, &r, &x);
        if (op == 0) modify1(l, r, x);
        else if (op == 1) modify2(l, r, x);
        else if (op == 2) printf("%lld\n", (a[r] * c[pos[r]] % mod + b[pos[r]]) % mod);
    }
    return 0;
}
// 区间询问等于c的个数，并修改成c：
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 5;
const int mod = 10007;
int pos[maxn], L[maxn], R[maxn];
int a[maxn], b[maxn], tag[maxn];
int n, m, k;
inline void modify(int l, int r, int c) {
    for (int i = L[pos[l]]; i <= R[pos[l]] && tag[pos[l]]; i++) a[i] = b[pos[l]];
    tag[pos[l]] = 0;
    for (int i = L[pos[l]]; i <= R[pos[l]]; i++) {
        if (l <= i && i <= r) a[i] = c;
    }
    if (pos[l] == pos[r]) return;
    for (int i = pos[l] + 1; i < pos[r]; i++) b[i] = c, tag[i] = 1;
    for (int i = L[pos[r]]; i <= R[pos[r]] && tag[pos[r]]; i++) a[i] = b[pos[r]];
    tag[pos[r]] = 0;
    for (int i = L[pos[r]]; i <= R[pos[r]]; i++) {
        if (l <= i && i <= r) a[i] = c;
    }
}
inline int query(int l, int r, int c) {
    int cnt = 0;
    for (int i = L[pos[l]]; i <= R[pos[l]] && tag[pos[l]]; i++) a[i] = b[pos[l]];
    tag[pos[l]] = 0;
    for (int i = L[pos[l]]; i <= R[pos[l]]; i++) {
        if (l <= i && i <= r && a[i] == c) cnt++;
    }
    if (pos[l] == pos[r]) return cnt;
    for (int i = pos[l] + 1; i < pos[r]; i++) {
        if (tag[i]) {
            if (b[i] == c) cnt += R[i] - L[i] + 1;
        } else {
            for (int j = L[i]; j <= R[i]; j++) {
                if (a[j] == c) cnt++;
            }
        }
    }
    for (int i = L[pos[r]]; i <= R[pos[r]] && tag[pos[r]]; i++) a[i] = b[pos[r]];
    tag[pos[r]] = 0;
    for (int i = L[pos[r]]; i <= R[pos[r]]; i++) {
        if (l <= i && i <= r && a[i] == c) cnt++;
    }
    return cnt;
}
int main() {
    scanf("%d", &n);
    m = sqrt(n + 0.5);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        pos[i] = (i - 1) / m + 1;
    }
    k = n / m;
    if (n % m) k++;
    for (int i = 1; i <= k; i++) {
        tag[i] = b[i] = 0;
        L[i] = (i - 1) * m + 1;
        R[i] = i * m;
    }
    R[k] = n;
    for (int i = 1; i <= n; i++) {
        int l, r, c;
        scanf("%d%d%d", &l, &r, &c);
        printf("%d\n", query(l, r, c));
        modify(l, r, c);
    }
    return 0;
}
// 区间众数：
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
const int maxm = 505;
map<int, int> M;
vector<int> v[maxn];
int a[maxn], b[maxn], c[maxn];
int pos[maxn], L[maxm], R[maxm], f[maxm][maxm];
int n, m, k, id;
void init(int j) {
    memset(c, 0, sizeof c);
    int mx = 0, ans = 0;
    for (int i = L[j]; i <= n; i++) {
        c[a[i]]++;
        if (c[a[i]] > mx || (c[a[i]] == mx && b[a[i]] < b[ans])) {
            mx = c[a[i]];
            ans = a[i];
        }
        f[j][pos[i]] = ans;
    }
}
int query(int l, int r, int x) {
    return upper_bound(v[x].begin(), v[x].end(), r) - lower_bound(v[x].begin(), v[x].end(), l);
}
int query(int l, int r) {
    int mx = 0, ans = 0;
    for (int i = L[pos[l]]; i <= R[pos[l]]; i++) {
        if (l <= i && i <= r) {
            int tmp = query(l, r, a[i]);
            if (tmp > mx || (tmp == mx && (b[a[i]] < b[ans]))) {
                mx = tmp;
                ans = a[i];
            }
        }
    }
    if (pos[l] == pos[r]) return ans;
    int tmp = query(l, r, f[pos[l] + 1][pos[r] - 1]);
    if (tmp > mx || (tmp == mx && b[f[pos[l] + 1][pos[r] - 1]] < b[ans])) {
        mx = tmp;
        ans = f[pos[l] + 1][pos[r] - 1];
    }
    for (int i = L[pos[r]]; i <= R[pos[r]]; i++) {
        if (l <= i && i <= r) {
            int tmp = query(l, r, a[i]);
            if (tmp > mx || (tmp == mx && (b[a[i]] < b[ans]))) {
                mx = tmp;
                ans = a[i];
            }
        }
    }
    return ans;
}
int main() {
    scanf("%d", &n);
    m = sqrt(n + 0.5);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        if (!M.count(a[i])) {
            M[a[i]] = ++id;
            b[id] = a[i];
        }
        a[i] = M[a[i]];
        v[a[i]].push_back(i);
        pos[i] = (i - 1) / m + 1;
    }
    k = n / m;
    if (n % m) k++;
    for (int i = 1; i <= k; i++) {
        L[i] = (i - 1) * m + 1;
        R[i] = i * m;
    }
    R[k] = n;
    for (int i = 1; i <= k; i++) init(i);
    for (int i = 1; i <= n; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%d\n", b[query(l, r)]);
    }
    return 0;
}
