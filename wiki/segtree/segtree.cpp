// TITLE: Standard SegTree
// COMPLEXITY: O(log(n)) query and update
// DESCRIPTION: Sum segment tree with point update.

using type = int;

type iden = 0;
vector<type> seg;
int segsize;

type func(type a, type b)
{
	return a + b;
}

// query do intervalo [l, r)
type query(int l, int r, int no = 0, int lx = 0, int rx = segsize)
{
	// l lx rx r
	if (r <= lx or rx <= l)
		return iden;
	if (l <= lx and rx <= r)
		return seg[no];

	int mid = lx + (rx - lx) / 2;
	return func(query(l, r, 2 * no + 1, lx, mid),
				query(l, r, 2 * no + 2, mid, rx));
}

void update(int dest, type val, int no = 0, int lx = 0, int rx = segsize)
{
	if (dest < lx or dest >= rx)
		return;
	if (rx - lx == 1)
	{
		seg[no] = val;
		return;
	}

	int mid = lx + (rx - lx) / 2;
	update(dest, val, 2 * no + 1, lx, mid);
	update(dest, val, 2 * no + 2, mid, rx);
	seg[no] = func(seg[2 * no + 1], seg[2 * no + 2]);
}

signed main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	segsize = n;
	if (__builtin_popcount(n) != 1)
	{
		segsize = 1 + (int)log2(segsize);
		segsize = 1 << segsize;
	}
	seg.assign(2 * segsize - 1, iden);

	loop(i, 0, n)
	{
		int x;
		cin >> x;
		update(i, x);
	}
}