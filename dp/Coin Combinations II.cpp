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
vi coin;
 
ll solve(int n) {
    ll arr[n+1];
    memset(arr, 0, sizeof arr);
    arr[0] = 1;
    rfor(a, coin) {
        for(int i=a; i<=n; i++)
            arr[i] = (arr[i] + arr[i - a]) % mod;
    }
    return arr[n];
}
 
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL); 
    int n, x;
    cin >> n >> x;
    coin.resize(n);
    rfor(a, coin) cin >> a;
    cout << solve(x);
    return 0;
}
