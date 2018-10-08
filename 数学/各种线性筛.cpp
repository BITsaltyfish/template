// ����ɸ��Ԫ/�׳���Ԫ ���޶��ſ���󣬱�MLE��
const static int mx = 2e7 + 10;
int inv[mx];// [0,mx)��Ԫ
int jc[mx], invjc[mx]; // 0!~(mx-1)!��Ԫ
void init() {
    //[0,mx)��Ԫ
    inv[0] = inv[1] = 1;
    int p, q;
    for (int i = 2; i < mx; i++) {
        p = mod / i, q = mod - p * i;
        inv[i] = 1ll * (mod - p) * inv[q] % mod;
    }
    //0!~(mx-1)!����Ԫ
    jc[0] = 1;
    for (int i = 1; i < mx; i++)jc[i] = 1ll * jc[i - 1] * i % mod;
    invjc[mx - 1] = quickpow(jc[mx - 1], mod - 2, mod);
    for (int i = mx - 2; i >= 0; i--)invjc[i] = 1ll * invjc[i + 1] * (i + 1) % mod;
}
//����ɸ����
const static int mx = 2e7 + 10;
int prime[mx], len;
bool isprime[mx];
void init() {
    len = 0;
    memset(isprime, 0, sizeof isprime);
    for (int i = 2; i < mx; i++) {
        if (!isprime[i])isprime[i] = 1, prime[++len] = i;
        else isprime[i] = 0;
        for (int j = 1; j <= len && prime[j]*i < mx; j++) {
            isprime[prime[j]*i] = 1;
            if (i % prime[j] == 0)break;
        }
    }
}
//����ɸŷ������phi
const static int mx = 2e7 + 10;
int prime[mx], phi[mx], len;
void init() {
    len = 0;
    memset(phi, 0, sizeof phi);
    phi[1] = 1;
    for (int i = 2; i < mx; i++) {
        if (!phi[i])phi[i] = i - 1, prime[++len] = i;
        for (int j = 1; j <= len && prime[j]*i < mx; j++) {
            if (i % prime[j] == 0) {
                phi[prime[j]*i] = phi[i] * prime[j];
                break;
            } else phi[prime[j]*i] = phi[i] * (prime[j] - 1);
        }
    }
}
//����ɸĪ����˹����mu
const static int mx = 2e7 + 10;
int prime[mx], mu[mx], len;
bool mrk[mx];
void init() {
    len = 0;
    memset(mu, 127 / 3, sizeof mu);
    mu[1] = 1;
    for (int i = 2; i < mx; i++) {
        if (mu[i] > 1)mu[i] = -1, prime[++len] = i;
        for (int j = 1; j <= len && prime[j]*i < mx; j++) {
            if (i % prime[j] == 0) {
                mu[prime[j]*i] = 0;
                break;
            } else mu[prime[j]*i] = -mu[i];
        }
    }
}
//����ɸ������Ժ�������Ҫ�ܹ�������������ݵĺ���ֵf[p^k]��
const static int mx = 2e7 + 10;
int prime[mx], dprime[mx], f[mx], len;
//dprime[i]��i����С�����Ӳ��֣����ܲ�����С������p������p^k
void init() {
    f[0] = 0;
    f[1] = 1;
    for (int i = 2; i < mx; i++) {
        if(!dprime[i])dprime[i] = prime[++len] = i, f[i] =;
        //fȡֵ�Լ��㣬����i������
        for (int j = 1; j <= len && i * prime[j] < mx; j++) {
            if (i % prime[j] == 0) {
                dprime[i * prime[j]] = dprime[i] * prime[j];
                if(dprime[i] == i)f[i * prime[j]] =;
                //����i*prime[j]��prime[j]^k,i=prime[j]^(k-1)
                else f[i * prime[j]] = f[i / dprime[i]] * f[dprime[i] * prime[j]];
                break;
            }
            dprime[i * prime[j]] = prime[j];
            f[i * prime[j]] = f[i] * f[prime[j]];
        }
    }
}

//����ɸ��Ԫ
for(int i = 2; i < p; i++)inv[i] = 1ll * (p - p / i) * inv[p % i] % p;
//����ɸŷ������
int mrk[1000010], prime[1000001], phi[1000010];
void getphi(int N) {
    int i, j;
    phi[1] = 1;
    int tot = 0;
    for(i = 2; i <= N; i++) { //�൱�ڷֽ�����ʽ�������
        if(!mrk[i]) {
            prime[++tot] = i; //ɸ������ʱ�����Ȼ��ж�i�Ƿ���������
            phi[i] = i - 1; //�� i ������ʱ phi[i]=i-1
        }
        for(j = 1; j <= tot; j++) {
            if(i * prime[j] > N)  break;
            mrk[i * prime[j]] = 1; //ȷ��i*prime[j]��������
            if(i % prime[j] == 0) { //�������ǻῴprime[j]�Ƿ���i��Լ��
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            } else
                phi[i * prime[j]] = phi[i] * (prime[j] - 1); //��ʵ����prime[j]-1����phi[prime[j]]��������ŷ�������Ļ���
        }
    }
}
//����ɸĪ����˹����
int mu[1000010];
void getmu(int N) {
    int cnt = 0;
    mu[1] = 1;
    for (int i = 2; i <= N ; ++i) {
        if(!vis[i]) {
            prime[cnt++] = i;
            mu[i] = -1;
        }
        for (int j = 0; j < cnt && i * prime[j] <= N ; ++j) {
            vis[i * prime[j]] = true;
            if(i % prime[j]) mu[i * prime[j]] = -mu[i];
            else {
                mu[i * prime[j]] = 0;
                break;
            }
        }
    }
}
//����ɸ����
#define MAXL 1299710
int prime[1000010];
int mrk[1000010];
void getprime(int N) {
    int tot = 0;
    memset(mrk, 0, sizeof(mrk));
    for (int i = 2; i <= N; ++i) {
        if (!mrk[i])prime[++tot] = i;
        for (int j = 1; j <= tot; ++j) {
            if (i * prime[j] > N)break;
            mrk[i * prime[j]] = 1;
            if (i % prime[j] == 0)break;
        }
    }
}
//n sqrt(n) �����
const int mod = 1e9 + 7;
void inc(int &x, int y) {
    x = x + y >= mod ? x + y�\mod : x + y;
}
void dec(int &x, int y) {
    x = x�\y < 0 ? x�\y + mod : x�\y;
}
void getchaifen(int N) {
    f[0] = 1;
    for(int i = 1; i <= N; i++) {
        for(int j = 1, w = 1; w <= i; w += 3 * j + 1, j++)
            if(j & 1)inc(f[i], f[i�\w]);
            else dec(f[i], f[i�\w]);
        for(int j = 1, w = 2; w <= i; w += 3 * j + 2, j++)
            if(j & 1)inc(f[i], f[i�\w]);
            else dec(f[i], f[i�\w]);
    }
}