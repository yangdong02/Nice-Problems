/*
  Link: http://codeforces.com/contest/1080/problem/F
  Source: Codeforces Round #524 (Div. 2)
  Solution: 对线段[l, r, p]按照l从大到小排序，依次插入，建立可持久化线段树
    节点{l, r, maxv, lc, rc}保存当前时刻组号在[l, r]范围内的组右端点的最大值
    
    回答询问时先以x为依据二分左端点找到时刻t0（upperbound），直接比较t0时刻[a, b]中
    右端点最大值与y的关系即可。
*/

#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= (n); ++i)
using namespace std;
const int maxn = 300200, INF = 0x3f3f3f3f;
template<typename T> void read(T &x){
    x = 0; int f = 1; char ch = getchar();
    while(!isdigit(ch) ) { if(ch == '-') f = -1; ch = getchar();}
    while( isdigit(ch) ) {x = x * 10 + ch - 48; ch = getchar();}
    x *= f;
}
template<typename T, typename... Args> void read(T& x, Args&... args)
{ read(x), read(args...); }


int n, m, k, root[maxn], tot = 0; // set, query, segment
struct Interval {
	int l, r, p;
	bool operator < (const Interval& it) const {
		return l > it.l;
	}
} seg[maxn];

struct node {
	int maxv, lc, rc;
	node(): maxv(INF), lc(0), rc(0) { }
} tr[maxn * 40];

inline void pushup(int id) { 
	tr[id].maxv = max(tr[id].lc ? tr[tr[id].lc].maxv : INF, tr[id].rc ? tr[tr[id].rc].maxv : INF);
}
int insert(int now, int l, int r, int pos, int val) {
	int q = ++tot;
	tr[q] = tr[now];
	if(l == r) { tr[q].maxv = min(tr[q].maxv, val); return q;} 
	int mid = (l + r) >> 1;
	if(pos <= mid) tr[q].lc = insert(tr[now].lc, l, mid, pos, val);
	else tr[q].rc = insert(tr[now].rc, mid + 1, r, pos, val);
	pushup(q);
	return q;
}

int query(int now, int l, int r, int ql, int qr) {
	if(now == 0) return INF;
	if(ql <= l && r <= qr) return tr[now].maxv;
	int mid = (l + r) >> 1, ans = 0;
	if(ql <= mid) ans = max(ans, query(tr[now].lc, l, mid, ql, qr));
	if(qr > mid) ans = max(ans, query(tr[now].rc, mid + 1, r, ql, qr));
	return ans;
}

int main() {
	read(n, m, k);
	for(int i = 1; i <= k; ++i) {
		read(seg[i].l, seg[i].r, seg[i].p);
	}
	sort(seg + 1, seg + 1 + k);
	root[0] = ++tot;
	for(int i = 1; i <= k; ++i)
		root[i] = insert(root[i-1], 1, n, seg[i].p, seg[i].r);
	
	while(m--) {
		int a, b, x, y;
		read(a, b, x, y);
		Interval it; it.l = x;
		int po = upper_bound(seg + 1, seg + 1 + k, it) - seg - 1;

		puts(query(root[po], 1, n, a, b) <= y ? "yes" : "no");
		fflush(stdout);
	}
	
	return 0;
}
