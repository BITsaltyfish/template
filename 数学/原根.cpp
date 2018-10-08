#include <bits/stdc++.h>
const int MAXN = 100000;
int prime[MAXN + 1];
void getPrime() { //素数筛选和合数分解
    memset(prime, 0, sizeof(prime));
    for(int i = 2; i <= MAXN; i++) {
        if(!prime[i])prime[++prime[0]] = i;
        for(int j = 1; j <= prime[0] && prime[j] <= MAXN / i; j++) {
            prime[prime[j]*i] = 1;
            if(i % prime[j] == 0) break;
        }
    }
}
long long factor[100][2];
int fatCnt;
int getFactors(long long x) {
    fatCnt = 0;
    long long tmp = x;
    for(int i = 1; prime[i] <= tmp / prime[i]; i++) {
        factor[fatCnt][1] = 0;
        if(tmp % prime[i] == 0) {
            factor[fatCnt][0] = prime[i];
            while(tmp % prime[i] == 0) {
                factor[fatCnt][1]++;
                tmp /= prime[i];
            }
            fatCnt++;
        }
    }
    if(tmp != 1) {
        factor[fatCnt][0] = tmp;
        factor[fatCnt++][1] = 1;
    }
    return fatCnt;
}
long long pow_m(long long a, long long n, long long mod) {
    long long ret = 1;
    long long tmp = a % mod;
    while(n) {
        if(n & 1)ret = ret * tmp % mod;
        tmp = tmp * tmp % mod;
        n >>= 1;
    }
    return ret;
}
//求素数P 的最小的原根
void solve(int P) {
    if(P == 2) {
        printf("1\n");
        return;
    }
    getFactors(P-
        1);
    for(int g = 2; g < P; g++) {
        bool flag = true;
        for(int i = 0; i < fatCnt; i++) {
            int t = (P-1) / factor[i][0];
            if(pow_m(g, t, P) == 1) {
                flag = false;
                break;
            }
        }
        if(flag) {
            printf("%d\n", g);
            return;
        }
    }
}
int main() {
    getPrime();
    int T;
    int P;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &P);
        solve(P);
    }
    return 0;
}