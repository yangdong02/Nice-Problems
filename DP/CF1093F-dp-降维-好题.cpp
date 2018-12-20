/*
  Link: https://codeforces.com/contest/1093/problem/F
  Source: Educational Codeforces Round 56 (Rated for Div. 2)
  Date: 2018-12-20
  Status: Accepted
  Difficulty: 2500
  Tag: DP
  Solution:
    Let's try dynamic programming approach to this problem. 
      Let dp[cnt,lst] be the number of ways to replace all −1 
      with numbers from 1 to k in such a way that array a1…cnt 
      is good and the last number of that array is lst.

    Let sdp[cnt] = sum dp[cnt,i]. for i = 1 to k

    Then initially it's dp[cnt,lst] = sdp[cnt−1] 
      if acnt equals to −1 or lst. However, we could 
      include incorrect states — such that segment 
      [acnt−len+1…acnt] consist of the same value. 
      It happens when:
        cnt≥len, 
      as we should have at least len elements; segment [acnt−len+1…acnt] 
      has all its elements either equal to −1 or lst. If both of these 
      conditions hold then you should subtract all the bad states from 
      dp[cnt,lst]. The number of them is sdp[cnt−len] − dp[cnt−len,lst].
*/

#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;

const int maxn = 100200, maxk = 109, mod = 998244353 ;
int dp[maxn][maxk], sdp[maxn], n, k, len, a[maxn], cnt[maxk];
inline int mo(int x) {
    while(x >= mod) x -= mod;
    while(x <  0) x += mod;
    return x;
}
inline int tr(int i) { return a[i]==-1 ? 0 : a[i]; }
int main() {
    scanf("%d%d%d", &n, &k, &len);
    rep(i, n) scanf("%d", &a[i]);
    if(len == 1) { puts("0"); return 0; }

    sdp[0] = 1;
    for(int i = 0; i < len; ++i) 
        cnt[ tr(i) ]++;

    for(int i = 1; i <= n; ++i) {
        if(a[i] != -1) dp[i][a[i]] = sdp[i - 1];
        else rep(j, k) dp[i][j] = sdp[i - 1];

        if(i >= len) {
            int ok = -1;
            cnt[ tr(i - len) ]--;
            cnt[ tr(i) ]++;

            for(int j = 1; j <= k; ++j)
                if(cnt[j]) {
                    if(ok == -1 || ok == j) ok = j;
                    else ok = -2;
                }

            if(ok == -1) { 
                rep(lst, k) if(dp[i][lst])    
                    dp[i][lst] = mo(dp[i][lst] - sdp[i - len] + dp[i - len][lst]);
            } else if(ok != -2 && dp[i][ok])
                dp[i][ok] = mo(dp[i][ok] - sdp[i - len] + dp[i - len][ok]);
        }
        
        rep(j, k) sdp[i] = mo(sdp[i] + dp[i][j]);
    }

    int ans = 0;
    rep(i, k) ans = mo(ans + dp[n][i]);
    printf("%d\n", ans);
    return 0;
}
