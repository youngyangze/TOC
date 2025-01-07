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
    line(ll a, ll b = -VINF) : a(a), b(b) {}
    ll f(ll x) { return (ll)a * x + b; }
};

struct node {
    int _left, _right, left, right;
    line _line;
};

class lichao_tree {
private:
    vector<node> tree;

public:
    int start = -2e9, end = 2e9;
    lichao_tree() { tree.push_back({-1, -1, start, end, line(0, -VINF)}); }

    void add_line(line new_line, int i = 0) {
        int left = tree[i].left, right = tree[i].right, mid = ((ll)left + right) >> 1;

        line low = tree[i]._line, high = new_line;

        if (low.f(left) >= high.f(left)) swap(low, high);

        if (low.f(right) <= high.f(right)) {
            tree[i]._line = high;
            return;
        }

        else if (low.f(mid) <= high.f(mid)) {
            tree[i]._line = high;
            if (tree[i]._right == -1) {
                tree[i]._right = tree.size();
                tree.push_back({-1, -1, mid + 1, right, line(0, -VINF)});
            }
            add_line(low, tree[i]._right);
        } else {
            tree[i]._line = low;
            if (tree[i]._left == -1) {
                tree[i]._left = tree.size();
                tree.push_back({-1, -1, left, mid, line(0, -VINF)});
            }
            add_line(high, tree[i]._left);
        }
    }

    ll query(ll x, int i = 0) {
        if (i == -1) return -VINF;
        int left = tree[i].left, right = tree[i].right, mid = ((ll)left + right) >> 1;
        if (x <= mid) return max(tree[i]._line.f(x), query(x, tree[i]._left));
        else return max(tree[i]._line.f(x), query(x, tree[i]._right));
    }

    line query2(ll x, int i = 0) {
        if (i == -1) return line(0, -VINF);
        int left = tree[i].left, right = tree[i].right, mid = ((ll)left + right) >> 1;
        if (x <= mid) {
            line _line = query2(x, tree[i]._left);
            if (_line.f(x) > tree[i]._line.f(x)) return _line;
            else return tree[i]._line;
        } else {
            line _line = query2(x, tree[i]._right);
            if (_line.f(x) > tree[i]._line.f(x)) return _line;
            else return tree[i]._line;
        }
    }
};

class offline_lichao {
private:
    vector<lichao_tree> tree;
    vector<tuple<int, int, ll, ll>> queries;
    vector<pair<int, ll>> q2;
    vll result;
    int query_index;

    void insert(int i, int start, int end, int _left, int _right, pll value) {
        if (_right < start || end < _left) return;

        if (_left <= start && end <= _right) {
            tree[i].add_line({value.first, value.second});
            return;
        }

        int mid = ((ll)start + end) >> 1;
        insert(i << 1, start, mid, _left, _right, value);
        insert((i << 1) + 1, mid + 1, end, _left, _right, value);
    }

    ll query(int i, int start, int end, int index, ll x) {
        if (!(start <= index && index <= end)) return -VINF;

        if (start == end) return tree[i].query(x);

        int mid = ((ll)start + end) >> 1;
        return max({tree[i].query(x), query(i << 1, start, mid, index, x), query((i << 1) + 1, mid + 1, end, index, x)});
    }

public:
    offline_lichao(int queries) : query_index(0), tree(4 * queries) {}

    int add_line(ll a, ll b) {
        queries.push_back({++query_index, -1, a, b});
        return queries.size() - 1;
    }

    void delete_line(int i) { get<1>(queries[i]) = ++query_index; }

    void query(ll x) { q2.push_back({++query_index, x}); }

    vll get_result() {
        for (auto [_left, _right, a, b] : queries) insert(1, 1, query_index, _left, (_right == -1 ? query_index : _right), {a, b});
        for (auto [index, x] : q2) result.push_back(query(1, 1, query_index, index, x));

        return result;
    }
};
