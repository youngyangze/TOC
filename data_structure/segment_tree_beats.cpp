#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using vint = vector<int>;
using matrix = vector<vint>;
using vll = vector<ll>;
using vull = vector<ull>;
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
#define rall(vec) vec.rbegin(), vec.rend()

const int INF = 0x3f3f3f3f;
const int SEMI_INF = 0x3f3f;
const double PI = acos(-1);

struct nodes {
    ll max, max2, maxCount, sum;
};

nodes merge(nodes a, nodes b) {
    if (a.max == b.max) return {a.max, max(a.max2, b.max2), a.maxCount + b.maxCount, a.sum + b.sum};
    if (a.max > b.max) swap(a, b);
    return {b.max, max(a.max, b.max2), b.maxCount, a.sum + b.sum};
}

class segmentTreeBeats {
    private:
    vll arr;
    vector<nodes> tree;

    public:
    segmentTreeBeats(vll a, ll n) {
        arr = a;
        tree.resize(n << 2);
    }

    void push(ll node, ll start, ll end) {
        if (start == end) return;
        for (auto i : {node << 1, (node << 1) + 1}) {
            if (tree[node].max < tree[i].max) {
                tree[i].sum -= tree[i].maxCount * (tree[i].max - tree[node].max);
                tree[i].max = tree[node].max;
            }
        }
    }

    nodes init(ll node, ll start, ll end) {
        if (start == end) return tree[node] = {arr[start], -1, 1, arr[start]};
        const ll mid = (start + end) >> 1;
        return tree[node] = merge(init(node << 1, start, mid), init((node << 1) + 1, mid + 1, end));
    }

    void update(ll node, ll start, ll end, ll left, ll right, ll value) {
        push(node, start, end);
        if (right < start || end < left || tree[node].max <= value) return;
        if (left <= start && end <= right && tree[node].max2 < value) {
            tree[node].sum -= tree[node].maxCount * (tree[node].max - value);
            tree[node].max = value;
            push(node, start, end);
            return;
        }
        const ll mid = (start + end) >> 1;
        update(node << 1, start, mid, left, right, value);
        update((node << 1) + 1, mid + 1, end, left, right, value);
        tree[node] = merge(tree[node << 1], tree[(node << 1) + 1]);
    }

    ll getMax(ll node, ll start, ll end, ll left, ll right) {
        push(node, start, end);
        if (right < start || end < left) return 0;
        if (left <= start && end <= right) return tree[node].max;
        const ll mid = (start + end) >> 1;
        return max(getMax(node << 1, start, mid, left, right), getMax((node << 1) + 1, mid + 1, end, left, right));
    }

    ll getSum(ll node, ll start, ll end, ll left, ll right) {
        push(node, start, end);
        if (right < start || end < left) return 0;
        if (left <= start && end <= right) return tree[node].sum;
        const ll mid = (start + end) >> 1;
        return getSum(node << 1, start, mid, left, right) + getSum((node << 1) + 1, mid + 1, end, left, right);
    }
};
