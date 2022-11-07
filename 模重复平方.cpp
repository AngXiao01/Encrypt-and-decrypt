#define _CRT_NO_SECURE_WARNINGS
#include<stdio.h>
#include<string.h>
#include "gmp.h"


int main() {
	int count;
	scanf("%d", &count);
	for (int i = 0; i < count; i++) {
		char exp[2048];
		mpz_t e, a, p, q,_p,_q,t, n, output;
		mpz_init(e);//a^e mod pq
		mpz_init(a);
		mpz_init(p);
		mpz_init(q);
		mpz_init(_p);//p-1
		mpz_init(_q);//q-1
		mpz_init(t);//p-1 * q-1
		mpz_init(n);//n=pq
		mpz_init_set_ui(output, 1);//set output=1
		gmp_scanf("%Zd %Zd %Zd %Zd", e, a, p, q);
		mpz_sub_ui(_p, p, 1);//_p=p-1
		mpz_sub_ui(_q, q, 1);//_q=q-1
		mpz_mul(t, _p, _q);
		mpz_mod(e, e, t);//e=e mod p-1 q-1
		mpz_get_str(exp, 2, e);//mpz_t e -> exp[2048](2)
		mpz_mul(n, p, q);//n=pq
		mpz_mod(a, a, n);
		for (int j = strlen(exp) - 1; j > -1; j--) {
			if (exp[j] == '1') {
				mpz_mul(output, output, a);//output=output*a
				mpz_mod(output, output, n);
			}
			mpz_mul(a, a, a);//a=a*a
			mpz_mod(a, a, n);
		}
		gmp_printf("%Zd\n", output);

		mpz_clear(output);
		mpz_clear(n);
		mpz_clear(_p);
		mpz_clear(_q);
		mpz_clear(t);
		mpz_clear(q);
		mpz_clear(p);
		mpz_clear(a);
		mpz_clear(e);
	}

}