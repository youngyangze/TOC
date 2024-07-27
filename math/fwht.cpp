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
const int MAX_N = 1 << 20;  // 2^20 = 1048576

void fwthOR(vll &a, const bool inv) {
    const ll n = a.size();
    int direction = inv ? -1 : 1;
    for (int s = 2, h = 1; s <= n; s <<= 1, h <<= 1) {
        for (int l = 0; l < n; l += s) {
            for (int i = 0; i < h; i++) {
                a[l + h + i] += direction * a[l + i];
            }
        }
    }
}

void fwhtAND(vll &a, const bool inv) {
    const ll n = a.size();
    int direction = inv ? -1 : 1;
    for (int s = 2, h = 1; s <= n; s <<= 1, h <<= 1) {
        for (int l = 0; l < n; l += s) {
            for (int i = 0; i < h; i++) {
                a[l + i] += direction * a[l + h + i];
            }
        }
    }
}

void fwhtXOR(vll &a, const bool inv) {
    const ll n = a.size();
    for (int s = 2, h = 1; s <= n; s <<= 1, h <<= 1) {
        for (int l = 0; l < n; l += s) {
            for (int i = 0; i < h; i++) {
                ll u = a[l + i], v = a[l + h + i];
                a[l + i] = u + v;
                a[l + h + i] = u - v;
                if (inv) {
                    a[l + i] >>= 1;
                    a[l + h + i] >>= 1;
                }
            }
        }
    }
}
