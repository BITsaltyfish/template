// 十进制按位桶排 O(nk)，k是log_10_max{a[i]}
#define inf 0x7fffffff
#define N 100010
#define max(a,b) ((a)>(b)?(a):(b))
int rk[N][2], sa[N][2];
int a[N], b[N];
void bucket_sort(int l, int r) {
    if (l >= r)return;
    int sz[10] = {0}, tot = r - l + 1, i;
    int bin = 1, mx = -inf;
    for (i = 1; i <= tot; i++)b[i] = a[i + l - 1], mx = max(mx, b[i]);
    int pre = 0, cur = 1;
    while (bin <= mx) {
        memset(sz, 0, sizeof(sz));
        for (i = 1; i <= tot; i++)sz[(b[i] / bin) % 10]++;
        for (i = 1; i <= 9; i++)sz[i] += sz[i - 1];
        if (bin == 1) {
            for (i = tot; i >= 1; i--) {
                rk[i][cur] = sz[(b[i] / bin) % 10]--;
                sa[rk[i][cur]][cur] = i;
            }
        } else for (i = tot; i >= 1; i--) {
                int now = sa[i][pre];
                rk[now][cur] = sz[(b[now] / bin) % 10]--;
                sa[rk[now][cur]][cur] = now;
            }
        bin *= 10;
        pre ^= 1;
        cur ^= 1;
    }
    for (i = l; i <= r; i++)a[i] = b[sa[i - l + 1][pre]];
}