// totally not boyfriend
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
const int MEMORY_SIZE = 32768, MAX_COMMANDS = 128000;

void runBrainfuck(const string &program) {
    vector<char> memory(MEMORY_SIZE, 0);
    int ptr = 0;
    unordered_map<int, int> loopMap;
    stack<int> loopStack;

    for (int i = 0; i < program.size(); i++) {
        if (program[i] == '[') {
            loopStack.push(i);
        } else if (program[i] == ']') {
            if (loopStack.empty()) {
                cout << "COMPILE ERROR" << endl;
                return;
            }
            int start = loopStack.top();
            loopStack.pop();
            loopMap[start] = i;
            loopMap[i] = start;
        }
    }

    if (!loopStack.empty()) {
        cout << "COMPILE ERROR" << endl;
        return;
    }

    for (int pc = 0; pc < program.size(); pc++) {
        switch (program[pc]) {
            case '>':
                ptr = (ptr + 1) % MEMORY_SIZE;
                break;
            case '<':
                ptr = (ptr - 1 + MEMORY_SIZE) % MEMORY_SIZE;
                break;
            case '+':
                memory[ptr] = (memory[ptr] + 1) % 256;
                break;
            case '-':
                memory[ptr] = (memory[ptr] - 1 + 256) % 256;
                break;
            case '.':
                cout << memory[ptr];
                break;
            case '[':
                if (memory[ptr] == 0) {
                    pc = loopMap[pc];
                }
                break;
            case ']':
                if (memory[ptr] != 0) {
                    pc = loopMap[pc];
                }
                break;
            default:
                break;
        }
    }
    cout << endl;
}
