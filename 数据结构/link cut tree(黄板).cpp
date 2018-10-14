/*
bzoj1180:
'b':ѯ��(x,y)�Ƿ���ͨ��������ǣ���ô��һ����(x,y)
'p':�޸�һ����ĵ�Ȩ
'e':���(x,y)��ͨ����ô���·����Ȩֵ��
//���ڴ���Ȩ�����⣬��ÿһ���߽�һ����P(id=[n+1,n+m])��Ȼ������(P,x)(P,y)����P�������õ�Ȩ����
*/
#include<bits/stdc++.h>
#define inf 1000000000
#define mod 1000000007
#define ll long long
using namespace std;
int n,q,top;
int c[30005][2],fa[30005],sum[30005],v[30005],st[30005];
bool rev[30005];
char ch[15];
void update(int x)
{
	int l=c[x][0],r=c[x][1];
	sum[x]=sum[l]+sum[r]+v[x];
}
void pushdown(int x)
{
	int l=c[x][0],r=c[x][1];
	if(rev[x])
	{
		rev[x]^=1,rev[l]^=1,rev[r]^=1;
		swap(c[x][0],c[x][1]);
	}
}
bool isroot(int x)
{
	return !(c[fa[x]][0]==x||c[fa[x]][1]==x);
}
void rotate(int &x)
{
	int y=fa[x],z=fa[y],l,r;
	l=(c[y][1]==x);r=l^1;
	if(!isroot(y))c[z][c[z][1]==y]=x;
	fa[x]=z;fa[y]=x;fa[c[x][r]]=y;
	c[y][l]=c[x][r];c[x][r]=y;
	update(y);update(x);
}
void splay(int x)
{
	top=0;st[++top]=x;
	for(int i=x;!isroot(i);i=fa[i])st[++top]=fa[i];
	while(top)pushdown(st[top--]);
	while(!isroot(x))
	{
		int y=fa[x],z=fa[y];
		if(!isroot(y))
		{
			if(c[y][0]==x^c[z][0]==y)rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
}
void access(int x)
{
	for(int t=0;x;t=x,x=fa[x])
		splay(x),c[x][1]=t,update(x);
}
void makeroot(int x)
{
	access(x);splay(x);rev[x]^=1;
}
void link(int x,int y)
{
    makeroot(x);fa[x]=y;
}
int getrt(int x)
{
	access(x);splay(x);
	while(c[x][0])x=c[x][0];
	return x;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d%d",sum+i,v+i);
	scanf("%d",&q);
	while(q--)
	{
		int x,y;scanf("%s%d%d",ch+1,&x,&y);
		if(ch[1]=='b')
		{
			if(getrt(x)==getrt(y))puts("no");
			else puts("yes"),link(x,y);
		}
		if(ch[1]=='p')
		{
			makeroot(x);v[x]=y;update(x);
		}
		if(ch[1]=='e')
		{
			if(getrt(x)!=getrt(y))puts("impossible");
			else
			{
				makeroot(x),access(y),splay(y);
				printf("%d\n",sum[y]);
			}
		}
	}
	return 0;
}
