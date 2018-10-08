#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
class Matrix {
#define N 2
public: 
    int a[N][N];
    int n;
    
    void Init(int key) {
        memset(a, 0, sizeof a);
        if (key) rep(i, 0, n) a[i][i] = 1;
    }
    
    Matrix operator+ (const Matrix &b) {
        Matrix c;
        c.n = n;
        rep(i, 0, n) rep(j, 0, n) c.a[i][j] = (a[i][j] + b.a[i][j]) % mod;
        return c;
    }

    Matrix operator+ (int x) {
        Matrix p = *this;
        rep(i, 0, n) p.a[i][i] = (p.a[i][i] + x % mod) % mod;
        return p;
    }
    
    Matrix operator- (const Matrix &b) {
        Matrix c;
        c.n = n;
        rep(i, 0, n) rep(j, 0, n) c.a[i][j] = (a[i][j] - b.a[i][j] + mod) % mod;
        return c;
    }

    Matrix operator* (const Matrix &b) {
        Matrix c;
        c.n = n;
        c.Init(0);
        rep(i, 0, n) rep(j, 0, n) rep(k, 0, n)
            c.a[i][j] = (c.a[i][j] + a[i][k] * b.a[k][j] % mod) % mod;
        return c;
    }

    Matrix Power(int t) {
        Matrix ans, p = *this;
        ans.n = p.n;
        ans.Init(1);
        while (t) {
            if (t & 1) ans = ans * p;
            p = p * p;
            t >>= 1;
        }
        return ans;
    }
    
    void Print() {
        rep(i, 0, n) {
            rep(j, 0, n) {
                if (j == 0) printf("%d", a[i][j]);
                else printf(" %d", a[i][j]);
            }
            puts("");
        }
    }
#undef N    
};
/* 带R、C版，但是其中快速幂必须是 n*n 方阵 */
struct Matrix {
#define N 155
    int r, c;
    int a[N][N];

    Matrix(int r = 0, int c = 0) {
        this->r = r; this->c = c;
        memset(a, 0, sizeof a);
    }

    Matrix operator* (Matrix& b) {
        Matrix res(r, b.c);
        for (int k = 0; k < c; k++) {
            for (int i = 0; i < r; i++) {
                if (!a[i][k]) continue;
                for (int j = 0; j < b.c; j++) {
                    res.a[i][j] += a[i][k] * b.a[k][j];
                }
            }
        }
        return res;
    }

    Matrix Power(int t) {
        Matrix res(r, r), p = *this;
        for (int i = 0; i < r; i++) res.a[i][i] = 1;
        while (t > 0) {
            if (t & 1) res = res * p;
            p = p * p;
            t >>= 1;
        }
        return res;
    }

    inline void Print() {
        printf("<%d,%d>\n", r, c);
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (j == 0) printf("%d", a[i][j]);
                else printf(" %d", a[i][j]);
            }
            puts("");
        }
    }
#undef N
};