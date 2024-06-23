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
	int value;
	node *left, *right, *parent;
	node(int value = 0, node *parent = nullptr, node *left = nullptr , node *right = nullptr) :left(left), right(right), parent(parent), value(value) {}
};

node *root;

void _rotate(node *a) {
	node *p = a->parent, *temp;
	if (a == p->left) {
		temp = p->left = a->right;
		a->right = p;
	}
	else {
		temp = p->right = a->left;
		a->left = p;
	}
	a->parent = p->parent;
	p->parent = a;

	if (temp) {
		temp->parent = p;
		if (p == a->parent->left) a->parent->left = a;
		else a->parent->right = a;
	}
	else root = a;
}

void splay(node *a) {
	while (a->parent) {
		if (a->parent->parent) _rotate((a == a->parent->left) == (a->parent == a->parent->parent->left) ? a->parent : a);
		_rotate(a);
	}
}

bool find(int key) {
	node *now = root;
	if (!now) return 0;
	while (now) {
		if (key == now->value) break;
		if (key < now->value) {
			if (!now->left) break;
			now = now->left;
		}
		else {
			if (!now->right) break;
			now = now->right;
		}
	}
	splay(now);
	return key == now->value;
}

void _insert(int key, node *previous, node *&now) {
	if (!now) {
		now = new node(key, previous);
		splay(now);
		return;
	}
	if (now->value == key) return;
	else if (now->value < key) _insert(key, now, now->right);
	else _insert(key, now, now->left);
}

void _delete(int key) {
	if (!find(key)) return;
	
	node *now = root;
	if (now->left && now->right) {
		root = now->left;
		root->parent = nullptr;
		node *temp = root;
		while (temp->right) temp = temp->right;
		temp->right = now->right;
		now->right->parent = temp;
		splay(temp);
	}
	else if (now->left) {
		root = now->left;
		root->parent = nullptr;
	}
	else if (now->right) {
		root = now->right;
		root->parent = nullptr;
	}
	delete now;
	return;
}
