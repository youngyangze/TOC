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

ll _pow(ll base, ll exp) {
    ll ret = 1;
    while (exp) {
      if (exp & 1) ret *= base;
      base *= base;
      exp >>= 1;
    }
    return ret;
}

template<ll mod, ll w>
class ntt{
public:
    void ntt(vll &f, bool inv = false) {
        int n = f.size(), j = 0;
        vll root(n >> 1);
        for (int i = 1; i < n; i++) {
            int bit = (n >> 1);
            while (j >= bit) {
                j -= bit;
                bit >>= 1;
            }
            j += bit;
            if (i < j) swap(f[i], f[j]);
        }
        ll ang = _pow(w, (mod - 1) / n, mod); if (inv) ang = _pow(ang, mod - 2, mod);
        root[0] = 1; for (int i = 1; i < (n >> 1); i++) root[i] = root[i-1] * ang % mod;
        for (int i = 2; i <= n; i <<= 1) {
            int step = n / i;
            for (int j = 0; j<n; j += i) {
                for (int k = 0; k < (i >> 1); k++) {
                    ll u = f[j | k], v = f[j | k | i >> 1] * root[step * k] % mod;
                    f[j | k] = (u + v) % mod;
                    f[j | k | i >> 1] = (u - v) % mod;
                    if (f[j | k | i >> 1] < 0) f[j | k | i >> 1] += mod;
                }
            }
        }
        ll t = _pow(n, mod - 2, mod);
        if (inv) for (int i = 0; i < n; i++) f[i] = f[i] * t % mod;
    }
    vll multiply(vll &_a, vll &_b) {
        vll a(all(_a)), b(all(_b));
        int n = 2;
        while (n < a.size() + b.size()) n <<= 1;
        a.resize(n);
        b.resize(n);
        ntt(a); ntt(b);
        for (int i = 0; i < n; i++) a[i] = a[i] * b[i] % mod;
        ntt(a, 1);
        return a;
    }
};

ll extGCD(ll a, ll b, ll &x, ll &y) {
    ll g = a; x = 1, y = 0;
    if (b) g = extGCD(b, a % b, y, x), y -= a / b * x;
    return g;
}

const ll m1 = 2281701377, m2 = 2483027969, m3 = 998244353;
ntt<m1, 3> ntt1;
ntt<m2, 3> ntt2;
ntt<m3, 3> ntt3;

ll f(const vll &a, ll mod) {
    const int size = a.size();
    vll rmn(size), lm(size, 1);
    ll ans = 0, m = 1;
    vll _m({m1, m2, m3});
    for (int i = 0; i < size; i++) {
        ll k = a[i] - rmn[i]; k %= _m[i];
        if (k < 0) k += _m[i];
        ll x, y;
        extGCD(lm[i], _m[i], x, y);
        k *= x; k %= _m[i];
        if (k < 0) k += _m[i];
        ans += k * m % mod;
        ans %= mod;
        for (int t = i + 1; t < size; t++) {
            rmn[t] += lm[t] * k;
            rmn[t] %= _m[t];
            lm[t] *= _m[i];
            lm[t] %= _m[t];
        }
        m *= _m[i]; m %= mod;
    }
    return ans;
}

vll multiply(vll &a, vll &b, ll mod) {
    vll a1(a), a2(a), a3(a), b1(b), b2(b), b3(b), res1 = ntt1.multiply(a1, b1), res2 = ntt2.multiply(a2, b2), res3 = ntt3.multiply(a3, b3), ret(res1.size());
    for (int i = 0; i < res1.size(); i++) ret[i] = f({res1[i], res2[i], res3[i]}, mod);
    return ret;
}
