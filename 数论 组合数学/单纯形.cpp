/* 功能：
 * 接受有n个约束，m个基本变量的方程组a[0~n][0~m]
 * a[0][]存放需要最大化的目标函数，a[][0]存放常数
 * Base[]存放基本变量的id,初始为1~m
 * Rest[]存放松弛变量的id,初始为m+1~m+n
 * 返回此线性规划的最小值ans
 * 要求方案的话，Base[]中的变量值为0,Rest[]中的变量值为相应行的[0]
 * 如果solve
    + 返回1,说明运行正常ans是它的最大值
    + 返回0,说明无可行解
    + 返回-1,说明解没有最大值
 * 测试： 
 *      m=2,n=3
 *      double a[4][3]={
 *          {0,1,3},
 *          {8,-1,1},
 *          {-3,1,1},
 *          {2,1,-4}
 *      };
 *      solve=1,ans=64/3;
 *  注意ac不了可能是eps的问题
 */
const int Maxn = 110, Maxm = 59;
class Simplex {
public:
    static const double Inf;
    static const double eps;
    int n, m;
    double a[Maxn][Maxm];
    int Base[Maxm], Rest[Maxn];
    double val[Maxm];
    double ans;
    void pt() {
        for(int i = 0; i <= n; i++) {
            for(int j = 0; j <= m; j++)printf("%.2f ", a[i][j]);
            puts("");
        }
    }
    void pivot(int x, int y) { //将第x个非基本变量和第y个基本变量调换
        swap(Rest[x], Base[y]);
        double tmp = -1. / a[x][y];
        a[x][y] = -1.;
        for(int j = 0; j <= m; j++)a[x][j] *= tmp;
        for(int i = 0; i <= n; i++) {
            if(i == x || fabs(a[i][y]) < eps)continue;
            tmp = a[i][y];
            a[i][y] = 0;
            for(int j = 0; j <= m; j++)a[i][j] += tmp * a[x][j];
        }
    }
    bool opt() {
        while(1) {
            int csi = 0;
            for(int i = 1; i <= m; i++)if(a[0][i] > eps && (!csi || Base[i] < Base[csi]))csi = i;
            if(!csi)break;
            int csj = 0;
            double cur;
            for(int j = 1; j <= n; j++) {
                if(a[j][csi] > -eps)continue;
                double tmp = -a[j][0] / a[j][csi];
                if(!csj || tmp + eps < cur || (fabs(tmp - cur) < eps && Rest[j] < Rest[csj]))csj = j, cur = tmp;
            }
            if(!csj)return 0;
            pivot(csj, csi);
        }
        ans = a[0][0];
        return 1;
    }
    bool init() {
        ans = 0;
        for(int i = 1; i <= m; i++)Base[i] = i;
        for(int i = 1; i <= n; i++)Rest[i] = m + i;
        int cs = 1;
        for(int i = 2; i <= n; i++)if(a[i][0] < a[cs][0])cs = i;
        if(a[cs][0] >= -eps)return 1;
        static double tmp[Maxm];
        for(int i = 0; i <= m; i++)tmp[i] = a[0][i], a[0][i] = 0;
        for(int i = 1; i <= n; i++)a[i][m + 1] = 1.;
        a[0][m + 1] = -1.;
        Base[m + 1] = m + n + 1;
        pivot(cs, ++m);
        opt();
        m--;
        if(a[0][0] < -eps)return 0;
        cs = -1;
        for(int i = 1; i <= n; i++) {
            if(Rest[i] > m + n) {
                cs = i;
                break;
            }
        }
        if(cs >= 1) {
            int nxt = -1;
            m++;
            for(int i = 1; i <= m; i++)if(a[cs][i] > eps || a[cs][i] < -eps) {
                    nxt = i;
                    break;
                }
            pivot(cs, nxt);
            m--;
        }
        for(int i = 1; i <= m; i++) {
            if(Base[i] > m + n) {
                swap(Base[i], Base[m + 1]);
                for(int j = 0; j <= n; j++)a[j][i] = a[j][m + 1];
                break;
            }
        }
        for(int i = 1; i <= m; i++)a[0][i] = 0;
        a[0][0] = tmp[0];
        for(int i = 1; i <= m; i++)if(Base[i] <= m)a[0][i] = tmp[Base[i]];
        for(int i = 1; i <= n; i++) {
            if(Rest[i] <= m) {
                for(int j = 0; j <= m; j++)a[0][j] += tmp[Rest[i]] * a[i][j];
            }
        }
        return 1;
    }
    void getval() {
        for(int i = 1; i <= m; i++)val[i] = 0;
        for(int i = 1; i <= n; i++)if(Rest[i] <= m)val[Rest[i]] = a[i][0];
        //for(int i=1;i<=m;i++)printf("%.2f ",val[i]);puts("");
    }
    int solve() {
        if(!init())return 0;
        if(!opt())return -1;
        getval();
        return 1;
    }
} solver;
const double Simplex:: Inf = 1e80;
const double Simplex:: eps = 1e-8;
int main() {
    int m, n, type;
    scanf("%d%d%d", &m, &n, &type);
    solver.a[0][0] = 0;
    for(int i = 1; i <= m; i++) scanf("%lf", &solver.a[0][i]);
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m + 1; j++) {
            if(j == m + 1) scanf("%lf", &solver.a[i][0]);
            else {
                scanf("%lf", &solver.a[i][j]);
                solver.a[i][j] = -solver.a[i][j];
            }
        }
    }
    solver.m = m, solver.n = n;
    int rep = solver.solve();
    if(rep == 0) puts("Infeasible");
    else if(rep == -1) puts("Unbounded");
    else {
        printf("%.12f\n", solver.ans);
        if(type == 1) {
            for(int i = 1; i <= m; i++)printf("%.12f%c", solver.val[i], i == m ? '\n' : ' ');
        }
    }
    return 0;
}
