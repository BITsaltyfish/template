#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e5 + 10;
typedef long long ll;
// 每个节点代表一个回文串
int len[maxn];// 此节点回文串长度
int nxt[maxn][26];
int fail[maxn];
int cnt[maxn];
int num[maxn];//border个数
int s[maxn];
int last;
int p;// 节点个数
int n;// 已添加字符个数
int newnode() {
    for(int i = 0; i < 26; i++)nxt[p][i] = 0;
    cnt[p] = num[p] = 0;
    return p++;
}
void init() {
    p = 0;
    len[0] = 0;
    len[1] = -1;
    fail[0] = 1;
    newnode();
    newnode();
    n = 0;
    s[0] = -1;// 开头放一个字符集中没有的字符，减少特判
    last = 1;
}
int get_fail(int x) {
    while(s[n - len[x] - 1] != s[n])x = fail[x];
    return x;
}
void add(char c) {
    int x = c - 'a';
    s[++n] = x;
    last = get_fail(last);
    int cur = last;
    if(!nxt[cur][x]) {
        int now = newnode();
        len[now] = len[cur] + 2;
        //以下两行因为边界原因，顺序不可互换
        fail[now] = nxt[get_fail(fail[cur])][x];
        nxt[cur][x] = now;
        num[now] = num[fail[now]] + 1;
    }
    last = nxt[cur][x];
    cnt[last]++;
}
char ss[maxn];
ll solve() {
    ll ans = 0;
    for(int i = p - 1; i >= 0; i--)cnt[fail[i]] += cnt[i];
    for(int i = 0; i < p; i++)ans = max(ans, 1ll * cnt[i] * len[i]);
    return ans;
}
int main(int argc, char const *argv[]) {
    scanf("%s", ss + 1);
    int len = strlen(ss + 1);
    init();
    for(int i = 1; i <= len; i++)add(ss[i]);
    printf("%lld\n", solve());
    return 0;
}