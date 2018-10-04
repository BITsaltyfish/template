/*
    �����ͼ���ƥ�䣬bfs��
    �����Ƕ���ͼ���ҵ��Ѿ��ֿ��İ汾�����·��������ҵ�û�ֿ��İ汾
    ���(1)~(n1)�ĵ��ǵ�һ�����ϣ����(n1+1)~(n2)�ĵ��ǵڶ�������
*/
#define M 2010
#define N 1010
struct edge{int to,next;}e[M];
int head[N],cnt;
int hungary_mrk[N];
int hungary_pre[N];
int match[N];
inline void ins(int u,int v)
{
    e[++cnt].to=v;
    e[cnt].next=head[u];
    head[u]=cnt;
}
inline void insert(int u,int v)
{
    ins(u,v);
    ins(v,u);
}
queue<int>Q;
int hungary(int n1,int n2)
{
    int tot=0;
    memset(match,0,sizeof(match));
    memset(hungary_mrk,0,sizeof(hungary_mrk));
    for(int i=1;i<=n1;i++)
    if (!match[i])
    {
        while(!Q.empty())Q.pop();Q.push(i);
        hungary_pre[i]=0;
        bool flg=0;
        while(!Q.empty()&&!flg)
        {
            int now=Q.front();Q.pop();
            for (int j=head[now];j&&!flg;j=e[j].next)
            {
                int nex=e[j].to;
                if (hungary_mrk[nex]!=i)
                {
                    hungary_mrk[nex]=i;
                    Q.push(match[nex]);
                    if (match[nex])hungary_pre[match[nex]]=now;
                    else
                    {
                        flg=1;
                        int uu=now,vv=nex;
                        while (uu)
                        {
                            int tt=match[uu];
                            match[uu]=vv;
                            match[vv]=uu;
                            uu=hungary_pre[uu];
                            vv=tt;
                        }
                    }
                }
            }
        }
        if (match[i])tot++;
    }
    return tot;
}



//========================================�����Ƕ���ͼ�����Ѿ��ֿ��İ汾==========================================
//========================================�����Ƕ���ͼ���ұ�Ŵ��ҵİ汾==========================================

#define M 2010
#define N 1010
struct edge{int to,next;}e[M];
int head[N],cnt;
int hungary_mrk[N];
int hungary_pre[N];
int hungary_left[N];
int match[N];
inline void ins(int u,int v)
{
    e[++cnt].to=v;
    e[cnt].next=head[u];
    head[u]=cnt;
}
inline void insert(int u,int v)
{
    ins(u,v);
    ins(v,u);
}
queue<int>Q2;
queue<pa >Q1;
int hungary(int n)
{
    int tot=0;
    memset(match,0,sizeof(match));
    memset(hungary_mrk,0,sizeof(hungary_mrk));
    memset(hungary_left,-1,sizeof(hungary_left));
    for (int i=1;i<=n;i++)
    if (hungary_left[i]==-1)
    {
        while (!Q1.empty())Q1.pop();Q1.push(mkp(i,1));
        while (!Q1.empty())
        {
            int now=Q1.front().first,op=Q1.front().second;Q1.pop();
            hungary_left[now]=op;
            for (int j=head[now];j;j=e[j].next)
                if (hungary_left[e[j].to]==-1)Q1.push(mkp(e[j].to,op^1));
        }
    }
    for(int i=1;i<=n;i++)
    if (hungary_left[i]&&!match[i])
    {
        while(!Q2.empty())Q2.pop();Q2.push(i);
        hungary_pre[i]=0;
        bool flg=0;
        while(!Q2.empty()&&!flg)
        {
            int now=Q2.front();Q2.pop();
            for (int j=head[now];j&&!flg;j=e[j].next)
            {
                int nex=e[j].to;
                if (hungary_mrk[nex]!=i)
                {
                    hungary_mrk[nex]=i;
                    Q2.push(match[nex]);
                    if (match[nex])hungary_pre[match[nex]]=now;
                    else
                    {
                        flg=1;
                        int uu=now,vv=nex;
                        while (uu)
                        {
                            int tt=match[uu];
                            match[uu]=vv;
                            match[vv]=uu;
                            uu=hungary_pre[uu];
                            vv=tt;
                        }
                    }
                }
            }
        }
        if (match[i])tot++;
    }
    return tot;
}