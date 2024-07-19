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

class SplayTree {
private:
    node *root;
    vector<node*> nodePointers;

    void update(node *node) {
        node->size = 1;
        node->sum = node->minValue = node->maxValue = node->value;
        if (node->left) {
            node->size += node->left->size;
            node->sum += node->left->sum;
            node->minValue = min(node->minValue, node->left->minValue);
            node->maxValue = max(node->maxValue, node->left->maxValue);
        }
        if (node->right) {
            node->size += node->right->size;
            node->sum += node->right->sum;
            node->minValue = min(node->minValue, node->right->minValue);
            node->maxValue = max(node->maxValue, node->right->maxValue);
        }
    }

    void push(node *node) {
        if (!node->flip) return;
        swap(node->left, node->right);
        if (node->left) node->left->flip = !node->left->flip;
        if (node->right) node->right->flip = !node->right->flip;
        node->flip = false;
    }

    node* gather(int start, int end) {
        kth(end + 1);
        auto temp = root;
        kth(start - 1);
        splay(temp, root);
        return root->right->left;
    }

    void rotate(node *node) {
        auto parent = node->parent;
        node *y;
        push(parent); push(node);
        if (node == parent->left) {
            parent->left = y = node->right;
            node->right = parent;
        } else {
            parent->right = y = node->left;
            node->left = parent;
        }
        node->parent = parent->parent;
        parent->parent = node;
        if (y) y->parent = parent;
        if (node->parent) {
            if (parent == node->parent->left) node->parent->left = node;
            else node->parent->right = node;
        } else {
            root = node;
        }
        update(parent); update(node);
    }

    void splay(node *node, node *goal = nullptr) {
        node *y;
        while (node->parent != goal) {
            node *parent = node->parent;
            if (parent->parent == goal) {
                rotate(node);
                break;
            }
            auto grandparent = parent->parent;
            if ((parent->left == node) == (grandparent->left == parent)) {
                rotate(parent); rotate(node);
            } else {
                rotate(node); rotate(node);
            }
        }
        if (!goal) root = node;
    }

public:
    SplayTree() : root(nullptr) {}

    ~SplayTree() {
        if (root) delete root;
    }

    void initialize(int n) {
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
        node *node = gather(start, end);
        node->flip = !node->flip;
    }

    void shift(int start, int end, int k) {
        node *node = gather(start, end);
        cout << node->minValue << ' ' << node->maxValue << ' ' << node->sum << endl;
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
        auto current = root;
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

    void print(node *node) {
        push(node);
        if (node->left) print(node->left);
        if (!node->isDummy) cout << node->value << ' ';
        if (node->right) print(node->right);
    }

    node* getRoot() {
        return root;
    }
};
