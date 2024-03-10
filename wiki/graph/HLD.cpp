// TITLE: HLD
// COMPLEXITY: O(log^2(n)) per query, O(log(n)) per update.
// DESCRIPTION: Non-Commutative Heavy-Light-Decomposition.

struct HLD {
	vvi g;
	int rt,n, dt;
	vi hv, ti,to, hd, p, ssz;
	SegTree seg;
	HLD(vvi _g, int _rt=0) :
		g(_g),rt(_rt),n(g.size()),dt(0),
		hv(n),ti(n),to(n),hd(n),p(n), ssz(n),seg(n)
	{
		dfs1(rt,rt);
		dfs2(rt,rt);
	}

	void dfs1(int a, int pai) {
		p[a]=pai;
		ssz[a]=1;

		pii hc(-1,-1);
		for (auto b:g[a]) if(b!=pai) {
			dfs1(b,a);
			hc=max(hc, pii(ssz[b], b));
			ssz[a]+= ssz[b];
		}
		hv[a]=hc.second;
	}

	void dfs2(int a, int h) {
		hd[a]=h;
		ti[a]=dt++;
		if (hv[a] != -1) dfs2(hv[a], h);
		for (auto b:g[a]) if (b != p[a] and b != hv[a])
			dfs2(b, b);
		to[a]=dt;
	}

	bool isa(int a, int b) {
		return ti[a] <= ti[b] and to[a]>=to[b];
	}

	// if seg.merge is commutative then queryI can be replaced by query.	
	S query(int a, int b) {
		// SegTree identity		
		auto a1=Info::id(), a2=Info::id();

		while(!isa(hd[a], b)) {
			a1=seg.merge(a1, seg.queryI(ti[hd[a]], ti[a]+1));
			a=p[hd[a]];
		}

		while(!isa(hd[b], a)) {
			a2=seg.merge(seg.query(ti[hd[b]], ti[b]+1), a2);
			b=p[hd[b]];
		}
		if (isa(a,b)) {
			a2=seg.merge(seg.query(ti[a], ti[b]+1), a2);
			return seg.merge(a1, a2);
		} else {
			a1=seg.merge(a1, seg.queryI(ti[b], ti[a]+1));
			return seg.merge(a1, a2);
		}
	}

	void update(int a, char c) {
		// Remember that "update" must update the inverse seg as well.
		seg.update(ti[a], c);
	}
};
