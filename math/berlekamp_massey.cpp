#include <bits/extc++.h>
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
using vint = vector<int>;
using matrix = vector<vint>;
using vll = vector<ll>;
using matrlx = vector<vll>;
using fourdimensionalMatrix = vector<matrix>;  // ;;
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
const ll MOD = 1e9 + 7;

ll _pow(ll base, ll exp) {
    ll ret = 1;
    while (exp) {
        if (exp & 1) ret = (ret * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return ret;
}

vll berlekampMassey(vll x) {
    vll ls, current;
    ll lf, ld;
    for (ll i = 0; i < x.size(); i++) {
        ll t = 0;
        for (ll j = 0; j < current.size(); j++) t = (t + 1ll * x[i - j - 1] * current[j]) % MOD;
        if ((t - x[i]) % MOD == 0) continue;
        if (current.empty()) {
            current.resize(i + 1);
            lf = i;
            ld = (t - x[i]) % MOD;
            continue;
        }
        ll k = -(x[i] - t) * _pow(ld, MOD - 2) % MOD;
        vll c(i - lf - 1);
        c.emplace_back(k);
        for (auto &j : ls) c.emplace_back(-j * k % MOD);
        if (c.size() < current.size()) c.resize(current.size());
        for (ll j = 0; j < current.size(); j++) c[j] = (c[j] + current[j]) % MOD;
        if (i - lf + (ll)ls.size() >= (ll)current.size()) tie(ls, lf, ld) = make_tuple(current, i, (t - x[i]) % MOD);
        current = c;
    }
    for (auto &i : current) i = (i % MOD + MOD) % MOD;
    return current;
}

ll getNth(vll rec, vll DP, ll n) {
    ll m = rec.size();
    vll s(m), t(m);
    s[0] = 1;
    if (m != 1)
        t[1] = 1;
    else
        t[0] = rec[0];
    auto _multiply = [&rec](vll v, vll w) {
        ll m = v.size();
        vll t(2 * m);
        for (ll j = 0; j < m; j++) {
            for (ll k = 0; k < m; k++) {
                t[j + k] += 1ll * v[j] * w[k] % MOD;
                if (t[j + k] >= MOD) t[j + k] -= MOD;
            }
        }
        for (ll j = 2 * m - 1; j >= m; j--) {
            for (ll k = 1; k <= m; k++) {
                t[j - k] += 1ll * t[j] * rec[k - 1] % MOD;
                if (t[j - k] >= MOD) t[j - k] -= MOD;
            }
        }
        t.resize(m);
        return t;
    };
    while (n) {
        if (n & 1) s = _multiply(s, t);
        t = _multiply(t, t);
        n >>= 1;
    }
    ll ret = 0;
    for (ll i = 0; i < m; i++) ret += 1ll * s[i] * DP[i] % MOD;
    return ret % MOD;
}

ll guessNthTerm(vll x, ll n) {
    if (n < x.size()) return x[n];
    vll v = berlekampMassey(x);
    if (v.empty()) return 0;
    return getNth(v, x, n);
}
