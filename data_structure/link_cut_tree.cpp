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

struct _ll {
    ll value;
    _ll() : _ll(0) {}
    _ll(ll value) : value(value) {}
    void set(ll v) {value = v;}
    _ll operator + (const _ll &t) const {return _ll(value + t.value);}
};

struct node {
    node *left, *right, *parent;
    int size;
    bool flip;
    _ll value, sum;

    node() : node(_ll()) {}
    node(_ll value) : value(value), sum(value), flip(false), left(nullptr), right(nullptr), parent(nullptr), size(1) {}

    bool isRoot() const {return !parent || (this != parent->left && this != parent->right);}
    bool isLeft() const {return parent && this == parent->left;}

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

        if (!parent->isRoot()) {
            if (parent->isLeft()) parent->parent->left = this;
            else parent->parent->right = this;
        }

        auto t = parent;
        parent = t->parent;
        t->parent = this;
        t->update();
        update();
    }

    void update() {
        size = 1;
        sum = value;
        if (left) {
            size += left->size;
            sum = sum + left->sum;
        }
        if (right) {
            size += right->size;
            sum = sum + right->sum;
        }
    }

    void push() {
        if (flip) {
            swap(left, right);
            flip = false;
            if (left) left->flip ^= 1;
            if (right) right->flip ^= 1;
        }
    }
};

class linkCutTree {
public:
    void splay(node *x) {
        while (!x->isRoot()) {
            if (!x->parent->isRoot()) x->parent->parent->push();
            x->parent->push();
            x->push();
            if (!x->parent->isRoot()) {
                if (x->isLeft() ^ x->parent->isLeft()) x->rotate();
                else x->parent->rotate();
            }
            x->rotate();
        }
        x->push();
    }

    void access(node *x) {
        splay(x);
        x->right = nullptr;
        x->update();
        for (node *y = x; x->parent; splay(x)) {
            y = x->parent;
            splay(y);
            y->right = x;
            y->update();
        }
    }

    void link(node *parent, node *child) {
        access(child);
        access(parent);
        child->left = parent;
        parent->parent = child;
        child->update();
    }

    void cut(node *x) {
        access(x);
        if (x->left) x->left->parent = nullptr;
        x->left = nullptr;
        x->update();
    }

    node* getLCA(node *x, node *y) {
        access(x);
        access(y);
        splay(x);
        return x->parent ? x->parent : x;
    }

    node* getRoot(node *x) {
        access(x);
        while (x->left) x = x->left;
        splay(x);
        return x;
    }

    node* getParent(node *x) {
        access(x);
        if (!x->left) return nullptr;
        x = x->left;
        while (x->right) x = x->right;
        splay(x);
        return x;
    }

    int getDepth(node *x) {
        access(x);
        return x->left ? x->left->size : 0;
    }

    void makeRoot(node *x) {
        access(x);
        splay(x);
        x->flip ^= 1;
    }

    void changeValue(node *x, const _ll &value) {
        access(x);
        x->value = value;
        x->update();
    }

    _ll vertexQuery(node *a, node *b) { // example
        node *lca = getLCA(a, b);
        _ll ret = lca->value;
        access(a);
        splay(lca);
        if (lca->right) ret += lca->right->sum;
        access(b);
        splay(lca);
        if (lca->right) ret += lca->right->sum;
        return ret;
    }
};
