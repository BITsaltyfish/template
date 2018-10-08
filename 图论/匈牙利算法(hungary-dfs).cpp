/* �����ͼ���ƥ�䣬dfs��
 * �����Ƕ���ͼ���ҵ��Ѿ��ֿ��İ汾�����·��������ҵ�û�ֿ��İ汾
 * ���(1)~(n1)�ĵ��ǵ�һ�����ϣ����(n1+1)~(n2)�ĵ��ǵڶ�������
*/
#define M 2010
#define N 1010
struct edge {
    int to, next;
} e[M];
int head[N], cnt;
bool hungary_mrk[N];
int match[N];
inline void ins(int u, int v) {
    e[++cnt].to = v;
    e[cnt].next = head[u];
    head[u] = cnt;
}
inline void insert(int u, int v) {
    ins(u, v);
    ins(v, u);
}
bool hungary_dfs(int x) {
    for (int i = head[x]; i; i = e[i].next)
        if (!hungary_mrk[e[i].to]) {
            int now = e[i].to;
            hungary_mrk[now] = 1;
            if (!match[now] || hungary_dfs(match[now])) {
                match[now] = x;
                match[x] = now;
                return 1;
            }
        }
    return 0;
}
inline int hungary(int n1, int n2) {
    int tot = 0;
    memset(match, 0, sizeof(match));
    for (int i = 1; i <= n1; i++) {
        if (!match[i])memset(hungary_mrk, 0, sizeof(hungary_mrk));
        if (hungary_dfs(i))tot++;
    }
    return tot;
}
//�����Ƕ���ͼ�����Ѿ��ֿ��İ汾
//�����Ƕ���ͼ���ұ�Ŵ��ҵİ汾
#define M 2010
#define N 1010
struct edge {
    int to, next;
} e[M];
int head[N], cnt;
bool hungary_mrk[N];
int hungary_left[N];
int match[N];
inline void ins(int u, int v) {
    e[++cnt].to = v;
    e[cnt].next = head[u];
    head[u] = cnt;
}
inline void insert(int u, int v) {
    ins(u, v);
    ins(v, u);
}
bool hungary_dfs(int x) {
    for (int i = head[x]; i; i = e[i].next)
        if (!hungary_mrk[e[i].to]) {
            int now = e[i].to;
            hungary_mrk[now] = 1;
            if (!match[now] || hungary_dfs(match[now])) {
                match[now] = x;
                match[x] = now;
                return 1;
            }
        }
    return 0;
}
inline void hungary_remark(int x, int op) {
    hungary_left[x] = op;
    for (int i = head[x]; i; i = e[i].next)
        if (hungary_left[e[i].to] == -1)hungary_remark(e[i].to, op ^ 1);
}
inline int hungary(int n) {
    memset(hungary_left, -1, sizeof(hungary_left));
    for (int i = 1; i <= n; i++)if (hungary_left[i] == -1)hungary_remark(i, 1);
    int tot = 0;
    memset(match, 0, sizeof(match));
    for (int i = 1; i <= n; i++)
        if(hungary_left[i]) {
            if (!match[i])memset(hungary_mrk, 0, sizeof(hungary_mrk));
            if (hungary_dfs(i))tot++;
        }
    return tot;
}