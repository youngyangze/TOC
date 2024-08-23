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

struct line {
	mutable ll m, k, p;
	bool operator <(const line& o) const { return m < o.m; }
	bool operator <(ll x) const { return p < x; }
};

struct lineContainer : multiset<line, less<>> {
	ll div(ll a, ll b) {
		return a / b - ((a ^ b) < 0 && a % b != 0);
	}
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = VINF, 0;
		if (x->m == y->m) x->p = x->k > y->k ? VINF : -VINF;
		else x->p = div(y->k - x->k, x->m - y->m);
		return x->p >= y->p;
	}

	void add(ll m, ll k) {
		auto z = insert({ m, k, 0 }), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
	}

	ll query(ll x) {
		auto l = *lower_bound(x);
		return l.m * x + l.k;
	}
};
