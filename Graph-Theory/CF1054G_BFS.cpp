/*
Link: http://codeforces.com/contest/1071/problem/B

Solution:
  First, use a dp to find the farthest points we can reach (Manhattan Distance). Add them in a queue
  Then, we will consider layers one by one. When traversing one layer, We need to find the 
    smallest node we can reach in the next layer and then add them in the queue. This can be done using
    a simple vector and when we meet a better answer update naively. Record the path when solving.
    
Overall complexity: O(n ^ 2)
  For we only need to consider O(n) layers and in each layer O(n) elements
  
Warning / Hint:
  Be careful to check if one node has been added into the vector 'tobe'! Or the algorithm may become O(2 ^ n)!
  
Similar Problems:
  UVa 1599: Output lexicographically smallest shortest path
  https://www.nowcoder.com/acm/contest/178/A: A little bit diffent, we need to calculate the plan for every
    point. THen we need sortings and complexity is O(nlogn)
*/
#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<pair<int, int>, int > p3;
const int maxn = 2039;
int n, k, dp[maxn][maxn];
bool inq[maxn][maxn];
char s[maxn][maxn];
pii fa[maxn][maxn];
inline bool valid(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= n;
}
struct Vec {
    pii point[1000200];
    int st = 1, ed = 1;
    inline void clear() {
        for(int i = st; i < ed; ++i) {
            inq[point[i].first][point[i].second] = false;
            point[i] = {0, 0};
        }
        ed = st = 1;
    }
    inline void push_back(pii p) {
        point[ed++] = p;
        if(ed > 10000)
            puts("NO!!!");
    }
} tobe;


int main(){
    int layer, bst = 'z' + 1;
    string ans = "";

    scanf("%d%d", &n, &k);
    int goal = 1;
    rep(i, n) scanf("%s", s[i] + 1);
    dp[1][1] = s[1][1] != 'a';
    if(dp[1][1] <= k) goal = 2;
    for(int j = 2; j <= n; ++j) {
        dp[1][j] = dp[1][j-1] + (s[1][j] != 'a');
        dp[j][1] = dp[j-1][1] + (s[j][1] != 'a');
        if(dp[1][j] <= k || dp[j][1] <= k)
            goal = max(goal, 1 + j);
    }
    for(int i = 2; i <= n; ++i) {
        for(int j = 2; j <= n; ++j) {
            int ad = s[i][j] != 'a';
            dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + ad;
            if(i + j > goal && dp[i][j] <= k) goal = i + j;
        }
    }
    queue<pii> q;
    for(int i = 1, j = goal - 1; i <= n; ++i, --j) {
        if(j > n || j < 1) continue;
        if(dp[i][j] <= k) {
            q.push({i, j});
        }
    }
    if(goal == 1) q.push({1, 1});
    layer = goal;
    rep(i, goal - 1) ans += "a";
    while(layer <= 2 * n) {
        if(q.empty()) {
            layer++;
            for(int v = tobe.st; v != tobe.ed; ++v) {
                q.push(tobe.point[v]);
            }
            tobe.clear();
            bst = 'z' + 1;
            if(layer >= 2 * n) break;
            continue;
        }
        auto cur = q.front(); q.pop();
        int x = cur.first, y = cur.second;
        if(x + y !=  layer) {layer = x + y;}

        if(inq[x + 1][y]) goto right;
        if(valid(x + 1, y) && s[x + 1][y] < bst) {
            tobe.clear();
            bst = s[x + 1][y];
            fa[x + 1][y] = {x, y};
            tobe.push_back({x + 1, y});
            inq[x + 1][y] = true;
        } else if (valid(x + 1, y) && s[x + 1][y] == bst) {
            fa[x + 1][y] = {x, y};
            tobe.push_back({x + 1, y});
            inq[x + 1][y] = true;
        }

        right:
        if(inq[x][y + 1]) continue;
        if(valid(x, y + 1) && s[x][y + 1] < bst) {
            tobe.clear();
            bst = s[x][y + 1];
            fa[x][y + 1] = {x, y};
            tobe.push_back({x, y + 1});
            inq[x][y + 1] = true;
        } else if (valid(x, y + 1) && s[x][y + 1] == bst) {  
            fa[x][y + 1] = {x, y};
            tobe.push_back({x, y + 1});
            inq[x][y + 1] = true;
        }
    }
    pii cur = {n, n};
    stack<char> st;
    rep(i, 2 * n - goal) st.push(s[cur.first][cur.second]), cur = fa[cur.first][cur.second];
    while(!st.empty()) ans += st.top(), st.pop();
    cout << ans << '\n';
    return 0;
}
