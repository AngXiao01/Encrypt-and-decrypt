#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>



int funx_y(int x, int key);
int _s[16] = { 14,3,4,8,1,12,10,15,7,13,9,6,11,2,0,5 };
int s[16] = { 14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7 };

int _S(int n)
{
	return 	(_s[(n >> 12) & 0xf] << 12) | (_s[(n >> 8) & 0xf] << 8) | (_s[(n >> 4) & 0xf] << 4) | (_s[n & 0xf]);
}
int P(int z) {
	z = (z & 0x8000) | ((z & 0x0800) << 3) | ((z & 0x0080) << 6) | ((z & 0x0008) << 9) | ((z & 0x4000) >> 3) | (z & 0x0400) | ((z & 0x0040) << 3) | ((z & 0x0004) << 6) | ((z & 0x2000) >> 6) | ((z & 0x0200) >> 3) | (z & 0x0020) | ((z & 0x0002) << 3) | ((z & 0x1000) >> 9) | ((z & 0x0100) >> 6) | ((z & 0x0010) >> 3) | (z & 0x0001);
	return z;
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
 
int y[0x10000];

int main() {
	int n, flag, key, _key;
	scanf("%d", &n);
	//对每一个循环
	for (int I = 0; I < n; I++) {
		int k5, k6, k7, k8;
		flag = 1;
		int v1, _v1, v2, _v2, v3, _v3, v4, _v4, u1, _u1, u2, _u2, u3, _u3, u4, _u4, count[256] = {}, _count[256] = {};
		for (int i = 0; i <= 0xffff; i++) {
			y[i] = read();
		}

		for (int i = 0; i < 0x1500; i++) {
			int y1, y2;
			y1 = y[i];
			y2 = y[i ^ 0xb00];
			if ((y1 & 0xf0f0) == (y2 & 0xf0f0)) {
				for (int k1 = 0; k1 < 16; k1++)
					for (int k2 = 0; k2 < 16; k2++) {
						v2 = k1 ^ (y1 >> 8 & 15);
						u2 = _S(v2);
						v4 = k2 ^ (y1 & 15);
						u4 = _S(v4);

						_v2 = k1 ^ (y2 >> 8 & 15);
						_u2 = _S(_v2);
						_v4 = k2 ^ (y2 & 15);
						_u4 = _S(_v4);
						if ((u4 ^ _u4) == 6)
							if ((u2 ^ _u2) == 6)
								count[(k1 << 4) + k2] += 1;
					}
			}
		}
		while (flag) {
			int max = -1;
			for (int j = 0; j < 256; j++) {
				if (count[j] > max) {
					max = count[j];
					_key = j;
				}
			}
			//k6,k8
			k6 = _key >> 4;
			k8 = _key % 16;

			//k6,k8没问题

			for (int i = 0; i < 0x5000; i++) {
				int y1, y2;
				y1 = y[i];
				y2 = y[i ^ 0xf0f0];
				if ((y1 & 0xf00) == (y2 & 0xf00)) {
					int t = 0;
					for (int k1 = 0; k1 < 16; k1++) {
						for (int k2 = 0; k2 < 16; k2++) {
							v4 = k8 ^ (y1 & 15);
							u4 = _S(v4);
							_v4 = k8 ^ (y2 & 15);
							_u4 = _S(_v4);
							if ((u4 ^ _u4) != 8) { t = 1; break; }

							v1 = k1 ^ (y1 >> 12 & 15);
							u1 = _S(v1);
							v3 = k2 ^ (y1 >> 4 & 15);
							u3 = _S(v3);

							_v1 = k1 ^ (y2 >> 12 & 15);
							_u1 = _S(_v1);
							_v3 = k2 ^ (y2 >> 4 & 15);
							_u3 = _S(_v3);

							if ((u1 ^ _u1) == 8)
								if ((u3 ^ _u3) == 8)
									_count[(k1 << 4) + k2] += 1;
						}
						if (t == 1) break;
					}
				}
			}

			max = -1;
			for (int j = 0; j < 256; j++) {
				if (_count[j] > max) {
					max = _count[j];
					_key = j;
				}
			}
			//k5,k7
			k5 = _key >> 4;
			k7 = _key % 16;
			_key = (k5 << 12) + (k6 << 8) + (k7 << 4) + k8;

			//取两对值检验
			for (int k = 0; k <= 0xffff; k++) {
				key = (k << 16) + _key;
				if (y[1] == funx_y(1, key))
					if (y[123] == funx_y(123, key)) {
						printf("%08x\n", key);
						flag = 0;
						break;
					}
			}
			if (flag) count[(k6 << 4) + k8] = 0;//最大值置0
		}
	}
	return 0;
}


int funx_y(int x, int k) {
	int v, u, w, y;
	for (int i = 0; i < 4; i++) {
		if (i != 0) {
			w = P(v);
			u = w ^ ((k >> (16 - 4 * i)) & 0xffff);
			v = (s[(u >> 12) & 0xf] << 12);
			v += s[(u >> 8) & 0xf] << 8;
			v += s[(u >> 4) & 0xf] << 4;
			v += s[u & 0xf];
		}
		else {
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