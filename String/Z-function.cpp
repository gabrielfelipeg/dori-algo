#include<bits/stdc++.h>

using namespace std;

void getZarr(string str, int Z[]){
    int n = str.length();
    int L, R, k;
 
    L = R = 0;
    for (int i = 1; i < n; ++i){
        if (i > R){
            L = R = i;
            while (R<n && str[R-L] == str[R]) R++;
            Z[i] = R-L;
            R--;
        }
        else{
            k = i-L;
            if (Z[k] < R-i+1) Z[i] = Z[k];
            else{
                L = i;
                while (R<n && str[R-L] == str[R]) R++;
                Z[i] = R-L;
                R--;
            }
        }
	}
	Z[0] = str.size();
}

int main(){
	string txt;
	cin >> txt;
	int Z[txt.size() + 1];
	getZarr(txt, Z);
	return 0;
} 
