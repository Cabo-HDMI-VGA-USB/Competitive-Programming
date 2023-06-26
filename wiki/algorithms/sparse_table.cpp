// TITLE: Sparse table
// COMPLEXITY: O(n log(n)) preprocessing, O(1) query
// DESCRIPTION: Computes the minimum of a half open interval.

struct sptable {
	vector<vi> table;
 
	int ilog(int x) {
		return (__builtin_clzll(1ll) - __builtin_clzll(x));
	}
 
	sptable(vi& vals) {
		int n = vals.size();
		int ln= ilog(n)+1;
		table.assign(ln, vi(n));
 
		loop(i,0,n) table[0][i]=vals[i];
 
		loop(k, 1, ln) {
			loop(i,0,n) {
				table[k][i] = min(table[k-1][i],
				table[k-1][min(i + (1<<(k-1)), n-1)]);
			}
		}
	}
    
    // returns minimum of vals in range [a, b)
	int getmin(int a, int b) {
		int k = ilog(b-a);
		return min(table[k][a], table[k][b-(1<<k)]);
	}
};