// Link: https://www.luogu.org/problemnew/show/P1020
// A classic example of Dilworth theorem: the answer is just LDS(with equal) and LIS(without equal)

#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;
const int maxn = 100200;
int a[maxn], n = 0, lis[maxn], lds[maxn];
int main(){
    while(~scanf("%d", &a[++n])) continue;
    n--;
    int leni = 1, lend = 1;
    lis[1] = lds[1] = a[1];
    for(int i = 2; i <= n; ++i) {
        if(lds[lend] >= a[i]) lds[++lend] = a[i];
        else lds[upper_bound(lds + 1, lds + 1 + lend, a[i], greater<int>()) - lds] = a[i];
        if(lis[leni] < a[i]) lis[++leni] = a[i];
        else lis[lower_bound(lis + 1, lis + 1 + leni, a[i]) - lis] = a[i]; 
    }
    cout << lend << endl << leni;
    
    return 0;
}
