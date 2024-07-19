#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
using vint = vector<int>;
using matrix = vector<vint>;
using vll = vector<ll>;
using vull = vector<ull>;
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

class node {
public:
    node *left, *right, *parent;
    ll value, size, sum, maxValue, minValue;
    bool isDummy, flip;

    node(ll n, node *par) : value(n), parent(par) {
        left = right = nullptr;
        sum = maxValue = minValue = n;
        size = 1;
        isDummy = false;
        flip = false;
    }

    node(int n) : node(n, nullptr) {}
    node() : node(0) {}

    ~node() {
        if (left) delete left;
        if (right) delete right;
    }
};

class splayTree {
private:
    node *root;
    vector<node*> nodePointers;

public:
    splayTree() : root(nullptr) {}

    ~splayTree() {
        if (root) delete root;
    }

    void update(node *_node) {
        _node->size = 1;
        _node->sum = _node->minValue = _node->maxValue = _node->value;
        if (_node->left) {
            _node->size += _node->left->size;
            _node->sum += _node->left->sum;
            _node->minValue = min(_node->minValue, _node->left->minValue);
            _node->maxValue = max(_node->maxValue, _node->left->maxValue);
        }
        if (_node->right) {
            _node->size += _node->right->size;
            _node->sum += _node->right->sum;
            _node->minValue = min(_node->minValue, _node->right->minValue);
            _node->maxValue = max(_node->maxValue, _node->right->maxValue);
        }
    }

    void push(node *_node) {
        if (!_node->flip) return;
        swap(_node->left, _node->right);
        if (_node->left) _node->left->flip = !_node->left->flip;
        if (_node->right) _node->right->flip = !_node->right->flip;
        _node->flip = false;
    }

    node* gather(int start, int end) {
        kth(end + 1);
        node *temp = root;
        kth(start - 1);
        splay(temp, root);
        return root->right->left;
    }

    void rotate(node *_node) {
        node *parent = _node->parent, *y;
        push(parent); push(_node);
        if (_node == parent->left) {
            parent->left = y = _node->right;
            _node->right = parent;
        } else {
            parent->right = y = _node->left;
            _node->left = parent;
        }
        _node->parent = parent->parent;
        parent->parent = _node;
        if (y) y->parent = parent;
        if (_node->parent) {
            if (parent == _node->parent->left) _node->parent->left = _node;
            else _node->parent->right = _node;
        } else {
            root = _node;
        }
        update(parent); update(_node);
    }

    void splay(node *_node, node *goal = nullptr) {
        node *y;
        while (_node->parent != goal) {
            node *parent = _node->parent;
            if (parent->parent == goal) {
                rotate(_node);
                break;
            }
            node *grandparent = parent->parent;
            if ((parent->left == _node) == (grandparent->left == parent)) {
                rotate(parent); rotate(_node);
            } else {
                rotate(_node); rotate(_node);
            }
        }
        if (!goal) root = _node;
    }

    void init(int n) {
        if (root) delete root;
        root = new node(-INF);
        auto current = root;
        nodePointers.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            nodePointers[i] = current->right = new node(i, current);
            current = current->right;
        }
        current->right = new node(INF, current);
        root->isDummy = current->right->isDummy = true;
        for (int i = n; i >= 1; i--) update(nodePointers[i]);
        splay(nodePointers[n >> 1]);
    }

    void flip(int start, int end) {
        node *_node = gather(start, end);
        _node->flip = !_node->flip;
    }

    void shift(int start, int end, int k) {
        node *_node = gather(start, end);
        cout << _node->minValue << ' ' << _node->maxValue << ' ' << _node->sum << endl;
        if (k >= 0) {
            k %= (end - start + 1);
            if (!k) return;
            flip(start, end);
            flip(start, start + k - 1);
            flip(start + k, end);
        } else {
            k *= -1;
            k %= (end - start + 1);
            if (!k) return;
            flip(start, end);
            flip(start, end - k);
            flip(end - k + 1, end);
        }
    }

    void getIndex(int k) {
        splay(nodePointers[k]);
        cout << root->left->size << endl;
    }

    void kth(int k) {
        node *current = root;
        push(current);
        while (true) {
            while (current->left && current->left->size > k) {
                current = current->left;
                push(current);
            }
            if (current->left) k -= current->left->size;
            if (!k) break;
            k--;
            current = current->right;
            push(current);
        }
        splay(current);
    }

    void print(node *_node) {
        push(_node);
        if (_node->left) print(_node->left);
        if (!_node->isDummy) cout << _node->value << ' ';
        if (_node->right) print(_node->right);
    }

    node* getRoot() {
        return root;
    }
};
