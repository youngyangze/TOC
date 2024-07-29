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

void makeTree(int currentNode, int _value);
void makeChain(int currentNode, int _value);
void stackPlus(int currentNode, int _value);
void chainPlus(int currentNode, int _value);

struct node {
    int children[2];
    int parent;
    bool reversed;
    int value, subtreeRoot, stackPlus, chainPlus, stackMake, chainMake, chainSum, stackSum, chainMax, chainMin, stackMax, stackMin, size, dSize;
} nodes[MAX_N];

vint _stack(MAX_N), stackTop = -1;
int treeTop = 0, _treeRoot;

struct splayTree {
    vint left(MAX_N), right(MAX_N), subtreeRoot(MAX_N), values(MAX_N), groups(MAX_N), valueMax(MAX_N), valueMin(MAX_N), sum(MAX_N), size(MAX_N), plus(MAX_N), makeValue(MAX_N), _stack(MAX_N);
    int treeTop, stackTop;
    splayTree() {
        stackTop = -1;
        treeTop = 0;
        valueMax[0] = -INF;
        valueMin[0] = INF;
    }

    void update(int currentNode) {
        valueMax[currentNode] = max(max(nodes[values[currentNode]].chainMax, nodes[values[currentNode]].stackMax), max(valueMax[left[currentNode]], valueMax[right[currentNode]]));
        valueMin[currentNode] = min(min(nodes[values[currentNode]].chainMin, nodes[values[currentNode]].stackMin), min(valueMin[left[currentNode]], valueMin[right[currentNode]]));
        sum[currentNode] = sum[left[currentNode]] + sum[right[currentNode]] + nodes[values[currentNode]].stackSum + nodes[values[currentNode]].chainSum;
        size[currentNode] = size[left[currentNode]] + size[right[currentNode]] + nodes[values[currentNode]].size + nodes[values[currentNode]].dSize;
        subtreeRoot[currentNode] = subtreeRoot[left[currentNode]] + subtreeRoot[right[currentNode]] + 1;
    }

    void applyMakeValue(int currentNode, int _value) {
        makeValue[currentNode] = _value;
        sum[currentNode] = _value * size[currentNode];
        plus[currentNode] = 0;
        valueMax[currentNode] = valueMin[currentNode] = _value;
    }

    void applyAddValue(int currentNode, int delta) {
        valueMax[currentNode] += delta;
        valueMin[currentNode] += delta;
        sum[currentNode] += delta * size[currentNode];
        plus[currentNode] += delta;
    }

    void propagate(int currentNode) {
        if (makeValue[currentNode] != INF) {
            makeTree(values[currentNode], makeValue[currentNode]);
            makeChain(values[currentNode], makeValue[currentNode]);
            if (left[currentNode]) applyMakeValue(left[currentNode], makeValue[currentNode]);
            if (right[currentNode]) applyMakeValue(right[currentNode], makeValue[currentNode]);
            makeValue[currentNode] = INF;
        }
        if (plus[currentNode]) {
            stackPlus(values[currentNode], plus[currentNode]);
            chainPlus(values[currentNode], plus[currentNode]);
            if (left[currentNode]) applyAddValue(left[currentNode], plus[currentNode]);
            if (right[currentNode]) applyAddValue(right[currentNode], plus[currentNode]);
            plus[currentNode] = 0;
        }
    }

    void leftRotate(int &currentNode) {
        propagate(currentNode);
        propagate(right[currentNode]);
        int temp = right[currentNode];
        right[currentNode] = left[temp];
        update(currentNode);
        left[temp] = currentNode;
        update(temp);
        currentNode = temp;
    }

    void rightRotate(int &currentNode) {
        propagate(currentNode);
        propagate(left[currentNode]);
        int temp = left[currentNode];
        left[currentNode] = right[temp];
        update(currentNode);
        right[temp] = currentNode;
        update(temp);
        currentNode = temp;
    }

    void maintain(int &currentNode) {
        if (subtreeRoot[left[left[currentNode]]] > subtreeRoot[right[currentNode]]) {
            rightRotate(currentNode);
            maintain(left[currentNode]);
            maintain(right[currentNode]);
            maintain(currentNode);
        }
        if (subtreeRoot[right[right[currentNode]]] > subtreeRoot[left[currentNode]]) {
            leftRotate(currentNode);
            maintain(left[currentNode]);
            maintain(right[currentNode]);
            maintain(currentNode);
        }
        if (subtreeRoot[left[right[currentNode]]] > subtreeRoot[left[currentNode]]) {
            rightRotate(right[currentNode]);
            leftRotate(currentNode);
            maintain(left[currentNode]);
            maintain(right[currentNode]);
            maintain(currentNode);
        }
        if (subtreeRoot[right[left[currentNode]]] > subtreeRoot[right[currentNode]]) {
            leftRotate(left[currentNode]);
            rightRotate(currentNode);
            maintain(right[currentNode]);
            maintain(left[currentNode]);
            maintain(currentNode);
        }
    }

    void insert(int &currentNode, int value, int address) {
        if (!currentNode) {
            if (stackTop == -1) currentNode = ++treeTop;
            else currentNode = _stack[stackTop--];
            left[currentNode] = right[currentNode] = 0;
            values[currentNode] = value;
            groups[currentNode] = address;
            makeValue[currentNode] = INF;
            plus[currentNode] = 0;
            update(currentNode);
            return;
        }
        propagate(currentNode);
        if (value < values[currentNode]) insert(left[currentNode], value, address);
        else insert(right[currentNode], value, address);
        update(currentNode);
        maintain(currentNode);
    }

    void erase(int &currentNode, int value) {
        propagate(currentNode);
        if (value == values[currentNode]) {
            if (!left[currentNode]) {
                _stack[++stackTop] = currentNode;
                currentNode = right[currentNode];
            } else if (!right[currentNode]) {
                _stack[++stackTop] = currentNode;
                currentNode = left[currentNode];
            } else {
                leftRotate(currentNode);
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

    int find(int &currentNode, int value) {
        if (value == values[currentNode]) {
            propagate(currentNode);
            return currentNode;
        }
        propagate(currentNode);
        if (value < values[currentNode]) return find(left[currentNode], value);
        else return find(right[currentNode], value);
    }
} bst;

matrix edge(MAX_N, vint(2));


bool isRoot(int currentNode) {return !nodes[currentNode].parent || (nodes[nodes[currentNode].parent].children[0] != currentNode && nodes[nodes[currentNode].parent].children[1] != currentNode);}

void update(int currentNode) {
    nodes[currentNode].chainMax = max(nodes[currentNode].value, max(nodes[nodes[currentNode].children[0]].chainMax, nodes[nodes[currentNode].children[1]].chainMax));
    nodes[currentNode].chainMin = min(nodes[currentNode].value, min(nodes[nodes[currentNode].children[1]].chainMin, nodes[nodes[currentNode].children[0]].chainMin));
    nodes[currentNode].chainSum = nodes[currentNode].value + nodes[nodes[currentNode].children[0]].chainSum + nodes[nodes[currentNode].children[1]].chainSum;
    nodes[currentNode].stackMax = max(bst.valueMax[nodes[currentNode].subtreeRoot], max(nodes[nodes[currentNode].children[0]].stackMax, nodes[nodes[currentNode].children[1]].stackMax));
    nodes[currentNode].stackMin = min(bst.valueMin[nodes[currentNode].subtreeRoot], min(nodes[nodes[currentNode].children[1]].stackMin, nodes[nodes[currentNode].children[0]].stackMin));
    nodes[currentNode].stackSum = bst.sum[nodes[currentNode].subtreeRoot] + nodes[nodes[currentNode].children[0]].stackSum + nodes[nodes[currentNode].children[1]].stackSum;
    nodes[currentNode].size = bst.size[nodes[currentNode].subtreeRoot] + nodes[nodes[currentNode].children[0]].size + nodes[nodes[currentNode].children[1]].size;
    nodes[currentNode].dSize = 1 + nodes[nodes[currentNode].children[0]].dSize + nodes[nodes[currentNode].children[1]].dSize;
}

void _reverse(int currentNode) {
    nodes[currentNode].reversed ^= 1;
    swap(nodes[currentNode].children[0], nodes[currentNode].children[1]);
}

void makeTree(int currentNode, int _value) {
    nodes[currentNode].stackMake = _value;
    nodes[currentNode].stackPlus = 0;
    if (nodes[currentNode].size) {
        if (nodes[currentNode].subtreeRoot) bst.applyMakeValue(nodes[currentNode].subtreeRoot, _value);
        nodes[currentNode].stackMax = nodes[currentNode].stackMin = _value;
        nodes[currentNode].stackSum = _value * nodes[currentNode].size;
    }
}

void stackPlus(int currentNode, int _value) {
    nodes[currentNode].stackPlus += _value;
    nodes[currentNode].stackSum += _value * nodes[currentNode].size;
    nodes[currentNode].stackMax += _value;
    nodes[currentNode].stackMin += _value;
    if (nodes[currentNode].subtreeRoot) bst.applyAddValue(nodes[currentNode].subtreeRoot, _value);
}

void makeChain(int currentNode, int _value) {
    nodes[currentNode].value = _value;
    nodes[currentNode].chainMake = _value;
    nodes[currentNode].chainPlus = 0;
    nodes[currentNode].chainMax = nodes[currentNode].chainMin = _value;
    nodes[currentNode].chainSum = _value * nodes[currentNode].dSize;
}

void chainPlus(int currentNode, int _value) {
    nodes[currentNode].value += _value;
    nodes[currentNode].chainPlus += _value;
    nodes[currentNode].chainMax += _value;
    nodes[currentNode].chainMin += _value;
    nodes[currentNode].chainSum += _value * nodes[currentNode].dSize;
}

void propagate(int currentNode) {
    if (nodes[currentNode].reversed) {
        if (nodes[currentNode].children[0]) _reverse(nodes[currentNode].children[0]);
        if (nodes[currentNode].children[1]) _reverse(nodes[currentNode].children[1]);
        nodes[currentNode].reversed = 0;
    }
    if (nodes[currentNode].stackMake != INF) {
        if (nodes[currentNode].children[0]) makeTree(nodes[currentNode].children[0], nodes[currentNode].stackMake);
        if (nodes[currentNode].children[1]) makeTree(nodes[currentNode].children[1], nodes[currentNode].stackMake);
        nodes[currentNode].stackMake = INF;
    }
    if (nodes[currentNode].stackPlus) {
        if (nodes[currentNode].children[0]) stackPlus(nodes[currentNode].children[0], nodes[currentNode].stackPlus);
        if (nodes[currentNode].children[1]) stackPlus(nodes[currentNode].children[1], nodes[currentNode].stackPlus);
        nodes[currentNode].stackPlus = 0;
    }
    if (nodes[currentNode].chainMake != INF) {
        if (nodes[currentNode].children[0]) makeChain(nodes[currentNode].children[0], nodes[currentNode].chainMake);
        if (nodes[currentNode].children[1]) makeChain(nodes[currentNode].children[1], nodes[currentNode].chainMake);
        nodes[currentNode].chainMake = INF;
    }
    if (nodes[currentNode].chainPlus) {
        if (nodes[currentNode].children[0]) chainPlus(nodes[currentNode].children[0], nodes[currentNode].chainPlus);
        if (nodes[currentNode].children[1]) chainPlus(nodes[currentNode].children[1], nodes[currentNode].chainPlus);
        nodes[currentNode].chainPlus = 0;
    }
}

void rotate(int currentNode) {
    int _parent = nodes[currentNode].parent, ancestor = nodes[_parent].parent, direction = nodes[_parent].children[0] == currentNode;
    if (!isRoot(_parent)) nodes[ancestor].children[nodes[ancestor].children[1] == _parent] = currentNode;
    nodes[currentNode].parent = ancestor;
    nodes[nodes[currentNode].children[direction]].parent = _parent;
    nodes[_parent].children[1 - direction] = nodes[currentNode].children[direction];
    nodes[_parent].parent = currentNode;
    nodes[currentNode].children[direction] = _parent;
    update(_parent);
    update(currentNode);
}

int getPrevious(int currentNode) {
    int x = currentNode;
    _stack[++stackTop] = x;
    while (!isRoot(x)) {
        x = nodes[x].parent;
        _stack[++stackTop] = x;
    }
    while (~stackTop) propagate(_stack[stackTop--]);
    if (nodes[currentNode].children[0]) {
        currentNode = nodes[currentNode].children[0];
        propagate(currentNode);
        while (currentNode && nodes[currentNode].children[1]) {
            currentNode = nodes[currentNode].children[1];
            propagate(currentNode);
        }
        return currentNode;
    } else {
        while (currentNode && nodes[nodes[currentNode].parent].children[0] == currentNode) currentNode = nodes[currentNode].parent;
        currentNode = nodes[currentNode].parent;
        return currentNode;
    }
}

void splay(int currentNode) {
    int x = currentNode;
    _stack[++stackTop] = x;
    while (!isRoot(x)) {
        x = nodes[x].parent;
        _stack[++stackTop] = x;
        if (x == _treeRoot) _treeRoot = currentNode;
    }
    if (nodes[x].parent) {
        int _parent = nodes[x].parent;
        bst.erase(nodes[_parent].subtreeRoot, x);
    }
    while (~stackTop) propagate(_stack[stackTop--]);
    while (!isRoot(currentNode)) {
        int _parent = nodes[currentNode].parent, ancestor = nodes[_parent].parent;
        if (isRoot(_parent)) rotate(currentNode);
        else if ((nodes[ancestor].children[0] == _parent) == (nodes[_parent].children[0] == currentNode)) rotate(_parent), rotate(currentNode);
        else rotate(currentNode), rotate(currentNode);
    }
    if (nodes[currentNode].parent) {
        int _parent = nodes[currentNode].parent;
        bst.insert(nodes[_parent].subtreeRoot, currentNode, _parent);
    }
}

int access(int currentNode) {
    int x = currentNode;
    while (x) {
        _stack[++stackTop] = x;
        x = nodes[x].parent;
    }
    while (~stackTop) {
        propagate(_stack[stackTop]);
        if (stackTop && isRoot(_stack[stackTop - 1])) bst.find(nodes[_stack[stackTop]].subtreeRoot, _stack[stackTop - 1]);
        stackTop--;
    }
    int son = 0;
    while (currentNode) {
        splay(currentNode);
        if (son) bst.erase(nodes[currentNode].subtreeRoot, son);
        if (nodes[currentNode].children[1]) bst.insert(nodes[currentNode].subtreeRoot, nodes[currentNode].children[1], currentNode);
        nodes[currentNode].children[1] = son;
        update(currentNode);
        son = currentNode;
        currentNode = nodes[currentNode].parent;
    }
    return son;
}

void makeRoot(int currentNode) {
    _treeRoot = currentNode;
    _reverse(access(currentNode));
}

void link(int a, int b) {
    makeRoot(a);
    access(a);
    makeRoot(b);
    access(b);
    nodes[a].parent = b;
    nodes[b].children[1] = a;
    update(b);
}

void _makeTree(int currentNode, int value) {
    access(currentNode);
    int temp = getPrevious(currentNode);
    if (temp) splay(temp);
    makeTree(currentNode, value);
    makeChain(currentNode, value);
    if (temp) update(temp);
}

void _makeChain(int a, int b, int value) {
    makeRoot(a);
    makeChain(access(b), value);
}

void plusTree(int currentNode, int value) {
    access(currentNode);
    splay(currentNode);
    int temp = getPrevious(currentNode);
    if (temp) splay(temp);
    stackPlus(currentNode, value);
    chainPlus(currentNode, value);
    if (temp) update(temp);
}

void plusChain(int a, int b, int value) {
    makeRoot(a);
    chainPlus(access(b), value);
}

bool isSame(int a, int b) {
    while (nodes[a].parent) a = nodes[a].parent;
    while (nodes[b].parent) b = nodes[b].parent;
    return a == b;
}

int sumChain(int a, int b) {
    makeRoot(a);
    return nodes[access(b)].chainSum;
}

int maxChain(int a, int b) {
    makeRoot(a);
    return nodes[access(b)].chainMax;
}

int minChain(int a, int b) {
    makeRoot(a);
    return nodes[access(b)].chainMin;
}

int sumQuery(int a) {
    access(a);
    int temp = getPrevious(a);
    if (temp) splay(temp);
    return nodes[a].stackSum + nodes[a].chainSum;
}

int maxQuery(int a) {
    access(a);
    int temp = getPrevious(a);
    if (temp) splay(temp);
    return max(nodes[a].chainMax, nodes[a].stackMax);
}

int minQuery(int a) {
    access(a);
    int temp = getPrevious(a);
    if (temp) splay(temp);
    return min(nodes[a].chainMin, nodes[a].stackMin);
}
