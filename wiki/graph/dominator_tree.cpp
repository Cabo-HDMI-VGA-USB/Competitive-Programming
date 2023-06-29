// TITLE: Dominator tree
// COMPLEXITY: O(E + V)
// DESCRIPION: Builds dominator tree

vector<int> g[mxN];
vector<int> S, gt[mxN], T[mxN];
int dsu[mxN], label[mxN];
int sdom[mxN], idom[mxN], id[mxN];
int dfs_time = 0;

vector<int> bucket[mxN];
vector<int> down[mxN];

void prep(int a)
{
    S.pb(a);
    id[a] = ++dfs_time;
    label[a] = sdom[a] = dsu[a] = a;

    for (auto b: g[a]) {
        if (!id[b]) {
            prep(b);
            down[a].pb(b);
        }
        gt[b].pb(a);
    }
}

int fnd(int a, int flag = 0)
{
    if (a == dsu[a]) return a;
    int p = fnd(dsu[a], 1);
    int b = label[ dsu[a] ];
    if (id [ sdom[b] ] < id[ sdom[ label[a] ] ]) {
        label[a] = b;
    }
    dsu[a] = p;
    return (flag ? p: label[a]);
}

void build_dominator_tree(int root)
{
    prep(root);
    reverse(all(S));

    int w;
    for (int a: S) {
        for (int b: gt[a]) {
            w = fnd(b);
            if (id[ sdom[w] ] < id[ sdom[a] ]) {
                sdom[a] = sdom[w];
            }
        }
        gt[a].clear();
        if (a != root) {
            bucket[ sdom[a] ].pb(a);
        }
        for (int b: bucket[a]) {
            w = fnd(b);
            if (sdom[w] == sdom[b]) {
                idom[b] = sdom[b];
            }
            else {
                idom[b] = w;
            }
        }
        bucket[a].clear();
        for (int b: down[a]) {
            dsu[b] = a;
        }
        down[a].clear();
    }
    reverse(all(S));
    for (int a: S) {
        if (a != root) {
            if (idom[a] != sdom[a]) {
                idom[a] = idom[ idom[a] ];
            }
            T[ idom[a] ].pb(a);
        }
    }
    S.clear();
}
