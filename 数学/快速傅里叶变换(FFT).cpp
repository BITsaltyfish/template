#define data_type int
//==============记得改类型！记得改类型！记得改类型！记得改类型！记得改类型！
//==============记得改类型！记得改类型！记得改类型！记得改类型！记得改类型！
//==============记得改类型！记得改类型！记得改类型！记得改类型！记得改类型！
//==============记得改类型！记得改类型！记得改类型！记得改类型！记得改类型！
//==============记得改类型！记得改类型！记得改类型！记得改类型！记得改类型！
#define maxfft 131072+5
const double pi=acos(-1.0);
struct cp
{
    double a,b;
    cp operator +(const cp &o)const {return (cp){a+o.a,b+o.b};}
    cp operator -(const cp &o)const {return (cp){a-o.a,b-o.b};}
    cp operator *(const cp &o)const {return (cp){a*o.a-b*o.b,b*o.a+a*o.b};}
    cp operator *(const double &o)const {return (cp){a*o,b*o};}
    cp operator !()const{return (cp){a,-b};}
}w[maxfft];
int pos[maxfft];
void fft_init(int len)
{
    int j=0;while((1<<j)<len)j++;j--;
    for(int i=0;i<len;i++)pos[i]=pos[i>>1]>>1|((i&1)<<j);
}
void fft(cp *x,int len,int sta)
{
    for(int i=0;i<len;i++)if(i<pos[i])swap(x[i],x[pos[i]]);
    w[0]=(cp){1,0};
    for(unsigned i=2;i<=len;i<<=1)
    {
        cp g=(cp){cos(2*pi/i),sin(2*pi/i)*sta};
        for(int j=i>>1;j>=0;j-=2)w[j]=w[j>>1];
        for(int j=1;j<i>>1;j+=2)w[j]=w[j-1]*g;
        for(int j=0;j<len;j+=i)
        {
            cp *a=x+j,*b=a+(i>>1);
            for(int l=0;l<i>>1;l++)
            {
                cp o=b[l]*w[l];
                b[l]=a[l]-o;
                a[l]=a[l]+o;
            }
        }
    }
    if(sta==-1)for(int i=0;i<len;i++)x[i].a/=len,x[i].b/=len;
}

/*


//普通FFT
cp x[maxfft],y[maxfft],z[maxfft];
void FFT(data_type *a,data_type *b,int n,int m,data_type *c)//直接调用，n,m是a,b的长度，下标0开始,c是卷出来的东西
{
    int i,j,len=1;while(len<(n+m+1)>>1)len<<=1;
    fft_init(len);
    for(i=n/2;i<len;i++)x[i].a=x[i].b=0;
    for(i=m/2;i<len;i++)y[i].a=y[i].b=0;
    for(i=0;i<n;i++)(i&1?x[i>>1].b:x[i>>1].a)=a[i];
    for(i=0;i<m;i++)(i&1?y[i>>1].b:y[i>>1].a)=b[i];
    fft(x,len,1),fft(y,len,1);
    for(i=0;i<len/2;i++)
    {
        j=len-1&len-i;
        z[i]=x[i]*y[i]-(x[i]-!x[j])*(y[i]-!y[j])*(w[i]+(cp){1,0})*0.25;
    }
    for(i=len/2;i<len;i++)
    {
        j=len-1&len-i;
        z[i]=x[i]*y[i]-(x[i]-!x[j])*(y[i]-!y[j])*((cp){1,0}-w[i^len>>1])*0.25;
    }
    fft(z,len,-1);
    for(i=0;i<n+m;i++)
        if(i&1)c[i]=(data_type)(z[i>>1].b+0.5);
        else c[i]=(data_type)(z[i>>1].a+0.5);
}


*/



/*


//模数较大时,注意data_type=int || long long
cp x[maxfft],y[maxfft],z[maxfft];
int temp[maxfft];
void FFT(data_type *a,data_type *b,int n,int m,data_type *c)//直接调用，n,m是a,b的长度，下标0开始,c是卷出来的东西
{
    if(n<=100&&m<=100||min(n,m)<=5)
    {
        for(int i=0;i<n+m-1;i++)temp[i]=0;
        for(int i=0;i<n;i++)for(int j=0;j<m;j++)
        {
            temp[i+j]+=(ll)a[i]*b[j]%mod;
            if(temp[i+j]>=mod)temp[i+j]-=mod;
        }
        for(int i=0;i<n+m-1;i++)c[i]=temp[i];
        return;
    }
    int len=1;while(len<n+m+1)len<<=1;
    fft_init(len);
    for(int i=0;i<len;i++)
    {
        int aa=i<n?a[i]:0,bb=i<m?b[i]:0;
        x[i]=(cp){(aa>>15),(aa&32767)},y[i]=(cp){(bb>>15),(bb&32767)};
    }
    fft(x,len,1),fft(y,len,1);
    for(int i=0;i<len;i++)
    {
        int j=len-1&len-i;
        z[i]=((x[i]+!x[j])*(y[i]-!y[j])+(x[i]-!x[j])*(y[i]+!y[j]))*(cp){0,-0.25};
    }
    fft(z,len,-1);
    for(int i=0;i<n+m-1;i++)
    {
        ll ta=(ll)(z[i].a+0.5)%mod;
        ta=(ta<<15)%mod;c[i]=ta;
    }
    for(int i=0;i<len;i++)
    {
        int j=len-1&len-i;
        z[i]=(x[i]-!x[j])*(y[i]-!y[j])*(cp){-0.25,0}+(x[i]+!x[j])*(y[i]+!y[j])*(cp){0,0.25};
    }
    fft(z,len,-1);
    for(int i=0;i<n+m-1;i++)
    {
        ll ta=(ll)(z[i].a+0.5)%mod,tb=(ll)(z[i].b+0.5)%mod;
        ta=(ta+(tb<<30))%mod;
        c[i]=(c[i]+ta)%mod;
    }
}


*/