#include <bits/extc++.h>
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
using vint = vector<int>;
using matrix = vector<vint>;
using vll = vector<ll>;
using matrlx = vector<vll>;
using fourdimensionalMatrix = vector<matrix>;  // ;;
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

int n, m;
vint connectionStrength;
matrix graph;
dbl isVertexDeleted, isInSet;

void init() {
    graph.assign(n + 1, vint(n + 1, 0));
    isVertexDeleted.assign(n + 1, false);
}

int mincutPhase(int &lastVertex, int &currentVertex) {
    connectionStrength.assign(n + 1, 0);
    isInSet.assign(n + 1, false);
    int minCutValue = 0;

    for (int i = 1; i <= n; i++) {
        int selectedVertex = -1, maxStrength = -1;

        for (int j = 1; j <= n; j++) {
            if (isVertexDeleted[j] || isInSet[j]) continue;
            if (connectionStrength[j] > maxStrength) {
                maxStrength = connectionStrength[j];
                selectedVertex = j;
            }
        }

        if (selectedVertex == -1) return minCutValue;

        lastVertex = currentVertex, currentVertex = selectedVertex;
        isInSet[selectedVertex] = true;
        minCutValue = maxStrength;

        for (int j = 1; j <= n; j++) {
            if (!isVertexDeleted[j] && !isInSet[j]) connectionStrength[j] += graph[selectedVertex][j];
        }
    }
    return minCutValue;
}

int getMinCut() {
    int globalMinCut = INF;

    for (int phase = 1; phase < n; phase++) {
        int lastVertex, currentVertex;
        int minCutInPhase = mincutPhase(lastVertex, currentVertex);
        globalMinCut = min(globalMinCut, minCutInPhase);

        if (globalMinCut == 0) return 0;

        isVertexDeleted[currentVertex] = true;
        for (int j = 1; j <= n; j++) {
            if (!isVertexDeleted[j]) {
                graph[lastVertex][j] += graph[currentVertex][j];
                graph[j][lastVertex] = graph[lastVertex][j];
            }
        }
    }
    return globalMinCut;
}
