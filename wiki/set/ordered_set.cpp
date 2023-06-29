// TITLE: Ordered Set
// COMPLEXITY: log n
// DESCRIPTION: Worst set with adtional operations


#include <bits/extc++.h>
using namespace __gnu_pbds; // or pb_ds;
template<typename T, typename B = null_type>
using ordered_set = tree<T, B, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int32_t main() {
    ordered_set<int> oset;

    oset.insert(5);
    oset.insert(1);
    oset.insert(2);
    // o_set = {1, 2, 5}
    5 == *(oset.find_by_order(2)); // Like an array index
    2 == oset.order_of_key(4); // How many elements are strictly less than 4
}
