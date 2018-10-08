/* 例题：HDU - 6070：给你长度为n的序列，求某个区间[l,r]使得区间内的数字种类/区间长度最小，输出这个最小值
 * 解法：对于这种区间最优比率问题（分数规划问题）我们常规的解法是二分答案来求
 *     根据题目意思我们二分答案后可以转化成 size(l,r)/(r-l+1)<=mid   ->   size(l,r)+l*mid <=(r+1)*mid
 *     这里我们可以枚举右边的r ，然后用最值线段树来维护左边的最小值，  
 *     我们build的时候将线段树初始化为l*mid,然后对于枚举i,a[i]的贡献区间为 [pre[a[i]]+1,i]+1
 *     因为如果前面已经存在了a[i]，该数就对之前的区间没有贡献了
 */
const int MX = 60005
int n;
struct segtree {
    int l, r, tag;
    double mn;
} t[MX * 4];

int num[MX];
int pre[MX];
int pos[MX];
inline void update(int k) {
    t[k].mn = min(t[k << 1].mn, t[k << 1 | 1].mn);
}
inline void pushdown(int k) {
    if(t[k].l == t[k].r || !t[k].tag)return;
    int tt = t[k].tag;
    t[k].tag = 0;
    t[k << 1].tag += tt;
    t[k << 1 | 1].tag += tt;
    t[k << 1].mn += tt;
    t[k << 1 | 1].mn += tt;
}
inline void buildtree(int now, int l, int r, double x) {
    t[now].l = l;
    t[now].r = r;
    t[now].tag = 0;
    if(l == r) {
        t[now].mn = x * l;
        return;
    }
    int mid = (l + r) >> 1;
    buildtree(now << 1, l, mid, x);
    buildtree(now << 1 | 1, mid + 1, r, x);
    update(now);
}
void change(int now, int x, int y) {
    pushdown(now);
    int l = t[now].l, r = t[now].r;
    if(l >= x && r <= y ) {
        t[now].mn++;
        t[now].tag++;
        return;
    }
    int mid = (l + r) >> 1;
    if(y <= mid) change(now << 1, x, y);
    else if(x > mid)change(now << 1 | 1, x, y);
    else change(now << 1, x, mid), change(now << 1 | 1, mid + 1, y);
    update(now);
}
inline double askmn(int now, int x, int y) {
    pushdown(now);
    int l = t[now].l, r = t[now].r;
    if(l >= x && r <= y)return t[now].mn;
    int mid = (l + r) >> 1;
    if(y <= mid) return askmn(now << 1, x, y);
    else if(x > mid) return askmn(now << 1 | 1, x, y);
    else return min(askmn(now << 1, x, mid), askmn(now << 1 | 1, mid + 1, y));
}
inline bool jud(double x) {
    buildtree(1, 1, n, x);
    for (int i = 1; i <= n ; i++) {
        change(1, pre[i] + 1, i);
        if(askmn(1, 1, i) <= x * (i + 1)) return true;
    }
    return false;
}
int main(int argc, char const *argv[]) {
    int t;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)pos[i] = 0;
        for (int i = 1; i <= n ; ++i) {
            scanf("%d", &num[i]);
            pre[i] = pos[num[i]];
            pos[num[i]] = i;
        }
        double l = 0, r = 1;
        double ans = 1;
        for (int i = 0; i < 15; ++i) {
            double mid = (l + r) / 2;
            if(jud(mid))r = mid, ans = mid;
            else l = mid;
        }
        printf("%f\n", ans );
    }
    return 0;
}