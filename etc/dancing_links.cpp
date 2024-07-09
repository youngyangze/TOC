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
const int SIZE = 9, SUBGRID_SIZE = 3, ROW_SIZE = SIZE * SIZE * SIZE, COL_SIZE = SIZE * SIZE * 4;

struct node {
    node *left, *right, *up, *down, *column;
    int size, row;
};

class dancingLinks {
private:
    int rows, cols;
    node *head;
    vector<node*> columnHeaders, rowHeaders;

public:
    dancingLinks(int rows, int cols) : rows(rows), cols(cols) {
        head = new node();
        head->left = head->right = head;
        columnHeaders.resize(cols);
        for (int i = 0; i < cols; i++) {
            node *col = new node();
            col->column = col;
            col->size = 0;
            col->up = col->down = col;
            columnHeaders[i] = col;
            col->left = head->left;
            col->right = head;
            head->left->right = col;
            head->left = col;
        }
        rowHeaders.resize(rows);
        for (int i = 0; i < rows; i++) rowHeaders[i] = nullptr;
    }

    void addNode(int row, int col) {
        node *newNode = new node();
        newNode->row = row;
        newNode->column = columnHeaders[col];
        columnHeaders[col]->size++;
        newNode->down = columnHeaders[col];
        newNode->up = columnHeaders[col]->up;
        columnHeaders[col]->up->down = newNode;
        columnHeaders[col]->up = newNode;
        if (!rowHeaders[row]) {
            rowHeaders[row] = newNode;
            newNode->right = newNode->left = newNode;
        } else {
            newNode->left = rowHeaders[row];
            newNode->right = rowHeaders[row]->right;
            rowHeaders[row]->right->left = newNode;
            rowHeaders[row]->right = newNode;
        }
    }

    void cover(node *column) {
        column->right->left = column->left;
        column->left->right = column->right;
        for (node *row = column->down; row != column; row = row->down) {
            for (node *node = row->right; node != row; node = node->right) {
                node->down->up = node->up;
                node->up->down = node->down;
                node->column->size--;
            }
        }
    }

    void uncover(node *column) {
        for (node *row = column->up; row != column; row = row->up) {
            for (node *node = row->left; node != row; node = node->left) {
                node->column->size++;
                node->down->up = node;
                node->up->down = node;
            }
        }
        column->right->left = column;
        column->left->right = column;
    }

    bool search(vint &result) {
        if (head->right == head) return true;
        node *pointer = nullptr;
        int minSize = INF;
        for (node *node = head->right; node != head; node = node->right) {
            if (node->size < minSize) {
                minSize = node->size;
                pointer = node;
            }
        }
        cover(pointer);
        for (node *row = pointer->down; row != pointer; row = row->down) {
            result.push_back(row->row);
            for (node *node = row->right; node != row; node = node->right) {
                cover(node->column);
            }
            if (search(result)) return true;
            result.pop_back();
            for (node *node = row->left; node != row; node = node->left) {
                uncover(node->column);
            }
        }
        uncover(pointer);
        return false;
    }
};
