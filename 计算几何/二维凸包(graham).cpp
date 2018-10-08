/*
 * zhan��˳ʱ�뱣����͹���ϵĵ���,��top��
 * ���е���±�1��ʼ��ջ��Ҳ���±�1��ʼ
 * ע���ظ��㣡��Ӱ��͹��
*/
#include <bits/stdc++.h>
#define maxn 50010
#define eps 1e-8
using namespace std;
typedef int data_type;
struct point {
    data_type x, y;
    int id;
    point() {}
    inline point(data_type _x, data_type _y, int _id) {
        x = _x;
        y = _y;
        id = _id;
    }
    inline point(data_type _x, data_type _y) {
        x = _x;
        y = _y;
    }
    inline point operator+(const point &b)const {
        return point(x + b.x, y + b.y);
    }
    inline point operator-(const point &b)const {
        return point(x - b.x, y - b.y);
    }
    inline data_type operator^(const point &b)const {
        return x * b.y - y * b.x;   //���
    }
    inline data_type operator*(const point &b)const {
        return x * b.x - y * b.y;   //���
    }
    inline bool operator<(const point &b)const {
        return x < b.x || x == b.x && y < b.y;
    }
} p[maxn];
inline data_type sqr_dist(const point a, point b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
inline double dist(const point a, point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
inline bool jijiao_cmp(const point &a, const point &b) { //˳ʱ��
    data_type tmp = (a - p[1]) ^ (b - p[1]);
    if (tmp < -eps)return 0;
    if (tmp > eps)return 1;
    return sqr_dist(p[1], a) < sqr_dist(p[1], b);
}
int zhan[maxn], top;
inline void graham(int n) {
    top = 0;
    for (int i = 2; i <= n; i++)if (p[i] < p[1])swap(p[i], p[1]);
    sort(p + 2, p + n + 1, jijiao_cmp);
    for(int i = 1; i <= n; i++) { //Ĭ��͹���߽�ֱ���ϵĵ���͹���ϣ������Ҫ�㣬'<'��'<='����
        while (top > 1 && ((p[zhan[top]] - p[zhan[top - 1]]) ^ (p[i] - p[zhan[top - 1]])) < 0)top--; 
        zhan[++top] = i;
    }
    int now = n - 1;
    //Ĭ��͹���߽�ֱ���ϵĵ���͹���ϣ�Ҫ����һ��
    while (now >= 1 && ((p[now] - p[1]) ^ (p[zhan[top]] - p[1])) == 0)zhan[++top] = now--; 
}
int n;
inline void work() {
    for (int i = 1; i <= n; i++)scanf("%d%d", &p[i].x, &p[i].y);
    graham(n);
    puts(top == n ? "convex" : "concave");
}
int main() {
    while (~scanf("%d", &n) && n) work();
    return 0;
}