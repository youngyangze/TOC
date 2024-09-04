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

const int INF = 0x3f3f3f3f;
const ll VINF = 2e18;
const double PI = acos(-1);

__int128 multiply(__int128 a, __int128 b, __int128 mod) {
    return a * b % mod;
}

ull power(ull base, ull exp, ull mod) {
    ull result = 1;
    while (exp > 0) {
        if (exp & 1) {
            result = multiply(result, base, mod);
        }
        base = multiply(base, base, mod);
        exp >>= 1;
    }
    return result;
}

bool millerRabinTest(ull n, ull d, ull r, ull a) {
    ull x = power(a, d, n);
    if (x == 1 || x == n - 1) return true;
    for (int i = 1; i < r; i++) {
        x = multiply(x, x, n);
        if (x == n - 1) return true;
    }
    return false;
}

bool isPrime(ull n) {
    if (n == 2 || n == 3) return true;
    if (n <= 1 || !(n & 1)) return false;

    ull d = n - 1, r = 0;
    while (!(d & 1)) {
        d >>= 1;
        r++;
    }

    static const vull test = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (const ull &i: test) {
        if (i > n - 2) break;
        if (!millerRabinTest(n, d, r, i)) return false;
    }
    return true;
}

ull gcd(ull a, ull b) {
    while (b) {
        ull temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

ull pollardRho(ull n) {
    if (!(n & 1)) return 2;
    __int128 x = rand() % (n - 2) + 2, y = x, c = rand() % 10 + 1, d = 1;

    auto f = [&](__int128 x) { return (multiply(x, x, n) + c) % n; };

    while (d == 1) {
        x = f(x);
        y = f(f(y));
        d = gcd(abs(x - y), n);
    }
    return d;
}
