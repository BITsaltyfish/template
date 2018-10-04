#include <bits/stdc++.h>
using namespace std;
/*n为总字符串的长度
 *r数组为被操作的字符串，索引从0开始，最后一位(r[n-1])一定是'$'(char数组)||'0'(int数组)
 *sa为生成的后缀数组，从0开始到n-1结束，保证sa[0] = n-1
 *m代表字符集的大小或者说范围。
 *height[1]的值无效因为其没有前驱字符串
 *查询两个后缀的lcp应该查询query(rnk[l]+1,rnk[r]);
 */
typedef long long ll;
const int maxn = 300010;
char a[maxn];
int wa[maxn],wb[maxn],wv[maxn],wts[maxn];
int cmp(int *r,int a,int b,int l)
{
	return r[a] == r[b]&&r[a+l] == r[b+l];
}
void init_sa(char *r,int *sa,int n,int m)
{
	int i,j,*x = wa,*y = wb,*t;
	int p;
	for(i = 0;i < m;i ++) wts[i] = 0;
	for(i = 0;i < n;i ++) wts[ x[i] = r[i]]++;
	for(i = 0;i < m;i ++) wts[i] += wts[i-1];
	for(i = n-1;i >= 0; --i) sa[--wts[x[i]]] = i;
	for(j = 1,p = 1; p < n ; j <<= 1 , m = p )
	{
        for(p = 0,i = n - j; i < n; i ++) y[p++] = i;
		for(i = 0;i < n; i ++) if(sa[i] >= j) y[p++] = sa[i] - j;
		for(i = 0;i < n; i ++) wv[i] = x[y[i]];
		for(i = 0;i < m; i ++) wts[i] = 0;
		for(i = 0;i < n; i ++) wts[wv[i]]++;
        for(i = 1;i < m; i ++) wts[i] += wts[i-1];
		for(i = n-1;i >= 0;i--) sa[--wts[wv[i]]] = y[i];
        for(t = x,x = y,y = t,p = 1,x[sa[0]] = 0,i = 1;i < n; i++)
			x[sa[i]] = cmp(y,sa[i-1],sa[i],j)?p-1:p++;
	}

	return;
}
int rnk[maxn],height[maxn];
int d[maxn][20],inx[maxn];
void init_inx()
{
    inx[0] = -1;for(int i = 1;i < maxn;i++)inx[i] = (((i)&(i-1))?0:1)+inx[i-1];
}
void init_rmq(int *r,int n)
{
    for(int i = 0;i<n;i++)d[i][0] = height[i];
    for(int j = 1;j<20; ++j)
    {
        int k = 1<<(j-1);
        for(int i = 0;i+k*2-1 < n;++i)d[i][j] = min(d[i][j-1],d[i+k][j-1]);
    }
}
int query(int l,int r)
{
    int k = inx[r-l+1];return min(d[l][k],d[r- (1<<k)+1][k]);
}
void calheight(char *r,int *sa,int n)
{
	int i,j,k = 0;
	for(i = 1;i < n;i++)rnk[sa[i]] = i;
	for(i = 0;i < n-1;height[rnk[i++]] = k)
        for(k?k--:0,j = sa[rnk[i]-1];r[i+k] == r[j+k];k++);
}
int sa[maxn];
void solve()
{
	scanf("%s",a);
	int len = strlen(a);a[len]='$';len++;
	int n=len;
	scanf("%s",a+len);len = strlen(a);a[len]='#';len++;
	init_sa(a,sa,len,256);
	calheight(a,sa,len);
	init_rmq(height,len);
	int r = 2;
	int ans =0;
	for(int i=2;i<len;i++)
	{
		r = max(r,i);
		if(sa[i]>=n)continue;
		while(r<len&&sa[r]<n)r++;if(r == len)break;
		ans = max(ans,query(i+1,r));
	}
	r = 2;
	for(int i=2;i<len;i++)
	{
		r = max(r,i);
		if(sa[i]<n)continue;
		while(r<len&&sa[r]>=n)r++;if(r == len)break;
		ans = max(ans,query(i+1,r));
	}
	printf("%d\n",ans );
}
int main(int argc, char const *argv[])
{
	init_inx();
	solve();
	return 0;
}