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
const int MOD = 1e9 + 7;

class HLD {
private:
	vint size, depth, parent, top, in, out, visited;
    matrix tree, inputGraph;
    int currentTime;
public:
    HLD(int n) : size(n + 1), depth(n + 1), parent(n + 1), top(n + 1),
                 in(n + 1), out(n + 1), visited(n + 1), 
                 tree(n + 1), inputGraph(n + 1), currentTime(0) {}

    void dfs(int node = 1) {
        visited[node] = 1;
        for (auto neighbor : inputGraph[node]) {
            if (visited[neighbor]) continue;
            visited[neighbor] = 1;
            tree[node].push_back(neighbor);
            dfs(neighbor);
        }
    }

    void dfs1(int node = 1) {
        size[node] = 1;
        for (auto &child : tree[node]) {
            depth[child] = depth[node] + 1;
            parent[child] = node;
            dfs1(child);
            size[node] += size[child];
            if (size[child] > size[tree[node][0]]) swap(child, tree[node][0]);
        }
    }

    void dfs2(int node = 1) {
        in[node] = ++currentTime;
        for (auto child : tree[node]) {
            top[child] = (child == tree[node][0]) ? top[node] : child;
            dfs2(child);
        }
        out[node] = currentTime;
    }

    void init(int root = 1) {
        dfs(root);
        dfs1(root);
        // top[root] = root;
        dfs2(root);
    }
};
