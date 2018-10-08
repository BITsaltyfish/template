/* 找出一组ax+by==gcd(a,b)的方案，返回值即gcd(a,b)
 * ax==1(mod b)等价于ax-by==1
 * 可能需要调整解x到最小正数
 */
ll exgcd(ll a, ll b, ll &x, ll &y) {
    ll d = a;
    if(b != 0)d = exgcd(b, a % b, y, x), y -= (a / b) * x;
    else x = 1, y = 0;
    return d;
}