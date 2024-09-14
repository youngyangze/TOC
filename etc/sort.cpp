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
using cd = complex<double>;

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
        const ll m = 2147483647, a = 16807, q = m / a, r = m % a;
        seed = a * (seed % q) - r * (seed / q);
        if (seed <= 0) seed += m;
        return seed;
    }

    ll randint(int low, int high) {
        return low + _random() % (high - low);
    }
};

template<typename T> void blockMergeSort(vector<T> &a) {
    const int blockSize = (int)sqrt(a.size());
    vector<vector<T>> blocks;
 
    for (int i = 0; i < a.size(); i += blockSize) {
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

template <typename T> void pigeonholeSort(vector<T> &a) {
    if (a.empty()) return;
    
    T minValue = *min_element(all(a)), maxValue = *max_element(all(a));
    int range = maxValue - minValue + 1;
    
    vector<vector<T>> pigeonholes(range);
    for (const auto &n : a) pigeonholes[n - minValue].push_back(n);

    int index = 0;
    for (int i = 0; i < range; i++) {
        for (const auto &n : pigeonholes[i]) a[index++] = n;
    }
}

template <typename T> void stalinSort(vector<T> &a) {
    if (a.empty()) return;

    T maxValue = a[0];
    vector<T> result = {maxValue};
    for (int i = 1; i < a.size(); i++) {
        if (a[i] >= maxValue) {
            maxValue = a[i];
            result.push_back(a[i]);
        }
    }

    a = result;
}

template<typename T> void shuffle(vector<T> &a, PRNG &rng) {
    for (int i = a.size() - 1; i > 0; i--) _swap(a[i], a[rng.randint(0, i + 1)]);
}

template<typename T> inline bool sorted(const vector<T> &a, const vector<T> &b) {
    vector<T> c = a;
    sort(all(c));
    return c == b;
}

template <typename T> void bogoSort(vector<T> &a) {
	PRNG rng(0x94949);
    while (!sorted(a)) shuffle(a, rng);
}

template <typename T> T getMax(const vector<T> &a) {
    T maxValue = a[0];
    for (const T &i : a) {
        if (i > maxValue) maxValue = i;
    }
    return maxValue;
}

template <typename T> void countSort(vector<T> &a, int exp) {
    vector<T> output(a.size());
    vint count(10, 0);

    for (int i = 0; i < a.size(); i++) count[(a[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++) count[i] += count[i - 1];

    for (int i = a.size() - 1; i >= 0; i--) {
        output[count[(a[i] / exp) % 10] - 1] = a[i];
        count[(a[i] / exp) % 10]--;
    }

    for (int i = 0; i < a.size(); i++) a[i] = output[i];
}

template <typename T> void _radixSort(vector<T> &a) {
    T maxValue = getMax(a);
    for (int exp = 1; maxValue / exp > 0; exp *= 10) countSort(a, exp);
}

template <typename T> void radixSort(vector<T> &a) {
    vector<T> positive, negative;

    for (const T &i : a) {
        if (i < 0) negative.push_back(-i);
        else positive.push_back(i);
    }

    if (!positive.empty()) _radixSort(positive);

    if (!negative.empty()) {
        _radixSort(negative);
        reverse(all(negative));
        for (T &i : negative) i = -i;
    }

    a = negative;
    a.insert(a.end(), all(positive));
}

template <typename T> void youngyangzeSort(vector<T> &a, int n) {
    PRNG prng(0xDEADBEEF);
    
    for (int k = 0; k < n * n * n; k++) {
        for (int i = 0; i < a.size(); i++) {
            int pivot = i;
            T pivotValue = a[pivot];

            for (int j = 0; j < a.size(); j++) {
                if (j != pivot) {
                    if (a[j] < pivotValue && j > pivot) _swap(a[j], a[pivot]);
                    else if (a[j] > pivotValue && j < pivot) _swap(a[j], a[pivot]);
                }
            }
        }
    }
}

void fft(vector<cd> &a, bool invert) {
    int n = a.size();
    if (n == 1) return;

    vector<cd> a0(n / 2), a1(n / 2);
    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[2 * i];
        a1[i] = a[2 * i + 1];
    }
    fft(a0, invert);
    fft(a1, invert);

    double ang = 2 * PI / n * (invert ? -1 : 1);
    cd w(1), wn(cos(ang), sin(ang));
    for (int i = 0; 2 * i < n; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i + n / 2] = a0[i] - w * a1[i];
        if (invert) {
            a[i] /= 2;
            a[i + n / 2] /= 2;
        }
        w *= wn;
    }
}

template <typename T> vector<T> multiply(const vector<T> &a, const vector<T> &b) {
    vector<cd> fa(all(a)), fb(all(b));
    int n = 1;
    while (n < a.size() + b.size()) n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++) fa[i] *= fb[i];
    fft(fa, true);

    vector<T> result(n);
    for (int i = 0; i < n; i++) result[i] = round(fa[i].real());
    return result;
}

template <typename T> void fftSort(vector<T> &a) {
    if (a.empty()) return;

    T minValue = *min_element(all(a)), maxValue = *max_element(all(a));
    int offset = -minValue;
    vint frequency(maxValue - minValue + 1, 0);

    for (const T &i : a) frequency[i + offset]++;

    vint sortedFrequency = multiply(frequency, {1});
    a.clear();
    for (int i = 0; i < sortedFrequency.size(); i++) {
        while (sortedFrequency[i] > 0) {
            a.push_back(i - offset);
            sortedFrequency[i]--;
        }
    }
}

template <typename T> int partition(vector<T> &a, int low, int high) {
    T pivot = a[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (a[j] <= pivot) _swap(a[++i], a[j]);
    }
    _swap(a[i + 1], a[high]);
    return i + 1;
}

template <typename T> void quickSort(vector<T> &a, int low, int high) {
    if (low < high) {
        int pivot = partition(a, low, high);
        quickSort(a, low, pivot - 1);
        quickSort(a, pivot + 1, high);
    }
}

template <typename T> void quickSort(vector<T> &a) {
    quickSort(a, 0, a.size() - 1);
}

template <typename T> void countSort(vector<T> &a) {
    if (a.empty()) return;
    T minValue = *min_element(all(a)), maxValue = *max_element(all(a));

    int range = maxValue - minValue + 1;
    vint count(range, 0);
    for (int i = 0; i < a.size(); i++) count[a[i] - minValue]++;

    int index = 0;
    for (int i = 0; i < range; i++) {
        while (count[i] > 0) {
            a[index++] = i + minValue;
            count[i]--;
        }
    }
}

template <typename T> void print(const vector<T> &a) {
    for (const auto &i : a) cout << i << ' ';
    cout << endl;
}

vint b;
system_clock::time_point starts, __________ends;

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
                if (uniqueNumbers.find(rnn) == uniqueNumbers.end()) {
                    uniqueNumbers.insert(rnn);
                    a.emplace_back(rnn);
                }
            }
        } else {
            for (int i = 0; i < n; i++) a.emplace_back(i);
            shuffle(a, rng);
        }
    }

    print(a);
    cout << "Checking..." << endl << endl;

    b = a;
    cout << "Checking: Block Merge Sort" << endl;
    starts = system_clock::now();
    blockMergeSort(b);
    __________ends = system_clock::now();
    milliseconds time = duration_cast<milliseconds>(__________ends - starts);
    cout << (sorted(a, b) ? "AC, " : "WA, ") << time.count() << "ms" << endl << endl;

    b = a;
    cout << "Checking: Bubble Sort" << endl;
    starts = system_clock::now();
    bubbleSort(b);
    __________ends = system_clock::now();
    time = duration_cast<milliseconds>(__________ends - starts);
    cout << (sorted(a, b) ? "AC, " : "WA, ") << time.count() << "ms" << endl << endl;

    b = a;
    cout << "Checking: Bubble Sort (Optimized)" << endl;
    starts = system_clock::now();
    optimizedBubbleSort(b);
    __________ends = system_clock::now();
    time = duration_cast<milliseconds>(__________ends - starts);
    cout << (sorted(a, b) ? "AC, " : "WA, ") << time.count() << "ms" << endl << endl;

    /*b = a;
    cout << "Checking: Bogo Sort" << endl;
    starts = system_clock::now();
    bogoSort(b);
    __________ends = system_clock::now();
    time = duration_cast<milliseconds>(__________ends - starts);
    cout << (sorted(a, b) ? "AC, " : "WA, ") << time.count() << "ms" << endl << endl;*/

    b = a;
    cout << "Checking: Pigeon Hole Sort" << endl;
    starts = system_clock::now();
    pigeonholeSort(b);
    __________ends = system_clock::now();
    time = duration_cast<milliseconds>(__________ends - starts);
    cout << (sorted(a, b) ? "AC, " : "WA, ") << time.count() << "ms" << endl << endl;

    b = a;
    cout << "Checking: Stalin Sort" << endl;
    starts = system_clock::now();
    stalinSort(b);
    __________ends = system_clock::now();
    time = duration_cast<milliseconds>(__________ends - starts);
    cout << (sorted(a, b) ? "AC, " : "WA, ") << time.count() << "ms" << endl << endl;

    b = a;
    cout << "Checking: Radix Sort" << endl;
    starts = system_clock::now();
    radixSort(b);
    __________ends = system_clock::now();
    time = duration_cast<milliseconds>(__________ends - starts);
    cout << (sorted(a, b) ? "AC, " : "WA, ") << time.count() << "ms" << endl << endl;

    b = a;
    cout << "Checking: youngyangze Sort" << endl;
    starts = system_clock::now();
    youngyangzeSort(b, b.size());
    __________ends = system_clock::now();
    time = duration_cast<milliseconds>(__________ends - starts);
    cout << (sorted(a, b) ? "AC, " : "WA, ") << time.count() << "ms" << endl << endl;

    b = a;
    cout << "Checking: FFT Sort" << endl;
    starts = system_clock::now();
    fftSort(b);
    __________ends = system_clock::now();
    time = duration_cast<milliseconds>(__________ends - starts);
    cout << (sorted(a, b) ? "AC, " : "WA, ") << time.count() << "ms" << endl << endl;

    b = a;
    cout << "Checking: Quick Sort" << endl;
    starts = system_clock::now();
    quickSort(b);
    __________ends = system_clock::now();
    time = duration_cast<milliseconds>(__________ends - starts);
    cout << (sorted(a, b) ? "AC, " : "WA, ") << time.count() << "ms" << endl << endl;

    b = a;
    cout << "Checking: Count Sort" << endl;
    starts = system_clock::now();
    countSort(b);
    __________ends = system_clock::now();
    time = duration_cast<milliseconds>(__________ends - starts);
    cout << (sorted(a, b) ? "AC, " : "WA, ") << time.count() << "ms" << endl << endl;
}

int main() {
    fastio;
    test(10, true, false);
}
