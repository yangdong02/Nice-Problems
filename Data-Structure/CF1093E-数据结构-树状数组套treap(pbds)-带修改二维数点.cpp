// 主要利用每一个x坐标或y坐标只能对应一个点
#include<bits/stdc++.h>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/assoc_container.hpp>
#define rep(i, n) for(register int i = 1; i <= n; ++i)
#pragma GCC optimize("-O3", "-Ofast", "inline")
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;

const int BUFF_SIZE = 1 << 20;
char BUFF[BUFF_SIZE],*BB,*BE;
#define gc() (BB == BE ? (BE = (BB = BUFF) + fread(BUFF,1,BUFF_SIZE,stdin),BB == BE ? EOF : *BB++) : *BB++)
template<typename T> void read(T &x){
    x = 0; int f = 1; char ch = gc();
    while(!isdigit(ch) ) { if(ch == '-') f = -1; ch = gc();}
    while( isdigit(ch) ) {x = x * 10 + ch - 48; ch = gc();}
    x *= f;
}
template<typename T, typename... Args> void read(T& x, Args&... args)
{ read(x), read(args...); }
template<typename T> void write(T x) {
    if(x < 0) putchar('-'), write(-x);
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

const int maxn = 200200;
int n, q;
tree<int, null_type, less<int>, rb_tree_tag, 
  tree_order_statistics_node_update> tr[maxn];

inline int lowbit(int x) { return x & -x; }
inline void del(int pos, int val) {
    for(; pos <= n; pos += lowbit(pos))
        tr[pos].erase(val);
}
inline void ins(int pos, int val) {
    for(; pos <= n; pos += lowbit(pos))
        tr[pos].insert(val);
}
inline int query(int x, int l, int r) {
    int tot = 0;
    for(; x; x -= lowbit(x))
        tot += tr[x].order_of_key(r + 1) - tr[x].order_of_key(l);
    return tot;
}

int mp[maxn], a[maxn], b[maxn];
int main() {
    read(n, q);
    rep(i, n) read(a[i]), mp[a[i]] = i;
    rep(i, n) read(b[i]), b[i] = mp[b[i]], ins(i, b[i]);
    while(q--) {
        int opt, x, y, l, r;
        read(opt);
        if(opt == 1) {
            read(l, r, x, y);
            write(query(y, l, r) - query(x - 1, l, r));
            putchar('\n');
        } else {
            read(x, y);
            del(x, b[x]);
            del(y, b[y]);
            swap(b[x], b[y]);
            ins(x, b[x]);
            ins(y, b[y]);
        }
    }

    
    return 0;
}
