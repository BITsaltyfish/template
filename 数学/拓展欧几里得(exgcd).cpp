/* �ҳ�һ��ax+by==gcd(a,b)�ķ���������ֵ��gcd(a,b)
 * ax==1(mod b)�ȼ���ax-by==1
 * ������Ҫ������x����С����
 */
ll exgcd(ll a, ll b, ll &x, ll &y) {
    ll d = a;
    if(b != 0)d = exgcd(b, a % b, y, x), y -= (a / b) * x;
    else x = 1, y = 0;
    return d;
}