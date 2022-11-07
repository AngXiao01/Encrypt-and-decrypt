#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int _S(int n);
int P(int z);
int funx_y(int x, int key);
int _s[16] = { 14,3,4,8,1,12,10,15,7,13,9,6,11,2,0,5 };
int s[16] = { 14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7 };

int main() {
	int n, flag, key, _key;
	int x[8000], y[8000];
	scanf("%d", &n);
	for (int I = 0; I < n; I++) {
		int k5, k6, k7, k8;
		flag = 1;
		int v1, v2, v3, v4, u1, u2, u3, u4, count[256] = {}, _count[256] = {}, i = 0;
		do {
			x[i] = read();
			y[i] = read();
			for (int k1 = 0; k1 < 16; k1++)
				for (int k2 = 0; k2 < 16; k2++) {
					int z;
					v2 = k1 ^ (y[i] >> 8 & 15);
					u2 = _S(v2);
					v4 = k2 ^ (y[i] & 15);
					u4 = _S(v4);
					z = (x[i] >> 11 & 1) ^ (x[i] >> 9 & 1) ^ (x[i] >> 8 & 1) ^ (u2 >> 2 & 1) ^ (u2 & 1) ^ (u4 >> 2 & 1) ^ (u4 & 1);
					if (z == 0)
						count[(k1 << 4) + k2] += 1;
				}
			i++;
		} while (i < 8000);

		while (flag) {
			int max = -1;
			for (int j = 0; j < 256; j++){
				_count[j] = count[j] - 4000;
				if (_count[j] < 0) _count[j] = -_count[j];
				if (_count[j] > max){
					max = _count[j];
					_key = j;
				}
			}
			//k6,k8
			k6 = _key >> 4;
			k8 = _key % 16;
			for (int j = 0; j < 256; j++)	_count[j] = 0;

			for (int j = 0; j < 8000; j++){
				for (int k1 = 0; k1 < 16; k1++)
					for (int k2 = 0; k2 < 16; k2++){
						int z;
						v1 = k1 ^ (y[j] >> 12 & 15);
						u1 = _S(v1);
						v2 = k6 ^ (y[j] >> 8 & 15);
						u2 = _S(v2);
						v3 = k2 ^ (y[j] >> 4 & 15);
						u3 = _S(v3);
						z = (x[j] >> 11 & 1) ^ (x[j] >> 10 & 1) ^ (x[j] >> 9 & 1) ^ (x[j] >> 8 & 1) ^ (u1 >> 2 & 1) ^ (u1 & 1) ^ (u3 >> 2 & 1) ^ (u3 & 1) ^ (u2 >> 2 & 1) ^ (u2 & 1);
						if (z == 0)
							_count[k1 * 16 + k2] += 1;
					}
			}

			max = -1;
			for (int j = 0; j < 256; j++){
				_count[j] = _count[j] - 4000;
				if (_count[j] < 0) _count[j] = -_count[j];
				if (_count[j] > max){
					max = _count[j];
					_key = j;
				}
			}
			//k5,k7
			k5 = _key >> 4;
			k7 = _key % 16;
			_key = (k5 << 12) + (k6 << 8) + (k7 << 4) + k8;

			//取两对值检验
			for (int k = 0; k <= 0xffff; k++){
				key = (k << 16) + _key;
				if (y[12] == funx_y(x[12], key))
					if (y[123] == funx_y(x[123], key)){
						printf("%08x\n", key);
						flag = 0;
						break;
					}
			}
			if (flag) count[(k6 << 4) + k8] = 4000;//最大值置0
		}
	}
	return 0;
}


inline int read() {
	int x = 0;
	char ch = getchar();
	while (ch < '0' || ch>'f') {
		ch = getchar();
	}
	while (ch >= '0' && ch <= 'f') {
		if (ch <= '9')
			x = (x << 4) + (ch - 48);
		else
			x = (x << 4) + (ch - 87);
		ch = getchar();
	}
	return x;
}

int _S(int n){
	int s = 0;
	s += _s[(n >> 12) & 0xf] << 12;
	s += _s[(n >> 8) & 0xf] << 8;
	s += _s[(n >> 4) & 0xf] << 4;
	s += _s[n & 0xf];
	return s;
}

int P(int w) {
	int p = 0;
	p += w & 0x8000;
	p += (w & 0x800) << 3;
	p += (w & 0x80) << 6;
	p += (w & 0x8) << 9;
	p += (w & 0x4000) >> 3;
	p += w & 0x0400;
	p += (w & 0x40) << 3;
	p += (w & 0x4) << 6;
	p += (w & 0x2000) >> 6;
	p += (w & 0x200) >> 3;
	p += w & 0x20;
	p += (w & 0x2) << 3;
	p += (w & 0x1000) >> 9;
	p += (w & 0x100) >> 6;
	p += (w & 0x10) >> 3;
	p += w & 0x1;
	return p;
}

int funx_y(int x, int k) {
	int v , u, w, y;
	for (int i = 0; i < 4; i++) {
		if (i != 0) {
			w = P(v);
			u = w ^ ((k >> (16 - 4 * i)) & 0xffff);
			v = (s[(u >> 12) & 0xf] << 12);
			v += s[(u >> 8) & 0xf] << 8;
			v += s[(u >> 4) & 0xf] << 4;
			v += s[u & 0xf];
		}
		else{
			u = x ^ ((k >> 16) & 0xffff);
			v = (s[(u >> 12) & 0xf] << 12);
			v += s[(u >> 8) & 0xf] << 8;
			v += s[(u >> 4) & 0xf] << 4;
			v += s[u & 0xf];
		}
	}
	y = v ^ (k & 0xffff);
	return y;
}
