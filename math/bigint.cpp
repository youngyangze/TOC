#include <bits/stdc++.h>

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

#define fastio ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
#define endl '\n'
#define _CRT_SECURE_NO_WARNINGS
#define all(vec) vec.begin(), vec.end()
#define rall(vec) vec.rbegin(), vec.rend()

const int INF = 0x3f3f3f3f;
const ll VINF = 2e18;
const double PI = acos(-1);

class bigint {
public:
    string value;
    bool negative;

    bigint() : value("0"), negative(false) {}
    bigint(string s) { 
        if (s[0] == '-') {
            negative = true;
            value = s.substr(1);
        } else {
            negative = false;
            value = s;
        }
        trim();
    }

    bigint(ll n) {
        negative = (n < 0);
        value = to_string(negative ? -n : n);
    }

    friend ostream &operator<<(ostream &out, const bigint &b) {
        if (b.negative && b.value != "0") out << '-';
        out << b.value;
        return out;
    }

    friend istream &operator>>(istream &in, bigint &b) {
        string s;
        in >> s;
        b = bigint(s);
        return in;
    }

    bool operator ==(const bigint &b) const {
        return value == b.value && negative == b.negative;
    }

    bool operator !=(const bigint &b) const {
        return !(*this == b);
    }

    bool operator <(const bigint &b) const {
        if (negative != b.negative) return negative;
        if (value.length() != b.value.length()) return negative ? value.length() > b.value.length() : value.length() < b.value.length();
        return negative ? value > b.value : value < b.value;
    }

    bool operator >(const bigint &b) const {
        return b < *this;
    }

    bool operator <=(const bigint &b) const {
        return !(b < *this);
    }

    bool operator >=(const bigint &b) const {
        return !(*this < b);
    }

    bigint operator +() const {
        return *this;
    }

    bigint operator -() const {
        bigint result = *this;
        if (result.value != "0") result.negative = !negative;
        return result;
    }

    bigint operator +(const bigint &b) const {
        if (negative == b.negative) {
            bigint result = add(value, b.value);
            result.negative = negative;
            return result;
        }
        if (absGreater(*this, b)) {
            bigint result = subtract(value, b.value);
            result.negative = negative;
            return result;
        }
        bigint result = subtract(b.value, value);
        result.negative = b.negative;
        return result;
    }

    bigint operator -(const bigint &b) const {
        bigint negB = b;
        negB.negative = !b.negative;
        return *this + negB;
    }

    bigint operator *(const bigint &b) const {
        bigint result = multiply(value, b.value);
        result.negative = negative != b.negative;
        return result;
    }

    bigint operator /(const bigint &b) const {
        bigint result = divide(value, b.value);
        result.negative = negative != b.negative;
        return result;
    }

    bigint operator %(const bigint &b) const {
        bigint result = mod(value, b.value);
        result.negative = negative;
        return result;
    }

    bigint &operator +=(const bigint &b) {
        *this = *this + b;
        return *this;
    }

    bigint &operator -=(const bigint &b) {
        *this = *this - b;
        return *this;
    }

    bigint &operator *=(const bigint &b) {
        *this = *this * b;
        return *this;
    }

    bigint &operator /=(const bigint &b) {
        *this = *this / b;
        return *this;
    }

    bigint &operator %=(const bigint &b) {
        *this = *this % b;
        return *this;
    }

    bigint abs() const {
        bigint result = *this;
        result.negative = false;
        return result;
    }

    friend bigint abs(const bigint &a) {
        return a.abs();
    }

    friend bigint gcd(const bigint &a, const bigint &b) {
        bigint x = a.abs();
        bigint y = b.abs();
        while (y != bigint("0")) {
            bigint temp = y;
            y = x % y;
            x = temp;
        }
        return x;
    }

private:
    void trim() {
        while (value.length() > 1 && value[0] == '0') value.erase(0, 1);
        if (value == "0") negative = false;
    }

    static bigint add(const string &a, const string &b) {
        string result;
        int carry = 0, sum, lenA = a.size(), lenB = b.size();
        for (int i = 0; i < max(lenA, lenB) || carry; i++) {
            sum = carry;
            if (i < lenA) sum += a[lenA - 1 - i] - '0';
            if (i < lenB) sum += b[lenB - 1 - i] - '0';
            carry = sum / 10;
            result += (sum % 10) + '0';
        }
        reverse(all(result));
        return bigint(result);
    }

    static bigint subtract(const string &a, const string &b) {
        string result;
        int carry = 0, sub, lenA = a.size(), lenB = b.size();
        for (int i = 0; i < lenA; i++) {
            sub = a[lenA - 1 - i] - '0' - carry;
            if (i < lenB) sub -= b[lenB - 1 - i] - '0';
            carry = (sub < 0);
            if (carry) sub += 10;
            result += sub + '0';
        }
        reverse(all(result));
        return bigint(result);
    }

    static bigint multiply(const string &a, const string &b) {
        vint result(a.size() + b.size(), 0);
        for (int i = a.size() - 1; i >= 0; i--) {
            for (int j = b.size() - 1; j >= 0; j--) {
                int mul = (a[i] - '0') * (b[j] - '0') + result[i + j + 1];
                result[i + j + 1] = mul % 10;
                result[i + j] += mul / 10;
            }
        }
        string res;
        for (int num : result) if (!(res.empty() && num == 0)) res += num + '0';
        return res.empty() ? bigint("0") : bigint(res);
    }

    static bigint divide(const string &a, const string &b) {
        bigint divisor(b), remainder("0"), quotient("0");
        for (char c : a) {
            remainder = remainder * bigint(10) + bigint(c - '0');
            int count = 0;
            while (remainder >= divisor) {
                remainder -= divisor;
                count++;
            }
            quotient = quotient * bigint(10) + bigint(count);
        }
        return quotient;
    }

    static bigint mod(const string &a, const string &b) {
        bigint divisor(b), remainder("0");
        for (char c : a) {
            remainder = remainder * bigint(10) + bigint(c - '0');
            while (remainder >= divisor) remainder -= divisor;
        }
        return remainder;
    }

    static bool absGreater(const bigint &a, const bigint &b) {
        if (a.value.size() != b.value.size()) return a.value.size() > b.value.size();
        return a.value > b.value;
    }
};
