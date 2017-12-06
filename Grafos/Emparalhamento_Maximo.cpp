#include <bits/stdc++.h>
#define mp(a, b) make_pair(a, b)

using namespace std;

typedef vector <int> vi;
typedef pair <int, int> ii;

vi match, vis;
vector < vi > ladj;
int V;

int Aug(int node){
    if (vis[node]) return 0;
    vis[node] = 1;
    for(int i = 0; i < ladj[node].size(); i++){
        int vizinho = ladj[node][i];
        if(match[vizinho] == -1 || Aug(match[vizinho])){
            match[vizinho] = node;
            return 1;
        }
    }
    return 0;
}

int main(){
    int ans = 0;
    match.assign(V, -1);
    int verticesDoSet1;
    for(int i = 0; i < verticesDoSet1; i++){
        vis.assign(V, 0);
        ans += Aug(i);
    }
    printf("%d\n", ans);
    return 0;
}