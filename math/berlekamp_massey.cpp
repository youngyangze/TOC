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
const int MOD = 1e9 + 7;

ull _pow(ull base, ull exp) {
	ull ret = 1;
	while (exp){
		if(exp & 1) ret *= base % MOD;
		exp *= exp % MOD;
		exp >>= 1;
	}
	return ret;
}

vint berlekampMassey(vint x) {
	vint ls, current;
	int lf, ld;
	for (int i = 0; i < x.size(); i++) {
		ull t = 0;
		for (int j = 0; j < current.size(); j++)t = (t + 1ll * x[i - j - 1] * current[j]) % MOD;
		if ((t - x[i]) % MOD == 0) continue;
		if (current.empty()) {
			current.resize(i + 1);
			lf = i;
			ld = (t - x[i]) % MOD;
			continue;
		}
		ull k = -(x[i] - t) * _pow(ld, MOD - 2) % MOD;
		vint c(i - lf - 1);
		c.push_back(k);
		for (auto &j : ls) c.push_back(-j * k % MOD);
		if (c.size() < current.size()) c.resize(current.size());
		for (int j = 0; j < current.size(); j++) c[j] = (c[j] + current[j]) % MOD;
		if (i - lf + (int)ls.size() >= (int)current.size()) tie(ls, lf, ld) = make_tuple(current, i, (t - x[i]) % MOD);
		current = c;
	}
	for(auto &i : current) i = (i % MOD + MOD) % MOD;
	return current;
}

int getNth(vint rec, vint dp, ull n){
	int m = rec.size();
	vint s(m), t(m);
	s[0] = 1;
	if(m != 1) t[1] = 1;
	else t[0] = rec[0];
	auto _multiply = [&rec](vint v, vint w) {
		int m = v.size();
		vint t(2 * m);
		for(int j = 0; j < m; j++){
			for(int k = 0; k < m; k++){
				t[j + k] += 1ll * v[j] * w[k] % MOD;
				if (t[j + k] >= MOD) t[j + k] -= MOD;
			}
		}
		for(int j = 2 * m - 1; j >= m; j--){
			for(int k = 1; k <= m; k++){
				t[j - k] += 1ll * t[j] * rec[k - 1] % MOD;
				if (t[j - k] >= MOD) t[j - k] -= MOD;
			}
		}
		t.resize(m);
		return t;
	};
	while(n) {
		if(n & 1) s = _multiply(s, t);
		t = _multiply(t, t);
		n >>= 1;
	}
	ull ret = 0;
	for (int i = 0; i < m; i++) ret += 1ll * s[i] * dp[i] % MOD;
	return ret % MOD;
}

int guessNthTerm(vint x, ull n) {
	if(n < x.size()) return x[n];
	vint v = berlekampMassey(x);
	if(v.empty()) return 0;
	return getNth(v, x, n);
}
