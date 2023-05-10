// TITLE: Set
// COMPLEXITY: Insertion Log(n)
// Description: Keeps elements sorted, remove duplicates, upper_bound, lower_bound, find, count

int main() {
  set<int> set1;

  set1.insert(1);       // O(log(n))
  set1.erase(1);        // O(log(n))

  set1.upper_bound(1);  // O(log(n))
  set1.lower_bound(1);  // O(log(n))
  set1.find(1);         // O(log(n))
  set1.count(1);        // O(log(n))

  set1.size();          // O(1)
  set1.empty();         // O(1)

  set1.clear()          // O(1)
  return 0;
}
