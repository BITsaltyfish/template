using namespace std;
typedef long long LL; 
const int N=1000010; 
const int maxn = 100005;
const LL INF=0x3f3f3f3f3f3f3f3f; 
/*
    一张无向图每条边可以多次经过问s到t的不小于k的最短路
    对于终点的边取最短的边w 然后对%2w跑同余最短路
*/
typedef pair<LL,int>seg; 
priority_queue<seg,vector<seg>,greater<seg> >q;    
int stu[N],u[N],vto[N],w[N],nxt[N],n,m,tot=0;
LL d[maxn][N],W;
void add(int a,int b,int c){ 
    u[++tot]=a,vto[tot]=b,w[tot]=c;
    nxt[tot]=stu[u[tot]];
    stu[u[tot]]=tot;    
}
void SPFA(int src)
{   
    for(int i = 0;i <= n;i ++ )for(int j = 0;j < W;j ++ ) d[i][j]=INF;   
    q.push(make_pair(0,src)); 
    while(!q.empty())
    { 
        seg now = q.top(); q.pop(); 
        LL wnow = now.first;
        int x = now.second;
        if(wnow > d[x][wnow%W])continue; 
        for(int e = stu[x] ; e!=-1 ; e=nxt[e]){
            LL nw = wnow + w[e];
            int v = vto[e];
            if(d[v][nw % W] > nw){ 
                d[v][nw % W] = nw; 
                q.push( make_pair (nw,v)); 
            }   
        }
    }
} 