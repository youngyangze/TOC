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
const int MAX_N = 200007;

struct harc {
    int id, start, end, lowerWeightIndex;
    ll weightProduct, baseValue, numerator, denominator;
    
    bool contains(const harc& other) const {return start <= other.start && other.end <= end;}
    
    ll f() const {return numerator / denominator;}

    bool operator <(const harc& other) const {return f() < other.f();}
    bool operator <=(const harc& other) const {return f() <= other.f();}
    bool operator ==(const harc& other) const {return f() == other.f();}
};

class huAndShing {
public:
    harc arcs[MAX_N];
    ll weights[MAX_N], cumulativeProducts[MAX_N];
    vpii edgeList;
    vint tree[MAX_N];
    vector<harc> arcConnections[MAX_N];
    priority_queue<harc> arcQueues[MAX_N];
    int queueIds[MAX_N], subtreeSize[MAX_N];
    int totalArcs, totalQueues, n;

    void createArc(int start, int end) {
        arcs[++totalArcs].id = totalArcs;
        arcs[totalArcs].start = start;
        arcs[totalArcs].end = end;
        arcs[totalArcs].lowerWeightIndex = weights[start] < weights[end] ? start : end;
        arcs[totalArcs].weightProduct = weights[start] * weights[end];
        arcs[totalArcs].baseValue = cumulativeProducts[end] - cumulativeProducts[start] - arcs[totalArcs].weightProduct;
    }

    ll calculateWeightProduct(int node) {
        if (node == 1) return weights[1] * weights[2] + weights[1] * weights[n];
        
        harc& current = arcs[node];
        if (current.start == current.lowerWeightIndex) {
            if (arcConnections[current.start].empty() || !current.contains(arcConnections[current.start].back())) return weights[current.start] * weights[current.start + 1];
            return arcConnections[current.start].back().weightProduct;
        } else {
            if (arcConnections[current.end].empty() || !current.contains(arcConnections[current.end].back())) return weights[current.end] * weights[current.end - 1];
            return arcConnections[current.end].back().weightProduct;
        }
    }

    void addArc(int node) {
        harc& current = arcs[node];
        arcQueues[queueIds[node]].push(current);
        arcConnections[current.start].push_back(current);
        arcConnections[current.end].push_back(current);
    }

    void removeArc(int node) {
        arcConnections[arcQueues[queueIds[node]].top().start].pop_back();
        arcConnections[arcQueues[queueIds[node]].top().end].pop_back();
        arcQueues[queueIds[node]].pop();
    }

    void mergePriorityQueues(int node) {
        int largestSubtreeIndex = -1;
        for (const auto& arc : tree[node]) {
            if (largestSubtreeIndex == -1 || subtreeSize[largestSubtreeIndex] < subtreeSize[arc]) {
                largestSubtreeIndex = arc;
            }
        }
        queueIds[node] = queueIds[largestSubtreeIndex];
        auto& currentQueue = arcQueues[queueIds[node]];
        for (const auto& arc : tree[node]) {
            if (arc == largestSubtreeIndex) continue;
            auto& childQueue = arcQueues[queueIds[arc]];
            while (!childQueue.empty()) {
                currentQueue.push(childQueue.top());
                childQueue.pop();
            }
        }
    }

    void dfs(int node) {
        harc& current = arcs[node];
        subtreeSize[node] = 1;
        if (tree[node].empty()) {
            queueIds[node] = ++totalQueues;
            current.denominator = current.baseValue;
            current.numerator = weights[current.lowerWeightIndex] * (current.denominator + current.weightProduct - calculateWeightProduct(node));
            addArc(node);
            return;
        }
        current.denominator = current.baseValue;
        for (const auto& arc : tree[node]) {
            dfs(arc);
            subtreeSize[node] += subtreeSize[arc];
            current.denominator -= arcs[arc].baseValue;
        }
        current.numerator = weights[current.lowerWeightIndex] * (current.denominator + current.weightProduct - calculateWeightProduct(node));
        mergePriorityQueues(node);
        auto& currentQueue = arcQueues[queueIds[node]];
        while (!currentQueue.empty() && currentQueue.top().f() >= weights[current.lowerWeightIndex]) {
            auto topArc = currentQueue.top();
            current.denominator += topArc.denominator;
            removeArc(node);
            current.numerator = weights[current.lowerWeightIndex] * (current.denominator + current.weightProduct - calculateWeightProduct(node));
        }

        while (!currentQueue.empty() && current <= currentQueue.top()) {
            auto topArc = currentQueue.top();
            current.denominator += topArc.denominator;
            removeArc(node);
            current.numerator += topArc.numerator;
        }

        addArc(node);
    }
};
