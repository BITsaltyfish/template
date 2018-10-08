#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100010;
const double eps = 1e-16;
int T, n, cnt, front, rear;
double area;
int dcmp(double x) {
    if(fabs(x) < eps) return 0;
    return x > eps ? 1 : -1;
}
struct Point {
    double x, y;
    Point() {}
    Point(double x, double y): x(x), y(y) {}
} p[MAXN];
typedef Point Vector;
Vector operator+(const Vector &p, const Vector &q) {
    return Vector(p.x + q.x, p.y + q.y);
}
Vector operator-(const Vector &p, const Vector &q) {
    return Vector(p.x - q.x, p.y - q.y);
}
Vector operator*(const Vector &p, double k) {
    return Vector(p.x * k, p.y * k);
}
double Cross(const Vector &p, const Vector &q) {
    return p.x * q.y - p.y * q.x;
}
struct Line {
    Point p;
    Vector v;
    double ang;
    Line() {}
    Line(const Point &p, const Vector &v): p(p), v(v) {
        ang = atan2(v.y, v.x);
    }
    friend bool operator<(const Line &p, const Line &q) {
        return p.ang < q.ang;
    }
} L[MAXN], q[MAXN];
Point LineIntersection(const Line &a, const Line &b) {
    Vector p = a.p - b.p;
    double t = Cross(b.v, p) / Cross(a.v, b.v);
    return Point(a.p + a.v * t);
}
bool Left(const Point &a, const Line &b) {
    return dcmp(Cross(a - b.p, b.v)) < 0;
}
bool Halfplane() {
    sort(L + 1, L + n + 1);
    q[front = rear = 1] = L[1];
    for(int i = 2; i <= n; i++) {
        while(front < rear && !Left(p[rear - 1], L[i])) rear--;
        while(front < rear && !Left(p[front], L[i])) front++;
        q[++rear] = L[i];
        if(!dcmp(q[rear].ang - q[rear - 1].ang) && Left(L[i].p, q[--rear])) q[rear] = L[i];
        if(front < rear) p[rear - 1] = LineIntersection(q[rear - 1], q[rear]);
    }
    while(front < rear && !Left(p[rear - 1], q[front])) rear--;
    if(rear - front <= 1) return false;
    p[rear] = LineIntersection(q[rear], q[front]);
    return true;
}
int len[10];
inline void work() {
    int T = 2;
    scanf("%d%d", len + 1, len + 2);
    n = cnt = front = rear = 0;
    area = 0;
    for(int cas = 1; cas <= T; cas++) {
        n = len[cas];
        for(int i = 1; i <= n; i++)scanf("%lf%lf", &p[i].x, &p[i].y);
        for(int i = 1; i < n; i++) L[++cnt] = Line(p[i], p[i + 1] - p[i]);
        L[++cnt] = Line(p[n], p[1] - p[n]);
    }
    n = cnt;
    if(!Halfplane()) {
        puts("0.0000");
        return;
    } else {
        for(int i = front; i < rear; i++) area += Cross(p[i], p[i + 1]);
        area += Cross(p[rear], p[front]);
    }
    printf("%.4f\n", fabs(area / 2));
}
int main() {
    int T;
    scanf("%d", &T);
    while (T--) work();
    return 0;
}