#include <bits/stdc++.h>
using namespace std;
namespace fastIO {
#define BUF_SIZE 10000
#define OUT_SIZE 10000
//fread -> read
bool IOerror = 0;
inline char nc() {static char buf[BUF_SIZE], *p1 = buf + BUF_SIZE, *pend = buf + BUF_SIZE;if(p1 == pend) {p1 = buf;pend = buf + fread(buf, 1, BUF_SIZE, stdin);if(pend == p1) {IOerror = 1;return -1;}} return *p1++;}
inline bool blank(char ch) {return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';}
inline void read(int &x) {char ch;int f = 1;while(blank(ch = nc()));while (ch == '-')f = -f, ch = nc();if(IOerror)return;for(x = ch - '0'; (ch = nc()) >= '0' && ch <= '9'; x = x * 10 + ch - '0');x *= f;}
inline void read(char *s) {char ch;while(blank(ch = nc()));if(IOerror)return;int i = 0;for (; !blank(ch); s[i++] = ch, ch = nc());s[i] = '\0';}
//fwrite
struct Ostream_fwrite{
        char *buf,*p1,*pend;
        Ostream_fwrite(){buf=new char[BUF_SIZE];p1=buf;pend=buf+BUF_SIZE;}
        void out(char ch){if (p1==pend){fwrite(buf,1,BUF_SIZE,stdout);p1=buf;}*p1++=ch;}
        void flush(){if (p1!=buf){fwrite(buf,1,p1-buf,stdout);p1=buf;}}
    ~Ostream_fwrite(){flush();}
}Ostream;
inline void print(char x){Ostream.out(x);}
inline void println(){Ostream.out('\n');}
inline void flush(){Ostream.flush();}
char Out[OUT_SIZE],*o=Out;
inline void print1(char c){*o++=c;}
inline void println1(){*o++='\n';}
inline void flush1(){if (o!=Out){if (*(o-1)=='\n')*--o=0;puts(Out);}}
struct puts_write{~puts_write(){flush1();}}_puts;
};
using namespace fastIO;