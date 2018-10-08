// The problem is equivalent to support these operations: 
//  1. find kth smallest
//  2. delete elements
//  The first approach is using balanced binary search tree, as shown below
//  The second solution is to use binary indexed tree, which I think is quite elegant
// Link: https://cn.vjudge.net/problem/UVA-11525

#include<bits/stdc++.h>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/assoc_container.hpp>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
template<typename T> void read(T &x){
    x = 0; int f = 1; char ch = getchar();
    while(!isdigit(ch) ) { if(ch == '-') f *= -1; ch = getchar();}
    while( isdigit(ch) ) {x = x * 10 + ch - 48; ch = getchar();}
    x *= f;
}
template <typename T>
void write(T x){
	 if (x < 0) putchar('-'),x = ~x + 1;
	 if (x > 9) write(x / 10);
	 putchar( x % 10 + '0');
}

tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> bst;
int main(){
    int T; read(T);
    while(T--) {
        int n, cnt; read(n), cnt = 0;
        bst.clear();
        rep(i, n) bst.insert(i);
        rep(i, n) {
            int rk; read(rk);
            auto it = bst.find_by_order(rk);
            write(*it), bst.erase(it);
            if(++cnt == n) putchar('\n'); else putchar(' ');
        }
    }
    return 0;
}
