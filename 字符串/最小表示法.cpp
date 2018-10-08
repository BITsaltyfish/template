#include <bits/stdc++.h>
using namespace std;
char str[1000010];
// 最小表示法模板 字符串从0开始
int main() {
    scanf("%s", str);
    int n = strlen(str);
    int i = 0, j = 1, k = 0;
    while(i < n && j < n && k < n) {
        int t = str[(i + k) % n] - str[(j + k) % n] ;
        if(t == 0)k++;
        else {
            if(t > 0)i += k + 1;
            else j += k + 1;
            if(i == j)j++;
            k = 0;
        }
    }
    printf("%d\n", (i < j ? i : j) + 1);
}