struct BigInt {
    const static int mod = 10000;
    const static int LEN = 4;
    int a[maxn], len;
    BigInt() {
        memset(a, 0, sizeof(a));
        len = 1;
    }
    void init(int x) {
        memset(a, 0, sizeof(a));
        len = 0;
        do {
            a[len++] = x % mod;
            x /= mod;
        } while(x);
    }
    int Compare(const BigInt &b) {
        if(len < b.len)return -1;
        if(len > b.len)return 1;
        for(int i = len - 1; i >= 0; i--)
            if(a[i] < b.a[i])return -1;
            else if(a[i] > b.a[i])return 1;
        return 0;
    }
    BigInt operator +(const BigInt &b)const {
        BigInt ans;
        ans.len = max(len, b.len);
        for(int i = 0; i <= ans.len; i++)ans.a[i] = 0;
        for(int i = 0; i < ans.len; i++) {
            ans.a[i] += ((i < len) ? a[i] : 0) + ((i < b.len) ? b.a[i] : 0);
            ans.a[i + 1] += ans.a[i] / mod;
            ans.a[i] %= mod;
        }
        if(ans.a[ans.len] > 0)ans.len++;
        return ans;
    }
    BigInt operator -(const BigInt &b)const {
        BigInt ans;
        ans.len = len;
        int k = 0;
        for(int i = 0; i < ans.len; i++) {
            ans.a[i] = a[i] + k - b.a[i];
            if(ans.a[i] < 0)ans.a[i] += mod, k = -1;
            else k = 0;
        }
        while(ans.a[ans.len - 1] == 0 && ans.len > 1)ans.len--;
        return ans;
    }
    BigInt operator *(const BigInt &b)const {
        BigInt ans;
        for(int i = 0; i < len; i++) {
            int k = 0;
            for(int j = 0; j < b.len; j++) {
                int temp = a[i] * b.a[j] + ans.a[i + j] + k;
                ans.a[i + j] = temp % mod;
                k = temp / mod;
            }
            if(k != 0)ans.a[i + b.len] = k;
        }
        ans.len = len + b.len;
        while(ans.a[ans.len - 1] == 0 && ans.len > 1)ans.len--;
        return ans;
    }
    void output() {
        printf("%d", a[len - 1]);
        for(int i = len - 2; i >= 0; i--)
            printf("%04d", a[i]);
        printf("\n");
    }
} ans[121];