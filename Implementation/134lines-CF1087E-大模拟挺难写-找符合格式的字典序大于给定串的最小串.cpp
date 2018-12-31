#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;

const int maxn = 3002000;
int n, T, k;
char a_tp[maxn], b_tp[maxn], s_tp[maxn];

int a[maxn], b[maxn], s[maxn];
int ans[maxn], chk_time[maxn]; // ans: 比a字典序大的最小字符串
int vis[30], col[30]; // 各个字母是否已经被分配，每一类的颜色
vector<int> eq[30];

int chk_clock = 0;

void draw(int type, int color) {
    if(color == 0) {
        for(auto v : eq[type]) {
            chk_time[v] = 0;
            ans[v] = 0;
        }
        vis[col[type]] = 0;
        col[type] = 0;
        return;
    }
    for(auto v : eq[type]) {
        chk_time[v] = chk_clock;
        ans[v] = color;
    }
    vis[color] = chk_clock;
    col[type] = color;
}

bool dfs(int pos, bool loose) {
    if(loose) {
        int p = 1;
        while(vis[p]) p++;
        for(int i = pos; i <= n; ++i) {
            if(chk_time[i] != chk_clock) { 
                if(p > k) return false;
                draw(s[i], p);
            }
            while(vis[p]) p++;
        }
        return true;
    }
    if(pos > n) return true;
    if(chk_time[pos] == chk_clock) {
        if(ans[pos] < a[pos]) return false;
        else if(ans[pos] == a[pos]) return dfs(pos + 1, false);
        else return dfs(pos + 1, true);
    }
    int nxt = a[pos];
    bool Lo = false;
    while(vis[nxt]) nxt++;
    if(nxt != a[pos]) Lo = true;
    if(nxt > k) return false;
    draw(s[pos], nxt);
    if(dfs(pos + 1, Lo)) return true;
    else {
        draw(s[pos], 0);
        nxt++;
        while(vis[nxt]) nxt++;
        if(nxt > k) return false;
        draw(s[pos], nxt);
        if(dfs(pos + 1, true)) return true;
        else draw(s[pos], 0);
    }
    return false;
}

bool getA() {
    memset(vis, 0, sizeof vis);
    chk_clock++;
    if(!dfs(1, false)) return false;
    return true;
}

bool Compare() {
    for(int i = 1; i <= n; ++i) {
        if(ans[i] > k || ans[i] < 1) return false;
        if(ans[i] < b[i]) return true;
        if(ans[i] > b[i]) return false;
    }
    return true;
}

int mp[30];
void Show() {
    memset(vis, 0, sizeof vis);
    memset(mp, 0, sizeof mp);
    puts("YES");
    rep(i, n) {
        mp[s[i]] = ans[i];
        vis[ans[i]] = true;
    }
    int pos = 1;
    while(vis[pos]) pos++;
    rep(i, k) if(!mp[i]) {
        mp[i] = pos;
        vis[pos] = true;
        while(vis[pos]) pos++;
    }
    rep(i, k) putchar('a' - 1 + mp[i]);
    putchar('\n');
}

void Parse_input() {
    scanf("%d%s%s%s", &k, s_tp + 1, a_tp + 1, b_tp + 1);
    n = strlen(s_tp + 1);
    rep(i, n) {
        a[i] = a_tp[i] - 'a' + 1;
        b[i] = b_tp[i] - 'a' + 1;
        s[i] = s_tp[i] - 'a' + 1;
    }
    rep(i, n) eq[s[i]].push_back(i);
}


int main() {
    scanf("%d", &T);
    while(T--) {
        for(int i = 0; i <= 26; ++i) eq[i].clear();

        Parse_input();
        if(!getA()) { puts("NO"); continue; };

        if(Compare()) Show();
        else puts("NO");
    }
    
    return 0;
}
