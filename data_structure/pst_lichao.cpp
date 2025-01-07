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
const ll VINF = 1e18;
const double PI = acos(-1);

struct line {
    ll a, b;

    line(ll a = 0, ll b = -INF) : a(a), b(b) {}
    ll f(ll x) const {
        return a * x + b;
    }
};

struct node {
    int left, right;
    ll _left, _right;
    line _line;

    node(int left = -1, int right = -1, ll _left = -INF, ll _right = INF, line _line = line()) : left(left), right(right), _left(_left), _right(_right), _line(_line) {}
};

class pst_lichao {
private:
    vector<node> tree;
    map<int, vector<pair<int, node>>> changes;
    int version = 0;

    void add_line(line new_line, int i = 0) {
        ll _left = tree[i]._left, _right = tree[i]._right;
        const ll mid = (_left + _right) >> 1;

        changes[version].push_back({i, tree[i]});

        line low = tree[i]._line, high = new_line;
        if (low.f(_left) >= high.f(_left)) swap(low, high);

        if (low.f(_right) <= high.f(_right)) tree[i]._line = high;
        else if (low.f(mid) <= high.f(mid)) {
            tree[i]._line = high;
            if (tree[i].right == -1) {
                tree[i].right = tree.size();
                tree.emplace_back(-1, -1, mid + 1, _right, line());
            }
            add_line(low, tree[i].right);
        } else {
            tree[i]._line = low;
            if (tree[i].left == -1) {
                tree[i].left = tree.size();
                tree.emplace_back(-1, -1, _left, mid, line());
            }
            add_line(high, tree[i].left);
        }
    }

public:
    pst_lichao() {
        tree.emplace_back(-1, -1, -INF, INF, line());
    }

    void add_line(ll a, ll b) {
        add_line(line(a, b), 0);
        version++;
    }

    void delete_last() {
        for (auto &[i, old_node] : changes[--version]) tree[i] = old_node;
        changes.erase(version);
    }

    ll query(ll x, int i = 0) {
        return (i == -1 ? -VINF : max(tree[i]._line.f(x), query(x, (x <= (tree[i]._left + tree[i]._right) / 2 ? tree[i].left : tree[i].right))));
    }

    bool is_empty() {
        return version == 0;
    }
};
