// TITLE: Lazy SegTree
// COMPLEXITY: O(log(n)) query and update
// DESCRIPTION: Sum segment tree with range sum update.
vector<int> seg, lazy;
int segsize;

// change 0s to -1s if update is
// set instead of add. also,
// remove the +=s
void prop(int no, int lx, int rx) {
    if (lazy[no] == 0) return;

    seg[no]+=(rx-lx)*lazy[no];
    if(rx-lx>1) {
        lazy[2*no+1] += lazy[no];
        lazy[2*no+2] += lazy[no];
    }

    lazy[no]=0;
}

void update(int l, int r, int val,int no=0, int lx=0, int rx=segsize) {
    // l r lx rx
    prop(no, lx, rx);
    if (r <= lx or rx <= l) return;
    if (l <= lx and rx <= r) {
        lazy[no]=val;
        prop(no,lx,rx);
        return;
    }

    int mid=lx+(rx-lx)/2;
    update(l,r,val,2*no+1,lx,mid);
    update(l,r,val,2*no+2,mid,rx);
    seg[no] =seg[2*no+1]+seg[2*no+2];
}

int query(int l,int r,int no=0,int lx=0, int rx=segsize) {
    prop(no,lx,rx);
    if (r <= lx or rx <= l) return 0;
    if (l <= lx and rx <= r) return seg[no];

    int mid=lx+(rx-lx)/2;
    return query(l,r,2*no+1, lx, mid)+
           query(l,r,2*no+2,mid,rx);
}

signed main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

    int n;cin>>n;
    segsize=n;
    if(__builtin_popcount(n) != 1) {
        segsize=1+(int)log2(segsize);
        segsize= 1<<segsize;
    }

    seg.assign(2*segsize-1, 0);
    // use -1 instead of 0 if
    // update is set instead of add
    lazy.assign(2*segsize-1, 0);
}