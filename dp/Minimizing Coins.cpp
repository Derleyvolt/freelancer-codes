#include<bits/stdc++.h> 
 
using namespace std;
 
vector<int> coin;
 
int r;
 
int dp[1000010];
 
int solve(int n) {
	if (n == 0)
		return 1;
	if (n < 0)
		return 0;
 
	int q = 10000000;
 
	for (size_t i = 0; i < coin.size(); i++) {
        if (! (n >= coin[i]))
            continue;
		if (dp[n-coin[i]] != -1)
			r = dp[n - coin[i]];
		else {
			r = solve(n - coin[i]);
			dp[n - coin[i]] = r;
		}
		if (q > r && r)
			q = r;
	}
 
	return q == 10000000 ? 0 : q + 1;
}
 
int main() {
	int n, x;
	cin >> n >> x;
	coin.resize(n);
	for (auto& i : coin) cin >> i;
	memset(dp, -1, sizeof dp);
	cout << solve(x) - 1 << endl;
}
