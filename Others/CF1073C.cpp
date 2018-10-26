/*
Link: http://codeforces.com/contest/1073/problem/C
Comment: This problem has confused me for 1 hr. I thought it was a dp problem, but it isn't
Solution: Just binary search the answer, and use two-pointers
*/

#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;
#define int ll
const int maxn = 200200;
char s[maxn];
int n, x, y, prex[maxn], prey[maxn], sufx[maxn], sufy[maxn];
inline bool judge(int an) {
    for(int i = 0, j = i + an + 1; j - 1 <= n; ++i, ++j) {
        int mo = 0;
        mo += abs(prex[i] + sufx[j] - x);
        mo += abs(prey[i] + sufy[j] - y);
        if(mo <= an) return true;
    }
    return false;
}
signed main(){
    scanf("%lld%s%lld%lld", &n, s + 1, &x, &y);
    bool ub = (y < 0), rb = (x < 0);
    if(rb) x = -x;
    if(ub) y = -y;
    rep(i, n) {
        if(ub) {
            if(s[i] == 'U') s[i] = 'D';
            else if(s[i] == 'D') s[i] = 'U';
        }
        if(rb) {
            if(s[i] == 'R') s[i] = 'L';
            else if(s[i] == 'L') s[i] = 'R';
        }
    }
    if(x + y > n) {puts("-1"); return 0;}
    if(((x + y) ^ (n)) & 1) {puts("-1"); return 0;}
    
    rep(i, n) {
        prex[i] = prex[i-1] + (s[i]=='L' ? -1 : s[i]=='R' ? 1 : 0);
        prey[i] = prey[i-1] + (s[i]=='D' ? -1 : s[i]=='U' ? 1 : 0);
    }
    for(int i = n; i; --i) {    
        sufx[i] = sufx[i+1] + (s[i]=='L' ? -1 : s[i]=='R' ? 1 : 0);
        sufy[i] = sufy[i+1] + (s[i]=='D' ? -1 : s[i]=='U' ? 1 : 0);
    }
    int l = 0, r = n;
    while(l < r) {
        int mid = (l + r) >> 1;
        if(judge(mid)) r = mid;
        else l = mid + 1;
    }
    printf("%lld\n", l);
    return 0;
}
