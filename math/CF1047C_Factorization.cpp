// This problem is not difficult , and even the bruteforce solution which complexity is O(n Sqrt(a) ) could pass
// However, it introduces a new way to factorize numbers (under 1.5e7):
// O(n) Euler sieve to get the minimum divisor of every number in [2, 1.5e7]
// O(logn) Factorize each number as we can divide it by its minimum divisor and record the data.
// Link: https://vjudge.net/problem/CodeForces-1047C

// This problem has a little bit tight time limit so I open all the optimizations that I can think of
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#define rep(i, n) for(register int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

template <typename T> inline void read(T& x){ int w = 1; T data = 0; char ch = getchar(); while(!isdigit(ch) && ch != '-') ch = getchar(); if(ch == '-') w = -1, ch = getchar(); while(isdigit(ch)) data = 10 * data + ch - '0', ch = getchar(); x = data * w; }
template <typename T> void write(T x){ if (x < 0) putchar('-'),x = ~x + 1; if (x > 9) write(x / 10); putchar( x % 10 + '0'); }
template <typename T> inline void writeln(T x){ write(x), putchar('\n'); }

int gcd(int x, int y) {return y == 0 ? x : gcd(y, x % y);}
const int maxn = 300200;
int n, a[maxn], mx, gd, p[1000000] = {0}, pcnt = 1, vis[15000030] = {0};
int cnt[1000000] = {0};

// vis[] array is used to store minimum divisor of each number
inline void euler(int nn){
    for(register int i = 2; i <= nn; ++i){
        if(!vis[i]) p[pcnt] = i, vis[i] = pcnt, pcnt++;
        for(register int j = 1; i * p[j] <= nn &&  j< pcnt; ++j){
            vis[i * p[j]] = j;
            if(i % p[j] == 0) break;
        }
    }
}

int main()
{
    read(n);
    euler(15000010);
    rep(i, n)
        read(a[i]),
        mx = max(a[i], mx),
        gd = i == 1 ? a[1] : gcd(gd, a[i]);
    rep(i, n) a[i] /= gd;
    mx /= gd;
    
    // Factorizing and updating the cnt[] array
    rep(i, n){
        int x = a[i];
        while(x != 1){
            int t = vis[x];
            while(vis[x] == t) x /= p[t];
            cnt[t]++;
        }
    }
    int ans = 0;
    for(register int i = 1; i < pcnt; ++i)
        ans = max(ans, cnt[i]);
    writeln(ans ? n - ans : -1);
    return 0;
}
