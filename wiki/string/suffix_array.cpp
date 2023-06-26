// TITLE: Suffix Array
// COMPLEXITY: O(n log(n)), contains big constant (around 25).
// DESCRIPTION: Computes the hash of arbitrary substrings of a given string s.

void countingsort(vi& p, vi& c) {
	int n=p.size();
	vi count(n,0);
	loop(i,0,n) count[c[i]]++;

	vi psum(n); psum[0]=0;
	loop(i,1,n) psum[i]=psum[i-1]+count[i-1];

	vi ans(n);
	loop(i,0,n)
		ans[psum[c[p[i]]]++]=p[i];
	
	p = ans;
}

vi sfa(string s) {
	s += "$";
	
	int n=s.size();
	vi p(n);
	vi c(n);
	{
		vector<pair<char, int>> a(n);
		loop(i,0,n) a[i]={s[i],i};
		sort(all(a));

		loop(i,0,n) p[i]=a[i].second;

		c[p[0]]=0;
		loop(i,1,n) {
			if(s[p[i]] == s[p[i-1]]) {
				c[p[i]]=c[p[i-1]];
			} 
			else c[p[i]]=c[p[i-1]]+1;
		}
	}

	for(int k=0; (1<<k) < n; k++) {
		loop(i, 0, n) 
			p[i] = (p[i] - (1<<k) + n) % n;

		countingsort(p,c);

		vi nc(n);
		nc[p[0]]=0;
		loop(i,1,n) {
			pii prev = {c[p[i-1]], c[(p[i-1]+(1<<k))%n]};	
			pii cur = {c[p[i]], c[(p[i]+(1<<k))%n]};	
			if (prev == cur)
				nc[p[i]]=nc[p[i-1]];
			else nc[p[i]]=nc[p[i-1]]+1;
		}
		c=nc;
	}

	return p;
}
