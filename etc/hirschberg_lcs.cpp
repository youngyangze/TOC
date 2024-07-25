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

string a, b, result;

void hirschberg(int start, int end, int _start, int _end) {
	if (start > end) return;
	if (start == end) {
		for (int i = _start; i <= _end; i++) {
            if (b[i] == a[start]) {
                result += b[i];
                break;
            }
        }
		return;
	}

	const int mid = start + end >> 1, length = _end - _start + 3;
	vint up(length), lower(length), previous(length);
	for (int i = start; i <= mid; i++) {
		for (int j = _start; j <= _end; j++) {
			if (a[i] == b[j]) up[j - _start + 1] = previous[j - _start] + 1;
			else up[j - _start + 1] = max(up[j - _start], previous[j - _start + 1]);
		}
		previous = up;
	}
	fill(all(previous), 0);
	for (int i = end; i > mid; i--) {
		for (int j = _end; j >= _start; j--) {
			if (a[i] == b[j]) lower[j - _start + 1] = previous[j - _start + 2] + 1;
			else lower[j - _start + 1] = max(lower[j - _start + 2], previous[j - _start + 1]);
		}
		previous = lower;
	}

	int max = -1, index = 0;
	for (int i = _start; i <= _end + 1; i++) {
		if (max < up[i - _start] + lower[i - _start + 1]){
            max = up[i - _start] + lower[i - _start + 1];
            index = i;
        }
	}

	hirschberg(start, mid, _start, index - 1);
	hirschberg(mid + 1, end, index, _end);
}
