#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i,a,n) for (ll i=a;i<n;i++)
#define per(i,a,n) for (ll i=n-1;i>=a;i--)
#define SZ(x) ((long long)(x).size())
#define pb push_back
typedef vector<long long> VI;
const static int mod = 1e9 + 7;
inline ll quickpow(ll a, ll b, ll mod) {
    ll s = 1;
    while (b) {
        if (b & 1)s = s * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return s;
}
namespace linear_seq {
    const ll N = 10010;
    ll res[N], base[N], _c[N], _md[N];

    vector<ll> Md;
    void mul(ll *a, ll *b, ll k) {
        rep(i, 0, k + k) _c[i] = 0;
        rep(i, 0, k) if (a[i]) rep(j, 0, k)
            _c[i + j] = (_c[i + j] + a[i] * b[j]) % mod;
        per(i, k, k + k) if (_c[i]) rep(j, 0, SZ(Md))
            _c[i - k + Md[j]] = (_c[i - k + Md[j]] - _c[i] * _md[Md[j]]) % mod;
        rep(i, 0, k) a[i] = _c[i];
    }
    ll solve(ll n, VI a, VI b) {
        // a系数b初值b[n+1]=a[0]*b[n]+...
        ll ans = 0, pnt = 0, k = SZ(a);
        assert(SZ(a) == SZ(b));
        rep(i, 0, k) _md[k - 1 - i] = -a[i];
        _md[k] = 1;
        Md.clear();
        rep(i, 0, k) if (_md[i] != 0) Md.push_back(i);
        rep(i, 0, k) res[i] = base[i] = 0;
        res[0] = 1;
        while ((1ll << pnt) <= n) pnt++;
        per(p, 0, pnt + 1) {
            mul(res, res, k);
            if ((n >> p) & 1) {
                per(i, 0, k) res[i + 1] = res[i];
                res[0] = 0;
                rep(j, 0, SZ(Md)) res[Md[j]] = (res[Md[j]] - res[k] * _md[Md[j]]) % mod;
            }
        }
        rep(i, 0, k) ans = (ans + res[i] * b[i]) % mod;
        if (ans < 0) ans += mod;
        return ans;
    }
    VI BM(VI s) {
        VI C(1, 1), B(1, 1);
        ll L = 0, m = 1, b = 1;
        rep(n, 0, SZ(s)) {
            ll d = 0;
            rep(i, 0, L + 1) d = (d + (ll)C[i] * s[n - i]) % mod;
            if (d == 0) ++m;
            else if (2 * L <= n) {
                VI T = C;
                ll c = mod - d * quickpow(b, mod - 2, mod) % mod;
                while (SZ(C) < SZ(B) + m) C.pb(0);
                rep(i, 0, SZ(B)) C[i + m] = (C[i + m] + c * B[i]) % mod;
                L = n + 1 - L;
                B = T;
                b = d;
                m = 1;
            } else {
                ll c = mod - d * quickpow(b, mod - 2, mod) % mod;
                while (SZ(C) < SZ(B) + m) C.pb(0);
                rep(i, 0, SZ(B)) C[i + m] = (C[i + m] + c * B[i]) % mod;
                ++m;
            }
        }
        return C;
    }
    ll gao(VI a, ll n) {
        VI c = BM(a);
        c.erase(c.begin());
        rep(i, 0, SZ(c)) c[i] = (mod - c[i]) % mod;
        return solve(n, c, VI(a.begin(), a.begin() + SZ(c)));
    }
};
int main() {
    ll n;
    while (~scanf("%lld", &n)) printf("%lld\n", linear_seq::gao(VI{1, 2, 3, 4, 5}, n - 1));
    //输入前几项输出第n项，前几项越多越好
}
