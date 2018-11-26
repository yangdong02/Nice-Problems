/*
  Source: Codeforces Round 524
  Note: This is not a hard problem, and the fomula for lower bound and
    upper bound is not hard to see. However, the numbers can be up to
    2 ^ (1e6), so we should estimate the most suitable lower bound and check
    the upper bound. Use double to avoid the risk of overflowing.
*/
#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef unsigned long long ll;

template<typename T> void read(T &x){
    x = 0; int f = 1; char ch = getchar();
    while(!isdigit(ch) ) { if(ch == '-') f = -1; ch = getchar();}
    while( isdigit(ch) ) {x = x * 10 + ch - 48; ch = getchar();}
    x *= f;
}
template<typename T, typename... Args> void read(T& x, Args&... args)
{ read(x), read(args...); }

ll t, k;

inline double Sl(double x) { return  ( pow(2, (2*x)) - 1.0) / 3.0; }
inline double upbl(double n) {
    return Sl(t) - Sl(n) * (pow(2, (t-n+1.0)) - 1.0);
}

inline ll S(int x) { 
    return  ( (1LL << (2*x)) - 1) / 3; 
}
inline ll lowb(int n) { 
    int m = t - n + 1;
    return (1LL << m) - m - 1;
}

const ll inf = 2000000000000000044ULL;
inline ll upb(int n) {
    if(t - n >= 31) return inf;
    if(t >= 33) return inf;
    double ret = upbl(n);
    if(ret > 1e18) return inf;
    return S(t) - S(n) * ((1LL << (t-n+1)) - 1);
}



int main() {
    int n, T;
    read(T);
    while(T--) {
        read(t, k);
        for(n = t - 1; n >= 0; --n)
            if(lowb(n) > k) break;
        n++;
        if(upb(n) >= k) printf("YES %d\n", n);
        else puts("NO");
    }
    
    return 0;
}
