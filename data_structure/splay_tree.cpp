#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using vint = vector<int>;
using matrix = vector<vint>;
using vll = vector<ll>;
using vull = vector<ull>;
using matrlx = vector<vll>;
using fourdimensionalMatrix = vector<matrix>; // ;;
using pii = pair<int, int>;
using vpii = vector<pii>;
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
const int SEMI_INF = 0x3f3f;
const double PI = acos(-1);

struct node {
    node* left, *right, *parent;
    ll size, value, sum, maxValue, minValue;
    bool flip, dummy;

    node() : node(0) {}
    node(ll value) : node(value, nullptr) {}
    node(ll value, node *parent) : value(value), sum(value), maxValue(value), minValue(value), parent(parent) {
        left = right = nullptr;
        size = 1;
        flip = dummy = false;
    }
    ~node() {
        if (left) delete left;
        if (right) delete right;
    }

    bool isLeft() const {return this == parent->left;}

    void rotate() {
        if (isLeft()) {
            if (right) right->parent = parent;
            parent->left = right;
            right = parent;
        } else {
            if (left) left->parent = parent;
            parent->right = left;
            left = parent;
        }
        if (parent->parent) {
            if (parent->isLeft()) parent->parent->left = this;
            else parent->parent->right = this;
        }
        node *temp = parent;
        parent = temp->parent;
        temp->parent = this;
        temp->update();
        update();
    }

    void update() {
        size = 1;
        sum = minValue = maxValue = value;
        if (left) {
            size += left->size;
            sum += left->sum;
            minValue = min(minValue, left->minValue);
            maxValue = max(maxValue, left->maxValue);
        }
        if (right) {
            size += right->size;
            sum += right->sum;
            minValue = min(minValue, right->minValue);
            maxValue = max(maxValue, right->maxValue);
        }
    }

    void updateValue(int value) {
        value = value;
        update();
    }

    void push() {
        if (flip) {
            swap(left, right);
            if (left) left->flip ^= 1;
            if (right) right->flip ^= 1;
            flip = false;
        }
    }
};

class splayTree {
    node *root;
    vector<node*> nodes;

public:
    splayTree() : root(nullptr) {}

    ~splayTree() {
        if (root) delete root;
    }

    void splay(node *_node, node *targetParent = nullptr) {
        for (; _node->parent != targetParent; _node->rotate()) {
            if (_node->parent->parent != targetParent) _node->parent->parent->push();
            _node->parent->push();
            _node->push();
            if (_node->parent->parent == targetParent) continue;
            if (_node->isLeft() == _node->parent->isLeft()) _node->parent->rotate();
            else _node->rotate();
        }
        _node->push();
        if (!targetParent) root = _node;
    }

    void kth(int k) {
        node *current = root;
        current->push();
        while (true) {
            while (current->left && current->left->size > k) {
                current = current->left;
                current->push();
            }
            if (current->left) k -= current->left->size;
            if (!k--) break;
            current = current->right;
            current->push();
        }
        splay(current);
    }

    node *gather(int left, int right) {
        kth(right + 1);
        node *temp = root;
        kth(left - 1);
        splay(temp, root);
        return root->right->left;
    }

    void init(const vint &values) {
        if (root) delete root;
        root = new node(-INF);
        int n = values.size();
        node *current = root;
        for (int i = 1; i <= n; i++) {
            nodes[i] = current->right = new node(values[i - 1], current);
            current = current->right;
        }
        current->right = new node(INF, current);
        for (int i = n; i >= 1; i--) nodes[i]->update();
        splay(nodes[(n + 1) >> 1]);
    }

    void _init(const int &n) {
        if (root) delete root;
        root = new node(-INF);
        node *current = root;
        for (int i = 1; i <= n; i++) {
            nodes[i] = current->right = new node(i, current);
            current = current->right;
        }
        current->right = new node(INF, current);
        for (int i = n; i >= 1; i--) nodes[i]->update();
        splay(nodes[(n + 1) >> 1]);
    }

    void print(node *_node) {
        _node->push();
        if (_node->left) print(_node->left);
        if (abs(_node->value) != INF) cout << _node->value << ' ';
        if (_node->right) print(_node->right);
    }

    void flip(int left, int right) {
        node *target = gather(left, right);
        target->flip ^= 1;
    }

    void shift(int left, int right, int k) {
        gather(left, right);
        k %= right - left + 1;
        if (k < 0) k += right - left + 1;
        if (k) {
            flip(left, right);
            flip(left, left + k - 1);
            flip(left + k, right);
        }
    }

    void getIndex(int k) {splay(nodes[k]);}

    void insert(int k, int value) {
		kth(k);
		node *_root = root, *temp = new node(value, root);
		_root->left->parent = temp;
		temp->left = _root->left;
		_root->left = temp;
		splay(temp);
	}

	void erase(int k) {
		node *temp = gather(k, k);
		temp->parent->left = nullptr;
		splay(temp->parent);
		delete temp;
	}
};
