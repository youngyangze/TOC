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

template<typename T> inline bool sorted(const vector<T> &a) {
    vector<T> b = a;
    sort(all(b));
    return a == b;
}

int main() {
    vint a = {5, 1, 8, 0, 1, 5, 0};

    blockMergeSort(a, 3);

    for (auto i: a) cout << i << ' ';
}
