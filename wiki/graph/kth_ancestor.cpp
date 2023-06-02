// TITLE: Kth Ancestor
// COMPLEXITY: O(n * log(n))
// DESCRIPTION: Preprocess, then find in log n

const int LOG_N = 30;
int get_kth_ancestor(vector<vector<int>> & up, int v, int k)
{
    for (int j = 0; j < LOG_N; j++) {
        if (k & ((int)1 << j)) {
            v = up[v][j];
        }
    }
    return v;
}

void solve()
{
    vector<vector<int>> up(n, vector<int>(LOG_N));

    for (int i = 0; i < n; i++) {
        up[i][0] = parents[i];
        for (int j = 1; j < LOG_N; j++) {
            up[i][j] = up[up[i][j-1]][j-1];
        }
    }
    cout << get_kth_ancestor(up, x, k) << endl;

}
