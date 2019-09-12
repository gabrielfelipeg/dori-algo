#include <bits/stdc++.h>
#define MAX 10000007

using namespace std;
 
const int N = 10000000;
int lp[N+1];
vector<int> pr;
void crivo(){
    for (int i=2; i<=N; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.push_back (i);
        }
        for (int j=0; j<(int)pr.size() && pr[j]<=lp[i] && i*pr[j]<=N; ++j)
            lp[i * pr[j]] = pr[j];
    }
}
int main(){
    crivo();
    return 0;
}