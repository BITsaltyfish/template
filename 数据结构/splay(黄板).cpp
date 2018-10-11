/*
bzoj1251 序列终结者
操作1:区间加 操作2:区间翻转 操作3:区间最大值
*/
#include<bits/stdc++.h>
#define inf 0x7fffffff
using namespace std;
const int maxn=100010;
int n,m,sz,rt;
int fa[maxn],c[maxn][2],id[maxn];
int tag[maxn],v[maxn],mx[maxn],size[maxn];
bool rev[maxn];
inline void pushup(int k)
{
    int l=c[k][0],r=c[k][1];
    mx[k]=max(mx[l],mx[r]);
    mx[k]=max(mx[k],v[k]);
    size[k]=size[l]+size[r]+1;
}
void pushdown(int k)
{
    int l=c[k][0],r=c[k][1],t=tag[k];
    if(t)
    {
		tag[k]=0;
		if(l){tag[l]+=t;mx[l]+=t;v[l]+=t;}
		if(r){tag[r]+=t;mx[r]+=t;v[r]+=t;}
    }
    if(rev[k])
    {
		rev[k]=0;
		rev[l]^=1;rev[r]^=1;
		swap(c[k][0],c[k][1]);
    }
}
void rotate(int x,int &k)
{
    int y=fa[x],z=fa[y],l,r;
    if(c[y][0]==x)l=0;else l=1;r=l^1;
    if(y==k)k=x;
    else {if(c[z][0]==y)c[z][0]=x;else c[z][1]=x;}
    fa[x]=z;fa[y]=x;fa[c[x][r]]=y;
    c[y][l]=c[x][r];c[x][r]=y;
    pushup(y);pushup(x);
}
void splay(int x,int &k)
{
    while(x!=k)
    {
		int y=fa[x],z=fa[y];
		if(y!=k)
		{
			if(c[y][0]==x^c[z][0]==y)
				rotate(x,k);
			else rotate(y,k);
		}
		rotate(x,k);
    }
}
int find(int k,int rank)
{
    if(tag[k]||rev[k])pushdown(k);
    int l=c[k][0],r=c[k][1];
    if(size[l]+1==rank)return k;
    else if(size[l]>=rank)return find(l,rank);
    else return find(r,rank-size[l]-1);
}
inline void update(int l,int r,int val)
{
    int x=find(rt,l),y=find(rt,r+2);
    splay(x,rt);splay(y,c[x][1]);
    int z=c[y][0];
    tag[z]+=val;v[z]+=val;mx[z]+=val;
}
inline void rever(int l,int r)
{
    int x=find(rt,l),y=find(rt,r+2);
    splay(x,rt);splay(y,c[x][1]);
    int z=c[y][0];
    rev[z]^=1;
}
inline void query(int l,int r)
{
    int x=find(rt,l),y=find(rt,r+2);
    splay(x,rt);splay(y,c[x][1]);
    int z=c[y][0];
    printf("%d\n",mx[z]);
}
inline void build(int l,int r,int f)
{
    if(l>r)return;
    int now=id[l],last=id[f];
    if(l==r)
    {
		fa[now]=last;size[now]=1;
		if(l<f)c[last][0]=now;
		else c[last][1]=now;
		return;
    }
    int mid=(l+r)>>1;now=id[mid];
    build(l,mid-1,mid);build(mid+1,r,mid);
    fa[now]=last;pushup(now);
    if(mid<f)c[last][0]=now;
    else c[last][1]=now;
}
int main()
{
    mx[0]=-inf;
    n=read();m=read();
    for(int i=1;i<=n+2;i++)
		id[i]=++sz;
    build(1,n+2,0);rt=(n+3)>>1;
    for(int i=1;i<=m;i++)
    {
		int f,l,r,d;scanf("%d",&f);
		switch(f)
		{
			case 1:scanf("%d%d%d",&l,&r,&d);update(l,r,d);break;
			case 2:scanf("%d%d",&l,&r);rever(l,r);break;
			case 3:scanf("%d%d",&l,&r);query(l,r);break;
		}
    }
    return 0;
}
