/* codeforces 70D
 * 操作一：插入一个点 操作二：查询一个点是否在凸包内
 */
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
typedef long long ll;
using namespace std;
map<int,int> lower,upper;
ll det(ll x1,ll y1,ll x2,ll y2,ll x3,ll y3){return x1*y2-x2*y1+x2*y3-x3*y2+x3*y1-x1*y3;}
bool check(map<int,int> &A,int x,int y)//检查(x,y)是否在A下凸壳内
{
	auto it=A.lower_bound(x);
	if (it==A.end())return false;
	if (it->first==x)return it->second>=y;
	if (it==A.begin())return false;
	auto itp=it--;
	return det(it->first,it->second,x,y,itp->first,itp->second)>=0;
}
void add(map<int,int> &A,int x,int y)
{
	if (check(A,x,y)) return;
	A[x]=y;
	auto it=A.find(x),ita=it++,itb=it;
	while (it!=A.end())
	{
		itb=it++;
		if (it==A.end())break;
		if (det(ita->first,ita->second,itb->first,itb->second,it->first,it->second)<0) break;
		A.erase(itb);
	}
	while (1)
	{
		it=ita;
		if (it==A.begin()) break;
		ita=it--;
		if (it==A.begin()) break;
		itb=it--;
		if (det(ita->first,ita->second,itb->first,itb->second,it->first,it->second)>0) break;
		A.erase(itb);
	}
}
int main()
{
	int T;scanf("%d",&T);
	for (int i=1;i<=T;i++)
	{
		int t,x,y;
		scanf("%d%d%d",&t,&x,&y);
		if (t==1)add(lower,x,y),add(upper,x,-y);
		else puts((check(lower,x,y)&&check(upper,x,-y))?"YES":"NO");
	}
	return 0;
}
