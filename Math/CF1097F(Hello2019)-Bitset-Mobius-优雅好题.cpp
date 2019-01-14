/*
  Link: https://codeforces.com/contest/1097/problem/F
  Source: Hello 2019 by Radewoosh
*/

#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;

const int N = 7070, M = 100020;
bitset<N> mu, a[M], b[N], e[N]; 
int q, x, y, z, op;
int main() {
    mu.flip();
    for(int i = 2; i * i <= 7000; ++i) 
        for(int j = i * i; j <= 7000; j += i * i)
            mu[j] = false;
    for(int i = 1; i <= 7000; ++i)
        for(int j = i; j <= 7000; j += i)
            e[j][i] = true;
    for(int i = 1; i <= 7000; ++i)
        for(int j = i; j <= 7000; j += i)
            if(mu[j / i]) b[i][j] = true;
    
    scanf("%*d%d", &q);
    while(q--) {
        scanf("%d%d%d", &op, &x, &y);
        if(op != 1 && op != 4) scanf("%d", &z);
        if(op == 1) a[x] = e[y];
        if(op == 2) a[x] = a[y] ^ a[z];
        if(op == 3) a[x] = a[y] & a[z];
        if(op == 4) putchar(((a[x] & b[y]).count() & 1) + '0');
    }
    return 0;
}
