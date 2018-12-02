// Link: https://www.luogu.org/problemnew/show/P2161
// O(n log^2 n)
// 此代码会被卡常数#include<bits/stdc++.h>
#pragma GCC optimize("O3", "Ofast", "inline")
#define rep(i, n) for(int i = 1; i <= n; ++i)
#define writeln(x) (write(x), putchar('\n'))
#define INF 0x7fffffff
using namespace std;
typedef long long ll;
typedef pair<int ,int> pii;

template<typename T> inline void read(T &x){
    x = 0; int f = 1; char ch = getchar();
    while(!isdigit(ch) ) { if(ch == '-') f = -1; ch = getchar();}
    while( isdigit(ch) ) {x = x * 10 + ch - 48; ch = getchar();}
    x *= f;
}
template<typename T, typename... Args> inline void read(T& x, Args&... args)
{ read(x), read(args...); }
template<typename T> inline void write(T x) {
    if(x < 0) putchar('-'), write(-x);
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

const int maxn = 500200;

namespace Treap {
    int tot = 0;
    struct node {
        int dat, cnt, sz;
        pair<int, int> val;
        node *lc, *rc;
        inline void update() {
            sz = lc->sz + rc->sz + cnt;
        }
    } tr[maxn], *Null;
    inline node* New(pii v) {
        tr[++tot].val = v;
        tr[tot].dat = rand();
        tr[tot].cnt = tr[tot].sz = 1;
        tr[tot].lc = tr[tot].rc = Null;
        return tr + tot;
    }
    inline void lrot(node* &p) {
        node* q = p->rc;
        p->rc = q->lc;
        q->lc = p;
        p = q;
        p->lc->update();
        p->update();
    }
    inline void rrot(node* &p) {
        node* q = p->lc;
        p->lc = q->rc;
        q->rc = p;
        p = q;
        p->rc->update();
        p->update();
    }
    inline int small(pii v, node* p) {
        if(p == Null) return 0;
        if(p->val > v) return small(v, p->lc);
        if(p->val == v) return p->lc->sz;
        return p->lc->sz + p->cnt + small(v, p->rc);
    }
    inline pii kth_s(int v, node* p) {
        if(p == Null) return {INF, INF};
        if(p->lc->sz >= v) return kth_s(v, p->lc);
        if(p->lc->sz + p->cnt >= v) return p->val;
        return kth_s(v - p->lc->sz - p->cnt, p->rc);
    }
    namespace Functions {
        node* lhs, *rhs;
        inline void init() {
            Null = tr;
            lhs = New(make_pair(INF, INF));
            lhs->lc = New(make_pair(-INF, -INF));
            rhs = New(make_pair(INF, INF));
            rhs->lc = New(make_pair(-INF, -INF));
            lhs->update(), rhs->update();
        }
        inline void Insert(pii v, node* &p) {
            if(p == Null) { p = New(v); return ; }
            if(p->val == v) {
                p->cnt++;
                p->update();
                return;
            }
            if(p->val < v) {
                Insert(v, p->rc);
                if(p->rc->dat > p->dat) lrot(p);
            } else {
                Insert(v, p->lc);
                if(p->lc->dat > p->dat) rrot(p);
            }
            p->update();
        }
        inline void Remove(pii v, node* &p) {
            if(p == Null) return;
            if(p->val == v) {
                if(p->cnt > 1) { p->cnt--, p->update(); return; }
                if(p->lc != Null || p->rc != Null) {
                    if(p->rc == Null || p->lc->dat > p->rc->dat) {
                        rrot(p);
                        Remove(v, p->rc);
                    } else lrot(p), Remove(v, p->lc);
                    p->update();
                } else p = Null;
                return;
            }
            if(p->val < v) Remove(v, p->rc), p->update();
            else Remove(v, p->lc), p->update();
        }

        inline int Rank(pii k, node* rt) { return small(k, rt); }
        inline pii Kth (int k, node* rt) { return kth_s(k + 1, rt); }
        inline pii Prev(pii v, node* rt) { return Kth(Rank(v, rt) - 1, rt); }
        inline pii Next(pii v, node* rt) { return Kth(Rank({v.first, v.second+1}, rt), rt); }
        inline bool End(pii v) { return v.first >= 1e9; }
    }
}
using namespace Treap::Functions;
int n, cnt = 0, tot = 0;
int main() {
    srand(2333333);
    read(n), init();
    while(n--) {
        char sss[3]; scanf("%s", sss);
        char opt = sss[0]; int l, r;
        while(!isalpha(opt)) opt = getchar();
        if(opt == 'A') {
            cnt = 0;
            read(l, r);
            pii cur = Prev({l, r}, lhs);

            auto disj = [&]() -> bool { return r < cur.first || cur.second < l; };
            while(disj() && !End(cur)) 
                cur = Next(cur, lhs);
            while(!disj()) {
                Remove(cur, lhs);
                cur = Next(cur, lhs);
                tot--, cnt++;
            }
            write(cnt), putchar('\n');
            tot++;
            Insert({l, r}, lhs);
        } else write(tot), putchar('\n');
    }

    return 0;
}
