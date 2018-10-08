/* 例题：POJ - 3461(Oulipo), hdu1711(Number Sequence)
 * 这个模板 字符串是从0开始的
 * Next数组是从1开始的
 */
#include <iostream>
#include <cstring>
using namespace std;
const int N = 1000002;
int next_[N];
void getNext(char *pattern, int plen) {
    int j, k;
    j = 0;
    k = -1;
    next_[0] = -1;
    while(j < plen)
        if(k == -1 || pattern[j] == pattern[k]) {
            next_[++j] = ++k; //表示T[j-1]和T[k-1]相匹配，当j处失配时，直接用next_[j]处来匹配当前失配处
        } else k = next_[k];
}
/*返回模式串T在主串S中首次出现的位置，返回的位置是从0开始的。*/
int KMP_Index(char *str, char *pattern, int slen, int plen) {
    int i = 0, j = 0;
    getNext(pattern, plen);
    while(i < slen && j < plen) {
        if(j == -1 || str[i] == pattern[j]) {
            i++;
            j++;
        } else j = next_[j];
    }
    if(j == plen) return i - plen;
    else return -1;
}
/* 返回模式串在主串S中出现的次数 */
int KMP_Count(char *str, char *pattern, int slen, int plen) {
    int ans = 0;
    int i, j = 0;
    if(slen == 1 && plen == 1) {
        if(str[0] == pattern[0])  return 1;
        else  return 0;
    }
    getNext(pattern, plen);
    for(i = 0; i < slen; i++) {
        while(j > 0 && str[i] != pattern[j])j = next_[j];
        if(str[i] == pattern[j])
            j++;
        if(j == plen) {
            ans++;
            j = next_[j];
        }
    }
    return ans;
}