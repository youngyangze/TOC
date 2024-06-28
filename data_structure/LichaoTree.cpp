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
using vpii = vector<pii>;
using dbl = deque<bool>;
using dbltrix = deque<dbl>;
using sint = stack<int>;
using tii = tuple<int, int, int>;
using ordered_set = __gnu_pbds::tree<int, __gnu_pbds::null_type, less<int>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

#define fastio ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
#define endl '\n'
#define _CRT_SECURE_NO_WARNINGS
#define all(vec) vec.begin(), vec.end()

const int INF = 0x3f3f3f3f;
const ll VINF = 2e18;
const double PI = acos(-1);

struct line {
    ll a, b;
    ll get(ll x) {
        return a * x + b;
    }
};

struct node {
    int left, right;
    ll start, end;
    line _line;
};

class liChao {
private:
    vector<node> tree;

public:
    liChao(ll start, ll end) {
        tree.push_back({ -1, -1, start, end, {0, -VINF}});
    }

    void update(int node, line v) {
        const ll start = tree[node].start, end = tree[node].end, mid = (start + end) >> 1;

        line low = tree[node]._line, high = v;
        if (low.get(start) > high.get(start)) swap(low, high);

        if (low.get(end) <= high.get(end)) {
            tree[node]._line = high;
            return;
        }

        if (low.get(mid) < high.get(mid)) {
            tree[node]._line = high;
            if (tree[node].right == -1) {
                tree[node].right = tree.size();
                tree.push_back({ -1, -1, mid + 1, end, {0, -VINF}});
            }
            update(tree[node].right, low);
        } else {
            tree[node]._line = low;
            if (tree[node].left == -1) {
                tree[node].left = tree.size();
                tree.push_back({ -1, -1, start, mid, {0, -VINF}});
            }
            update(tree[node].left, high);
        }
    }

    ll query(int node, ll x) {
        if (node == -1) return -VINF;
        const ll start = tree[node].start, end = tree[node].end, mid = (start + end) >> 1;
        if (x <= mid) return max(tree[node]._line.get(x), query(tree[node].left, x));
        else return max(tree[node]._line.get(x), query(tree[node].right, x));
    }
};
