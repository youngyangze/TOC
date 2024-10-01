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
const int MAX_ELEMENTS = 1337; // Adjust as needed

template <typename T>
class bitvec {
    static_assert(is_integral<T>::value || is_floating_point<T>::value, "no");

private:
    static constexpr int BITS_PER_ELEMENT = sizeof(T) * 8;
    static constexpr int TOTAL_BITS = MAX_ELEMENTS * BITS_PER_ELEMENT;

    bitset<TOTAL_BITS> data;

    int size_;

    void clear_element(int index) {
        for (int i = 0; i < BITS_PER_ELEMENT; i++) data.reset(index * BITS_PER_ELEMENT + i);
    }

public:
    bitvec() : size_(0) {}

    void push_back(T value) {
        if (size_ >= MAX_ELEMENTS) throw overflow_error("capacity problem");

        if constexpr (is_floating_point<T>::value) {
            union {
                T floatValue;
                unsigned long long intValue;
            } converter;
            converter.floatValue = value;

            for (int i = 0; i < BITS_PER_ELEMENT; i++) data[size_ * BITS_PER_ELEMENT + i] = (converter.intValue >> i) & 1;
        } else {
            for (int i = 0; i < BITS_PER_ELEMENT; i++) data[size_ * BITS_PER_ELEMENT + i] = (static_cast<unsigned long long>(value) >> i) & 1;
        }

        size_++;
    }

    T get(int index) const {
        if (index < 0 || index >= size_) throw out_of_range("bounds");

        if constexpr (is_floating_point<T>::value) {
            unsigned long long intValue = 0;
            for (int i = 0; i < BITS_PER_ELEMENT; i++) {
                if (data[index * BITS_PER_ELEMENT + i]) intValue |= (1ULL << i);
            }

            union {
                unsigned long long intValue;
                T floatValue;
            } converter;
            converter.intValue = intValue;
            return converter.floatValue;
        } else {
            unsigned long long value = 0;
            for (int i = 0; i < BITS_PER_ELEMENT; i++) {
                if (data[index * BITS_PER_ELEMENT + i]) value |= (1ULL << i);
            }
            return static_cast<T>(value);
        }
    }

    T operator[](int index) const {
        return get(index);
    }

    T front() const {
        if (size_ == 0) throw out_of_range("waltuh we need to get capacity");
        return get(0);
    }

    T back() const {
        if (size_ == 0) throw out_of_range("waltuh we need to get capacity");
        return get(size_ - 1);
    }

    void pop_back() {
        if (size_ == 0) throw underflow_error("waltuh we need to get capacity");
        clear_element(--size_);
    }

    void resize(int n) {
        if (n < 0 || n > MAX_ELEMENTS) throw out_of_range("noo");

        if (n < size_) {
            for (int i = n; i < size_; i++) clear_element(i);
        } else if (n > size_) {
            // why???
        }

        size_ = n;
    }

    int size() const {
        return size_;
    }

    void print() const {
        for (int i = 0; i < size_; i++) {
            if constexpr (is_same<T, bool>::value) cout << boolalpha << get(i) << ' ';
            else if constexpr (is_floating_point<T>::value) cout << get(i) << ' ';
            else cout << get(i) << ' ';
        }
        cout << endl;
    }
};
