#include<cstdio>
#include<set>
#include<utility>
#include<map>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;
const int maxn = 50020;

struct SegmentTree {
    #define lson (o << 1)
    #define rson (o << 1 | 1)
    private:
    int Set[maxn << 2], m;
    set<int> st;
    inline void pushdown(int o) {
        if(Set[o] == -1) return;
        Set[lson] = Set[o];
        Set[rson] = Set[o];
        Set[o] = -1;
    }
    void query(int o, int l, int r) {
        if(Set[o] ^ -1) {
            if(Set[o] == 0) return;
            if(st.count(Set[o])) return;
            st.insert(Set[o]);
            return;
        }
        int mid = (l + r) >> 1;
        query(lson, l, mid);
        query(rson, mid + 1, r);
    }

    public: 
    void IntervalSet(int o, int l, int r, int ql, int qr, int v) {
        if(ql <= l && r <= qr) { Set[o] = v; return; }
        pushdown(o);
        int mid = (l + r) >> 1;
        if(ql <= mid) IntervalSet(lson, l, mid, ql, qr, v);
        if(qr > mid) IntervalSet(rson, mid + 1, r, ql, qr, v);
    }
    inline int QueryType() {
        st.clear();
        query(1, 1, m);
        return st.size();
    }
    inline void Init(int sz) { m = sz; IntervalSet(1, 1, m, 1, m, 0); }
} seg;

pair<int, int> poster[maxn];
map<int, int> mp;
int num[maxn << 2], n;

int main(){
    int T; scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        mp.clear();
        for(register int i = 1; i <= n; ++i) {
            scanf("%d%d", &poster[i].first, &poster[i].second);
            mp[poster[i].first ] = 1;
            mp[poster[i].second] = 1;
        }
        int cnt = 0, lst = -1;
        for(map<int, int>::iterator it = mp.begin(); it != mp.end(); ++it) {
            it->second = ++cnt;
            num[cnt] = it->first;
            if(lst != -1 && it->first - lst > 1) cnt++;
            lst = it->first;
        }
        seg.Init(cnt);
        for(int i = 1; i <= n; ++i) // [a, b]
            seg.IntervalSet(1, 1, cnt, mp[poster[i].first], mp[poster[i].second], i);
        printf("%d\n", seg.QueryType());
    }
    
    return 0;
}
