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

vint getPEO(matrix &adjacencyList) {
    int numberVertices = adjacencyList.size();
    vint connectionCount(numberVertices), vertexOrder(numberVertices);
    for (int i = 0; i < numberVertices; i++) sort(all(adjacencyList[i]));
    
    priority_queue<pii> maxHeap;
    for (int i = 0; i < numberVertices; i++) maxHeap.emplace(connectionCount[i], i);
    
    vint peo;
    while (!maxHeap.empty()) {
        int currentVertex = maxHeap.top().second, currentConnections = maxHeap.top().first;
        maxHeap.pop();
        
        if (connectionCount[currentVertex] != currentConnections || vertexOrder[currentVertex]) continue;
        
        peo.push_back(currentVertex);
        vertexOrder[currentVertex] = numberVertices + 1 - peo.size();
        
        for (auto& neighbor : adjacencyList[currentVertex]) {
            if (!vertexOrder[neighbor]) {
                connectionCount[neighbor]++;
                maxHeap.emplace(connectionCount[neighbor], neighbor);
            }
        }
    }
    
    reverse(all(peo));
    for (auto& vertex : peo) {
        int minIndexBefore = INF;
        for (auto& neighbor : adjacencyList[vertex]) {
            if (vertexOrder[neighbor] > vertexOrder[vertex]) 
                minIndexBefore = min(minIndexBefore, vertexOrder[neighbor]);
        }
        
        minIndexBefore--;
        if (minIndexBefore < numberVertices) {
            minIndexBefore = peo[minIndexBefore];
            for (auto& neighbor : adjacencyList[vertex]) {
                if (vertexOrder[neighbor] > vertexOrder[minIndexBefore] && !binary_search(adjacencyList[minIndexBefore].begin(), adjacencyList[minIndexBefore].end(), neighbor)) return vint();
            }
        }
    }
    return peo;
}
