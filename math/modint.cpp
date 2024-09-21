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
using cd = complex<double>;

#define fastio ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
#define endl '\n'
#define _CRT_SECURE_NO_WARNINGS
#define all(vec) vec.begin(), vec.end()
#define rall(vec) vec.rbegin(), vec.rend()

const int INF = 0x3f3f3f3f;
const ll VINF = 2e18;
const double PI = acos(-1);
const int MOD = 1e9 + 7;

class modint {
private:
    int n;

public:
    modint() : n(0) {}

    modint(const ll &_n) {
        n = (-MOD <= _n && _n < MOD) ? _n : _n % MOD;
        if (n < 0) n += MOD;
    }

    friend ostream &operator <<(ostream &os, const modint &a) { return os << a.n; }
    friend bool operator==(const modint &a, const modint &b) { return a.n == b.n; }
    friend bool operator!=(const modint &a, const modint &b) { return !(a == b); }
    friend bool operator<(const modint &a, const modint &b) { return a.n < b.n; }

    modint operator -() const {
        return modint(-n);
    }

    modint &operator +=(const modint &m) {
        if ((n += m.n) >= MOD) n -= MOD;
        return *this;
    }

    modint &operator -=(const modint &m) {
        if ((n -= m.n) < 0) n += MOD;
        return *this;
    }

    modint &operator *=(const modint &m) {
        n = (ll)n * m.n % MOD;
        return *this;
    }

    friend modint ipow(modint a, ll p) {
        modint ret = 1;
        for (; p; p /= 2, a *= a) {
            if (p & 1) ret *= a;
        }
        return ret;
    }

    modint inv() const {
        return ipow(*this, MOD - 2);
    }

    modint &operator /=(const modint &m) {
        return (*this) *= m.inv();
    }

    friend modint operator +(modint a, const modint &b) {
        return a += b;
    }

    friend modint operator -(modint a, const modint &b) {
        return a -= b;
    }

    friend modint operator *(modint a, const modint &b) {
        return a *= b;
    }

    friend modint operator /(modint a, const modint &b) {
        return a /= b;
    }

    operator int64_t() const { return n; }
};
