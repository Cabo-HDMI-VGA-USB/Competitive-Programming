#include <bits/stdc++.h>

using namespace std;

#define endl "\n"

#define int long long
#define all(x) (x).begin(), (x).end()
#define debug(x) cout << #x << ": " << x << endl

const int oo = 0x3f3f3f3f3f3f3f3f;

vector<string> split_string(const string & s, const string & sep = " ") {
    int w = sep.size();
    vector<string> ans;
    string curr;

    auto add = [&](string a) {
        if (a.size() > 0) {
            ans.push_back(a);
        }
    };
    
    for (int i = 0; i + w < s.size(); i++) {
        if (s.substr(i, w) == sep) {
            i += w-1;
            add(curr);
            curr.clear();
            continue;
        }
        curr.push_back(s[i]);
    }
    add(curr);
    return ans;
}

vector<int> parse_vector_int(string & s)
{
    vector<int> nums;
    for (string x: split_string(s)) {
        nums.push_back(stoi(x));
    }
    return nums;
}

vector<float> parse_vector_float(string & s)
{
    vector<float> nums;
    for (string x: split_string(s)) {
        nums.push_back(stof(x));
    }
    return nums;
}

void solve()
{
    string s;
    getline(cin, s);

    auto nums = parse_vector_float(s);
    for (auto x: nums) {
        cout << x << endl;
    }
}
int32_t main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t = 1;
    // cin >> t;
    while(t--) solve();
    return 0;
}
