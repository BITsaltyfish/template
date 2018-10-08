#include <bits/stdc++.h>
using namespace std;
const int mod = 19930726;
typedef long long ll;
const int LEN = 2e5 + 10;
int len[LEN], fail[LEN], num[LEN];
const int mid = 100003;
int nxt[LEN][26];
int last[2], p, npre, nend;
char s[LEN];
ll ans;
int newnode() {
    memset(nxt[p], 0, sizeof nxt[p]);
    fail[p] = 0;
    return p++;
}
void init() {
    p = 0;
    ans = 0;
    len[0] = 0;
    len[1] = -1;
    newnode();
    newnode();
    fail[0] = 1;
    npre = nend = mid;
    npre++;
    s[npre] = s[nend] = -1;
    last[0] = 1;
    last[1] = 1;
}
int getfail(int x, int k) {
    if(k == 0)while(s[nend - (len[x] + 1)] != s[nend])x = fail[x];
    else while(s[npre + (len[x] + 1)] != s[npre])x = fail[x];
    return x;
}
void add(char c, int q) {
    int x = c - 'a';
    last[q] = getfail(last[q], q);
    int cur = last[q];
    if(!nxt[cur][x]) {
        int now = newnode();
        len[now] = len[cur] + 2;
        fail[now] = nxt[getfail(fail[cur], q)][x];
        nxt[cur][x] = now;
        num[now] = num[fail[now]] + 1;
    }
    last[q] = nxt[cur][x];
    if(len[last[q]] == nend - npre + 1)last[q ^ 1] = last[q];
    ans += num[last[q]];
}
void addpre(char c) {
    s[++nend] = c - 'a';
    s[nend + 1] = -1;
    add(c, 0);
}
void addend(char c) {
    s[--npre] = c - 'a';
    s[npre - 1] = -1;
    add(c, 1);
}
pair<int, int> a[LEN];
int main(int argc, char const *argv[]) {
    int m, op;
    while(~scanf("%d", &m)) {
        init();
        char a[10];
        while(m--) {
            scanf("%d", &op);
            if(op == 1) {
                scanf("%s", a);
                addpre(a[0]);
            } else if(op == 2) {
                scanf("%s", a);
                addend(a[0]);
            } else if(op == 3)printf("%d\n", p - 2);
            else printf("%lld\n", ans);

        }
    }
    return 0;
}