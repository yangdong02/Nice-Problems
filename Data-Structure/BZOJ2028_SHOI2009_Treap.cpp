// Link: https://www.luogu.org/problemnew/show/P2161
// O(n log^2 n)
// 此代码会被卡常数
#include<cstdio>
#include<cctype>
using namespace std;
int read() {
	int x = 0, f = 1; char ch = getchar();
	while(!isdigit(ch) ) { if(ch == '-') f = -1; ch = getchar();}
	while( isdigit(ch) ) {x = x * 10 + ch - 48; ch = getchar();}
	return x * f;
}
int min(int a, int b) { return a<b ? a : b;}
int max(int a, int b) { return a>b ? a : b;}
const int N = 100001;
int tree[N], end[N];
void add(int x, int c){
    for(; x < N; x += x&-x) tree[x] += c;
}
int ask(int x){
    int sum = 0;
    for(; x; x &= x-1) sum += tree[x];
    return sum;
}

int main(){
    int n = read(), ans = 0;
    for(int i = 1; i <= n; ++i) {
        scanf("\n");
        if(getchar() == 'A') {
            int del = 0, st = read(), ed = read();
            for(int p; p = ask(ed);) {
                int l = 0, r = ed;
                for(; l < r;) {
                    int m = ( l + r ) >> 1;
                    if( ask(m) + 1 <= p ) l = m + 1;
                    else r = m;
                }
                if(end[l] >= st) add(l, -1), del++, ans--;
                else break;
            }
            add(st, 1), end[st] = ed, ans++;
            printf("%d\n", del);
        }
        else printf("%d\n", ans);
    }
    return 0;
}
