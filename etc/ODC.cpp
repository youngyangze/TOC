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
#define rall(vec) vec.rbegin(), vec.rend()

const int INF = 0x3f3f3f3f;
const ll VINF = 2e18;
const double PI = acos(-1);

vector<vpii> segmentTree;
vint parent, ranks;
vpii history;

void init(int size) {
    parent.resize(size + 1);
    ranks.resize(size + 1, 0);
    for (int i = 1; i <= size; i++) parent[i] = i;
}

int find(int x) {
    while (x != parent[x]) x = parent[x];
    return x;
}

bool _union(int u, int v) {
    int _u = find(u), _v = find(v);
    if (_u == _v) return false;
    if (ranks[_u] > ranks[_v]) swap(_u, _v);
    history.push_back({_u, _v});
    parent[_u] = _v;
    if (ranks[_u] == ranks[_v]) ranks[_v]++;
    return true;
}

void rollback() {
    auto [u, v] = history.back();
    history.pop_back();
    parent[u] = u;
    if (ranks[u] == ranks[v] - 1) ranks[v]--;
}

void update(int node, int start, int end, int left, int right, pii edge) {
    if (right < start || end < left) return;
    if (left <= start && end <= right) {
        segmentTree[node].push_back(edge);
        return;
    }
    const int mid = (start + end) >> 1;
    update(node << 1, start, mid, left, right, edge);
    update((node << 1) + 1, mid + 1, end, left, right, edge);
}
