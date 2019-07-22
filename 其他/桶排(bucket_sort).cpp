//十进制按位桶排时间O((n+base)k)，k是log_base max{a[i]}
//空间O(6N),估算：N=1e7 约240M空间
#define N 5000010
#define max(a,b) ((a)>(b)?(a):(b))
typedef int T;
const static int base=131072,basem=base-1;
//base最好是2^k,否则把&basem改成%base
int rk[2][N],sa[2][N];
T b[N];
void bucket_sort(T* a,int l,int r)
{
    if(l>=r)return;
    int sz[base]={0};
    register int tot=r-l+1,pre=0,cur=1,i,now;
    T bin=1;
    register long long mx=-(1ll<<60);
    for(i=1;i<=tot;i++)b[i]=a[i+l],mx=max(mx,b[i]);
    while(bin<=mx)
    {
        int* csa=sa[cur],*psa=sa[pre];
        int* crk=rk[cur],*prk=rk[pre];
        memset(sz,0,sizeof(sz));
        for(i=1;i<=tot;i++)++sz[(b[i]/bin)&basem];
        for(i=1;i<base;i++)sz[i]+=sz[i-1];
        if(bin==1)
        {
            for(i=tot;i>=1;i--)
            {
                crk[i]=sz[(b[i]/bin)&basem]--;
                csa[crk[i]]=i;
            }
        }else for(i=tot;i>=1;i--)
        {
            now=psa[i];
            crk[now]=sz[(b[now]/bin)&basem]--;
            csa[crk[now]]=now;
        }
        pre^=1;
        cur^=1;
        if(1ll*bin*base>mx)break;
        bin*=base;
    }
    for(i=l;i<=r;i++)a[i]=b[sa[pre][i-l+1]];
}