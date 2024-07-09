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
	int value, counts = 1, sum = 0, lazy = 0;
    bool flip = false;
	node *parent, *left, *right;
	node(int value = 0, node *left = 0, node *right = 0, node *parent = 0): value(value), right(right), left(left){}
};

node *root;

void lazy(node* now) {
	int& _lazy = now->lazy;
	now->value += _lazy;
	if (now->left) {
		now->left->lazy += _lazy;
		now->left->value += _lazy * now->left->counts;
	}
	if (now->right) {
		now->right->lazy += _lazy;
		now->right->lazy += _lazy * now->right->counts;
	}
	_lazy = 0;
	if (!now->flip)return;
	node* t = now->left;
	now->left = now->right;
	now->right = t;
	now->flip = false;
	if (now->left) now->left->flip = !now->left->flip;
	if (now->right) now->right->flip = !now->right->flip;
}

void updates(node* now) {
	now->counts = 1;
	now->sum = now->value;
	if (now->left) {
		now->counts += now->left->counts;
		now->sum += now->left->sum;
	}
	if (now->right) {
		now->counts += now->right->counts;
		now->sum += now->right->sum;
	}
}

void rotates(node *x) {
	node *p = x->parent, *temp;
    lazy(p);
    lazy(x);
	if (x == p->left) {
		p->left = temp = x->right;
		x->right = p;
	}
	else {
		p->right = temp = x->left;
		x->left = p;
	}
	x->parent = p->parent;
    p->parent = x;
	if (temp) temp->parent = p;
	if (x->parent) {
		if (p == x->parent->left) x->parent->left = x;
		else x->parent->right = x;
	} else root = x;

    updates(p);
    updates(x);
}

void splay(node *x) {
	while (x->parent) {
		node *g = x->parent->parent, *p = x->parent;
		if (g) rotates((p->left == x) == (g->left == p) ? p : x);
		rotates(x);
	}
}

bool find(int n) {
	node *current = root;
	if (!current) return false;
	while (current) {
		if (n == current->value) break;
		if (n < current->value) {
			if (!current->left) break;
			current = current->left;
		}
		else {
			if (!current->right) break;
			current = current->right;
		}
	}
	splay(current);
	return n == current->value;
}

void deletes(int n) {
	if (!find(n)) return;
    
	node *p = root;
	if (p->left) {
		if (p->right) {
			root = root->left;
			root->parent = 0;
			node *current = root;
			while (current->right) current = current->right;
			current->right = p->right;
			p->right->parent = current;
			splay(current);
			delete p;
			return;
		}
		root = p->left;
		root->parent = 0;
		delete p;
		return;
	}
	if (p->right) {
		root = p->right;
		root->parent = 0;
		delete p;
		return;
	}
	delete p;
	root = 0;
}

void kth(int k) {
	node* current = root;
	lazy(current);
	while (true) {
		while (current->left && current->left->counts > k) {
			current = current->left;
            lazy(current);
		}
		if (current->left) k -= current->left->counts;
		if (!k--) break;
		current = current->right;
		lazy(current);
	}
	splay(current);
}

void build(int n) {
	node* x;
	root = x = new node();
	x->counts = n;
	for (int i = 1; i < n; i++) {
		x->right = new node();
		x->right->parent = x;
		x = x->right;
		x->counts = n - i;
	}
}

void add(int k, int v) {
	kth(k);
	root->sum += v;
	root->value += v;
}

void interval(int left, int right) {
	kth(left - 1);
	node* current = root;
	root = current->right;
	root->parent = 0;
	kth(right - left + 1);
	root->parent = current;
	current->right = root;
	root = current;
}

int sum(int left, int right) {
	interval(left, right);
	return root->right->left->sum;
}

void flips(int left, int right) {
	interval(left, right);
	root->right->left->flip = !root->right->left->flip;
}
