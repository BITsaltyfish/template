/* 杜教筛 h[i]=f*g(n) => g(1)S(n)=Σh(i)-Σg(d)*S(n/d)
 * 例题：【luogu-P4213】求Σμ(i)和Σφ(i)
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 6e6 + 5;
int phi[maxn], mu[maxn];
bool vis[maxn];
vector<int> prime;
ll sum_phi[maxn];
int sum_mu[maxn];
void init() {
    phi[1] = mu[1] = 1;
    for (int i = 2; i <= maxn-5; i++) {
        if (!vis[i]) {
            prime.push_back(i);
            mu[i] = -1;
            phi[i] = i-1;
        }
        for (int j = 0; j < (int)prime.size() && i*prime[j] <= maxn-5; j++) {
            vis[i*prime[j]] = 1;
            if (i % prime[j] == 0) {
                phi[i*prime[j]] = phi[i] * prime[j];
                break;
            } else {
                mu[i*prime[j]] = -mu[i];
                phi[i*prime[j]] = phi[i] * (prime[j]-1);
            }
        }
    }
    sum_phi[0] = sum_mu[0] = 0;
    for (int i = 1; i <= maxn-5; i++) {
        sum_phi[i] = sum_phi[i-1] + phi[i];
        sum_mu[i] = sum_mu[i-1] + mu[i];
    }
}
unordered_map<int, ll> M_phi;
ll S_phi(int n) {
    if (n <= maxn-5) return sum_phi[n];
    if (M_phi.count(n)) return M_phi[n];
    ll res = 1LL * n * (n+1) / 2;
    for (int l = 2, r; l <= n; l = r+1) {
        r = n/(n/l);
        res -= 1LL * (r-l+1) * S_phi(n/l);
    }
    return M_phi[n] = res;
}
unordered_map<int, int> M_mu;
int S_mu(int n) {
    if (n <= maxn-5) return sum_mu[n];
    if (M_mu.count(n)) return M_mu[n];
    int res = 1;
    for (int l = 2, r; l <= n; l = r+1) {
        r = n/(n/l);
        res -= (r-l+1) * S_mu(n/l);
    }
    return M_mu[n] = res;
}
int main() {
    int t, n;
    init();
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        printf("%lld %d\n", S_phi(n), S_mu(n));
    }
    return 0;
}