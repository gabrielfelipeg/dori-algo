#include <map>
#include <cmath>
using namespace std;

/*
 * Baby Steps Algorithm for Discrete Logarithm
 */

template <typename T>
T baby (T a, T b, T m) {
	a %= m; b %= m;
	T n = (T) sqrt (m + .0) + 1, an = 1;
	for (T i=0; i<n; ++i) an = (an * a) % m;
	map<T, T> vals;
	for (T i=1, cur=an; i<=n; ++i) {
		if (!vals.count(cur)) vals[cur] = i;
		cur = (cur * an) % m;
	}
	for (T i=0, cur=b; i<=n; ++i) {
		if (vals.count(cur)) {
			T ans = vals[cur] * n - i;
			if (ans < m) return ans;
		}
		cur = (cur * a) % m;
	}
	return -1;
}