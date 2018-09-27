// Multiway merge using a priority_queue
// Complexity: O(nlogk)
#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
priority_queue<pii, vector<pii>, greater<pii> > pq;
char buf[100];
int pe[3020], k;
int main(){
    while(~scanf("%s", buf) && buf[0] != '#'){
        int num; scanf("%d", &num);
        scanf("%d", &pe[num]);
        pq.push({pe[num], num});
    }
    scanf("%d", &k);
    while(k--){
        pii cur = pq.top(); pq.pop();
        printf("%d\n", cur.second);
        pq.push({cur.first + pe[cur.second], cur.second});
    }
    return 0;
}
