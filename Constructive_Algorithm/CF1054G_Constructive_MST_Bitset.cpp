
/*
Link: http://codeforces.com/contest/1054/problem/G

Solution 1:  (essentially simulates the search for such a spanning tree)
  We can see that if u is a leaf and v is its father, then any non-trivial set (|S| > 1) which includes u must include v.
  Conversely, if u and v satisfies the condition above, we can safely assume that u is a leaf and v is its father.
  Thus, let's find such pair (u, v), add an edge (u, v) to the answer, then delete u and go on. If we can't find
  such pair (u, v), then the answer is no. To speed up finding (u, v), we need to use bitset. (See mnbvmar's comment)
  
Solution 2: Maximum Spanning Tree (Implemented in the code below)
  Let xi be the number of people in the i-th group. In any solution, we expect to get have exactly xi - 1 edges between
    these people (we can't have less since they wouldn't be connected, and we can't have more or it wouldn't be a tree).
  Let wi, j be the number of groups that node i and node j have in common (and suppose we have these counts).
  Let's find a max weight spanning tree on the complete graph where the weight of an edge between nodes i and j is wi, j. 
    If the weight of this MST is equal to \sum(x_i - 1) , then the answer is yes and we can print any max spanning tree, 
    otherwise it is no.
  To show this is optimal, if a solution exists, the weight of that tree is exactly \sum(x_i - 1), so our algorithm will find it. 
    The other way is if we do find a tree with this weight, then this is a valid solution, each group can only contribute 
    at most xi - 1 to the weight of the max spanning tree, which shows it is also a valid solution since each group is connected.
  The only other tricky part is computing wi, j fast. This part can be done with bitsets (See lewin's comment)

Both solutions have complexity O(mn^2 / 64)
*/

#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;
const int N = 2020;
bitset<N> MySet[N];
int n, m, need, fa[N], ecnt, tcnt, cur;
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]);}
struct edge {
    int from, to, w;
    edge(int f = 0, int t = 0, int c = 0) : from(f), to(t), w(c) { }
    bool operator < (const edge& ed) const {
        return w > ed.w;
    }
} e[N * N];
pair<int, int> ans[N];

char tmp[N];
int main(){
    int T; scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        memset(MySet, 0, sizeof MySet);
        cur = tcnt = need = ecnt = 0;
        rep(i, n) fa[i] = i;
        rep(i, m) {
            int cnt = 0;
            scanf("%s", tmp + 1);
            rep(j, n) if(tmp[j] == '1')
                cnt++, MySet[j].set(i);
            need += cnt - 1;
        }
        for(int i = 1; i <= n; ++i)
            for(int j = i + 1; j <= n; ++j)
                e[++ecnt] = edge(i, j, (MySet[i] & MySet[j]).count());
        sort(e + 1, e + 1 + ecnt);
        for(int i = 1; tcnt < n && i <= ecnt; ++i) {
            int x = find(e[i].from), y = find(e[i].to);
            if(x == y) continue;
            cur += e[i].w, fa[x] = y;
            ans[++tcnt] = {e[i].from, e[i].to};
        }
        if(cur != need) {puts("NO"); continue;}
        puts("YES");
        rep(i, n - 1) 
            printf("%d %d\n", ans[i].first, ans[i].second);
    }
    return 0;
}
