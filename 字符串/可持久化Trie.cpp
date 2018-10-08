/* 例题：BZOJ 3261 - 给定一个非负整数序列 {a}，初始长度为 N。
 * 有M个操作，有以下两种操作类型：
     1. A x：添加操作，表示在序列末尾添加一个数 x，序列的长度 N+1。
     2. Q l r x：询问操作，你需要找到一个位置 p，满足 l<=p<=r，使得：a[p] xor a[p+1] xor ... xor a[N] xor x 最大，输出最大是多少。
 */
#include <bits/stdc++.h>
using namespace std;
struct Trie {
#define NODE  20000005
#define SET  2
    int nxt[NODE][SET];
    int cnt[NODE], tot;
    int root[600100];
    int nw;
    int newnode() {
        for(int i = 0; i < SET; i++)nxt[tot][i] = -1;
        cnt[tot] = 0;
        return tot++;
    }
    void init() {
        tot = 0;
        root[0] = newnode();
        nw = 0;
    }
    void insert(int x) {
        int dig[50] = {0};
        for(int i = 1; i <= 25; i++)dig[25 - i + 1] = x % 2, x /= 2;
        nw++;
        root[nw] = newnode();
        int p = root[nw], pre = root[nw - 1];
        for(int i = 0; i < SET; i++)nxt[p][i] = nxt[pre][i];
        for(int i = 1; i <= 25; i++) {
            int cur = dig[i];
            nxt[p][cur] = newnode();
            p = nxt[p][cur];
            if(~pre && ~nxt[pre][cur]) {
                pre = nxt[pre][cur];
                for(int j = 0; j < SET; j++)nxt[p][j] = nxt[pre][j];
                cnt[p] = cnt[pre] + 1;
            } else cnt[p] = 1, pre = -1;
        }
    }
    int query(int l, int r, int x) {
        int pl = root[l - 1], pr = root[r];
        int dig[50] = {0};
        for(int i = 1; i <= 25; i++)dig[25 - i + 1] = x % 2, x /= 2;
        int a, b, ans = 0;
        for(int i = 1; i <= 25; i++) {
            int cur = dig[i];
            if(~pl && ~nxt[pl][cur ^ 1])a = cnt[nxt[pl][cur ^ 1]];
            else a = 0;
            if(~nxt[pr][cur ^ 1])b = cnt[nxt[pr][cur ^ 1]];
            else b = 0;
            if(b - a) {
                if(~pl)pl = nxt[pl][cur ^ 1];
                pr = nxt[pr][cur ^ 1];
                ans <<= 1;
                ans++;
            } else {
                if(~pl)pl = nxt[pl][cur];
                pr = nxt[pr][cur];
                ans = (ans << 1);
            }
        }
        return ans;
    }
} T;
int main(int argc, char const *argv[]) {
    int n, m;
    scanf("%d%d", &n, &m);
    T.init();
    int x;
    int tot = 0, total = 0;
    T.insert(0);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &x);
        tot ^= x;
        T.insert(tot);
    }
    int lastans = 0, l, r;
    char s[10];
    for(int i = 1; i <= m; i++) {
        scanf("%s", s);
        if(s[0] == 'A') {
            scanf("%d", &x);
            tot ^= x;
            T.insert(tot);
        } else {
            scanf("%d%d%d", &l, &r, &x);
            printf("%d\n", T.query(l, r, tot ^ x));
        }
    }
    return 0;
}