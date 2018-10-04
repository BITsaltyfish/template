/*
    ��ȷ�������⣺
        ����01����ѡ��һЩ�еļ��ϣ�ʹ�ü�����ÿһ��**ǡ��**һ��1
        �÷� bool ans=dlx.dfs(0) ������dfs�������ù�
        ���Ҫ��ȡ�����У���Ҫ��dfs�޸�
    �ظ��������⣺
        ����01����ѡ��һЩ�еļ��ϣ�ʹ�ü�����ÿһ��**����**һ��1
        �÷� bool ans=dlx.dfs2(0) ������dfs2�������ù�
        ���Ҫ��ȡ�����У���Ҫ��dfs2�޸�
    ��������Ҫ dlx.init(n,m)
    ���󵥵�0��1��link(x,y)
    ���������dlx.ans[k]��ȡ����,0<=k<dlx.cnt
    maxn��maxm��maxnode��ֵ̫С���ܻ�T
*/
struct DLX{
    const static int maxn=2010;
    const static int maxm=2010;
    const static int maxnode=1000010;//���������'1'�ĸ���
    #define FF(i,A,s) for(int i=A[s];i!=s;i=A[i])
    int L[maxnode],R[maxnode],U[maxnode],D[maxnode];
    int size,col[maxnode],row[maxnode],s[maxm],H[maxn];
    bool vis[maxm];
    int ans[maxn],cnt;
    void init(int n,int m)
    {
        for(int i=0;i<=m;i++)
        {
            L[i]=i-1;R[i]=i+1;U[i]=D[i]=i;s[i]=0;
        }
        for (int i=1;i<=n;i++)H[i]=-1;
        L[0]=m;R[m]=0;size=m+1;
        cnt=-1;
    }
    void link(int r,int c)
    {
        U[size]=c;D[size]=D[c];U[D[c]]=size;D[c]=size;
        if(H[r]<0)H[r]=L[size]=R[size]=size;
        else{
            L[size]=H[r];R[size]=R[H[r]];
            L[R[H[r]]]=size;R[H[r]]=size;
        }
        s[c]++;col[size]=c;row[size]=r;size++;
    }


    //====================��ȷ����===================
    void del(int c)
    {
        L[R[c]]=L[c];R[L[c]]=R[c];
        FF(i,D,c)FF(j,R,i)U[D[j]]=U[j],D[U[j]]=D[j],--s[col[j]];
    }
    void add(int c)
    {
        R[L[c]]=L[R[c]]=c;
        FF(i,U,c)FF(j,L,i)++s[col[U[D[j]]=D[U[j]]=j]];
    }
    bool dfs(int k)
    {
        if(!R[0]){cnt=~cnt?min(k,cnt):k;return true;}
        if(~cnt&&k>=cnt)return false;
        int c=R[0];bool mk=0;FF(i,R,0)if(s[c]>s[i])c=i;
        del(c);
        FF(i,D,c)
        {
            FF(j,R,i)del(col[j]);
            ans[k]=row[i];

            if(dfs(k+1))return true; /*��ΪֻҪ���һ�⣬�Ͽ� */
            //mk|=dfs(k+1); /*��Ϊ���ȡ��������*/

            FF(j,L,i)add(col[j]);
        }
        add(c);
        return mk;
    }



    //====================�ظ�����===================
    void remove(int c)
    {
        FF(i,D,c)L[R[i]]=L[i],R[L[i]]=R[i];
    }
    void resume(int c)
    {
        FF(i,U,c)L[R[i]]=R[L[i]]=i;
    }
    int A()
    {
        int res=0;
        memset(vis,0,sizeof(vis));
        FF(i,R,0)if(!vis[i])
        {
            res++;vis[i]=1;
            FF(j,D,i)FF(k,R,j)vis[col[k]]=1;
        }
        return res;
    }
    bool dfs2(int k)
    {
        if(!R[0]){cnt=~cnt?min(k,cnt):k;return true;}
        if(~cnt&&k>=cnt)return false;
        bool mk=0;
        if(cnt==-1||k+A()<cnt)
        {
            int temp=inf,c;
            FF(i,R,0)if(temp>s[i])temp=s[i],c=i;
            FF(i,D,c)
            {
                remove(i);ans[k]=row[i];FF(j,R,i)remove(j);
                if (dfs2(k+1))return true; /*��ΪֻҪ���һ�⣬�Ͽ� */
                //mk|=dfs2(k+1); /*��Ϊ���ȡ��������*/
                FF(j,L,i)resume(j);resume(i);
            }
        }
        return mk;
    }
    #undef FF
}dlx;