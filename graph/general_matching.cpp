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

struct generalMatching {
    vint visited, parent, original, matched, auxiliary;
    vector<vint> connections;
    queue<int>  que;
    int timeStamp, vertexCount;

    generalMatching(int n) : visited(n + 1), parent(n + 1), original(n + 1), matched(n + 1), auxiliary(n + 1), connections(n + 1) {
        vertexCount = n;
        timeStamp = 0;
    }

    void addEdge(int u, int v) {
        connections[u].push_back(v);
        connections[v].push_back(u);
    }

    void init(int n) {
        vertexCount = n;
        timeStamp = 0;
        for (int i = 0; i <= n; i++) {
            connections[i].clear();
            matched[i] = auxiliary[i] = parent[i] = 0;
        }
    }

    void augmentPath(int startVertex, int endVertex) {
        int previousVertex = endVertex, nextVertex;
        do {
            previousVertex = parent[endVertex];
            nextVertex = matched[previousVertex];
            matched[endVertex] = previousVertex;
            matched[previousVertex] = endVertex;
            endVertex = nextVertex;
        } while (startVertex != previousVertex);
    }

    int lca(int v, int w) {
        timeStamp++;
        while (true) {
            if (v) {
                if (auxiliary[v] == timeStamp) return v;
                auxiliary[v] = timeStamp;
                v = original[parent[matched[v]]];
            }
            swap(v, w);
        }
    }

    void blossom(int vertex, int otherVertex, int lcaVertex) {
        while (original[vertex] != lcaVertex) {
            parent[vertex] = otherVertex;
            otherVertex = matched[vertex];
            if (visited[otherVertex] == 1) {
                que.push(otherVertex);
                visited[otherVertex] = 0;
            }
            original[vertex] = original[otherVertex] = lcaVertex;
            vertex = parent[otherVertex];
        }
    }

    bool bfs(int startVertex) {
        fill(visited.begin() + 1, visited.begin() + 1 + vertexCount, -1);
        iota(original.begin() + 1, original.begin() + 1 + vertexCount, 1);
        que = queue<int>();
        que.push(startVertex);
        visited[startVertex] = 0;
        while (!que.empty()) {
            int vertex = que.front();
            que.pop();
            for (int neighbor : connections[vertex]) {
                if (visited[neighbor] == -1) {
                    parent[neighbor] = vertex;
                    visited[neighbor] = 1;
                    if (!matched[neighbor]) {
                        augmentPath(startVertex, neighbor);
                        return true;
                    }
                    que.push(matched[neighbor]);
                    visited[matched[neighbor]] = 0;
                } else if (visited[neighbor] == 0 && original[vertex] != original[neighbor]) {
                    int lcaVertex = lca(original[vertex], original[neighbor]);
                    blossom(neighbor, vertex, lcaVertex);
                    blossom(vertex, neighbor, lcaVertex);
                }
            }
        }
        return false;
    }

    int findMaximumMatching() {
        int matchCount = 0;

        vint vertices(vertexCount - 1);
        iota(all(vertices), 1);
        shuffle(all(vertices), mt19937(0x94949));
        for (int vertex : vertices) {
            if (!matched[vertex]) {
                for (int neighbor : connections[vertex]) {
                    if (!matched[neighbor]) {
                        matched[vertex] = neighbor;
                        matched[neighbor] = vertex;
                        matchCount++;
                        break;
                    }
                }
            }
        }
        for (int i = 1; i <= vertexCount; i++) {
            if (!matched[i] && bfs(i)) matchCount++;
        }
        return matchCount;
    }
};
