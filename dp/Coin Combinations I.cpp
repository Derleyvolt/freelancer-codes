#include <bits/stdc++.h>
 
using namespace std;
 
#define fi                  first 
#define sec                 second
#define ll                  long long 
#define vi                  vector<int> 
#define pb                  push_back 
#define mp                  make_pair 
#define debug(x)            cout << x << "\n"; 
#define all(cont)           cont.begin(), cont.end() 
#define rfor(i, r)          for(auto& i:r) 
 
ll const mod = 1e9 + 7;
 
ll dp[1000010];
 
vi coin;
 
ll q;
 
ll solve(int k) {
    if (k == 0)
        return 1;
    if (k < 0)
        return 0;
    ll r = 0;
    for (int i = 0; i < coin.size(); i++) {
        if (k - coin[i] < 0)
            continue;
        if (dp[k - coin[i]] != -1)
            r = (r + dp[k - coin[i]]) % mod;
        else {
            dp[k - coin[i]] = solve(k - coin[i]);
            r = (r + dp[k - coin[i]]) % mod;
        }
    }
    return r;
}
 
int main() {
    int x, n;
    cin >> n >> x;
    coin.resize(n);
    rfor(a, coin) cin >> a;
    memset(dp, -1, sizeof dp);
    cout << solve(x);
    return 0;
}
