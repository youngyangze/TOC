#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
using vint = vector<int>;
using matrix = vector<vint>;
using vll = vector<ll>;
using matrlx = vector<vll>;
using fourdimensionalMatrix = vector<matrix>; // ;;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vpii = vector<pii>;
using vpll = vector<pll>;
using dbl = deque<bool>;
using dbltrix = deque<dbl>;
using sint = stack<int>;
using tii = tuple<int, int, int>;
using ordered_set = __gnu_pbds::tree<int, __gnu_pbds::null_type, less<int>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

#define fastio ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
#define endl '\n'
#define _CRT_SECURE_NO_WARNINGS
#define all(vec) vec.begin(), vec.end()
#define rall(vec) vec.rbegin(), vec.rend()

const int INF = 0x3f3f3f3f;
const ll VINF = 2e18;
const double PI = acos(-1);

struct node {
    ll length, fail, count;
    vint edge;

    node(ll length) : length(length), fail(0), count(0), edge(26, 0) {}
};

class palindrome_tree {
private:
    vector<node> tree;
    string s;
    ll total, last;

    ll get_fail(ll x, ll position) {
        while (position - tree[x].length - 1 < 0 || s[position - tree[x].length - 1] != s[position]) x = tree[x].fail;
        return x;
    }

public:
    palindrome_tree() {
        tree.emplace_back(0);
        tree.emplace_back(-1);
        tree[0].fail = 1;
        s.push_back('$');
        total = 1;
        last = 0;
    }

    void add_character(char c) {
        s.push_back(c);
        ll current = get_fail(last, s.size() - 1);

        if (!tree[current].edge[c - 'a']) {
            ll now = ++total;
            tree.emplace_back(tree[current].length + 2);
            tree[now].fail = tree[get_fail(tree[current].fail, s.size() - 1)].edge[c - 'a'];
            tree[current].edge[c - 'a'] = now;
        }

        last = tree[current].edge[c - 'a'];
        tree[last].count++;
    }

    void count_occurrences() {
        for (ll i = total; i > 0; i--) tree[tree[i].fail].count += tree[i].count;
    }

    ll max_occurrence() {
        ll ret = 0;
        for (ll i = 2; i <= total; i++) ret = max(ret, tree[i].length * tree[i].count);
        return ret;
    }
};
