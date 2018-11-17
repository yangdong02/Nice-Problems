/*
Link: Contest Hunter 4401
Solution 1 (4432 ms, 169.2 Mb):
  Memory and time: O( n^(5/3) )
  Divide the sequence into T blocks. 
  1. Discretize O(nlogn)
  2. Precalculate cnt array for each block O(nT^2)
  3. For each query [l, r]: find block boundary lb > l and rb < r
       Break it into [l, lb) + [lb, rb] + (rb, r] O(1)
       Use the answer of [lb, rb] (as we have precalculated) O(1)
       Update the cnt array and answer while scanning the two parts O(n/T)
       Recover the cnt array by scanning the two parts again O(n/T)
     O(qn/T) For all queries.
   Overall Complexity: O(nT^2 + nq/T), we can reach equilibrium by setting
   T = pow(n, 1/3), which results in O(n ^ (5/3))
   
Solution 2: Under construction 
  Time: O( n sqrt(nlogn) )
  Memory: O(nlogn)
*/

#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

const int maxn = 40100, maxB = 37;
int n, q, a[maxn], L[maxn], R[maxn], pos[maxn], t, b[maxn];
int cnt[maxB][maxB][maxn], raw[maxn], mcnt = 0, len;
pair<int,int> most[maxB][maxB];
map<int, int> val;

inline void precalc() {
    for(int l = 1; l <= t; ++l) {
        for(int r = l; r <= t; ++r) {
            int *c = cnt[l][r]; pii &w = most[l][r];
            for(int j = L[l]; j <= R[r]; ++j) {
                c[b[j]]++;
                if(make_pair(c[b[j]], -b[j]) > w)
                    w = make_pair(c[b[j]], -b[j]);
            }
        }
    }
}


int main() {
    scanf("%d%d", &n, &q);
    rep(i, n) scanf("%d", &a[i]), val[a[i]] = 1;
    
    for(auto it = val.begin(); it != val.end(); ++it) {
        raw[++mcnt] = it->first;
        it->second = mcnt;
    }

    rep(i, n) b[i] = val[a[i]];
    t = powl(n + 0.5, 1.0L / 3.0L), len = n / t;
    for(int i = 1; i <= t; ++i) {
        L[i] = (i - 1) * len + 1;
        R[i] = i * len;
        for(int j = L[i]; j <= R[i]; ++j) pos[j] = i;
    }
    if(R[t] < n) { t++, L[t] = R[t-1] + 1, R[t] = n; }
    for(int j = L[t]; j <= R[t]; ++j) pos[j] = t;

    precalc();

    int lastans = 0;
    while(q--) {
        int l0, r0, l, r, bl, br;
        scanf("%d%d", &l0, &r0);
        l = (l0 + lastans - 1) % n + 1;
        r = (r0 + lastans - 1) % n + 1;
        if(l > r) swap(l, r);
        bl = pos[l] + 1, br = pos[r] - 1;
        int* ar = cnt[bl][br];
        pair<int, int> an = most[bl][br];
        if(bl > br + 1) {
            for(int i = l; i <= r; ++i)
                an = max(an, make_pair(++ar[b[i]], -b[i]));
        } else {
            for(int i = l; i < L[bl]; ++i) 
                an = max(an, make_pair(++ar[b[i]], -b[i]));
            for(int i = R[br] + 1; i <= r; ++i) 
                an = max(an, make_pair(++ar[b[i]], -b[i]));
        }

        lastans = raw[-an.second];
        printf("%d\n", lastans);
        if(bl > br + 1) 
            for(int i = l; i <= r; ++i) ar[b[i]]--;
        else {
            for(int i = l; i < L[bl]; ++i)  ar[b[i]]--;
            for(int i = R[br] + 1; i <= r; ++i) ar[b[i]]--;
        }
    }
    
    return 0;
}
