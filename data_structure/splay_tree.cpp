#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using ll = long long;
using vll = vector<ll>;
using vint = vector<int>;
using matrix = vector<vint>;
using pii = pair<int, int>;
using vpii = vector<pii>;
using sint = stack<int>;
using tii = tuple<int, int, int>;
using ordered_set = __gnu_pbds::tree<int, __gnu_pbds::null_type, less<int>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

#define fastio ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
#define endl '\n'
#define _CRT_SECURE_NO_WARNINGS
#define all(vec) vec.begin(), vec.end()

const int INF = 0x3f3f3f3f;
const double PI = acos(-1);
const int MOD = 1e9 + 7;

struct node {
    node *left, *right, *parent;
    ll size, value, sum, maxValue, minValue;
    bool flip, dummy;

    node(ll value = 0, node *parent = nullptr) : value(value), sum(value), maxValue(value), minValue(value), parent(parent) {
        left = right = nullptr;
        size = 1;
        flip = dummy = false;
    }

    ~node() {
        delete left;
        delete right;
    }

    bool isLeft() const {
        return this == parent->left;
    }

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
        auto temp = parent;
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
public:
    node *root;
    vector<node*> nodes;

    splayTree() : root(nullptr) {
        nodes.resize(101010, nullptr);
    }

    ~splayTree() {
        if (root) delete root;
    }

    void splay(node *x, node *p = nullptr) {
        for (; x->parent != p; x->rotate()) {
            if (x->parent->parent != p) x->parent->parent->push();
            x->parent->push();
            x->push();
            if (x->parent->parent != p) (x->isLeft() ^ x->parent->isLeft() ? x : x->parent)->rotate();
        }
        if (!p) root = x;
        x->push();
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

    node *gather(int l, int r) {
        kth(r + 1);
        auto temp = root;
        kth(l - 1);
        splay(temp, root);
        return root->right->left;
    }

    void init(int n) {
        if (root) delete root;
        root = new node(-INF);
        root->dummy = true;
        auto current = root;
        for (int i = 1; i <= n; i++) {
            nodes[i] = current->right = new node(i, current);
            current = current->right;
        }
        current->right = new node(INF, current);
        current->right->dummy = true;
        for (int i = n; i >= 1; i--) nodes[i]->update();
        splay(nodes[n + 1 >> 1]);
    }

    void print(node *x) {
        x->push();
        if (x->left) print(x->left);
        if (!x->dummy) cout << x->value << ' ';
        if (x->right) print(x->right);
    }

    void flip(int l, int r) {
        node *temp = gather(l, r);
        temp->flip ^= 1;
    }

    void shift(int l, int r, int k) {
        gather(l, r);
        k %= r - l + 1;
        if (k < 0) k += r - l + 1;
        if (k) {
            flip(l, r);
            flip(l, l + k - 1);
            flip(l + k, r);
        }
    }
};
