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

class SHA0 {
private:
    uint32_t state[5];
    uint8_t buffer[64];
    size_t bufferSize;
    uint64_t totalSize;

    void reset() {
        state[0] = 0x67452301;
        state[1] = 0xEFCDAB89;
        state[2] = 0x98BADCFE;
        state[3] = 0x10325476;
        state[4] = 0xC3D2E1F0;
        bufferSize = 0;
        totalSize = 0;
    }

    void transform(const uint8_t block[64]) {
        uint32_t w[80];

        for (int i = 0; i < 16; i++) w[i] = (block[i * 4] << 24) | (block[i * 4 + 1] << 16) | (block[i * 4 + 2] << 8) | (block[i * 4 + 3]);
        for (int i = 16; i < 80; i++) w[i] = w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16];

        uint32_t a = state[0], b = state[1], c = state[2], d = state[3], e = state[4];

        for (int i = 0; i < 80; i++) {
            uint32_t f, k;
            if (i < 20) {
                f = (b & c) | (~b & d);
                k = 0x5A827999;
            } else if (i < 40) {
                f = b ^ c ^ d;
                k = 0x6ED9EBA1;
            } else if (i < 60) {
                f = (b & c) | (b & d) | (c & d);
                k = 0x8F1BBCDC;
            } else {
                f = b ^ c ^ d;
                k = 0xCA62C1D6;
            }

            uint32_t temp = rotateLeft(a, 5) + f + e + k + w[i];
            e = d;
            d = c;
            c = rotateLeft(b, 30);
            b = a;
            a = temp;
        }

        state[0] += a;
        state[1] += b;
        state[2] += c;
        state[3] += d;
        state[4] += e;
    }

    uint32_t rotateLeft(uint32_t value, size_t count) {
        return (value << count) | (value >> (32 - count));
    }

public:
    SHA0() { reset(); }

    void update(const uint8_t *data, size_t length) {
        size_t i = 0;

        if (bufferSize > 0) {
            while (length > 0 && bufferSize < 64) {
                buffer[bufferSize++] = data[i++];
                length--;
            }
            if (bufferSize == 64) {
                transform(buffer);
                totalSize += 512;
                bufferSize = 0;
            }
        }

        while (length >= 64) {
            transform(&data[i]);
            totalSize += 512;
            i += 64;
            length -= 64;
        }

        while (length > 0) {
            buffer[bufferSize++] = data[i++];
            length--;
        }
    }

    string final() {
        uint64_t totalBits = totalSize + bufferSize * 8;

        buffer[bufferSize++] = 0x80;

        if (bufferSize > 56) {
            while (bufferSize < 64) buffer[bufferSize++] = 0;
            transform(buffer);
            bufferSize = 0;
        }

        while (bufferSize < 56) buffer[bufferSize++] = 0;

        for (int i = 0; i < 8; i++) buffer[63 - i] = totalBits >> (i * 8);

        transform(buffer);

        ostringstream result;
        for (int i = 0; i < 5; i++) result << hex << setw(8) << setfill('0') << (state[i]);

        reset();
        return result.str();
    }
};

class SHA1 {
private:
    uint32_t state[5];
    uint8_t buffer[64];
    size_t bufferSize;
    uint64_t totalSize;

    void reset() {
        state[0] = 0x67452301;
        state[1] = 0xEFCDAB89;
        state[2] = 0x98BADCFE;
        state[3] = 0x10325476;
        state[4] = 0xC3D2E1F0;
        bufferSize = 0;
        totalSize = 0;
    }

    void transform(const uint8_t block[64]) {
        uint32_t w[80];
        for (int i = 0; i < 16; i++) w[i] = (block[i * 4] << 24) | (block[i * 4 + 1] << 16) | (block[i * 4 + 2] << 8) | (block[i * 4 + 3]);

        for (int i = 16; i < 80; i++) w[i] = rotateLeft(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1);

        uint32_t a = state[0], b = state[1], c = state[2], d = state[3], e = state[4];

        for (int i = 0; i < 80; i++) {
            uint32_t f, k;
            if (i < 20) {
                f = (b & c) | (~b & d);
                k = 0x5A827999;
            } else if (i < 40) {
                f = b ^ c ^ d;
                k = 0x6ED9EBA1;
            } else if (i < 60) {
                f = (b & c) | (b & d) | (c & d);
                k = 0x8F1BBCDC;
            } else {
                f = b ^ c ^ d;
                k = 0xCA62C1D6;
            }

            uint32_t temp = rotateLeft(a, 5) + f + e + k + w[i];
            e = d;
            d = c;
            c = rotateLeft(b, 30);
            b = a;
            a = temp;
        }

        state[0] += a;
        state[1] += b;
        state[2] += c;
        state[3] += d;
        state[4] += e;
    }

    uint32_t rotateLeft(uint32_t value, size_t count) {
        return (value << count) | (value >> (32 - count));
    }
    
public:
    SHA1() {reset();}

    void update(const uint8_t *data, size_t length) {
        size_t i = 0;

        if (bufferSize > 0) {
            while (length > 0 && bufferSize < 64) {
                buffer[bufferSize++] = data[i++];
                length--;
            }
            if (bufferSize == 64) {
                transform(buffer);
                totalSize += 512;
                bufferSize = 0;
            }
        }

        while (length >= 64) {
            transform(&data[i]);
            totalSize += 512;
            i += 64;
            length -= 64;
        }

        while (length > 0) {
            buffer[bufferSize++] = data[i++];
            length--;
        }
    }

    string final() {
        uint64_t totalBits = totalSize + bufferSize * 8;

        buffer[bufferSize++] = 0x80;

        if (bufferSize > 56) {
            while (bufferSize < 64) buffer[bufferSize++] = 0;
            transform(buffer);
            bufferSize = 0;
        }

        while (bufferSize < 56) buffer[bufferSize++] = 0;

        for (int i = 0; i < 8; i++) buffer[63 - i] = totalBits >> (i * 8);

        transform(buffer);

        ostringstream result;
        for (int i = 0; i < 5; i++) result << hex << setw(8) << setfill('0') << (state[i]);

        reset();
        return result.str();
    }
};

class SHA224 {
private:
    uint32_t state[8];
    uint8_t buffer[64];
    size_t bufferSize;
    uint64_t totalSize;

    void reset() {
        state[0] = 0xc1059ed8;
        state[1] = 0x367cd507;
        state[2] = 0x3070dd17;
        state[3] = 0xf70e5939;
        state[4] = 0xffc00b31;
        state[5] = 0x68581511;
        state[6] = 0x64f98fa7;
        state[7] = 0xbefa4fa4;
        bufferSize = 0;
        totalSize = 0;
    }

    void transform(const uint8_t block[64]) {
        uint32_t w[64];
        for (int i = 0; i < 16; i++) {
            w[i] = (block[i * 4] << 24) | (block[i * 4 + 1] << 16) | (block[i * 4 + 2] << 8) | (block[i * 4 + 3]);
        }
        for (int i = 16; i < 64; i++) {
            uint32_t s0 = rotateRight(w[i - 15], 7) ^ rotateRight(w[i - 15], 18) ^ (w[i - 15] >> 3), s1 = rotateRight(w[i - 2], 17) ^ rotateRight(w[i - 2], 19) ^ (w[i - 2] >> 10);
            w[i] = w[i - 16] + s0 + w[i - 7] + s1;
        }

        uint32_t a = state[0], b = state[1], c = state[2], d = state[3], e = state[4], f = state[5], g = state[6], h = state[7];
        const uint32_t k[64] = {
            0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
            0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
            0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
            0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
            0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
            0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
            0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
            0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
        };

        for (int i = 0; i < 64; i++) {
            uint32_t S1 = rotateRight(e, 6) ^ rotateRight(e, 11) ^ rotateRight(e, 25), ch = (e & f) ^ (~e & g), temp1 = h + S1 + ch + k[i] + w[i], S0 = rotateRight(a, 2) ^ rotateRight(a, 13) ^ rotateRight(a, 22), maj = (a & b) ^ (a & c) ^ (b & c), temp2 = S0 + maj;

            h = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }

        state[0] += a;
        state[1] += b;
        state[2] += c;
        state[3] += d;
        state[4] += e;
        state[5] += f;
        state[6] += g;
        state[7] += h;
    }

    uint32_t rotateRight(uint32_t value, size_t count) {
        return (value >> count) | (value << (32 - count));
    }

public:
    SHA224() {reset();}

    void update(const uint8_t *data, size_t length) {
        size_t i = 0;

        if (bufferSize > 0) {
            while (length > 0 && bufferSize < 64) {
                buffer[bufferSize++] = data[i++];
                length--;
            }
            if (bufferSize == 64) {
                transform(buffer);
                totalSize += 512;
                bufferSize = 0;
            }
        }

        while (length >= 64) {
            transform(&data[i]);
            totalSize += 512;
            i += 64;
            length -= 64;
        }

        while (length > 0) {
            buffer[bufferSize++] = data[i++];
            length--;
        }
    }

    string final() {
        uint64_t totalBits = totalSize + bufferSize * 8;

        buffer[bufferSize++] = 0x80;

        if (bufferSize > 56) {
            while (bufferSize < 64) buffer[bufferSize++] = 0;
            transform(buffer);
            bufferSize = 0;
        }

        while (bufferSize < 56) buffer[bufferSize++] = 0;

        for (int i = 0; i < 8; i++) buffer[63 - i] = totalBits >> (i * 8);

        transform(buffer);

        ostringstream result;
        for (int i = 0; i < 7; i++) {
            result << hex << setw(8) << setfill('0') << (state[i]);
        }

        reset();
        return result.str();
    }
};

class SHA256 {
private:
    uint32_t state[8];
    uint8_t buffer[64];
    size_t bufferSize;
    uint64_t totalSize;

    void reset() {
        state[0] = 0x6A09E667;
        state[1] = 0xBB67AE85;
        state[2] = 0x3C6EF372;
        state[3] = 0xA54FF53A;
        state[4] = 0x510E527F;
        state[5] = 0x9B05688C;
        state[6] = 0x1F83D9AB;
        state[7] = 0x5BE0CD19;
        bufferSize = 0;
        totalSize = 0;
    }

    void transform(const uint8_t block[64]) {
        static const uint32_t K[64] = {
            0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5, 0x3956C25B, 0x59F111F1, 0x923F82A4, 0xAB1C5ED5,
            0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3, 0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174,
            0xE49B69C1, 0xEFBE4786, 0x0FC19DC6, 0x240CA1CC, 0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA,
            0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7, 0xC6E00BF3, 0xD5A79147, 0x06CA6351, 0x14292967,
            0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13, 0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85,
            0xA2BFE8A1, 0xA81A664B, 0xC24B8B70, 0xC76C51A3, 0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070,
            0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5, 0x391C0CB3, 0x4ED8AA4A, 0x5B9CCA4F, 0x682E6FF3,
            0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208, 0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2
        };

        uint32_t w[64];
        for (int i = 0; i < 16; i++) {
            w[i] = (block[i * 4] << 24) | (block[i * 4 + 1] << 16) | (block[i * 4 + 2] << 8) | (block[i * 4 + 3]);
        }

        for (int i = 16; i < 64; i++) {
            uint32_t s0 = rotateRight(w[i - 15], 7) ^ rotateRight(w[i - 15], 18) ^ (w[i - 15] >> 3), s1 = rotateRight(w[i - 2], 17) ^ rotateRight(w[i - 2], 19) ^ (w[i - 2] >> 10);
            w[i] = w[i - 16] + s0 + w[i - 7] + s1;
        }

        uint32_t a = state[0], b = state[1], c = state[2], d = state[3], e = state[4], f = state[5], g = state[6], h = state[7];
        for (int i = 0; i < 64; i++) {
            uint32_t S1 = rotateRight(e, 6) ^ rotateRight(e, 11) ^ rotateRight(e, 25), ch = (e & f) ^ (~e & g), temp1 = h + S1 + ch + K[i] + w[i], S0 = rotateRight(a, 2) ^ rotateRight(a, 13) ^ rotateRight(a, 22), maj = (a & b) ^ (a & c) ^ (b & c), temp2 = S0 + maj;

            h = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }

        state[0] += a;
        state[1] += b;
        state[2] += c;
        state[3] += d;
        state[4] += e;
        state[5] += f;
        state[6] += g;
        state[7] += h;
    }

    uint32_t rotateRight(uint32_t value, size_t count) {
        return (value >> count) | (value << (32 - count));
    }

public:
    SHA256() {reset();}

    void update(const uint8_t *data, size_t legnth) {
        while (legnth > 0) {
            size_t amount = 64 - bufferSize;
            if (legnth < amount) {
                amount = legnth;
            }
            memcpy(buffer + bufferSize, data, amount);
            bufferSize += amount;
            data += amount;
            legnth -= amount;

            if (bufferSize == 64) {
                transform(buffer);
                totalSize += 512;
                bufferSize = 0;
            }
        }
    }

    string final() {
        uint64_t totalBits = totalSize + bufferSize * 8;

        buffer[bufferSize++] = 0x80;
        if (bufferSize > 56) {
            while (bufferSize < 64) buffer[bufferSize++] = 0;
            transform(buffer);
            bufferSize = 0;
        }

        while (bufferSize < 56) buffer[bufferSize++] = 0;

        for (int i = 0; i < 8; i++) buffer[63 - i] = totalBits >> (i * 8);

        transform(buffer);

        ostringstream result;
        for (int i = 0; i < 8; i++) result << hex << setw(8) << setfill('0') << (state[i]);

        reset();
        return result.str();
    }
};

int main() {
    fastio;
    string input;
    getline(cin, input);

    SHA224 sha224;
    sha224.update(reinterpret_cast<const uint8_t*>(input.c_str()), input.size());
    string hash = sha224.final();

    cout << hash << endl;

    return 0;
}
