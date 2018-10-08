// POJ 1681 需要枚举自由变元，找解中1 个数最少的 对2 取模的01 方程组
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 1010;
//有equ 个方程，var 个变元。增广矩阵行数为equ, 列数为var+1, 分别为0 到var
int equ, var;
int a[52][MAXN]; //增广矩阵
int x[MAXN]; //解集
int free_x[MAXN];//用来存储自由变元（多解枚举自由变元可以使用）
int free_num;//自由变元的个数

//返回值为-1 表示无解，为0 是唯一解，否则返回自由变元个数
int Gauss() {
    int max_r, col, k;
    free_num = 0;
    for(k = 0, col = 0 ; k < equ && col < var ; k++, col++) {
        max_r = k;
        for(int i = k + 1; i < equ; i++) {
            if(abs(a[i][col]) > abs(a[max_r][col]))max_r = i;
        }
        if(a[max_r][col] == 0) {
            k--;free_x[free_num++] = col;//这个是自由变元
            continue;
        }
        if(max_r != k) {
            for(int j = col; j < var ; j++)
                swap(a[k][j], a[max_r][j]);
        }
        for(int i = k + 1; i < equ; i++) {
            if(a[i][col] != 0) {
                for(int j = col; j < var ; j++)
                    a[i][j] ^= a[k][j];
            }
        }
    }
    if(col<var)
        for(int i = k; i < equ; i++)
            if(a[i][col] != 0)return -1;//无解
    if(k < var) return var-k;//自由变元个数
    //唯一解，回代
    for(int i = var-1; i >= 0; i--) {
        x[i] = a[i][var];
        for(int j = i + 1; j < var; j++)
            x[i] ^= (a[i][j] && x[j]);
    }
    return 0;
}
int n;
void solve() {
    int n;
    ll s;scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%lld",&s);
        for(int j=0;j<50;j++)a[j][i] = s%2,s/=2;
    }
    for(int i=0;i<50;i++)x[i] = 0;
    equ = 50;var = n;
    int t = Gauss();
    if(t == -1||t == 0||n == 1)printf("No\n");
    else printf("Yes\n");
}
int main() {
    int T;
    scanf("%d", &T);
    while(T--) solve();
    return 0;
}