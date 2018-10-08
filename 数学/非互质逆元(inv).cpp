// a对模MOD的逆元,无解返回-1
ll exgcd(ll a, ll b, ll &x, ll &y) {
    ll d = a;
    if(b != 0)d = exgcd(b, a % b, y, x), y -= (a / b) * x;
    else x = 1, y = 0;
    return d;
}
ll inv(ll a, ll MOD) {
    ll x, y, d = exgcd(a, MOD, x, y);
    return d == 1 ? (x + MOD) % MOD : -1;
}