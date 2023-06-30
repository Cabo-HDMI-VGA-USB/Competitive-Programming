// TITLE: Persistent sum segment tree
// COMPLEXITY: O(log(n)) query and update, O(k log(n)) memory, n = number of elements, k = number of operations
// DESCRIPTION: Sum segment tree which preserves its history.

int segsize;
 
struct node {
	int val;
	int lx, rx;
	node *l=0, *r=0;
	
	node() {}
	node(int val, int lx, int rx, node *l, node *r) : 
	val(val), lx(lx),rx(rx),l(l),r(r) {}
};
 
node* build(vi& arr, int lx=0, int rx=segsize) {
	if (rx - lx == 1) {
		if (lx < (int)arr.size()) {
			return new node(arr[lx], lx, rx, 0, 0);
		}
 
		return new node(0,lx,rx,0,0);
	}
 
	int mid = (lx+rx)/2;
	auto nol = build(arr, lx, mid);
	auto nor = build(arr, mid, rx);
	return new node(nol->val + nor->val, lx, rx, nol, nor);
}
 
node* update(int idx, int val, node *no) {
	if (idx < no->lx or idx >= no->rx) return no;
	if (no->rx - no->lx == 1) {
		return new node(val+no->val, no->lx, no->rx, no->l, no->r);
	}
 
	auto nol = update(idx, val, no->l);
	auto nor = update(idx, val, no->r);
	return new node(nol->val + nor->val, no->lx, no->rx, nol, nor);
}
 
int query(int l, int r, node *no) {
	if (r <= no->lx or no->rx <= l) return 0;
	if (l <= no->lx and no->rx <= r) return no->val;
 
	return query(l,r,no->l) + query(l,r,no->r);
} 