// TITLE: Binary Indexed Tree
// COMPLEXITY: O(log(n)) query and update
// DESCRIPTION: Range sum queries with point update. One-indexed.

struct BIT{
    #define lowbit(x) ( x & -x )
    int n;
    vi b;
 
    BIT( int n ) : n(n) , b(n+1 , 0){};
	BIT( vi &c ){
        n = c.size() , b = c;
        for( int i = 1 , fa = i + lowbit(i) ; i <= n ;
		i ++ , fa = i + lowbit(i) )
            if( fa <= n ) b[fa] += b[i];
    }
    void add( int i , int y ){
        for( ; i <= n ; i += lowbit(i) ) b[i] += y;
    }
 
    int calc( int i ){
        int sum = 0;
        for( ; i ; i -= lowbit(i) ) sum += b[i];
        return sum;
    }
};
