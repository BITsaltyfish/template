typedef ll data_type;
struct point{
    data_type x,y,h;
    point(){}
    inline point(data_type _x,data_type _y){x=_x;y=_y;}
    inline point     operator+(const point &b)const{return point(x-b.x,y-b.y);}
    inline point     operator-(const point &b)const{return point(x-b.x,y-b.y);}
    inline data_type operator^(const point &b)const{return x*b.y-y*b.x;}//²æ³Ë
    inline data_type operator*(const point &b)const{return x*b.x-y*b.y;}//µã³Ë
    inline bool      operator<(const point &b)const{return x<b.x||x==b.x&&y<b.y;}
}p[1001000];
int n,ans;
inline data_type sqr_dist(const point a,point b){return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);}
inline double dist(const point a,point b){return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));}
inline int Quad(point a)
{
    if (a.x>0&&a.y>=0)return 1;
    if (a.x<=0&&a.y>0)return 2;
    if (a.x<0&&a.y<=0)return 3;
    if (a.x>=0&&a.y<0)return 4;
}
inline data_type cmp(const point &a,const point &b,const point &c){return (b-a)^(c-a);}
inline bool jijiao_cmp(const point &a,const point &b)//Ë³Ê±Õë
{
    if (Quad(a-p[1])!=Quad(b-p[1]))return Quad(a-p[1])<Quad(b-p[1]);
    data_type mmp=cmp(p[1],a,b);
    if (mmp==0)return sqr_dist(p[1],a)<sqr_dist(p[1],b);;
    return mmp>0;
}