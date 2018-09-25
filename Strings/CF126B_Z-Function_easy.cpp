// A good exercise for training Z algorithm
// Link: http://codeforces.com/contest/126/problem/B

#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;
const int maxn = 1000200;
string s;
int z[maxn], n, maxz = 0;
inline void getz(){
    int L = 0, R = 0;
    for(int i = 1; i < n; ++i){
        if(i > R){
            L = R = i;
            while(R < n && s[R] == s[R-L]) R++;
            z[i] = R - L, R--;
        } else{
            if(z[i - L] < R - i + 1) z[i] = z[i - L];
            else {
                L = i;
                while(R < n && s[R] == s[R-L]) R++;
                z[i] = R - L, R--;
            }
        }
    }
}

int main(){
    cin >> s;
    n = s.length();
    getz();
    for(register int i = 1; i < n; ++i){
        if(z[i] == n - i && maxz >= n - i) {
            cout << s.substr(0, n - i);
            return 0;
        }
        maxz = max(maxz, z[i]);
    }
    cout << "Just a legend\n";
    return 0;
}
