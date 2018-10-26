/*
Link: http://codeforces.com/contest/1067/problem/C
Source: Codeforces Round #518 (Div. 1) [Thanks, Mail.Ru!] C. Knights

Solution 1: (Mine)
  Draw a cross, then the Knights will be like this:
        #      
      #####
      #####
     #######
      #####
      #####
        #
  When n is large, we can guarantee that number of knights will be O(n^2)
  
Solution 2: (Author's)
  Just do like this: (There are two blank lines)
   #  #  #  #  #  #  #  #  #  #
  
   
  ################################
  I can't prove it now
*/

#include<bits/stdc++.h>
typedef long long ll;
int n, cnt = 1;
int main(){
    scanf("%d", &n);
    puts("0 0");
    for(int cur = 1; cnt < n; ++cur) {
        if(++cnt <= n) printf("%d 0\n", cur);
        if(++cnt <= n) printf("0 %d\n", cur);
        if(++cnt <= n) printf("%d 0\n", -cur);
        if(++cnt <= n) printf("0 %d\n", -cur);
    }
    return 0;
}
