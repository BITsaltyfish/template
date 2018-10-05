Burnside引理和Pólya定理
/*Burnside引理*/
等价类的个数为 = [c1(a1)+c1(a2)+···c1(an)]/|G|
竞赛中使用没有polya普遍

/*Pólya定理*/
c = 色数
p_i 每个置换的分解积个数 （如置换 3 4 5 6 1 2 的分解积为 (3,5,1)(4,6,2) 个数为 2）
ans = ∑c^{p_i}/|G|
一般循环置换的代码是
for(int i=0;i<n;i++)
	ans += a[gcd(n,i)];
ans /= n;