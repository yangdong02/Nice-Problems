//https://www.cnblogs.com/ljh2000-jump/p/5869991.html
/*
OpenTrains 1511A
- 线性基的题。线性基常常用来解决子集异或问题，因为自然数、异或运算是构成线性空间的。
- 对于这道题来说，出现偶数次的数位直接忽略，因为对答案没有影响。这样，分成的两组A,B
  满足xor(A) + xor(B)为定值，因此若xor(A) > xor(B)，那么应该尽量使xor(A)与xor(B)
  尽量接近。这只需要把最高位的1分给A，剩下数位贪心即可。即：如果数位是1且线性基中有
  这一位，那么就将它异或掉，否则继续。
Extension
### HDU3949
    题意是求出n个数异或起来第k大的数。求出线性基之后按照k数位是0是1以及异或之后变大变
    小选择是否异或。注意坑点在于0的判断：如果满秩，则还需要考虑0，k应当减一。
### BZOJ2460
 
    题意是选出对于异或线性无关的一组数，使得权值之和最大。这就是拟阵贪心的裸题：按照权
    值排序，能插入线性基就插入。
### BZOJ2115 （好题）
    题意是给出一个无向连通图，要求1到n的一条（可以重复走边走点的）路径，使得经过的边的
    权值异或和最大。
    做法非常有趣。先找出1到n的任意一条路径，然后处理出基本回路的权值，基本回路组成线性
    空间，求出线性基之后与之前求的路径进行异或，贪心处理即可。
*/
#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;

template<typename T> void read(T &x){
	x = 0; int f = 1; char ch = getchar();
	while(!isdigit(ch) ) { if(ch == '-') f = -1; ch = getchar();}
	while( isdigit(ch) ) {x = x * 10 + ch - 48; ch = getchar();}
	x *= f;
}
template<typename T, typename... Args> void read(T& x, Args&... args)
{ read(x), read(args...); }
template<typename T> void write(T x) {
	if(x < 0) putchar('-'), write(-x);
	if(x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

const int maxn = 200500;
int head[maxn], nxt[maxn], n, m, ecnt = 0, ccnt = 0; 
int fae[maxn];
ll pre[maxn], cyc[maxn], ans = 0;
struct edge {
	int from, to;
	ll w;
	edge(int f = 0, int t = 0, ll c = 0):
		from(f), to(t), w(c) { }
} tr[maxn], cy[maxn];
inline void addedge(int f, int t, ll c) {
	tr[++ecnt] = edge(f, t, c);
	nxt[ecnt] = head[f];
	head[f] = ecnt;
}

int _fa[maxn];
int find(int x) { return _fa[x] == x ? x : _fa[x] = find(_fa[x]); }

inline void input() {
	read(n, m);
	rep(i, n) _fa[i] = i;
	for(int i = 1; i <= m; ++i) {
		int x, y; ll w;
		read(x, y, w);
		int xf = find(x), yf = find(y);
		if(xf == yf) {
			cy[++ccnt] = edge(x, y, w);
		} else {
			addedge(x, y, w);
			addedge(y, x, w);
			_fa[find(xf)] = yf;
		}
	}
}

void dfs(int v, int fath, ll Xor) {
	pre[v] = Xor;
	for(int i = head[v]; i ; i = nxt[i]) {
		int to = tr[i].to;
		if(to == fath) continue;
		fae[to] = i;
		dfs(to, v, Xor ^ tr[i].w);
	}
}

inline void FindPath() {
	vector<int> Path;
	Path.push_back(n);
	int cur = n;
	while(cur != 1) {
		ans ^= tr[fae[cur]].w;
		cur = tr[fae[cur]].from;
		Path.push_back(cur);
	}
}

ll base[80];
void ins(ll x) {
	for(int i = 62; i >= 0; --i) {
		if(x >> i & 1) {
			if(base[i]) x ^= base[i];
			else { base[i] = x; return; }
		}
	}
}

inline void DealCycle() {
	for(int i = 1; i <= ccnt; ++i) {
		cyc[i] = pre[cy[i].from] ^ pre[cy[i].to] ^ cy[i].w;
		ins(cyc[i]);
	}
}

ll query() {
	for(int i = 62; i >= 0; --i) {
		if(ans >> i & 1) continue;
		if(base[i] == 0) continue;
		ans ^= base[i];
	}
	return ans;
}

int main() {
	input();
	dfs(1, -1, 0);
	FindPath();
	DealCycle();
	printf("%lld\n", query());
	return 0;
}
