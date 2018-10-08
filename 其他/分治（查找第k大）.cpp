#include<bits/stdc++.h>
using namespace std;
int quickSort(int a[],int left,int right,int k) {
	int i=left;
	int j=right;
	swap(a[left],a[left+rand()%(right-left+1)]);//随机选择基准防止原数据有序
	int temp=a[left];					//temp代表选择的基准
	while(i!=j) {
		while(i<j&&a[j]>=temp)j--;		//一定要先从后到前找第一个比基准要大的
		if(j>i)a[i]=a[j];				//a[i]已经赋值给temp,所以直接将a[j]赋值给a[i],赋值完之后a[j],有空位
		while(i<j&&a[i]<=temp)i++;		//从前到后找第一个比基准要小的
		if(i<j)a[j]=a[i];
	}
	a[i]=temp;							//把基准插入,此时i与j已经相等R[low..pivotpos-1].keys≤R[pivotpos].key≤R[pivotpos+1..high].keys
	if(k+left-1<i) return quickSort(a,left,i-1,k);			//查询左边
	else if(k+left-1>i)return quickSort(a,i+1,right,k-(i-left+1));	//查询右边
	else return temp;
}
int a[1000010];
int main() {
	srand(time(0));
	int n,m;
	while(~scanf("%d%d",&n,&m)){
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		printf("%d\n", quickSort(a,1,n,m));
	}
	return 0;
}