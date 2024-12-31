#include <cstdint>
#include <cstring>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>

static inline uint32_t rotate_left(uint32_t x, uint32_t n) {
    return (x << n) | (x >> (32 - n));
}

void printHexArrayInHex(uint32_t* arr, int len) {
    for (int i = 0; i < len; i++) {
        printf("%08x ", arr[i]);
        if ((i + 1) % 2 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

std::string md5(const std::string &input) {
    // Constants for MD5
    static const uint32_t s[] = {
        7,12,17,22,  7,12,17,22,  7,12,17,22,  7,12,17,22,
        5, 9,14,20,  5, 9,14,20,  5, 9,14,20,  5, 9,14,20,
        4,11,16,23,  4,11,16,23,  4,11,16,23,  4,11,16,23,
        6,10,15,21,  6,10,15,21,  6,10,15,21,  6,10,15,21};
    static const uint32_t K[] = {
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
        0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
        0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
        0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
        0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
        0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
        0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
        0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
        0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
    };

    // Initialize MD5 state
    uint32_t a0 = 0x67452301;
    uint32_t b0 = 0xefcdab89;
    uint32_t c0 = 0x98badcfe;
    uint32_t d0 = 0x10325476;

    // Pre-processing (padding)
    std::vector<unsigned char> msg(input.begin(), input.end());
    uint64_t bitLen = msg.size() * 8;

    // Append the '1' bit
    msg.push_back(0x80);
    // Append 0 <= k < 512 bits so that length mod 512 = 448
    while ((msg.size() * 8) % 512 != 448) {
        msg.push_back(0x00);
    }
    // Append length in bits (little-endian)
    for (int i = 0; i < 8; i++) {
        msg.push_back(static_cast<unsigned char>((bitLen >> (8 * i)) & 0xff));
    }

    std::cout << "Message block in hex:" << std::endl;
    for (size_t i = 0; i < msg.size(); ++i) {
        if (i > 0 && i % 8 == 0) {
        std::cout << std::endl;
        }
        if (i > 0 && i % 4 == 0) {
        std::cout << ' ';
        }
        std::cout << std::hex << std::setw(2) << std::setfill('0')
              << static_cast<int>(msg[i]);
    }
    std::cout << std::endl;

    // Process the message in 512-bit chunks
    for (size_t offset = 0; offset < msg.size(); offset += 64) {
        uint32_t w[16];
        for (int i = 0; i < 16; i++) {
            w[i]  = (msg[offset + i*4 + 0]      ) |
                    (msg[offset + i*4 + 1] << 8 ) |
                    (msg[offset + i*4 + 2] << 16) |
                    (msg[offset + i*4 + 3] << 24);
        }

    printHexArrayInHex(w, 16);
  
        uint32_t A = a0, B = b0, C = c0, D = d0;

        for (int i = 0; i < 64; i++) {
            uint32_t F, g;
            if (i < 16) {
                F = (B & C) | ((~B) & D);
                g = i;
            } else if (i < 32) {
                F = (D & B) | ((~D) & C);
                g = (5*i + 1) % 16;
            } else if (i < 48) {
                F = B ^ C ^ D;
                g = (3*i + 5) % 16;
            } else {
                F = C ^ (B | (~D));
                g = (7*i) % 16;
            }
            uint32_t temp = D;
            D = C;
            C = B;
            B = B + rotate_left(A + F + K[i] + w[g], s[i]);
            A = temp;

        //std::cout << std::dec << i << "+" << g << " " << std::hex << A << " " << B << " " << C << " " << D << std::endl;
        printf("%04d+%04d %08x %08x %08x %08x\n", i, g, A, B, C, D);            

        }

        a0 += A; b0 += B; c0 += C; d0 += D;
    }

    // Convert to little-endian
    auto toBytes = [&](uint32_t val) {
        std::ostringstream oss;
        for (int i = 0; i < 4; i++) {
            oss << std::hex << std::setw(2) << std::setfill('0')
                << ((val >> (8*i)) & 0xff);
        }
        return oss.str();
    };

    // Final digest
    std::ostringstream result;
    result << toBytes(a0) << toBytes(b0) << toBytes(c0) << toBytes(d0);
    return result.str();
}

int main() {
    std::string data = "abcdwxyz1";
    std::cout << "MD5(\"" << data << "\") = " << md5(data) << std::endl;
    return 0;
}