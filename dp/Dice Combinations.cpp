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
 
const ll m = 1000000000 + 7;
 
ll dp[1000010];
 
int n;
 
ll solve(int k) {
    if (k == 0)
        return 1;
    if (k < 0)
        return 0;
    ll r = 0;
    for (int i = 1; i <= min(6, k); i++) {
        if (dp[k - i] != -1)
            r = (r + dp[k - i]) % m;
        else {
            dp[k - i] = solve(k - i);
            r = (r + dp[k - i]) % m;
        }
    }
    return r;
}
 
int main() {
    cin >> n;
    memset(dp, -1, sizeof dp);
    cout << solve(n);
    return 0;
}
