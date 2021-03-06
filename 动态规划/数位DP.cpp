/*
 原题是求x,y之间有多少个 0 digit
 real 代表是否为前导0
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll dp[20][20][3][20];
int digit[35];
ll dfs(int len, int hasl, int vto, int real, int fp) {
    if(vto < hasl) return 0;
    if(!len) {
        if(vto == hasl) return 1;
        else return 0;
    }
    if((!fp) && dp[len][hasl][real][vto] != -1) return dp[len][hasl][real][vto];
    ll ret = 0;
    int fpmax = fp ? digit[len] : 9;
    for (int i = 0; i <= fpmax ; ++i) {
        if(real) ret += dfs(len - 1, hasl + (i == 0), vto, real, fp && i == digit[len]);
        else ret += dfs(len - 1, 0, vto, real || i != 0, fp && i == digit[len]);
    }
    if(!fp) dp[len][hasl][real][vto] = ret;
    return ret;
}
ll calc(ll n) {
    int len = 0;
    while(n > 0) {
        digit[++len] = n % 10;
        n /= 10;
    }
    ll ans = 0;
    for (int i = 1; i <= len ; ++i) ans += 1ll * i * dfs(len, 0, i, 0, 1);
    return ans;
}
int main() {
    int t;
    ll n, m;
    int kase = 1;
    memset(dp, -1, sizeof(dp));
    scanf("%d", &t);
    while(t--) {
        ll ans = 0;
        scanf("%lld%lld", &n, &m);
        if(n == 0) ans = calc(m) + 1;
        else ans = calc(m) - calc(n - 1);
        printf("Case %d: %lld\n", kase++, ans);
    }
    return 0;
}