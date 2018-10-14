//catalan数
//	1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796, 58786, 208012, 742900,
//	2674440, 9694845, 35357670, 129644790, 477638700, 1767263190, 6564120420,
//	24466267020, 91482563640, 343059613650, 1289904147324,
catalan[i] = 1ll*(4*i-2)*inv(i+1)%mod*catalan[i-1];
//第一类斯特林数：把p个对象排成k个非空循环排列的方案数
//
/*n|m     1     2      3      4     5    6   7    8  9
  -+-----------------------------------------------------
  1|      1     1
  2|      2     1      1
  3|      6     2      3      1
  4|     24     6     11      6     1
  5|    120    24     50     35    10     1
  6|    720   120    274    225    85    15    1
  7|   5040   720   1764   1624   735   175   21   1
  8|  40320  5040  13068  13132  6769  1960  322  28  1
*/
for (int i = 0; i <= N ; ++i)
{
	S1[i][0] = 0;
	S1[i][i] = 1;
	for (int j = 1; j < i ; ++j)
	{
		S1[i][j] = (1ll*S1[i-1][j-1] + 1ll*(i-1)*S1[i-1][j]%mod)%mod;
	}
}
//第二类斯特林数：把p个对象排成k个不可区分的盒子且没有空盒子的划分数
/*
n\ m   1    2     3      4      5    6    7    8     9
----------------------------------------------------------------------------------
1  |   1
2  |   1    1
3  |   1    3     1
4  |   1    7     6      1
5  |   1   15    25     10      1
6  |   1   31    90     65     15     1
7  |   1   63   301    350    140    21     1
8  |   1  127   966   1701   1050   266    28    1
9  |   1  255  3025   7770   6951  2646   462   36   1
---------------------------------------------------------------------------------
*/
for (int i = 0; i <= N; ++i)
{
	S2[i][0] = 1;
	S2[i][i] = 1;
	for (int j = 1; j < i ; ++j)
	{
		S2[i][j] = (1ll*S2[i-1][j-1] + 1ll*j*S2[i-1][j]%mod)%mod;
	}
}
//错排数：全排列中满足a[i]!=i的方案数。
D(1)=0,D(2)=1,D(n)=1ll*(n-1)*(D(n-2)+D(n-1));

// 拟卡特兰数f*[n]=n!f[n]（为了去掉分母）应用：n个数的无序乘法方案
f*[n]=(4n-6)f*[n-1];

//  贝尔数：把n个元素划分到1~n个集合内的方案数之和，即n个元素的集合划分方案数
//	1, 1, 2, 5, 15, 52, 203, 877, 4140, 21147, 115975, 678570, 4213597, 27644437, 190899322,
//	1.根据定义显然贝尔数就是第二类斯特林数之和
    B[0]=1,B[1]=1,B[x]=∑(k=1~x)S[x][k]
    B[n]=∑(k=0~n-1)C(n-1,k)B[k]
//	2.取模p意义下 B[n+p]=B[n]+B[n+1] (mod p)可以做p^3的矩阵快速幂转移
	B[i*p]~B[i*p+p-1]->B[(i+1)*p]~B[(i+1)*p+p-1]


// 拆分数 把一个数拆成一个或多个不增数字之和的方案数。如7=3+2+2. 做法是n*sqrt(n)筛正五边形数然后递推
	p(0)=1,p(x)=p(x-1)+p(x-2)-p(x-5)-p(x-7)....
const int mod=1e9+7;
void inc(int &x,int y){x=x+y>=mod?x+y‐mod:x+y;}
void dec(int &x,int y){x=x‐y<0?x‐y+mod:x‐y;}
void getchaifen(int N){
	p[0]=1;
	for(int i=1;i<=N;i++)
	{
		for(int j=1,w=1;w<=i;w+=3*j+1,j++)
			if(j&1)inc(p[i],p[i‐w]);
			else dec(p[i],p[i‐w]);
		for(int j=1,w=2;w<=i;w+=3*j+2,j++)
			if(j&1)inc(p[i],p[i‐w]);
			else dec(p[i],p[i‐w]);
	}
}
//组合数的一些定理
C(n,m)=(n!)/[m!(n-m)!]
C(n,m)=C(n-1,m)+C(n-1,m-1)
C(n,m)*C(m,k) = C(n,k)*C(n-k,m-k)
∑(k=0~n)C(n,k)=2^n
∑(k=0~m)C(n+k,k)=C(n+m+1,m)


范德蒙卷积公式 ∑(k=0~m){C(m1,k)*C(m2,n-k)}=C(m1+m2,n)
范德蒙卷积公式+性质2 ：C(2n,n)=C(n,0)^2+C(n,1)^2+...+C(n,n)^2

斐波那契数列 f[0]=0,f[1]=1,f[n]=f[n-1]+f[n-2](n>=2)
部分和Sn = f[0]+f[1]+...+f[n] = f[n+2]-1 数学归纳法可证，矩阵快速幂可求
显式解 f[n]=1/sqrt(5)[(1+sqrt(5))/2]^n-1/sqrt(5)[(1-sqrt(5))/2]^n
定义二元组T(a,b)=(1/2)a+(sqrt(5)/2)b，则可以用两个整数表示公式里奇异部分
T(a,b)+T(c,d)=T(a+c,b+d)
T(a,b)*T(c,d)=T((ac+5bd)/2,(ad+bc)/2)数学归纳法可证里面除2之后还是整数
f[n]=C(n-1,0)+C(n-2,1)+C(n-3,2)+...+C(n-t,t-1)=∑(k=0~n)C(n-k-1,k), t=(n-1)除二下取整。
证明右边也满足F(n)=F(n-1)+F(n-2)即可

如果有递推关系f[n]=a[1]f[n-1]+a[2]f[n-2]+a[3]f[n-3]+...+a[k]f[n-k]
解特征根方程：x^k-a[1]x^(k-1)-a[2]x^(k-2)+...+(-a[k])=0

n个球放进m个盒，根据球是否相同，盒是否相同，盒是否非空，共8种可能
    球相同，盒相同，盒非空：不会,很难,p(n,m)即总和为n，恰好m个数相加的拆分数
    球相同，盒相同，盒可空：p(n)//拆分数
    球相同，盒不同，盒非空：C(n-1,m-1)
    球相同，盒不同，盒可空：C(n+m-1,m-1)
    球不同，盒相同，盒非空：S(n,m)//第二类斯特林数
    球不同，盒相同，盒可空：S(n,1)+...+S(n,m)
    球不同，盒不同，盒非空：S(n,m)*m!
    球不同，盒不同，盒可空：m^n
	n种元素（每种足够多）选m个：C(n+m-1,m)
