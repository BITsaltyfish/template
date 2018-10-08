#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2000005;
char str1[MAXN], str[MAXN];
int ls, p[MAXN];
// transfer string:abcd ==> string:$#a#b#c#d# 预处理
void pre() {
    int ls1 = strlen(str1);
    ls = 0;
    str[ls++] = '$';
    str[ls++] = '#';
    for (int i = 0; i < ls1; i++) {
        str[ls++] = str1[i];
        str[ls++] = '#';
    }
    str[ls] = 0;
}
// o(n)
int manacher() {
    pre();
    int mx = 0, id, ans = 0; // mx表示最右的位置，id表示取到mx的中心位置
    for (int i = 1; i < ls; i++) {
        if (mx > i) p[i] = min(p[2 * id - i], mx - i);
        else p[i] = 1;
        for (; str[i + p[i]] == str[i - p[i]]; p[i]++);
        if (p[i] + i > mx) {
            mx = p[i] + i;
            id = i;
        }
        ans = max(ans, p[i]);
    }
    /*
        输出回文串
        p[ans]-=2;
        for(int i = (ans-p[ans])/2-1;i<=(ans+p[ans])/2-1;i++)printf("%c",str1[i]);printf("\n");
    */
    return ans - 1;
}
int main(int argc, char const *argv[]) {
    while(~scanf("%s", str1)) {
        printf("%d\n", manacher());
    }
    return 0;
}