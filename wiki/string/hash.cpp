// TITLE: String hash
// COMPLEXITY: O(n) preprocessing, O(1) query
// DESCRIPTION: Computes the hash of arbitrary substrings of a given string s.
int m1, m2;
int n; string s;

struct Hash {
    const int P = 31;
    int n; string s;
    vector<int> h, hi, p, p2, h2, hi2;
    Hash() {}
    Hash(string s):
	s(s), n(s.size()), h(n), hi(n), p(n), h2(n), hi2(n), p2(n) {
        for (int i=0;i<n;i++) p[i] = (i ? P*p[i-1]:1) % m1;
        for (int i=0;i<n;i++) p2[i] = (i ? P*p2[i-1]:1) % m2;

        for (int i=0;i<n;i++)
            h[i] = (s[i] + (i ? h[i-1]:0) * P) % m1;
        for (int i=0;i<n;i++)
            h2[i] = (s[i] + (i ? h2[i-1]:0) * P) % m2;

        for (int i=n-1;i>=0;i--) 
            hi[i] = (s[i] + (i+1<n ? hi[i+1]:0) * P) % m1;
        for (int i=n-1;i>=0;i--) 
            hi2[i] = (s[i] + (i+1<n ? hi2[i+1]:0) * P) % m2;
    }
    int gethash(int l, int r) {
        int hash = (h[r] - (l ? h[l-1]*p[r-l+1]%m1 : 0));
        int hash2 = (h2[r] - (l ? h2[l-1]*p2[r-l+1]%m2 : 0));
        hash = hash < 0 ? hash + m1 : hash;
        hash2 = hash2 < 0 ? hash2 + m2 : hash2;
		return (hash << 30) ^ hash2;
    }
    int gethashi(int l, int r) {
        int hash = (hi[l] - (r+1 < n ? hi[r+1]*p[r-l+1] % m1 : 0));
        int hash2 = (hi2[l] - (r+1 < n ? hi2[r+1]*p2[r-l+1] % m2 : 0));
        hash= hash < 0 ? hash + m1 : hash;
        hash2= hash2 < 0 ? hash2 + m2 : hash2;
		return (hash << 30) ^ hash2;
    }
};

void solve()
{
	srand(time(0));
	m1 = rand()/10 + 1e9;
	m2 = rand()/10 + 1e9;
	Hash hasher(s);
}
