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
const int MAX_N = 1e5 + 1;

void makeTree(const int &currentNode, const int &value);
void makeChain(const int &currentNode, const int &value);
void s(const int &currentNode, const int &value);
void c(const int &currentNode, const int &value);

struct node {
    int children[2];
    int parent, value, subtreeRoot, stackPlus, chainPlus, stackMake, chainMake, chainSum, stackSum, chainMax, chainMin, stackMax, stackMin, size, dSize;
    bool reversed;
} treeNodes[MAX_N];

int treeTop = 0;

struct splayTree {
    vint left, right, subtreeSize, values, group, valueMax, valueMin, sum, size, plus, makeValue, stack;
    int treeTop, stackTop;

    splayTree() {
        stackTop = -1;
        treeTop = 0;
        valueMax.assign(MAX_N, -INF);
        valueMin.assign(MAX_N, INF);
    }

    void update(const int &currentNode) {
        valueMax[currentNode] = max({treeNodes[values[currentNode]].chainMax, treeNodes[values[currentNode]].stackMax, valueMax[left[currentNode]], valueMax[right[currentNode]]});
        valueMin[currentNode] = min({treeNodes[values[currentNode]].chainMin, treeNodes[values[currentNode]].stackMin, valueMin[left[currentNode]], valueMin[right[currentNode]]});
        sum[currentNode] = sum[left[currentNode]] + sum[right[currentNode]] + treeNodes[values[currentNode]].stackSum + treeNodes[values[currentNode]].chainSum;
        size[currentNode] = size[left[currentNode]] + size[right[currentNode]] + treeNodes[values[currentNode]].size + treeNodes[values[currentNode]].dSize;
        subtreeSize[currentNode] = subtreeSize[left[currentNode]] + subtreeSize[right[currentNode]] + 1;
    }

    void applyMakeValue(const int &currentNode, const int &value) {
        makeValue[currentNode] = value;
        sum[currentNode] = value * size[currentNode];
        plus[currentNode] = 0;
        valueMax[currentNode] = valueMin[currentNode] = value;
    }

    void applyAddValue(const int &currentNode, const int &delta) {
        valueMax[currentNode] += delta;
        valueMin[currentNode] += delta;
        sum[currentNode] += delta * size[currentNode];
        plus[currentNode] += delta;
    }

    void propagate(const int &currentNode) {
        if (makeValue[currentNode] != INF) {
            applyMakeValue(values[currentNode], makeValue[currentNode]);
            makeChain(values[currentNode], makeValue[currentNode]);
            if (left[currentNode]) applyMakeValue(left[currentNode], makeValue[currentNode]);
            if (right[currentNode]) applyMakeValue(right[currentNode], makeValue[currentNode]);
            makeValue[currentNode] = INF;
        }
        if (plus[currentNode]) {
            s(values[currentNode], plus[currentNode]);
            c(values[currentNode], plus[currentNode]);
            if (left[currentNode]) applyAddValue(left[currentNode], plus[currentNode]);
            if (right[currentNode]) applyAddValue(right[currentNode], plus[currentNode]);
            plus[currentNode] = 0;
        }
    }

    void rotateLeft(int &currentNode) {
        propagate(currentNode);
        propagate(right[currentNode]);
        const int temp = right[currentNode];
        right[currentNode] = left[temp];
        update(currentNode);
        left[temp] = currentNode;
        update(temp);
        currentNode = temp;
    }

    void rotateRight(int &currentNode) {
        propagate(currentNode);
        propagate(left[currentNode]);
        const int temp = left[currentNode];
        left[currentNode] = right[temp];
        update(currentNode);
        right[temp] = currentNode;
        update(temp);
        currentNode = temp;
    }

    void maintain(int &currentNode) {
        if (subtreeSize[left[left[currentNode]]] > subtreeSize[right[currentNode]]) {
            rotateRight(currentNode);
            maintain(left[currentNode]);
            maintain(right[currentNode]);
            maintain(currentNode);
        }
        if (subtreeSize[right[right[currentNode]]] > subtreeSize[left[currentNode]]) {
            rotateLeft(currentNode);
            maintain(left[currentNode]);
            maintain(right[currentNode]);
            maintain(currentNode);
        }
        if (subtreeSize[left[right[currentNode]]] > subtreeSize[left[currentNode]]) {
            rotateRight(right[currentNode]);
            rotateLeft(currentNode);
            maintain(left[currentNode]);
            maintain(right[currentNode]);
            maintain(currentNode);
        }
        if (subtreeSize[right[left[currentNode]]] > subtreeSize[right[currentNode]]) {
            rotateLeft(left[currentNode]);
            rotateRight(currentNode);
            maintain(right[currentNode]);
            maintain(left[currentNode]);
            maintain(currentNode);
        }
    }

    void insert(int &currentNode, const int &value, int id) {
        if (!currentNode) {
            if (stackTop == -1) currentNode = ++treeTop;
            else currentNode = stack[stackTop--];
            left[currentNode] = right[currentNode] = 0;
            values[currentNode] = value;
            group[currentNode] = id;
            makeValue[currentNode] = INF;
            plus[currentNode] = 0;
            update(currentNode);
            return;
        }
        propagate(currentNode);
        if (value < values[currentNode]) insert(left[currentNode], value, id);
        else insert(right[currentNode], value, id);
        update(currentNode);
        maintain(currentNode);
    }

    void erase(int &currentNode, const int &value) {
        assert(currentNode);
        propagate(currentNode);
        if (value == values[currentNode]) {
            if (!left[currentNode]) {
                stack[++stackTop] = currentNode;
                currentNode = right[currentNode];
            } else if (!right[currentNode]) {
                stack[++stackTop] = currentNode;
                currentNode = left[currentNode];
            } else {
                rotateLeft(currentNode);
                erase(left[currentNode], value);
                update(currentNode);
                maintain(currentNode);
            }
            return;
        }
        if (value < values[currentNode]) erase(left[currentNode], value);
        else erase(right[currentNode], value);
        update(currentNode);
        maintain(currentNode);
    }

    int find(int &currentNode, const int &value) {
        if (value == values[currentNode]) {
            propagate(currentNode);
            return currentNode;
        }
        propagate(currentNode);
        if (value < values[currentNode]) return find(left[currentNode], value);
        else return find(right[currentNode], value);
    }
};

class topTree {
public:
    splayTree bst;
    matrix edge;
    vint stack;
    int tops = -1, troot = 0;

    topTree() {
        edge.resize(MAX_N, vint(2));
        stack.resize(MAX_N);
    }

    bool isRoot(const int &current) {
        return !topTreeNodes[current].parent || (topTreeNodes[topTreeNodes[current].parent].children[0] != current && topTreeNodes[topTreeNodes[current].parent].children[1] != current);
    }

    void update(const int &current) {
        topTreeNodes[current].chainMax = max(topTreeNodes[current].value, max(topTreeNodes[topTreeNodes[current].children[0]].chainMax, topTreeNodes[topTreeNodes[current].children[1]].chainMax));
        topTreeNodes[current].chainMin = min(topTreeNodes[current].value, min(topTreeNodes[topTreeNodes[current].children[1]].chainMin, topTreeNodes[topTreeNodes[current].children[0]].chainMin));
        topTreeNodes[current].chainSum = topTreeNodes[current].value + topTreeNodes[topTreeNodes[current].children[0]].chainSum + topTreeNodes[topTreeNodes[current].children[1]].chainSum;
        topTreeNodes[current].stackMax = max(bst.valueMax[topTreeNodes[current].subtreeRoot], max(topTreeNodes[topTreeNodes[current].children[0]].stackMax, topTreeNodes[topTreeNodes[current].children[1]].stackMax));
        topTreeNodes[current].stackMin = min(bst.valueMin[topTreeNodes[current].subtreeRoot], min(topTreeNodes[topTreeNodes[current].children[1]].stackMin, topTreeNodes[topTreeNodes[current].children[0]].stackMin));
        topTreeNodes[current].stackSum = bst.sum[topTreeNodes[current].subtreeRoot] + topTreeNodes[topTreeNodes[current].children[0]].stackSum + topTreeNodes[topTreeNodes[current].children[1]].stackSum;
        topTreeNodes[current].size = bst.size[topTreeNodes[current].subtreeRoot] + topTreeNodes[topTreeNodes[current].children[0]].size + topTreeNodes[topTreeNodes[current].children[1]].size;
        topTreeNodes[current].dSize = 1 + topTreeNodes[topTreeNodes[current].children[0]].dSize + topTreeNodes[topTreeNodes[current].children[1]].dSize;
    }

    void reverse(const int &current) {
        topTreeNodes[current].reversed ^= 1;
        swap(topTreeNodes[current].children[0], topTreeNodes[current].children[1]);
    }
    void makeTree(const int &current, const int &value) {
        topTreeNodes[current].stackMake = value;
        topTreeNodes[current].stackPlus = 0;
        if (topTreeNodes[current].size) {
            if (topTreeNodes[current].subtreeRoot) bst.makeTree(topTreeNodes[current].subtreeRoot, value);
            topTreeNodes[current].stackMax = topTreeNodes[current].stackMin = value;
            topTreeNodes[current].stackSum = value * topTreeNodes[current].size;
        }
    }
    void stackPlus(const int &current, const int &value) {
        topTreeNodes[current].stackPlus += value;
        topTreeNodes[current].stackSum += value * topTreeNodes[current].size;
        topTreeNodes[current].stackMax += value;
        topTreeNodes[current].stackMin += value;
        if (topTreeNodes[current].subtreeRoot) bst.addTree(topTreeNodes[current].subtreeRoot, value);
    }
    void makeChain(const int &current, const int &value) {
        topTreeNodes[current].value = value;
        topTreeNodes[current].chainMake = value;
        topTreeNodes[current].chainPlus = 0;
        topTreeNodes[current].chainMax = topTreeNodes[current].chainMin = value;
        topTreeNodes[current].chainSum = value * topTreeNodes[current].dSize;
    }
    void chainPlus(const int &current, const int &value) {
        topTreeNodes[current].value += value;
        topTreeNodes[current].chainPlus += value;
        topTreeNodes[current].chainMax += value;
        topTreeNodes[current].chainMin += value;
        topTreeNodes[current].chainSum += value * topTreeNodes[current].dSize;
    }

    void get(const int &current) {
        if (topTreeNodes[current].reversed) {
            if (topTreeNodes[current].children[0]) reverse(topTreeNodes[current].children[0]);
            if (topTreeNodes[current].children[1]) reverse(topTreeNodes[current].children[1]);
            topTreeNodes[current].reversed = 0;
        }
        if (topTreeNodes[current].stackMake != INF) {
            if (topTreeNodes[current].children[0]) makeTree(topTreeNodes[current].children[0], topTreeNodes[current].stackMake);
            if (topTreeNodes[current].children[1]) makeTree(topTreeNodes[current].children[1], topTreeNodes[current].stackMake);
            topTreeNodes[current].stackMake = INF;
        }
        if (topTreeNodes[current].stackPlus) {
            if (topTreeNodes[current].children[0]) stackPlus(topTreeNodes[current].children[0], topTreeNodes[current].stackPlus);
            if (topTreeNodes[current].children[1]) stackPlus(topTreeNodes[current].children[1], topTreeNodes[current].stackPlus);
            topTreeNodes[current].stackPlus = 0;
        }
        if (topTreeNodes[current].chainMake != INF) {
            if (topTreeNodes[current].children[0]) makeChain(topTreeNodes[current].children[0], topTreeNodes[current].chainMake);
            if (topTreeNodes[current].children[1]) makeChain(topTreeNodes[current].children[1], topTreeNodes[current].chainMake);
            topTreeNodes[current].chainMake = INF;
        }
        if (topTreeNodes[current].chainPlus) {
            if (topTreeNodes[current].children[0]) chainPlus(topTreeNodes[current].children[0], topTreeNodes[current].chainPlus);
            if (topTreeNodes[current].children[1]) chainPlus(topTreeNodes[current].children[1], topTreeNodes[current].chainPlus);
            topTreeNodes[current].chainPlus = 0;
        }
    }
    void rotate(const int &current) {
        int parent = topTreeNodes[current].parent, topParent = topTreeNodes[parent].parent, direction = topTreeNodes[parent].children[0] == current;
        if (!isRoot(parent)) topTreeNodes[topParent].children[topTreeNodes[topParent].children[1] == parent] = current;
        topTreeNodes[current].parent = topParent;
        topTreeNodes[topTreeNodes[current].children[direction]].parent = parent;
        topTreeNodes[parent].children[1 - direction] = topTreeNodes[current].children[direction];
        topTreeNodes[parent].parent = current;
        topTreeNodes[current].children[direction] = parent;
        update(parent);
        update(current);
    }

    int getPrevious(const int &current) {
        int x = current;
        stack[++tops] = x;
        while (!isRoot(x)) {
            x = topTreeNodes[x].parent;
            stack[++tops] = x;
        }
        while (~tops) get(stack[tops--]);
        if (topTreeNodes[current].children[0]) {
            current = topTreeNodes[current].children[0];
            get(current);
            while (current && topTreeNodes[current].children[1]) {
                current = topTreeNodes[current].children[1];
                get(current);
            }
            return current;
        } else {
            while (current && topTreeNodes[topTreeNodes[current].parent].children[0] == current) current = topTreeNodes[current].parent;
            current = topTreeNodes[current].parent;
            return current;
        }
    }

    void splay(const int &current) {
        int x = current;
        stack[++tops] = x;
        while (!isRoot(x)) {
            x = topTreeNodes[x].parent;
            stack[++tops] = x;
            if (x == troot) troot = current;
        }
        if (topTreeNodes[x].parent) {
            bst.erase(topTreeNodes[topTreeNodes[x].parent].subtreeRoot, x);
        }
        while (~tops) get(stack[tops--]);
        while (!isRoot(current)) {
            int parent = topTreeNodes[current].parent; topParent = topTreeNodes[parent].parent;
            if (isRoot(parent)) rotate(current);
            else if ((topTreeNodes[topParent].children[0] == parent) == (topTreeNodes[parent].children[0] == current)) rotate(parent), rotate(current);
            else rotate(current), rotate(current);
        }
        if (topTreeNodes[current].parent) {
            int parent = topTreeNodes[current].parent;
            bst.insert(topTreeNodes[parent].subtreeRoot, current, parent);
        }
    }

    int access(const int &current) {
        int x = current;
        while (x) {
            stack[++tops] = x;
            x = topTreeNodes[x].parent;
        }
        while (~tops) {
            get(stack[tops]);
            if (tops && isRoot(stack[tops - 1])) bst.find(topTreeNodes[stack[tops]].subtreeRoot, stack[tops - 1]);
            tops--;
        }
        int ret = 0;
        while (current) {
            splay(current);
            if (ret) bst.erase(topTreeNodes[current].subtreeRoot, ret);
            if (topTreeNodes[current].children[1]) bst.insert(topTreeNodes[current].subtreeRoot, topTreeNodes[current].children[1], current);
            topTreeNodes[current].children[1] = ret;
            update(current);
            ret = current;
            current = topTreeNodes[current].parent;
        }
        return ret;
    }

    void makeRoot(const int &current) {
        troot = current;
        reverse(access(current));
    }

    void link(int x, int y) {
        makeRoot(x);
        access(x);
        makeRoot(y);
        access(y);
        topTreeNodes[x].parent = y;
        topTreeNodes[y].children[1] = x;
        update(y);
    }

    void treeMake(const int &current, const int &value) {
        access(current);
        int prev = getPrevious(current);
        if (prev) splay(prev);
        makeTree(current, value);
        makeChain(current, value);
        if (prev) update(prev);
    }

    void chainMake(int a, int y, const int &value) {
        makeRoot(a);
        makeChain(access(y), value);
    }

    void plusTree(const int &current, const int &value) {
        access(current);
        splay(current);
        int prev = getPrevious(current);
        if (prev) splay(prev);
        stackPlus(current, value);
        chainPlus(current, value);
        if (prev) update(prev);
    }

    // tool
    bool isSame(int a, int b) {
        while (topTreeNodes[a].parent) a = topTreeNodes[a].parent;
        while (topTreeNodes[b].parent) b = topTreeNodes[b].parent;
        return a == b;
    }

    void plusChain(int a, int b, const int &value) {
        makeRoot(a);
        chainPlus(access(b), value);
    }

    int sumQuery(int a, int b) {
        makeRoot(a);
        return topTreeNodes[access(b)].chainSum;
    }

    int maxQuery(int a, int b) {
        makeRoot(a);
        return topTreeNodes[access(b)].chainMax;
    }

    int minQuery(int a, int b) {
        makeRoot(a);
        return topTreeNodes[access(b)].chainMin;
    }

    int sumTree(int a) {
        access(a);
        int prev = getPrevious(a);
        if (prev) splay(prev);
        return topTreeNodes[a].stackSum + topTreeNodes[a].chainSum;
    }

    int maxTree(int a) {
        access(a);
        int prev = getPrevious(a);
        if (prev) splay(prev);
        return max(topTreeNodes[a].chainMax, topTreeNodes[a].stackMax);
    }

    int minTree(int a) {
        access(a);
        int prev = getPrevious(a);
        if (prev) splay(prev);
        return min(topTreeNodes[a].chainMin, topTreeNodes[a].stackMin);
    }
};
