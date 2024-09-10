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

vector<double> ReLU(const vector<double> &a) {
    vector<double> ret(a.size());
    for (size_t i = 0; i < a.size(); i++) ret[i] = max(0.0, a[i]);
    return ret;
}

vector<double> affineTransformation(const vector<vector<double>> &weights, const vector<double> &biases, const vector<double> &a) {
    vector<double> ret(biases.size(), 0.0);
    for (size_t i = 0; i < weights.size(); i++) {
        double sum = 0.0;
        for (size_t j = 0; j < a.size(); j++) sum += a[j] * weights[i][j];
        ret[i] = sum + biases[i];
    }
    return ret;
}

int inference(const matrix &image) {
    vector<double> flatImage;
    for (const auto &row : image) {
        for (int pixel : row) flatImage.push_back((pixel / 255.0 - 0.13089969) / 0.308106541);
    }

    vector<double> result = affineTransformation(_connectedLayerWeight, _connectedLayerBias, ReLU(affineTransformation(connectedLayerWeight, connectedLayerBias, flatImage)));
    return max_element(all(result)) - result.begin();
}
