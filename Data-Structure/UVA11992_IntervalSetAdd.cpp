// Link: https://cn.vjudge.net/problem/UVA-11992
// Memory: 1.57 GB and it passed UVA tests

#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;
const int maxn = 1000200;

#define ABS(x) ( (x)>0 ? (x) : (-(x)) )
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

int row, n, q;

struct answer {
    int sum, mn, mx;
    answer(int x, int y, int z) : sum(x), mn(y), mx(z) { }
    answer operator + (answer ans) const {
        return answer(sum + ans.sum, min(mn, ans.mn), max(mx, ans.mx));
    }
    inline void show() { printf("%d %d %d\n", sum, mn, mx);}
};

struct SegmentTree {

    #define lson (o << 1)
    #define rson (o << 1 | 1)

    private:
    int sum[maxn << 2], mn[maxn << 2], mx[maxn << 2], Set[maxn << 2], Add[maxn << 2];
    inline void pushup(int o) {
        sum[o] = sum[lson] + sum[rson];
        mn[o] = min(mn[lson], mn[rson]);
        mx[o] = max(mx[lson], mx[rson]);
    }
    inline void pushdown(int o, int l, int r) {
        int mid = (l + r) >> 1;
        if(Set[o] ^ -1) {
            int val = Set[o] + Add[o];
            sum[lson] = val * (mid - l + 1), sum[rson] = val * (r - mid);
            mn[lson] = mx[lson] = mn[rson] = mx[rson] = val;
            Set[lson] = Set[rson] = val; Add[lson] = Add[rson] = 0;
        } else {
            if(!Add[o]) return;
            sum[lson] += Add[o] * (mid - l + 1), sum[rson] += Add[o] * (r - mid);
            mn[lson] += Add[o], mn[rson] += Add[o];
            mx[lson] += Add[o], mx[rson] += Add[o];
            Add[lson] += Add[o], Add[rson] += Add[o];
        }
        Add[o] = 0, Set[o] = -1;
    }

    public:
    void InterSet(int o, int l, int r, int ql, int qr, int v) {
        if(ql <= l && r <= qr) {
            Set[o] = v; Add[o] = 0;
            sum[o] = (r - l + 1) * v, mn[o] = v, mx[o] = v;
            return;
        }
        pushdown(o, l, r);
        int mid = (l + r) >> 1;
        if(ql <= mid) InterSet(lson, l, mid, ql, qr, v);
        if(qr > mid) InterSet(rson, mid + 1, r, ql, qr, v);
        pushup(o);
    }
    void InterAdd(int o, int l, int r, int ql, int qr, int v) {
        if(ql <= l && r <= qr) {
            sum[o] += (r - l + 1) * v, mn[o] += v, mx[o] += v;
            Add[o] += v;
            return;
        }
        pushdown(o, l, r);
        int mid = (l + r) >> 1;
        if(ql <= mid) InterAdd(lson, l, mid, ql, qr, v);
        if(qr > mid) InterAdd(rson, mid + 1, r, ql, qr, v);
        pushup(o);
    }
    void Build() { InterSet(1, 1, n, 1, n, 0); }
    answer Query(int o, int l, int r, int ql, int qr) {
        if(ql <= l && r <= qr) return answer(sum[o], mn[o], mx[o]);
        int mid = (l + r) >> 1;
        answer ans(0, 0x3f3f3f3f, 0);
        pushdown(o, l, r);
        if(ql <= mid) ans = ans + Query(lson, l, mid, ql, qr);
        if(qr > mid) ans = ans + Query(rson, mid + 1, r, ql, qr);
        return ans;
    }
} seg[21];


int main(){
    while(~scanf("%d%d%d", &row, &n, &q)) {
        int opt, X1, X2, Y1, Y2, v;
        rep(i, row) seg[i].Build();
        while(q--) {
            scanf("%d%d%d%d%d", &opt, &X1, &Y1, &X2, &Y2);
            if(opt == 1) {
                scanf("%d", &v); 
                for(int i = X1; i <= X2; ++i)
                    seg[i].InterAdd(1, 1, n, Y1, Y2, v);
            } else if(opt == 2) {
                scanf("%d", &v);
                for(int i = X1; i <= X2; ++i) 
                    seg[i].InterSet(1, 1, n, Y1, Y2, v);
            } else if(opt == 3) {
                answer ans(0, 0x3f3f3f3f, 0);
                for(int i = X1; i <= X2; ++i)
                    ans = ans + seg[i].Query(1, 1, n, Y1, Y2);
                ans.show();
            }
        }
    }
    
    return 0;
}
