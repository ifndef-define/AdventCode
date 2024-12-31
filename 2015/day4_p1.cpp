#include "../useful.hpp"

/**
 * Day 4 Puzzle
 * Part 1
 * 
 * https://adventofcode.com/2015/day/4
 * 
 * Note: I have choosen to write the MD5 hash algorithm myself in this example
 * 
 */

// Constants for rotations
const short int shift[64] = 
{
    7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
    5, 9, 14, 20,   5, 9, 14, 20,   5, 9, 14, 20,   5, 9, 14, 20,
    4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
    6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21
};

// const uint32_t kconst[64] = 
// {
//     0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
//     0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
//     0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
//     0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
//     0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
//     0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
//     0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
//     0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
//     0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
//     0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
//     0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
//     0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
//     0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
//     0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
//     0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
//     0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391,
// };

// Hardcoded starting values
// uint32_t Ap, A = 0x67452301;
// uint32_t Bp, B = 0xefcdab89;
// uint32_t Cp, C = 0x98badcfe;
// uint32_t Dp, D = 0x10325476;

uint32_t Ao = 0x67452301;
uint32_t Bo = 0xefcdab89;
uint32_t Co = 0x98badcfe;
uint32_t Do = 0x10325476;
uint32_t A = Ao;
uint32_t B = Bo;
uint32_t C = Co;
uint32_t D = Do;

/* MD5 Hash Steps
1) Input Prep
    a) Convert input string to hex string
    b) Store and pad input string to 512-bit block into 16 32-bit words
    c) Append 1 to the end of the input string
    d) Append the length of the input string in binary to the second to last index of the 512-bit block
2) 
*/

// Simple debugging function to print the 512-bit input block in hex
void printHexArrayInHex(uint32_t* arr, int len) {
    for (int i = 0; i < len; i++) {
        printf("%08x ", arr[i]);
        if ((i + 1) % 2 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

// uint32_t combine(uint32_t inp, uint32_t A, uint32_t B, uint32_t C, uint32_t D, unsigned short int i) {
//     uint32_t F;
//     if (i <= 15)
//         F = (B & C) | ((~B) & D);
//     else if (i <= 31)
//         F = (D & B) | ((~D) & C);
//     else if (i <= 47)
//         F = B ^ C ^ D;
//     else if (i <= 63)
//         F = C ^ (B | (~D));

//     // F = F + A + inp + floor(pow(2, 32) * abs(sin(i + 1)));
//     F += A + inp + kconst[i];
//     F = _rotl(F, shift[i]);
//     F += B;
//     return F;
// }

static inline uint32_t rotate_left(uint32_t x, uint32_t n) {
    return (x << n) | (x >> (32 - n));
}

string md5Hash(string input_str) {
    // Convert input string to hex string //
    char input_hex[128];
    memset(input_hex, 0, 128);

    for (int i=0,j=0; i<input_str.length(); i++,j+=2) {
        sprintf(&input_hex[j], "%x", input_str[i]);
    }
    for (int i = strlen(input_hex); i < 128; i++) {
        input_hex[i] = '0';
    }

    // Store and pad input string to 512-bit block into 16 32-bit words //
    uint32_t hexInp[16];
    for (int i=0; i<16; i++) {
        char tempStr[9];
        memset(tempStr, 0, 8);
        hexInp[i] = 0;
        strncpy(tempStr, &input_hex[i*8], 8);
        if (int l=strlen(tempStr) < 8) {
            strncpy(&tempStr[l+1], "30303030", 8-(l*2));
        }

        sscanf(tempStr, "%x", &hexInp[i]);
    }
    
    // Append 1 to the end of the input string //
    int lastCharIndex = input_str.length() * 2 - 1;
    int blockIndex = lastCharIndex / 8;
    int endIndex = lastCharIndex % 8;
    hexInp[blockIndex] |= (0x00000080 << (endIndex * 16));

    // Add the length of the input_str in hex to the second to last index of hexInp //
    unsigned int strBinLen = input_str.length() * 8;
    hexInp[14] = strBinLen;
    if (strBinLen <= 0xF)
        hexInp[14] <<= 7*4;
    else if (strBinLen <= 0xFF)
        hexInp[14] <<= 6*4;
    else if (strBinLen <= 0xFFF)
        hexInp[14] <<= 5*4;
    
    // Debugging to view the 512-bit block properly formatted for input into the MD5 algorithm //
    printHexArrayInHex(hexInp, 16);

    // Convert hexInp to little-endian
    uint32_t w[16];
    for(int i = 0; i < 16; i++) {
        w[i] = ((hexInp[i] & 0xFF      ) << 24) |
               ((hexInp[i] & 0xFF00    ) << 8 ) |
               ((hexInp[i] & 0xFF0000  ) >> 8 ) |
               ((hexInp[i] & 0xFF000000) >> 24);
    }

    printHexArrayInHex(w, 16);
    cout << endl;

    // Begin MD5 Hashing //
    cout << "Intial: " << std::hex << A << " " << B << " " << C << " " << D << endl;


    for (unsigned int i=0; i<64; i++) {
        uint32_t j;
        uint32_t F; 
        if (i <= 15) {
            F = (B & C) | ((~B) & D);
            j = i;
        }
        else if (i <= 31) {
            F = (D & B) | ((~D) & C);
            j = (5*i + 1)%16;
        }
        else if (i <= 47) {
            F = B ^ C ^ D;
            j = (3*i + 5)%16;
        }
        else if (i <= 63) {
            F = C ^ (B | (~D));
            j = (7*i)%16;
        }

        // // F = F + A + inp + floor(pow(2, 32) * abs(sin(i + 1)));
        // F += A + hexInp[j] + kconst[i];
        // F = rotate_left(F, shift[i]);

        // // if (j==0) {
        // //     Bp = combine(hexInp[i%16], A, B, C, D, i);
        // // } else if (j==1) {
        // //     Bp = combine(hexInp[(5*i+1)%16], A, B, C, D, i);
        // // } else if (j==2) {
        // //     Bp = combine(hexInp[(3*i+5)%16], A, B, C, D, i);
        // // } else if (j==3) {
        // //     Bp = combine(hexInp[(7*i)%16], A, B, C, D, i);
        // // }

        // A = D;
        // D = C;
        // C = B;
        // B += F;

        uint32_t kconst = [&](int i) {
            return floor(pow(2, 32) * abs(sin(i + 1)));
        };

        uint32_t temp = D;
        D = C;
        C = B;
        B = B + rotate_left(A + F + kconst[i] + w[j], shift[i]);
        A = temp;

        //cout << std::dec << i << "+" << j << " " << std::hex << A << " " << B << " " << C << " " << D << endl;
        printf("%04d+%04d %08x %08x %08x %08x\n", i, j, A, B, C, D);
    }
    // A += Ao;
    // B += Bo;
    // C += Co;
    // D += Do;

    Ao += A;
    Bo += B;
    Co += C;
    Do += D;

    // Convert hexInp to big-endian
    Ao = ((Ao & 0xFF) << 24) | ((Ao & 0xFF00) << 8) |
        ((Ao & 0xFF0000) >> 8) | ((Ao & 0xFF000000) >> 24);
    Bo = ((Bo & 0xFF) << 24) | ((Bo & 0xFF00) << 8) |
        ((Bo & 0xFF0000) >> 8) | ((Bo & 0xFF000000) >> 24);
    Co = ((Co & 0xFF) << 24) | ((Co & 0xFF00) << 8) |
        ((Co & 0xFF0000) >> 8) | ((Co & 0xFF000000) >> 24);
    Do = ((Do & 0xFF) << 24) | ((Do & 0xFF00) << 8) |
        ((Do & 0xFF0000) >> 8) | ((Do & 0xFF000000) >> 24);

    char As[9], Bs[9], Cs[9], Ds[9];
    sprintf(As, "%08x", Ao);
    sprintf(Bs, "%08x", Bo);
    sprintf(Cs, "%08x", Co);
    sprintf(Ds, "%08x", Do);
    return string(As) + string(Bs) + string(Cs) + string(Ds);
}

bool isFiveZeros(string inp) {
    return inp[0] == '0' && inp[1] == '0' && inp[2] == '0' && inp[3] == '0' && inp[4] == '0';
}
#include <bitset>
int main() {

    // 121,122 1d922 0001 1101 1001 0010 0010
    const string puzzleInp = "abcdwxyz";
    int i=1;

    string inp, out;

    // do {
        inp = puzzleInp + to_string(i++);
    cout << "Input: " << inp << endl;
        out = md5Hash(inp);
    cout << "Output:   " << out << endl;
    cout << "Expected: 1db508a2e2d86c22ef046e9f4721e27f" << endl;

    // uint32_t test = 0x12345678;
    // cout << std::hex << test << endl;
    // test = _rotl(test, 7);
    // cout << std::hex << test << endl;

    // } while (!isFiveZeros(out)); // Replace true with check of reached desired value

    return 0;
}

// 3f58ffd3363cc2a5e16c6e82700664e4 - my abcdwxyz1
// b4a80ab04ec9a3eaee3ba5b02f573506 - fixed rotation

// 1bed2db13e974f7386f682ae3f89897c 

// 1db508a2e2d86c22ef046e9f4721e27f - actual abcdwxyz1

/*
Input: abcdwxyz1
61626364 7778797a
31800000 00000000
00000000 00000000
00000000 00000000 
00000000 00000000
00000000 00000000
00000000 00000000
48000000 00000000

61626364 7778797a
31800000 00000000
00000000 00000000
00000000 00000000
00000000 00000000
00000000 00000000
00000000 00000000
48000000 00000000


Intial: 67452301 efcdab89 98badcfe 10325476
0+0 10325476 56519925 efcdab89 98badcfe
1+0 98badcfe 3b83ad1a 56519925 efcdab89
2+0 efcdab89 ee39366b 3b83ad1a 56519925
3+0 56519925 cfb429b4 ee39366b 3b83ad1a
4+0 3b83ad1a d05aa8d9 cfb429b4 ee39366b
5+0 ee39366b 9b7a0fec d05aa8d9 cfb429b4
6+0 cfb429b4 e626e67b 9b7a0fec d05aa8d9
7+0 d05aa8d9 4d7ec3ae e626e67b 9b7a0fec
8+0 9b7a0fec 4e86d136 4d7ec3ae e626e67b
9+0 e626e67b ad777264 4e86d136 4d7ec3ae
10+0 4d7ec3ae d52bd6ce ad777264 4e86d136
11+0 4e86d136 8d457789 d52bd6ce ad777264
12+0 ad777264 326219b8 8d457789 d52bd6ce
13+0 d52bd6ce ce1e70bd 326219b8 8d457789
14+0 8d457789 3247fe8d ce1e70bd 326219b8
15+0 326219b8 8c3e4689 3247fe8d ce1e70bd
16+1 ce1e70bd 174f2a34 8c3e4689 3247fe8d
17+1 3247fe8d d3eb2c8d 174f2a34 8c3e4689
18+1 8c3e4689 35522791 d3eb2c8d 174f2a34
19+1 174f2a34 b85cfb2a 35522791 d3eb2c8d
20+1 d3eb2c8d f329b05e b85cfb2a 35522791
21+1 35522791 6b9be57c f329b05e b85cfb2a
22+1 b85cfb2a e77f83c7 6b9be57c f329b05e
23+1 f329b05e ad084292 e77f83c7 6b9be57c
24+1 6b9be57c fc005d8a ad084292 e77f83c7
25+1 e77f83c7 a25e264f fc005d8a ad084292
26+1 ad084292 ce745966 a25e264f fc005d8a
27+1 fc005d8a fae06573 ce745966 a25e264f
28+1 a25e264f 8378e3c5 fae06573 ce745966
29+1 ce745966 ffd81ccc 8378e3c5 fae06573
30+1 fae06573 f898e93a ffd81ccc 8378e3c5
31+1 8378e3c5 e8f13374 f898e93a ffd81ccc
32+2 ffd81ccc 1b3f6c0b e8f13374 f898e93a
33+2 f898e93a 218c00a0 1b3f6c0b e8f13374
34+2 e8f13374 cbc73918 218c00a0 1b3f6c0b
35+2 1b3f6c0b 65575e78 cbc73918 218c00a0
36+2 218c00a0 ce8ad714 65575e78 cbc73918
37+2 cbc73918 fa90c580 ce8ad714 65575e78
38+2 65575e78 cbf4d94f fa90c580 ce8ad714
39+2 ce8ad714 2d86dc42 cbf4d94f fa90c580
40+2 fa90c580 6e1842b3 2d86dc42 cbf4d94f
41+2 cbf4d94f 62dd292a 6e1842b3 2d86dc42
42+2 2d86dc42 248ceb51 62dd292a 6e1842b3
43+2 6e1842b3 2c3a178e 248ceb51 62dd292a
44+2 62dd292a 51c8a5a9 2c3a178e 248ceb51
45+2 248ceb51 aacd2c2 51c8a5a9 2c3a178e
46+2 2c3a178e d3db8e4f aacd2c2 51c8a5a9
47+2 51c8a5a9 5fb12182 d3db8e4f aacd2c2
48+3 aacd2c2 3ee4f1f6 5fb12182 d3db8e4f
49+3 d3db8e4f f57028b2 3ee4f1f6 5fb12182
50+3 5fb12182 d5eff236 f57028b2 3ee4f1f6
51+3 3ee4f1f6 deff8cc9 d5eff236 f57028b2
52+3 f57028b2 b31df9f4 deff8cc9 d5eff236
53+3 d5eff236 30b7dd9d b31df9f4 deff8cc9
54+3 deff8cc9 273709e1 30b7dd9d b31df9f4
55+3 b31df9f4 f87e7187 273709e1 30b7dd9d
56+3 30b7dd9d bc7b0405 f87e7187 273709e1
57+3 273709e1 65ab58d2 bc7b0405 f87e7187
58+3 f87e7187 f9a5abd6 65ab58d2 bc7b0405
59+3 bc7b0405 c4423e7a f9a5abd6 65ab58d2
60+3 65ab58d2 b4a80ab0 c4423e7a f9a5abd6
61+3 f9a5abd6 2f573506 b4a80ab0 c4423e7a
62+3 c4423e7a ee3ba5b0 2f573506 b4a80ab0
63+3 b4a80ab0 4ec9a3ea ee3ba5b0 2f573506
Output: b4a80ab04ec9a3eaee3ba5b02f573506

1db508a2 e2d86c22 ef046e9f 4721e27f - actual abcdwxyz1

*/