#include <bits/stdc++.h>

using namespace std;

const int N = 1000 * 1000;

vector< pair<int,int> > primeFactor;
int lP[N]; // least prime , linear sive can be help with this
vector <int> divisor;

void recursive_walk(int pos, int curd) {
	if (pos == int(primeFactor.size())) {
        divisor.push_back(curd);
		return;
	}
	int curm = 1;
	for (int i = 0; i <= primeFactor[pos].second; ++i) {
		recursive_walk(pos + 1, curd * curm);
		curm *= primeFactor[pos].first;
	}
}

void dividir(int value) {
	primeFactor.clear();
	while (value > 1) {
		int d = lP[value];
		if (!primeFactor.empty() && primeFactor.back().first == d) {
			++primeFactor.back().second;
		} else {
			primeFactor.push_back(make_pair(d, 1));
		}
		value /= d;
	}
	recursive_walk(0, 1);
}

int main(){

    return 0;
}