#include <bits/stdc++.h>
using namespace std;
const int MX = 1000010;
int d[MX][21],inx[MX];
int num[MX];
void BuildSt(int n)
{
	inx[0] = -1;
	for (int i = 1; i <= n ; ++i)
	{
		d[i][0] = num[i];
		inx[i] = (((i)&(i-1))?0:1) + inx[i-1];
	}
	for (int j = 1; j < 21 ; ++j)
	{
		int k = 1<<(j-1);
		for (int i = 1; i + k*2 -1<=n; ++i)
			d[i][j] = min(d[i][j-1],d[i+k][j-1]);
	}
}
int query(int l,int r)
{
	int k = inx[r-l+1];
	return min(d[l][k],d[r-(1<<k)+1][k]);
}
int main(int argc, char const *argv[])
{
	int n;
}