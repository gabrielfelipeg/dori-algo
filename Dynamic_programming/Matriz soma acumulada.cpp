#include<bits/stdc++.h>
#define max 5050

using namespace std;

int mat[max][max];
int aux[max][max];

int preProcess(int N){
	int M = N;
   for (int i=0; i<N; i++)
      aux[0][i] = mat[0][i];
 
   for (int i=1; i<M; i++)
      for (int j=0; j<N; j++)
         aux[i][j] = mat[i][j] + aux[i-1][j];
    for (int i=0; i<M; i++)
      for (int j=1; j<N; j++)
         aux[i][j] += aux[i][j-1];
}
 
int sumQuery(int tli, int tlj, int rbi, int rbj){
    int res = aux[rbi][rbj];
    if (tli > 0)
       res = res - aux[tli-1][rbj];
 	if (tlj > 0)
       res = res - aux[rbi][tlj-1];
 	if (tli > 0 && tlj > 0)
       res = res + aux[tli-1][tlj-1];
    return res;
}

int main(){
	
	return 0;
}
