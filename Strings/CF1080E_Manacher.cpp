/*
  Link: https://codeforces.com/contest/1080/problem/E
  Source: Codeforces Round 524
  Date: 2018-11-29
  Status: Upsolve / Accepted
  Difficulty: 2400
  Tag: Manacher, Palindrome, String, Hash
  Solution:
    1. 先预处理出每一行[1, r]列中各个字母出现次数(cnt)，以及出现奇数次字母的位置
      （这里压缩到num数组内）
    2. 枚举子矩阵的左右边界，处理出这n行的奇偶性，判断它们是否可化为一个等价类，
       然后把这n行当做一个长度为n的字符串，每一行为一个字符，直接Manacher
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<bitset>
#define ll long long
using namespace std;

const int N = 260;

int n, m, cnt[N << 1][N][27], len[N << 1], odd[N << 1];
int num[N << 1][N];
char s[N][N];

bool cmp(int L, int R, int x, int y) {
    if (odd[x] > 1 || odd[y] > 1) return false;
    for (int k = 1; k <= 26; ++k)
        if (cnt[x][R][k] - cnt[x][L - 1][k] != cnt[y][R][k] - cnt[y][L - 1][k]) 
            return false;
    return true;
}

int cal(int l, int r) {
    len[1] = 1; int pos = 1, R = 1;
    int res = 0;
    for (int i = 2; i <= 2 * n + 1; ++i) {
        if (i <= R) {
            if (len[2 * pos - i] < R - i + 1) len[i] = len[2 * pos - i];
            else {
                len[i] = R - i + 1;
                while (i + len[i] <= 2 * n + 1 && i - len[i] && cmp(l, r, i + len[i], i - len[i]))
                    R++, len[i]++, pos = i;
            }
        } else {
            len[i] = 1;
            while (i + len[i] <= 2 * n + 1 && i - len[i] && cmp(l, r, i + len[i], i - len[i]))
                R++, len[i]++, pos = i;
        }
        if (odd[i] <= 1) res += len[i] / 2;
    }
     // printf("%d\n", res);
    return res;
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i)
        scanf("%s", s[i] + 1);
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j) {
            for(int k = 1; k <= 26; ++k)
                cnt[i << 1][j][k] = cnt[i << 1][j - 1][k];
            cnt[i << 1][j][s[i][j] - 'a' + 1]++;
            num[i << 1][j] = num[i << 1][j - 1] ^ (1 << (s[i][j] - 'a' + 1));
        }
    int ans = 0;
    for(int i = 1; i <= m; ++i)
        for(int j = 1; j <= i; ++j) {
            int tmp;
            for(int k = 1; k <= n; ++k) {
                tmp = num[k << 1][j - 1] ^ num[k << 1][i];
                odd[k << 1] = __builtin_popcount(tmp);
            }
            // printf("%d %d :", j, i);
            ans += cal(j, i);
        }
    printf("%d\n", ans);
}
