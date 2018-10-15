int a[2010][2010];
int h[2010][2010];
int n,m,ans;
int zhan[2010],l[2010],r[2010],top;
int main()
{
    n=read();
    for (int i=1;i<=n;i++)for (int j=1;j<=n;j++)a[i][j]=read();
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=n;j++)
            h[i][j]=a[i][j]==0?1+h[i-1][j]:0;
    }
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=n;j++)
        {
            while (top&&h[i][zhan[top]]>h[i][j])
            {
                ans=max(ans,h[i][zhan[top]]*(j-r[top-1]-1));
                top--;
            }
            if (top&&h[i][zhan[top]]==h[i][j]){r[top]=j;continue;}
            zhan[++top]=j;
            l[top]=r[top]=j;
        }
        while (top)
        {
            ans=max(ans,h[i][zhan[top]]*(n-r[top-1]));
            top--;
        }
    }
    printf("%d\n",ans);
}