// TITLE: Ordered Set
// COMPLEXITY: O(log(n))
// DESCRIPION: Set but you can look witch elements is in position (k)

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>

int32_t main() {
    ordered_set o_set;

    o_set.insert(5);
    o_set.insert(1);
    o_set.insert(2);
    // o_set = {1, 2, 5}
    5 == *(o_set.find_by_order(2));
    2 == o_set.order_of_key(4); // {1, 2}
}
