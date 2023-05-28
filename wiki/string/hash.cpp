// TITLE: String hash
// COMPLEXITY: O(n) preprocessing, O(1) query
// DESCRIPTION: Computes the hash of arbitrary substrings of a given string s.

struct hashs
{
	string s;
	int m1, m2, n, p;
	vector<int> p1, p2, sum1, sum2;

	hashs(string s) : s(s), n(s.size()), p1(n + 1), p2(n + 1), sum1(n + 1), sum2(n + 1)
	{
		srand(time(0));
		p = 31;
		m1 = rand() / 10 + 1e9; // 1000253887;
		m2 = rand() / 10 + 1e9; // 1000546873;

		p1[0] = p2[0] = 1;
		loop(i, 1, n + 1)
		{
			p1[i] = (p * p1[i - 1]) % m1;
			p2[i] = (p * p2[i - 1]) % m2;
		}

		sum1[0] = sum2[0] = 0;
		loop(i, 1, n + 1)
		{
			sum1[i] = (sum1[i - 1] * p) % m1 + s[i - 1];
			sum2[i] = (sum2[i - 1] * p) % m2 + s[i - 1];
			sum1[i] %= m1;
			sum2[i] %= m2;
		}
	}

	// hash do intervalo [l, r)
	int gethash(int l, int r)
	{
		int c1 = m1 - (sum1[l] * p1[r - l]) % m1;
		int c2 = m2 - (sum2[l] * p2[r - l]) % m2;
		int h1 = (sum1[r] + c1) % m1;
		int h2 = (sum2[r] + c2) % m2;
		return (h1 << 30) ^ h2;
	}
};