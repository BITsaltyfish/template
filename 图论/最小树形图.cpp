//求具有V个点,以root为根节点的图map的最小树形图
int zhuliu(int root, int V, int map[MAXV + 7][MAXV + 7]) {
    bool visited[MAXV + 7];
    bool flag[MAXV + 7];//缩点标记为true,否则仍然存在
    int pre[MAXV + 7];//点i的父节点为pre[i]
    int sum = 0;//最小树形图的权值
    int i, j, k;
    for(i = 0; i <= V; i++) flag[i] = false, map[i][i] = INF;
    pre[root] = root;
    while(true) {
        for(i = 1; i <= V; i++) { //求最短弧集合E0
            if(flag[i] || i == root) continue;
            pre[i] = i;
            for(j = 1; j <= V; j++)
                if(!flag[j] && map[j][i] < map[pre[i]][i])
                    pre[i] = j;
            if(pre[i] == i) return -1;
        }
        for(i = 1; i <= V; i++) { //检查E0
            if(flag[i] || i == root) continue;
            for(j = 1; j <= V; j++) visited[j] = false;
            visited[root] = true;
            a
            j = i;//从当前点开始找环
            do {
                visited[j] = true;
                j = pre[j];
            } while(!visited[j]);
            if(j == root)continue;//没找到环
            i = j;//收缩G中的有向环
            do { //将整个环的取值保存,累计计入原图的最小树形图
                sum += map[pre[j]][j];
                j = pre[j];
            } while(j != i);
            j = i;
            do { //对于环上的点有关的边,修改其权值
                for(k = 1; k <= V; k++)
                    if(!flag[k] && map[k][j] < INF && k != pre[j])
                        map[k][j] -= map[pre[j]][j];
                j = pre[j];
            } while(j != i);
            for(j = 1; j <= V; j++) { //缩点,将整个环缩成i号点,所有与环上的点有关的边转移到点i
                if(j == i) continue;
                for(k = pre[i]; k != i; k = pre[k]) {
                    if(map[k][j] < map[i][j]) map[i][j] = map[k][j];
                    if(map[j][k] < map[j][i]) map[j][i] = map[j][k];
                }
            }
            for(j = pre[i]; j != i; j = pre[j]) flag[j] = true;//标记环上其他点为被缩掉
            break;//当前环缩点结束,形成新的图G',跳出继续求G'的最小树形图
        }
        if(i > V) { //如果所有的点都被检查且没有环存在,现在的最短弧集合E0就是最小树形图.累计计入sum,算法结束
            for(i = 1; i <= V; i++)
                if(!flag[i] && i != root) sum += map[pre[i]][i];
            break;
        }
    }
    return sum;
}
