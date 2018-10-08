int dp[maxn];
//0-1背包，代价为cost,获得的价值为weight
void ZeroOnePack(int cost, int weight, int nValue) {
    for (int i = nValue; i >= cost; i--)
        dp[i] = max(dp[i], dp[i - cost] + weight);
}
//完全背包，代价为cost,获得的价值为weight
void CompletePack(int cost, int weight, int nValue) {
    for (int i = cost; i <= nValue; i++)
        dp[i] = max(dp[i], dp[i - cost] + weight);
}
//多重背包
void MultiplePack(int cost, int weight, int amount, int nValue) {
    if (cost * amount >= nValue)
        CompletePack(cost, weight, nValue);
    else {
        int k = 1;
        while (k < amount) {
            ZeroOnePack(k * cost, k * weight, nValue);
            amount -= k;
            k <<= 1;
        }
        ZeroOnePack(amount * cost, amount * weight, nValue);
    }
}