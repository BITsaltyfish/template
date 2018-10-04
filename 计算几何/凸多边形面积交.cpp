#include <bits/stdc++.h>
#define EPS 1e-8
using namespace std;
const int MAXN = 105;
inline int sgn(double x)
{
    if (x < -EPS) return -1;
    else if (x > EPS) return 1;
    else return 0;
}
struct Point
{
    double x, y;
    Point() {}
    Point(double x, double y) : x(x), y(y) {}
};
typedef Point Vector;
Vector operator + (Vector a, Vector b)
{
    return Vector(a.x + b.x, a.y + b.y);
}
Vector operator - (Vector a, Vector b)
{
    return Vector(a.x - b.x, a.y - b.y);
}
Vector operator * (Vector v, double mul)
{
    return Vector(v.x * mul, v.y * mul);
}
double cross(Vector a, Vector b)
{
    return a.x * b.y - a.y * b.x;
}
struct Segment
{
    Point s, e;
    Segment() {}
    Segment(Point s, Point e) : s(s), e(e) {}
    double y(double x)
    {
        return s.y + (e.y - s.y) * (x - s.x) / (e.x - s.x);
    }
};
bool Segment_intersect(Segment a, Segment b)
{
    if (sgn(min(a.s.x, a.e.x) - max(b.s.x, b.e.x)) > 0 ||
        sgn(max(a.s.x, a.e.x) - min(b.s.x, b.e.x)) < 0 ||
        sgn(min(a.s.y, a.e.y) - max(b.s.y, b.e.y)) > 0 ||
        sgn(max(a.s.y, a.e.y) - min(b.s.y, b.e.y)) < 0) return false;
    double t1 = cross(a.e - a.s, b.s - a.s),
        t2 = cross(a.e - a.s, b.e - a.s),
        t3 = cross(b.e - b.s, a.s - b.s),
        t4 = cross(b.e - b.s, a.e - b.s);
    return sgn(t1) * sgn(t2) < 0 && sgn(t3) * sgn(t4) < 0;
}
struct Line
{
    Point p;
    Vector v;
    Line() {}
    Line(Point p, Vector v) : p(p), v(v) {}
};
Point Line_intersect(Line a, Line b)
{
    double t = cross(b.v, a.p - b.p) / cross(a.v, b.v);
    return a.p + a.v * t;
}
typedef vector<Point> Polygon;
double Polygon_area(Polygon& poly)
{
    double ret = 0;
    for (int i = 1; i < (int)poly.size() - 1; i ++)
        ret += cross(poly[i] - poly[0], poly[i + 1] - poly[0]);
    return fabs(ret);
}
void Polygon_intersect(Polygon& a, Polygon& b, vector<Point>& res)
{
    int n = a.size(), m = b.size();
    for (int i = 0; i < n; i ++)
        for (int j = 0; j < m; j ++)
        {
            if (!Segment_intersect(Segment(a[i], a[(i + 1) % n]),
                Segment(b[j], b[(j + 1) % m]))) continue;
            Point p = Line_intersect(Line(a[i], a[(i + 1) % n] - a[i]),
                Line(b[j], b[(j + 1) % m] - b[j]));
            res.push_back(p);
        }
}
typedef pair<double, double> Interval;
int merge_Interval(vector<Interval>& itv)
{
    sort(itv.begin(), itv.end());
    int ret = 1;
    for (int i = 1; i < (int)itv.size(); i ++)
    {
        if (sgn(itv[ret - 1].second - itv[i].first) >= 0)
            itv[ret - 1].second = max(itv[ret - 1].second, itv[i].second);
        else itv[ret++] = itv[i];
    }
    itv.resize(ret);
    return ret;
}
double Polygons_area_union(Polygon* poly, int n)
{
    vector<double> scan;
    for (int i = 0; i < n; i ++)
        for (auto j : poly[i])
            scan.push_back(j.x);
    for (int i = 0; i < n; i ++)
    {
        vector<Point> p;
        for (int j = i + 1; j < n; j ++)
            Polygon_intersect(poly[i], poly[j], p);
        for (auto& j : p)
            scan.push_back(j.x);
    }
    sort(scan.begin(), scan.end());
    scan.resize(unique(scan.begin(), scan.end()) - scan.begin());
    double ret = 0;
    for (int i = 1; i < (int)scan.size(); i ++)
    {
        double x = (scan[i - 1] + scan[i]) / 2;
        vector<Interval> itv;
        for (int j = 0; j < n; j ++)
        {
            vector<double> y;
            int m = poly[j].size();
            for (int k = 0; k < m; k ++)
            {
                Point s = poly[j][k], e = poly[j][(k + 1) % m];
                if (sgn(min(s.x, e.x) - scan[i - 1]) > 0 ||
                    sgn(max(s.x, e.x) - scan[i]) < 0) continue;
                y.push_back(Segment(s, e).y(x));
            }
            if (y.size() < 2) continue;
            sort(y.begin(), y.end());
            for (int k = 0; k < (int)y.size(); k += 2)
                itv.emplace_back(y[k], y[k + 1]);
        }
        if (itv.empty()) continue;
        merge_Interval(itv);
        double sum = 0;
        for (auto& j : itv)
            sum += j.second - j.first;
        ret += sum * (scan[i] - scan[i - 1]);
    }
    return ret;
}
int n;
Polygon poly[MAXN];
int main()
{
    scanf("%d", &n);
    double tot = 0;
    for (int i = 0; i < n; i ++)
    {
        int m;
        scanf("%d", &m);
        while (m--)
        {
            Point p;
            scanf("%lf%lf", &p.x, &p.y);
            poly[i].push_back(p);
        }
        tot += Polygon_area(poly[i]);
    }
    tot /= 2;
    double cov = Polygons_area_union(poly, n);
    printf("%.08lf %.08lf\n", tot, cov);
    return 0;
}