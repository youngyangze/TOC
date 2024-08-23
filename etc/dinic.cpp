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

const int INF = 0x3f3f3f3f;
const ll VINF = 2e18;
const double PI = acos(-1);

struct dinic {
    int n;
    matrix capacity, flow;
    vint level, pointer;

    dinic(int n) : n(n), capacity(n, vint(n)), flow(n, vint(n)), level(n), pointer(n) {}

    void addEdge(int from, int to, int cap) {
        capacity[from][to] += cap;
    }

    bool bfs(int source, int sink) {
        fill(all(level), -1);
        level[source] = 0;
        queue<int> que;
        que.push(source);
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            for (int v = 0; v < n; v++) {
                if (level[v] < 0 && capacity[u][v] - flow[u][v] > 0) {
                    level[v] = level[u] + 1;
                    que.push(v);
                }
            }
        }
        return level[sink] >= 0;
    }

    int dfs(int u, int sink, int pushed) {
        if (u == sink || pushed == 0) return pushed;
        for (int &v = pointer[u]; v < n; v++) {
            if (level[v] == level[u] + 1 && capacity[u][v] - flow[u][v] > 0) {
                int f = dfs(v, sink, min(pushed, capacity[u][v] - flow[u][v]));
                if (f > 0) {
                    flow[u][v] += f;
                    flow[v][u] -= f;
                    return f;
                }
            }
        }
        return 0;
    }

    ll maxFlow(int source, int sink) {
        ll ret = 0;
        while (bfs(source, sink)) {
            fill(all(pointer), 0);
            while (int pushed = dfs(source, sink, INF)) ret += pushed;
        }
        return ret;
    }

    dbl findMinCut(int source) {
        dbl visited(n, false);
        queue<int> que;
        que.push(source);
        visited[source] = true;
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            for (int v = 0; v < n; v++) {
                if (!visited[v] && capacity[u][v] - flow[u][v] > 0) {
                    visited[v] = true;
                    que.push(v);
                }
            }
        }
        return visited;
    }
};
