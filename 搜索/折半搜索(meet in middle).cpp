/* 例题：codeforces - 888E - 有n(n<36)个数，求从中选任意个数加和对m(m<10^9)取模后的最大值
 * 解法：先对序列的前一半进行枚举，之后再对后一半序列进行枚举并维护和前一半情况相结合的最优结果。 
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
set<ll> s[2];
int a[36], n, m;
void dfs(ll sum, int l, int r) {
    if (l > r) {
        s[r == n].insert(sum);
        return;
    }
    dfs(sum, l + 1, r);
    dfs((sum + a[l]) % m, l + 1, r);
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    dfs(0, 1, n / 2);
    dfs(0, n / 2 + 1, n);
//    printf("%d %d\n", s[0].size(), s[1].size());
    ll ans = 0;
    for (auto left: s[0]) {
        if (left < m) {
            ll res = m - left - 1;
            auto it = s[1].upper_bound(res);
            it--;
            ans = max(ans, left + *it);
        }
    }
    printf("%lld\n", ans);
    return 0;
}