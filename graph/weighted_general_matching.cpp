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

class weightedGeneralMatching {
    int n, totalVertices;
    matrix graphWeight, blossomFrom, blossom;
    vint label, matching, slack, _stack, parent, _a, visited;
    queue<int> que;

public:
    weightedGeneralMatching(int _n) : n(_n), totalVertices(_n) {
        graphWeight.assign((n << 1) + 1, vint((n << 1) + 1, 0));
        label.assign((n << 1) + 1, 0);
        matching.assign((n << 1) + 1, 0);
        slack.assign((n << 1) + 1, 0);
        _stack.assign((n << 1) + 1, 0);
        parent.assign((n << 1) + 1, 0);
        blossomFrom.assign((n << 1) + 1, vint(n + 1, 0));
        _a.assign((n << 1) + 1, -1);
        visited.assign((n << 1) + 1, 0);
        blossom.resize((n << 1) + 1);
    }

    int calculateEdgeDelta(int u, int v) {
        return label[u] + label[v] - (graphWeight[u][v] << 1);
    }

    void updateSlack(int u, int x) {
        if (!slack[x] || calculateEdgeDelta(u, x) < calculateEdgeDelta(slack[x], x)) slack[x] = u;
    }

    void stackInit(int x) {
        slack[x] = 0;
        for (int u = 1; u <= n; u++) {
            if (graphWeight[u][x] > 0 && _stack[u] != x && _a[_stack[u]] == 0) updateSlack(u, x);
        }
    }

    void pushQueue(int x) {
        if (x <= n) que.push(x);
        else {
            for (int i : blossom[x]) pushQueue(i);
        }
    }

    void setBlossomBase(int x, int base) {
        _stack[x] = base;
        if (x > n) {
            for (int i : blossom[x]) setBlossomBase(i, base);
        }
    }

    int getBlossomPr(int base, int x) {
        int pr = find(all(blossom[base]), x) - blossom[base].begin();
        if (pr % 2 == 1) {
            reverse(blossom[base].begin() + 1, blossom[base].end());
            return blossom[base].size() - pr;
        }
        return pr;
    }

    void setMatching(int u, int v) {
        matching[u] = v;
        if (u <= n) return;
        int x = blossomFrom[u][graphWeight[u][v] > 0 ? v : 0], pr = getBlossomPr(u, x);
        for (int i = 0; i < pr; i++) setMatching(blossom[u][i], blossom[u][i ^ 1]);
        setMatching(x, v);
        rotate(blossom[u].begin(), blossom[u].begin() + pr, blossom[u].end());
    }

    void augmentPath(int u, int v) {
        while (true) {
            int nextV = _stack[matching[u]];
            setMatching(u, v);
            if (!nextV) return;
            setMatching(nextV, _stack[parent[nextV]]);
            u = _stack[parent[nextV]], v = nextV;
        }
    }

    int findLCA(int u, int v) {
        static int time = 0;
        time++;
        while (u || v) {
            if (u) {
                if (visited[u] == time) return u;
                visited[u] = time;
                u = _stack[matching[u]];
                if (u) u = _stack[parent[u]];
            }
            swap(u, v);
        }
        return 0;
    }

    void addBlossom(int u, int lca, int v) {
        int base = n + 1;
        while (base <= totalVertices && _stack[base]) base++;
        if (base > totalVertices) totalVertices++;

        label[base] = 0;
        _a[base] = 0;
        matching[base] = matching[lca];
        blossom[base].clear();
        blossom[base].push_back(lca);

        auto pushBlossom = [&](int x) {
            while (x != lca) {
                blossom[base].push_back(x);
                blossom[base].push_back(_stack[matching[x]]);
                pushQueue(_stack[matching[x]]);
                x = _stack[parent[_stack[matching[x]]]];
            }
        };

        pushBlossom(u);
        reverse(blossom[base].begin() + 1, blossom[base].end());
        pushBlossom(v);

        setBlossomBase(base, base);

        for (int i = 1; i <= totalVertices; i++) graphWeight[base][i] = graphWeight[i][base] = 0;
        for (int i = 1; i <= n; i++) blossomFrom[base][i] = 0;

        for (int i : blossom[base]) {
            for (int j = 1; j <= totalVertices; j++) {
                if (graphWeight[base][j] == 0 || calculateEdgeDelta(i, j) < calculateEdgeDelta(base, j)) graphWeight[base][j] = graphWeight[j][base] = graphWeight[i][j];
            }
            for (int j = 1; j <= n; j++) {
                if (blossomFrom[i][j]) blossomFrom[base][j] = i;
            }
        }
        stackInit(base);
    }

    void expandBlossom(int base) {
        for (int i : blossom[base]) setBlossomBase(i, i);

        int x = blossomFrom[base][graphWeight[base][parent[base]] > 0 ? parent[base] : 0], pr = getBlossomPr(base, x);
        for (int i = 0; i < pr; i += 2) {
            int u = blossom[base][i], v = blossom[base][i + 1];
            parent[u] = graphWeight[v][u] > 0 ? v : 0;
            _a[u] = 1;
            _a[v] = 0;
            slack[u] = 0;
            stackInit(v);
            pushQueue(v);
        }

        _a[x] = 1;
        parent[x] = parent[base];

        for (int i = pr + 1; i < blossom[base].size(); i++) {
            int u = blossom[base][i];
            _a[u] = -1;
            stackInit(u);
        }

        _stack[base] = 0;
    }

    bool processFoundEdge(int u, int v) {
        u = _stack[u], v = _stack[v];
        if (_a[v] == -1) {
            parent[v] = u;
            _a[v] = 1;
            int nextU = _stack[matching[v]];
            slack[v] = slack[nextU] = 0;
            _a[nextU] = 0;
            pushQueue(nextU);
        } else if (_a[v] == 0) {
            int lca = findLCA(u, v);
            if (!lca) {
                augmentPath(u, v);
                augmentPath(v, u);
                return true;
            } else addBlossom(u, lca, v);
        }
        return false;
    }

    bool findMatching() {
        fill(_a.begin() + 1, _a.begin() + totalVertices + 1, -1);
        fill(slack.begin() + 1, slack.begin() + totalVertices + 1, 0);
        que = queue<int>();

        for (int i = 1; i <= totalVertices; i++) {
            if (_stack[i] == i && !matching[i]) {
                parent[i] = 0;
                _a[i] = 0;
                pushQueue(i);
            }
        }

        if (que.empty()) return false;

        while (true) {
            while (!que.empty()) {
                int u = que.front();
                que.pop();
                if (_a[_stack[u]] == 1) continue;

                for (int i = 1; i <= n; i++) {
                    if (graphWeight[u][i] > 0 && _stack[u] != _stack[i]) {
                        if (calculateEdgeDelta(u, i) == 0) {
                            if (processFoundEdge(u, i)) return true;
                        } else updateSlack(u, _stack[i]);
                    }
                }
            }

            int d = INF;
            for (int i = n + 1; i <= totalVertices; i++) {
                if (_stack[i] == i && _a[i] == 1) d = min(d, label[i] >> 1);
            }

            for (int i = 1; i <= totalVertices; i++) {
                if (_stack[i] == i && slack[i]) {
                    if (_a[i] == -1) d = min(d, calculateEdgeDelta(slack[i], i));
                    else if (_a[i] == 0) d = min(d, calculateEdgeDelta(slack[i], i) >> 1);
                }
            }

            for (int i = 1; i <= n; i++) {
                if (_a[_stack[i]] == 0) {
                    if (label[i] <= d) return false;
                    label[i] -= d;
                } else if (_a[_stack[i]] == 1) label[i] += d;
            }

            for (int i = n + 1; i <= totalVertices; i++) {
                if (_stack[i] == i) {
                    if (_a[i] == 0) label[i] += d << 1;
                    else if (_a[i] == 1) label[i] -= d << 1;
                }
            }

            que = queue<int>();
            for (int i = 1; i <= totalVertices; i++) {
                if (_stack[i] == i && slack[i] && _stack[slack[i]] != i && calculateEdgeDelta(slack[i], i) == 0) {
                    if (processFoundEdge(slack[i], i)) return true;
                }
            }

            for (int i = n + 1; i <= totalVertices; i++) {
                if (_stack[i] == i && _a[i] == 1 && label[i] == 0) expandBlossom(i);
            }
        }

        return false;
    }

    pair<ll, int> solve() {
        fill(matching.begin() + 1, matching.begin() + n + 1, 0);
        totalVertices = n;
        int matchCount = 0;
        long long totalWeight = 0;

        for (int u = 1; u <= n; u++) {
            _stack[u] = u;
            blossom[u].clear();
        }

        int maxWeight = 0;
        for (int u = 1; u <= n; u++) {
            for (int v = 1; v <= n; v++) {
                blossomFrom[u][v] = (u == v ? u : 0);
                maxWeight = max(maxWeight, graphWeight[u][v]);
            }
        }

        fill(label.begin() + 1, label.begin() + n + 1, maxWeight);

        while (findMatching()) matchCount++;

        for (int u = 1; u <= n; u++) {
            if (matching[u] && matching[u] < u) totalWeight += graphWeight[u][matching[u]];
        }

        return make_pair(totalWeight, matchCount);
    }

    void addEdge(int u, int v, int w) {
        graphWeight[u][v] = graphWeight[v][u] = w;
    }
};
