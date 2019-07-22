typedef double datatype;
struct point {
    datatype x, y;
    int id;
    point() {}
    point(datatype _x, datatype _y) {
        x = _x;
        y = _y;
    }
    point(datatype _x, datatype _y, int _id) {
        x = _x;
        y = _y;
        id = _id;
    }
    point operator +(const point &b)const {
        return point(x + b.x, y + b.y);
    }
    point operator -(const point &b)const {
        return point(x - b.x, y - b.y);
    }
    point operator *(const datatype &b)const {
        return point(b * x, b * y);
    }
    datatype operator *(const point &b)const {
        return x * b.x + y * b.y;
    }
    datatype operator ^(const point &b)const {
        return x * b.y - y * b.x;
    }
};
inline double dist(const point &a, const point &b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
inline point get_neixin(const point &A, const point &B, const point &C) {//内切圆圆心
    datatype a = dist(B, C), b = dist(A, C), c = dist(A, B);
    return (A * a + B * b + C * c) * (1.0 / (a + b + c));
}
inline point get_waixin(const point &A, const point &B, const point &C) {//外接圆圆心
    datatype a1 = B.x - A.x, b1 = B.y - A.y, c1 = (a1 * a1 + b1 * b1) / 2;
    datatype a2 = C.x - A.x, b2 = C.y - A.y, c2 = (a2 * a2 + b2 * b2) / 2;
    datatype d = a1 * b2 - a2 * b1;
    return point(A.x + (c1 * b2 - c2 * b1) / d, A.y + (a1 * c2 - a2 * c1) / d);
}