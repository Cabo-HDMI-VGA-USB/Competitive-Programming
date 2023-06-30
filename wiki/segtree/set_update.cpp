// TITLE: Set and update lazy seg
// COMPLEXITY: O(log(n)) query and update
// DESCRIPTION: Sum segtree with set and update

vector<int> lazy, opvec;
vector<int> seg;
 
constexpr int SET = 30;
constexpr int ADD = 31;
 
int segsize;
 
void propagate(int no, int lx, int rx) {
	if (lazy[no] == -1) return;
 
	if (rx-lx == 1) {
		if(opvec[no] == SET) seg[no] = lazy[no];
		else seg[no] += lazy[no];
 
		lazy[no]=-1;
		opvec[no]=-1;
		return;
	}
 
	if(opvec[no] == SET) {
		seg[no] = (rx-lx) * lazy[no];
		lazy[2*no+1] = lazy[no];
		lazy[2*no+2] = lazy[no];
 
		opvec[2*no+1] = SET;
		opvec[2*no+2] = SET;
 
		lazy[no] = -1;
		opvec[no]=-1;
		return;
	}
	
	seg[no] += (rx-lx) * lazy[no];
	if (lazy[2*no+1] == -1) {
		lazy[2*no+1] = 0;
		opvec[2*no+1] = ADD;
	}
	if (lazy[2*no+2] == -1) {
		lazy[2*no+2] = 0;
		opvec[2*no+2] = ADD;
	}
	lazy[2*no+1] += lazy[no];
	lazy[2*no+2] += lazy[no];
 
	lazy[no] = -1;
	opvec[no]=-1;
}
 
void update(int l, int r, int val, int op, int no=0, int lx=0, int rx=segsize) {
	propagate(no, lx, rx);
	if (r <= lx or l >= rx) return;
	if (lx >= l and rx <= r) {
		lazy[no] = val;
		opvec[no] = op;
		propagate(no, lx, rx);
		return;
	}
 
	int mid = (rx+lx)/2; 
	update(l, r, val, op, 2*no+1, lx, mid);
	update(l, r, val, op, 2*no+2, mid, rx);
	seg[no] = seg[2*no+1]+seg[2*no+2];
}
 
int query(int l, int r, int no=0, int lx=0, int rx=segsize) {
	propagate(no, lx, rx);
	if (r <= lx or l >= rx) return 0;
	if (lx >= l and rx <= r) return seg[no];
 
	int mid = (rx+lx)/2; 
	return
		query(l,r,2*no+1,lx,mid) +
		query(l,r,2*no+2, mid, rx);
}