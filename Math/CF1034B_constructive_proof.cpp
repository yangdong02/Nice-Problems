// An elegant math problem which needs to prove a conclusion and construct a solution
// Bipartite graph matching can also be used to prevent proof on small cases
// But I think it is not elegant at all

// Source: Codeforces Round 511 Div2 D (This contest is a really high-quality math competition)
// Link: http://codeforces.com/problemset/problem/1034/B
#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;
ll a, b, ans;
int main(){
    cin >> a >> b;
    if(a > b) swap(a, b);
    if(a == 1) ans = (b / 6 * 6) + 2 * max(b % 6 - 3, 0LL);
    else if(a == 2) ans = b == 2 ? 0 : b == 3 ? 4 : b == 7 ? 12 : a * b;
    else ans = a * b - ( (a * b) & 1);
    printf("%lld\n", ans);
    return 0;
}
