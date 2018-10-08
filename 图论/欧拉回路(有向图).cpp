/* 例题：POJ 2337 - 给出n 个小写字母组成的单词，要求将n 个单词连接起来，使得前一个单词的最后一个字母
和后一个单词的第一个字母相同。输出字典序最小的解。
 */
struct Edge {
    int to, next;
    int index;
    bool flag;
} edge[2010];
int head[30], tot;
void init() {
    tot = 0;
    memset(head, −1, sizeof(head));
}
void addedge(int u, int v, int index) {
    edge[tot].to = v;
    edge[tot].next = head[u];
    edge[tot].index = index;
    edge[tot].flag = false;
    head[u] = tot++;
}
string str[1010];
int in[30], out[30];
int cnt;
int ans[1010];
void dfs(int u) {
    for(int i = head[u] ; i != −1; i = edge[i].next)
        if(!edge[i].flag) {
            edge[i].flag = true;
            dfs(edge[i].to);
            ans[cnt++] = edge[i].index;
        }
}
int main() {
    int T, n;
    scanf("%d", &T);
    while(T−−) {
        scanf("%d", &n);
        for(int i = 0; i < n; i++) cin >> str[i];
        sort(str, str + n); //要输出字典序最小的解，先按照字典序排序
        init();
        memset(in, 0, sizeof(in));
        memset(out, 0, sizeof(out));
        int start = 100;
        for(int i = n−1; i >= 0; i−−) { //字典序大的先加入
            int u = str[i][0] − 'a';
            int v = str[i][str[i].length() − 1] − 'a';
            addedge(u, v, i);
            out[u]++;
            in[v]++;
            if(u < start)start = u;
            if(v < start)start = v;
        }
        int cc1 = 0, cc2 = 0;
        for(int i = 0; i < 26; i++) {
            if(out[i] − in[i] == 1) {
                cc1++;
                start = i;//如果有一个出度比入度大1 的点，就从这个点出发，否则从最小的点出发
            } else if(out[i] − in[i] == −1) cc2++;
            else if(out[i] − in[i] != 0) cc1 = 3;
        }
        if(! ( (cc1 == 0 && cc2 == 0) || (cc1 == 1 && cc2 == 1) )) {
            printf("***\n");
            continue;
        }
        cnt = 0;
        dfs(start);
        if(cnt != n) { //判断是否连通
            printf("***\n");
            continue;
        }
        for(int i = cnt−1; i >= 0; i−−) {
            cout << str[ans[i]];
            if(i > 0)printf(".");
            else printf("\n");
        }
    }
    return 0;
}