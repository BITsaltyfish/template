/* ====================一维==========================
 * add单点修改，ask区间前缀和查询，如果改成单点查询区间修改 add(x,z),add(y+1,-z)然后ask(t)
 */
#define mx 1000010
ll c[mx];
int n, q;
inline void add(int x, int d) {
    for (int i = x; i < mx; i += i & (-i))c[i] += d;
}
inline ll ask(int x) {
    ll sum = 0;
    for (int i = x; i; i -= i & (-i))sum += c[i];
    return sum;
}
// ===================一维区间修改，区间查询===========================
#define mx 1000010
ll c1[mx], c2[mx];
void modify(int x, int y) {
    for(int i = x; i < mx; i += i & (-i))c1[i] += y, c2[i] += (ll)x * y;
}
// 差分数组中位置x加上y
void add(int l, int r, int x) {
    modify(l, x);    // 区间加x
    modify(r + 1, -x);
}
ll ask(int x) { // 查询前缀和
    ll ans(0);
    for(int i = x; i; i -= i & (-i)) ans += (ll)(x + 1) * c1[i] - c2[i];
    return ans;
}
// ===================二维区间修改，区间查询===========================
#define y1 y1234
#define mx 2060
ll c1[mx][mx], c2[mx][mx], c3[mx][mx], c4[mx][mx];
void modify(int x, int y, ll z) { // 差分数组中位置(x,y)加上z
    for(int i = x; i < mx; i += i & -i) {
        for (int j = y; j < mx; j += j & -j) {
            c1[i][j] += z;
            c2[i][j] += z * x;
            c3[i][j] += z * y;
            c4[i][j] += z * x * y;
        }
    }
}
void add(int x1, int y1, int x2, int y2, ll x) { // 区间加x
    x2++;
    y2++;
    modify(x2, y2, x);
    modify(x1, y2, -x);
    modify(x2, y1, -x);
    modify(x1, y1, x);
}
ll query(int x, int y) {
    ll ans = 0;
    for (int i = x; i; i -= i & (-i)) {
        for (int j = y; j; j -= j & (-j)) {
            ans += c1[i][j] * (x + 1) * (y + 1) - c2[i][j] * (y + 1) - c3[i][j] * (x + 1) + c4[i][j];
        }
    }
    return ans;
}
ll ask(int x1, int y1, int x2, int y2) { //查询前缀和
    x1--;
    y1--;
    return query(x2, y2) - query(x1, y2) - query(x2, y1) + query(x1, y1);
}
#undef y1