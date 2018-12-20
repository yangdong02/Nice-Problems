#include<cstdio>
#include<cctype>
#include<cstring>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;

template<typename T> void read(T &x){
    x = 0; int f = 1; char ch = nc();
    while(!isdigit(ch) ) { if(ch == '-') f = -1; ch = nc();}
    while( isdigit(ch) ) {x = x * 10 + ch - 48; ch = nc();}
    x *= f;
}
template<typename T, typename... Args> void read(T& x, Args&... args)
{ read(x), read(args...); }
template<typename T> void write(T x) {
    if(x < 0) putchar('-'), write(-x);
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

const int maxn = 1020;
int n;
bool f[maxn][maxn];
inline int lowbit(int x) { return x & -x; }
inline void Modify(int x, int y) {
    for(int i = x; i <= n; i += lowbit(i))
        for(int j = y; j <= n; j += lowbit(j))
            f[i][j] ^= 1;
}
inline bool Query(int x, int y) {
    bool sum = 0;
    for(int i = x; i; i -= lowbit(i))
        for(int j = y; j ; j -= lowbit(j))
            sum ^= f[i][j];
    return sum;
}

int T, q, xp, yp, xxp, yyp;
char opt[5];
int main() {
    read(T);
    while(T--) {
        memset(f, 0, sizeof f);
        read(n, q), n++;
        while(q--) {
            opt[0] = 0;
            while(!isalpha(opt[0])) opt[0] = nc();
            if(opt[0] == 'C') {
                read(xp, yp, xxp, yyp);
                Modify(xp, yp);
                Modify(xxp + 1, yyp + 1);
                Modify(xxp + 1, yp);
                Modify(xp, yyp + 1);
            } else {
                read(xp, yp);
                write(Query(xp, yp));
                putchar('\n');
            }
        }
        if(T) putchar('\n');
    }
    
    return 0;
}
