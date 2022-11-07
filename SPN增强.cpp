#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

unsigned short S[16][16] = { \
0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30,  0x1, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76\
, 0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0\
, 0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15\
, 0x4, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x5, 0x9a, 0x7, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75\
, 0x9, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84\
, 0x53, 0xd1, 0x0, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf\
, 0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x2, 0x7f, 0x50, 0x3c, 0x9f, 0xa8\
, 0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2\
, 0xcd, 0xc, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73\
, 0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0xb, 0xdb\
, 0xe0, 0x32, 0x3a, 0xa, 0x49, 0x6, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79\
, 0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x8\
, 0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a\
, 0x70, 0x3e, 0xb5, 0x66, 0x48, 0x3, 0xf6, 0xe, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e\
, 0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf\
, 0x8c, 0xa1, 0x89, 0xd, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0xf, 0xb0, 0x54, 0xbb, 0x16\
};

unsigned short P[32] = { \
16, 7, 20, 21 ,29 ,12 ,28, 17\
,1	,15, 23 ,26, 5 ,18, 31 ,10\
,2	,8	,24	,14	,32,	27 ,3 ,9\
,19, 13, 30, 6, 22, 11, 4, 25\
};

unsigned long long Key[9];

unsigned long long S_Box(unsigned long long In)//字节代换
{
    unsigned long long Out = 0;
    unsigned long long _S[16];
    _S[0] = (In & 0xF000000000000000) >> 60;
    _S[1] = (In & 0xF00000000000000) >> 56;
    _S[2] = (In & 0xF0000000000000) >> 52;
    _S[3] = (In & 0xF000000000000) >> 48;
    _S[4] = (In & 0xF00000000000) >> 44;
    _S[5] = (In & 0xF0000000000) >> 40;
    _S[6] = (In & 0xF000000000) >> 36;
    _S[7] = (In & 0xF00000000) >> 32;
    _S[8] = (In & 0xF0000000) >> 28;
    _S[9] = (In & 0xF000000) >> 24;
    _S[10] = (In & 0xF00000) >> 20;
    _S[11] = (In & 0xF0000) >> 16;
    _S[12] = (In & 0xF000) >> 12;
    _S[13] = (In & 0xF00) >> 8;
    _S[14] = (In & 0x0F0) >> 4;
    _S[15] = (In & 0xF);
    _S[0] = S[_S[0]][_S[1]];
    _S[1] = S[_S[2]][_S[3]];
    _S[2] = S[_S[4]][_S[5]];
    _S[3] = S[_S[6]][_S[7]];
    _S[4] = S[_S[8]][_S[9]];
    _S[5] = S[_S[10]][_S[11]];
    _S[6] = S[_S[12]][_S[13]];
    _S[7] = S[_S[14]][_S[15]];
    _S[0] <<= 56;
    _S[1] <<= 48;
    _S[2] <<= 40;
    _S[3] <<= 32;
    _S[4] <<= 24;
    _S[5] <<= 16;
    _S[6] <<= 8;
    Out = _S[0] | _S[1] | _S[2] | _S[3] | _S[4] | _S[5] | _S[6] | _S[7];
    return Out;
}

unsigned long long P_Box(unsigned long long In)
{
    unsigned long long Out = 0;
    int P1[64], P2[64];
    for (int i = 63; i >= 0; i--)
    {
        P1[i] = In & 1;
        In >>= 1;
    }
    for (int i = 0; i < 64; i++) 
    {
        if (i < 32)
            P2[i] = P1[P[i] - 1];
        else
            P2[i] = P1[P[i - 32] + 31];
        Out = (Out << 1) + P2[i];
    }
    return Out;
}

unsigned long long SPN(unsigned long long In)
{
    int i;
    const int round = 4;
    unsigned long long Out;
    unsigned long long w[round] = { };
    unsigned long long u[round] = { };
    unsigned long long v[round] = { };

    w[0] = In;
    for (i = 0; i < round; i++)
    {
        u[i] = w[i] ^ Key[(3*i)%8];
        v[i] = S_Box(u[i]);
        if (i < round - 1)
            w[i + 1] = P_Box(v[i]);
        else
            continue;
    }
    Out = v[round - 1] ^ Key[(round)%8];
    return Out;
}

unsigned long long _SPN(unsigned long long In)
{
    int i;
    const int round = 4;
    unsigned long long Out;
    unsigned long long w[round] = { };
    unsigned long long u[round] = { };
    unsigned long long v[round] = { };

    w[0] = In;
    for (i = 0; i < round; i++)
    {
        u[i] = w[i] ^ Key[(3 * i+1) % 8];
        v[i] = S_Box(u[i]);
        if (i < round - 1)
            w[i + 1] = P_Box(v[i]);
        else
            continue;
    }
    Out = v[round - 1] ^ Key[(round) % 8];
    return Out;
}

void genkey(unsigned long long* key, unsigned long long key1, unsigned long long key2)
{
    key[0] = S_Box(key1);
    key[1] = S_Box(key1 << 8 | key2 >> 56);
    key[2] = S_Box(key1 << 16 | key2 >> 48);
    key[3] = S_Box(key1 << 24 | key2 >> 40);
    key[4] = S_Box(key1 << 32 | key2 >> 32);
    key[5] = S_Box(key1 << 40 | key2 >> 24);
    key[6] = S_Box(key1 << 48 | key2 >> 16);
    key[7] = S_Box(key1 << 56 | key2 >> 8);
    key[8] = S_Box(key2);
}

unsigned long long _random(void)
{
    srand(time(NULL));
    unsigned long long ran = 0;
    for (int i = 0; i < 64; i++)
    {
        ran <<= 1;
        ran |= (rand() & 1);
    }
    return ran;
}

int main()
{
    unsigned long long IN, OUT, ran, key1, key2;
    fread(&key1, 8, 1, stdin);
    fread(&key2, 8, 1, stdin);
    genkey(Key, key1, key2);
    ran = _random();//初始向量
    fread(&IN, 8, 1, stdin);
    IN ^= ran;
    IN = SPN(IN);//SPN
    OUT = _SPN(IN);//_SPN
    fwrite(&OUT, 8, 1, stdout);
    for (int i = 1; i < 1 << 21; i++)
    {
        fread(&IN, 8, 1, stdin);
        IN ^= OUT;
        IN = _SPN(IN);
        OUT = SPN(IN);
        fwrite(&OUT, 8, 1, stdout);
    }
    return 0;
}
