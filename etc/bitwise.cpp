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
using pii = pair<ll, int>;
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
const int BIT_SIZE = 32;

int bitAnd(int a, int b) {
    bitset<BIT_SIZE> bitsA(a), bitsB(b), ret;

    for (int i = 0; i < BIT_SIZE; i++) {
        if (bitsA[i] == 1) {
            if (bitsB[i] == 1) ret.set(i);
        }
    }

    return static_cast<int>(ret.to_ulong());
}

int bitOr(int a, int b) {
    bitset<BIT_SIZE> bitsA(a), bitsB(b), ret;

    for (int i = 0; i < BIT_SIZE; i++) {
        if (bitsA[i] == 1) ret.set(i);
        else {
            if (bitsB[i] == 1) ret.set(i);
        }
    }

    return static_cast<int>(ret.to_ulong());
}

int bitXor(int a, int b) {
    bitset<BIT_SIZE> bitsA(a), bitsB(b), ret;

    for (int i = 0; i < BIT_SIZE; i++) {
        if (bitsA[i] != bitsB[i]) ret.set(i);
    }

    return static_cast<int>(ret.to_ulong());
}

int bitNot(int a) {
    bitset<BIT_SIZE> bitsA(a), ret;

    for (int i = 0; i < BIT_SIZE; i++) {
        if (bitsA[i] == 0) ret.set(i);
    }

    return static_cast<int>(ret.to_ulong());
}

int leftShift(int a, int shift) {
    bitset<BIT_SIZE> bitsA(a), ret;

    if (shift < 0) return a;

    for (int i = 0; i < BIT_SIZE; i++) {
        if (i + shift < BIT_SIZE) {
            if (bitsA[i] == 1) {
                ret.set(i + shift);
            }
        }
    }

    return static_cast<int>(ret.to_ulong());
}

int rightLogicalShift(int a, int shift) {
    bitset<BIT_SIZE> bitsA(a), ret;

    if (shift < 0) return a;

    for (int i = shift; i < BIT_SIZE; i++) {
        if (bitsA[i] == 1) {
            ret.set(i - shift);
        }
    }

    return static_cast<int>(ret.to_ulong());
}

int rightArithmeticShift(int a, int shift) {
    bitset<BIT_SIZE> bitsA(a), ret;

    if (shift < 0) return a;

    int sign = bitsA[BIT_SIZE - 1];

    for (int i = shift; i < BIT_SIZE; i++) {
        if (bitsA[i] == 1) ret.set(i - shift);
    }

    for (int i = BIT_SIZE - shift; i < BIT_SIZE; i++) {
        if (sign == 1) ret.set(i);
        else ret.reset(i);
    }

    return static_cast<int>(ret.to_ulong());
}

int circularLeftShift(int a, int shift) {
    bitset<BIT_SIZE> bitsA(a), ret;

    if (shift < 0) return a;

    shift = shift % BIT_SIZE;
    for (int i = 0; i < BIT_SIZE; i++) {
        int newPosition = (i + shift) % BIT_SIZE;
        if (bitsA[i] == 1) {
            ret.set(newPosition);
        }
    }

    return static_cast<int>(ret.to_ulong());
}

int circularRightShift(int a, int shift) {
    bitset<BIT_SIZE> bitsA(a), ret;

    if (shift < 0) return a;

    shift = shift % BIT_SIZE;
    for (int i = 0; i < BIT_SIZE; i++) {
        int newPosition = (i - shift);
        if (newPosition < 0) newPosition += BIT_SIZE;
        if (bitsA[i] == 1) ret.set(newPosition);
    }

    return static_cast<int>(ret.to_ulong());
}

void print(int a) {
    bitset<BIT_SIZE> bits(a);
    cout << bits.to_string() << " (" << a << ")" << endl;
}
