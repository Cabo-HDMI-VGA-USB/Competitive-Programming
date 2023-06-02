// TITLE: Parsing Functions

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
    cin.ignore();
    string s;
    getline(cin, s);

    auto nums = parse_vector_float(s);
    for (auto x: nums) {
        cout << x << endl;
    }
}
