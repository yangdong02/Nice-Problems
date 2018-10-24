
/*
Link: http://codeforces.com/contest/1054/problem/E
Move col1 and row1 into (1, 1)
Move all elements from (1, 1) to (2, 1) and (1, 2)
Move all 0s into (1, 2)
Move all 1s into (2, 1)
*/

#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<pii, pii> Ans;
const int maxn = 400;
int n, m;
vector<Ans> ans1, ans2;
struct node {
    deque<char> v;
    int xp, yp;
    bool Start = true;
    inline size_t Cnt() { return v.size(); }
    inline void Init(int xx, int yy, bool sta) {
        char ch = getchar();
        xp = xx, yp = yy, Start = sta;
        while(!isdigit(ch)) ch = getchar();
        while( isdigit(ch)) 
            v.push_back(ch), ch = getchar();
    }
    inline void Push_Front(node& nd) {
        char ch = v.back(); v.pop_back();
        nd.v.push_front(ch);
    }
    inline void Push_Back(node& nd) {
        char ch = v.front(); v.pop_front();
        nd.v.push_back(ch);
    }
    inline int Back() {
        if(Start) return v.back();
        return v.front();
    }
    inline void Operate(node& nd) {
        if(Start) {
            Push_Front(nd);
            ans1.push_back({{xp, yp}, {nd.xp, nd.yp}});
        }
        else {
            Push_Back(nd);
            ans2.push_back({{nd.xp, nd.yp}, {xp, yp}});
        }
    }
} f[maxn][maxn], g[maxn][maxn];
inline void solve(bool Start) {
    auto G = (Start ? f : g);
    for(int i = 2; i <= n; ++i)
        while(G[i][1].Cnt()) 
            G[i][1].Operate(G[1][1]);
    for(int i = 2; i <= m; ++i)
        while(G[1][i].Cnt())
            G[1][i].Operate(G[1][1]);
    while(G[1][1].Cnt()) {
        int cur = G[1][1].Back();
        if (cur == '0') G[1][1].Operate(G[1][2]);
        if (cur == '1') G[1][1].Operate(G[2][1]);
    }
    for(int i = 2; i <= n; ++i) {
        for(int j = 2; j <= m; ++j) {
            while(G[i][j].Cnt()) {
                int cur = G[i][j].Back();
                if (cur == '0') G[i][j].Operate(G[1][j]);
                if (cur == '1') G[i][j].Operate(G[i][1]);
            }
        }
    }
    for(int i = 3; i <= m; ++i) {
        while(G[1][i].Cnt()) {
            G[1][i].Operate(G[1][2]);
        }
    }
    for(int i = 3; i <= n; ++i) {
        while(G[i][1].Cnt()) {
            G[i][1].Operate(G[2][1]);
        }
    }
}
inline void Show(Ans a) {
    printf("%d %d %d %d\n", a.first.first, a.first.second, 
                            a.second.first, a.second.second);
}
int main(){
    scanf("%d%d", &n, &m);
    rep(i, n) rep(j, m) f[i][j].Init(i, j, 1);
    rep(i, n) rep(j, m) g[i][j].Init(i, j, 0);
    solve(1), solve(0);
    int a1 = ans1.size(), a2 = ans2.size();
    printf("%d\n", a1 + a2);
    for(int i = 0; i < a1; ++i)
        Show(ans1[i]);
    for(int i = a2 - 1; i >= 0; --i)
        Show(ans2[i]);
    return 0;
}
