/*
  Link: https://codeforces.com/problemset/problem/1088/D
  Source: Codeforces Round 525 (Div 2)
  Date: 2018-12-5
  Status: Accepted (+)
  Difficulty: 1800
  Tag: Interactive, Constructive
  Solution:
    交互题，只要认真分析，就能发现，按位次从高到低考虑a和b，
    如果已知剩下位数的大小关系，就可以用两次询问确定这一位a
    和b分别的取值，以及这一位之后的a与b的大小关系。因此可以
    先询问一次获得a,b大小关系，再用上面的方法即可使用61次询
    问完成任务。
*/

#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;

inline int query(int a, int b) {
    printf("? %d %d\n", a, b);
    fflush(stdout);
    int reply;
    scanf("%d", &reply);
    if(reply == -2) exit(0);
    return reply;
}

int x = 0, y = 0, sgn;

int main() {
    sgn = query(0, 0);
    for(int i = 29; i >= 0; --i) {
        int ask1 = query(x ^ (1 << i), y);
        int ask2 = query(x, y ^ (1 << i));
        if(ask1 == ask2) {
            if(sgn == 1) x ^= (1 << i);
            else y ^= (1 << i);
            sgn = ask1;
        } else if(ask1 == -1) {
            x ^= (1 << i);
            y ^= (1 << i);
        }
    }
    printf("! %d %d\n", x, y);
    fflush(stdout);
    return 0;
}
