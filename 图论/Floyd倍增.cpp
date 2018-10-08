/* 例题：给出一张图，求经过k条边的最短路。
 * 解法：魔改矩阵乘法，换成floyd传递形式，那么矩阵的k次方就是答案
 *      注意到n很大，因此需要快速幂加速矩阵乘法
 */
#include <cstdio>
#include <algorithm>
#include <map>
#include <cstring>
using namespace std;
const int MAXN = 210;
int ID[1010];
int n, k, q, z, tn;
struct Matrix {
    int a[MAXN][MAXN];
    Matrix operator * (const Matrix &x) const {
        Matrix c;
        memset(c.a, 0x3f, sizeof(c.a));
        for (int k = 1; k <= tn; k++)
            for (int i = 1; i <= tn; ++i)
                for (int j = 1; j <= tn; ++j)
                    c.a[i][j] = min(c.a[i][j], a[i][k] + x.a[k][j]);
        return c;
    }
} s, ans;
void quickpow() {
    ans = s;
    k--;
    for (; k; k >>= 1) {
        if (k & 1) ans = ans * s;
        s = s * s;
    }
}
int main() {
    scanf("%d%d%d%d", &k, &n, &q, &z);
    memset(s.a, 0x3f, sizeof(s.a));
    for (int i = 1; i <= n; ++i) {
        int x, y, w;
        scanf("%d%d%d", &w, &x, &y);
        if (!ID[x]) ID[x] = ++tn;
        if (!ID[y]) ID[y] = ++tn;
        s.a[ID[x]][ID[y]] = s.a[ID[y]][ID[x]] = w;
    }
    quickpow();
    printf("%d\n", ans.a[ID[q]][ID[z]]);
    return 0;
}