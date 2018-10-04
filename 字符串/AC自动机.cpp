#include <bits/stdc++.h>
using namespace std;
const int AC_NOD = 28,AC_N = 5e5+10;
struct Tire
{
    int nxt[AC_N][AC_NOD],fail[AC_N],cnt[AC_N];
    int root ,tot;
    int id[AC_NOD];
    int end[AC_N];
    int newnode()
    {
        for(int i = 0;i < AC_NOD ;i++)nxt[tot][i] = -1;
        fail[tot] = -1;cnt[tot] = 0;
        return tot++;
    }
    void init()
    {
        tot = 0;
        memset(end,false,sizeof end);
        root = newnode();
    }
    int getid(char x)
    {
        if(x<='z'&&x>='a') return x-'a'+10;
        else if(x<='Z'&&x>='A')return 36+x-'A';
        else return x-'0';
    }


    void insert(string s)
    {
        int p = root,len = s.length();
        for(int i = 0;i< len;i++)
        {
            int cur = getid(s[i]);
            if(nxt[p][cur] == -1)nxt[p][cur] = newnode();
            p = nxt[p][cur];
        }
        cnt[p]++;end[p] = true;
    }
    void build()
    {
        queue<int> que;
        que.push(root);
        int now;

        while(!que.empty())
        {
            now = que.front();que.pop();
            if(end[fail[now]])end[now] = true;
            for(int i = 0;i< AC_NOD;i++)
            {
                if(~nxt[now][i])
                {
                    if(now == root) fail[nxt[now][i]] = root;
                    else fail[nxt[now][i]] = nxt[fail[now]][i];
                    que.push(nxt[now][i]);
                }
                else
                {
                    if(now == root) nxt[now][i] = root;
                    else nxt[now][i] = nxt[fail[now]][i];
                }
            }
        }
    }
    int count(string t)
    {
        int now = root;
        int len = t.length(),p,ans = 0;
        for(int i = 0;i<len;i++)
        {
            p = getid(t[i]),now = nxt[now][p];
            for(int tmp = now;tmp!= root;tmp = fail[tmp])ans += cnt[tmp];
        }return ans;
    }
}T;
int main()
{
    int t;
    cin.sync_with_stdio(0);
    cin>>t;
    while(t--)
    {
        T.init();
        int n;cin>>n;
        string q;for(int i = 1;i<= n;i++)cin>>q,T.insert(q);
        T.build();
        cin>>q; cout<<T.count(q)<<endl;
    }
    return 0;
}
