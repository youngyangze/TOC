#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace chrono;
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
const int LOW = -100007, HIGH = 100007;

struct PRNG {
    ll seed;
    PRNG(ll seed) : seed(seed) {}

    ll _random() {
        const ll m = 2147483647, a = 16807, q = m / a, R = m % a;
        seed = a * (seed % q) - R * (seed / q);
        if (seed <= 0) seed += m;
        return seed;
    }

    ll randint(int low, int high) {
        return low + _random() % (high - low);
    }
};

template<typename T> void blockMergeSort(vector<T> &a, const T &blockSize) {
    vector<vector<T>> blocks;
 
    for (T i = 0; i < a.size(); i += blockSize) {
        vector<T> block;
        for (T j = i; j < i + blockSize && j < a.size(); j++) block.emplace_back(a[j]);
        sort(all(block));
        blocks.emplace_back(block);
    }

    vector<T> ret;
    while (!blocks.empty()) {
        T minIndex = 0;
        for (T i = 1; i < blocks.size(); i++) {
            if (blocks[i][0] < blocks[minIndex][0]) minIndex = i;
        }
 
        ret.emplace_back(blocks[minIndex][0]);
        blocks[minIndex].erase(blocks[minIndex].begin());

        if (blocks[minIndex].empty()) blocks.erase(blocks.begin() + minIndex);
    }

    a = ret;
}

template<typename T> inline void _swap(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

template <typename T> void bubbleSort(vector<T> &a) {
    for (int i = 0; i < a.size(); i++) {
        for (int j = 1; j < a.size(); j++) {
            if (a[j] < a[j - 1]) _swap(a[j], a[j - 1]);
        }
    }
}

template <typename T> void optimizedBubbleSort(vector<T> &a) {
    for (int i = 0; i < a.size(); i++) {
        bool swapped = false;
        for (int j = 1; j < a.size() - i; j++) {
            if (a[j] < a[j - 1]) {
                swapped = true;
                _swap(a[j], a[j - 1]);
            }
        }
        if (!swapped) break;
    }
}

template<typename T> inline bool sorted(const vector<T> &a) {
    vector<T> b = a;
    sort(all(b));
    return a == b;
}

template<typename T> void shuffle(vector<T> &a, PRNG &rng) {
    for (int i = a.size() - 1; i > 0; i--) _swap(a[i], a[rng.randint(0, i + 1)]);
}

void test(int n, bool allowDuplicate, bool fm) {
    vint a;
    a.reserve(n);
    PRNG rng(0x94949);
    if (allowDuplicate) {
        for (int i = 0; i < n; i++) a.emplace_back(rng.randint(LOW, HIGH + 1));
    } else {
        if (!fm) {
            set<int> uniqueNumbers;
            while (a.size() < n) {
                int rnn = rng.randint(LOW, HIGH + 1);
                if (uniqueNumbers.find(rnn) != uniqueNumbers.end()) {
                    uniqueNumbers.insert(rnn);
                    a.emplace_back(rnn);
                }
            }
        } else {
            for (int i = 0; i < n; i++) a.emplace_back(i);
            shuffle(a, rng);
        }
    }

    for (const int &i : a) cout << i << ' ';
    cout << endl << "Checking..." << endl << endl;
    vint b = a;

    cout << "Checking: Block Merge Sort(block size 3)" << endl;
    system_clock::time_point start = system_clock::now();
    blockMergeSort(b, 3);
    system_clock::time_point end = system_clock::now();
    milliseconds time = duration_cast<milliseconds>(end - start);
    cout << (sorted(b) ? "AC, " : "WA, ") << time.count() << "ms" << endl << endl;

    b = a;
    cout << "Checking: Bubble Sort" << endl;
    start = system_clock::now();
    bubbleSort(b);
    end = system_clock::now();
    time = duration_cast<milliseconds>(end - start);
    cout << (sorted(b) ? "AC, " : "WA, ") << time.count() << "ms" << endl << endl;
    
    b = a;
    cout << "Checking: Bubble Sort(Optimized)" << endl;
    start = system_clock::now();
    optimizedBubbleSort(b);
    end = system_clock::now();
    time = duration_cast<milliseconds>(end - start);
    cout << (sorted(b) ? "AC, " : "WA, ") << time.count() << "ms" << endl << endl;
}

int main() {
    fastio;
    test(458, true, false);
}
