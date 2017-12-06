#include<bits/stdc++.h>
#define V 6 // qtd vertices

using namespace std;
 
struct edge{
    int v, flow, capacity, reverse;
};
 

vector <edge> ladj[V];
int level[V];

void addEdge(int u, int v, int C){
    // Forward edge : 0 flow and C capacity
    edge a{v, 0, C, (int)ladj[v].size()};

    // Back edge : 0 flow and 0 capacity
    edge b{u, 0, 0, (int)ladj[u].size()};

    ladj[u].push_back(a);
    ladj[v].push_back(b); // reverse edge
}

bool BFS(int s, int t){
    for (int i = 0 ; i < V ; i++)
        level[i] = -1;
 
    level[s] = 0;
 
    list< int > q;
    q.push_back(s);

    while (!q.empty()){
        int u = q.front();
        q.pop_front();
        
        for (auto i : ladj[u]){
            if (level[i.v] < 0  && i.flow < i.capacity){
                level[i.v] = level[u] + 1;
                q.push_back(i.v);
            }
        }
    }
    return level[t] < 0 ? false : true ;
}
 
int sendFlow(int u, int flow, int t, int start[]){
    if (u == t)
        return flow;
 
    for (  ; start[u] < ladj[u].size(); start[u]++){
        
        edge &e = ladj[u][start[u]]; 
                                     
        if (level[e.v] == level[u]+1 && e.flow < e.capacity){

            int curr_flow = min(flow, e.capacity - e.flow);
 
            int temp_flow = sendFlow(e.v, curr_flow, t, start);
 
            if (temp_flow > 0){
                
                e.flow += temp_flow;
 
                ladj[e.v][e.reverse].flow -= temp_flow;
                return temp_flow;
            }
        }
    }
    return 0;
}
 
int DinicMaxflow(int s, int t){
    if (s == t)
        return -1;
 
    int total = 0;
    while (BFS(s, t) == true){ // Cria o LevelGraph

        int start[V + 1];
        memset(start, 0, sizeof start);
 
        while (int flow = sendFlow(s, INT_MAX, t, start))

            total += flow;
    }
    return total;
}

int main(){
    addEdge(0, 1, 16 );
    addEdge(0, 2, 13 );
    addEdge(1, 2, 10 );
    addEdge(1, 3, 12 );
    addEdge(2, 1, 4 );
    addEdge(2, 4, 14);
    addEdge(3, 2, 9 );
    addEdge(3, 5, 20 );
    addEdge(4, 3, 7 );
    addEdge(4, 5, 4);
    cout << "Maximum flow " << DinicMaxflow(0, 5) << endl;
    return 0;
}