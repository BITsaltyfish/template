#include <bits/stdc++.h>
/*求取一个点的m维度的最近的点*/
using namespace std;
const int maxn=200010;
int cmpNo,K;
struct Node{
    int x[10],l,r,id;
    bool operator <(const Node &b)const{
        return x[cmpNo]<b.x[cmpNo];
    }
};

long long Dis(const Node &a,const Node &b){
    long long ret=0;
    for(int i=0;i<K;i++)
        ret+=(a.x[i]-b.x[i])*(a.x[i]-b.x[i]);
    return ret;    
}

Node p[maxn];

int Build(int l,int r,int d){
    if(l>r)return 0;
    cmpNo=d;
    int mid=l+r>>1;
    nth_element(p+l,p+mid,p+r+1);
    p[mid].l=Build(l,mid-1,(d+1)%K);
    p[mid].r=Build(mid+1,r,(d+1)%K);
    return mid;
}

priority_queue<pair<long long,int> >q;
void Kth(int l,int r,Node tar,int k,int d){
    if(l>r)return;
    int mid=l+r>>1;
    pair<long long,int>v=make_pair(Dis(p[mid],tar),p[mid].id);
    if(q.size()==k&&v<q.top())q.pop();
    if(q.size()<k)q.push(v);
    long long t=tar.x[d]-p[mid].x[d]; 
    if(t<=0){
        Kth(l,mid-1,tar,k,(d+1)%K);
        if(q.top().first>t*t)
            Kth(mid+1,r,tar,k,(d+1)%K);
    }
    else{
        Kth(mid+1,r,tar,k,(d+1)%K);
        if(q.top().first>t*t)
            Kth(l,mid-1,tar,k,(d+1)%K);
    }    
}
int k,ans[20];
Node a[maxn];
int main(){
    int n;
    while(scanf("%d%d",&n,&K)!=EOF){
        for(int id=1;id<=n;id++){
            for(int i=0;i<K;i++)
                scanf("%d",&p[id].x[i]);
            p[id].id=id;
            a[id]=p[id];    
        }
        Build(1,n,0);
        int Q,tot;
        scanf("%d",&Q);
        Node tar;
        while(Q--){
            for(int i=0;i<K;i++)
                scanf("%d",&tar.x[i]);
            scanf("%d",&k);
            printf("the closest %d points are:\n",k);
            for(int i=1;i<=k;i++)q.push(make_pair(1e18,-1));
            Kth(1,n,tar,k,0);tot=0;
            while(!q.empty()){
                int id=(q.top()).second;q.pop();
                ans[tot++]=id;
            }
            for(int i=tot-1;i>=0;i--)
                for(int j=0;j<K;j++)
                    printf("%d%c",a[ans[i]].x[j],j==K-1?'\n':' ');        
        }
    }
    return 0;
}