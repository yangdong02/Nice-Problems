// ans = min( \sum x^2 + \sum y^2 - 2*\sum x*y + n*c^2 -2c\sum(x-y) )
// 前两项定值，后两项是二次函数，中间求卷积。把x反转并加倍，求出x[n+1...2*n]系数中最大值即可。
#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;


const int maxn = 50050, FFT_MAXN = 400400;

struct comp {
    double re, im;
    comp(double x = 0, double y = 0): re(x), im(y) { }
    comp operator + (const comp& c) { return comp(re+c.re, im+c.im); }
    comp operator - (const comp& c) { return comp(re-c.re, im-c.im); }
    comp operator * (const comp& c) { return comp(re*c.re-im*c.im, re*c.im+im*c.re); }
    comp operator / (double v) { return comp(re / v, im / v); }
} A[FFT_MAXN], B[FFT_MAXN];
int n, m, l, r[FFT_MAXN], lim;
double a[maxn * 2], b[maxn * 2], tota, totb, asqr, bsqr, diff;
double ans1, ans2 = 1e18, ans3 = 0;
const double Pi = 3.1415926535897932384626;

void fft(comp* x, int dft) {
    for(int i = 0; i < lim; ++i) if(i < r[i]) swap(x[i], x[r[i]]);
    for(int mid = 1; mid < lim; mid <<= 1) {
        comp wn(cos(Pi / mid), sin(Pi / mid) * dft);
        for(int len = mid << 1, j = 0; j < lim; j += len) {
            comp w(1, 0);
            for(int k = 0; k < mid; ++k, w = w * wn) {
                comp p = x[j + k], q = w * x[j + k + mid];
                x[j + k] = p + q;
                x[j + k + mid] = p - q;
            }
        }
    }
    if(dft == -1) for(int i = 0; i < lim; ++i) x[i] = x[i] / lim;
}
void fft_pmul(comp* x, int degA, comp* y, int degB) {
    lim = 1, l = 0;
    while(degA + degB >= lim) lim <<= 1, l++;
    for(int i = 0; i < lim; ++i)
        r[i] = (r[i >> 1] >> 1) | ( (i & 1) << (l - 1) );
    fft(x, 1);
    fft(y, 1);
    for(int i = 0; i < lim; ++i) x[i] = x[i] * y[i];
    fft(x, -1);
} 

int main() {
    scanf("%d%d", &n, &m);
    rep(i, n) scanf("%lf", &a[i]), tota += a[i], asqr += a[i] * a[i];
    rep(i, n) scanf("%lf", &b[i]), totb += b[i], bsqr += b[i] * b[i];
    
    ans1 = asqr + bsqr, diff = tota - totb;	
    double c = diff / n;
    for(int i = c - 5; i <= c + 8; ++i)
        ans2 = min(ans2, n * i * i - 2 * i * diff);
        
    reverse(a + 1, a + n + 1);
    for(int i = n + 1; i <= 2 * n; ++i) a[i] = a[i - n];
    for(int i = 1; i <= 2 * n; ++i) A[i].re = a[i], B[i].re = b[i];
    fft_pmul(A, 2 * n, B, 2 * n);
    for(int i = n + 1; i <= 2 * n; ++i)
        ans3 = max(ans3, A[i].re);
        
    double ans = ans1 - 2 * ans3 + ans2;
    printf("%lld\n", (long long) (ans + 0.5));

    return 0;
}
