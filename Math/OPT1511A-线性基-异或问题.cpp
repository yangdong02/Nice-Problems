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
const int maxn = 100200;

int T, n, maxbit;
ll a[maxn], sum = 0, base[80];

void insert(ll x) {
    for(int i = 62; i >= 0; --i) {
        if(x >> i & 1LL) {
            if(base[i]) x ^= base[i];
            else { base[i] = x; return; }
        }
    }
}
ll query() {
    ll ret = base[maxbit];
    for(int i = maxbit - 1; i >= 0; --i) {
        if(!base[i]) continue;
        if(base[i] && (ret >> i & 1LL)) ret ^= base[i];
    }
    return ret - (sum ^ ret);
}

int main() {
    scanf("%d", &T);
    while(T--) {
        sum =  0, maxbit = -1;
        memset(base, 0, sizeof base);
        scanf("%d", &n);
        rep(i, n) scanf("%lld", &a[i]), sum ^= a[i];
        rep(i, n) a[i] &= sum, insert(a[i]);
        if(sum == 0LL) { puts("0"); continue; }
        for(int i = 62; i >= 0; --i)
            if(sum >> i & 1LL) { maxbit = i; break; }
        printf("%lld\n", query());
    }
    
    return 0;
}
