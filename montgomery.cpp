#define _CRT_NO_SECURE_WARNING
#include<stdio.h>
#include "gmp.h"

int main() {
	int count;
	mpz_t e, d, a, p, q, _p, _q, t, n, output, __p,__q;
	mpz_init(e);//a^ed = 1
	mpz_init(d);//a^d mod pq
	mpz_init(a);
	mpz_init(p);
	mpz_init(q);
	mpz_init(_p);//p-1
	mpz_init(_q);//q-1
	mpz_init(__p);//p-1
	mpz_init(__q);//q-1
	mpz_init(t);//p-1 * q-1
	mpz_init(n);//n=pq
	mpz_init(output);
	//scanf("%d", &count);
	//mpz_inp_str(p, stdin, 10);
	//mpz_inp_str(q, stdin, 10);
	//mpz_inp_str(e, stdin, 10);
	gmp_scanf("%d %Zd %Zd %Zd", &count, p, q, e);
	mpz_sub_ui(_p, p, 1);//_p=p-1
	mpz_sub_ui(_q, q, 1);//_q=q-1
	//gmp_printf("_p=%Zd _q=%Zd\n", _p, _q);
	mpz_mul(t, _p, _q);
	mpz_invert(__p, p, q);//__p=p^-1 mod q
	mpz_invert(__q, q, p);//__q=q^-1 mod p
	mpz_mul(__q, q, __q);
	mpz_mul(__p, p, __p);
	mpz_mul(n, p, q);
	mpz_invert(d, e, t);
	for (int i = 0; i < count; i++) {
		mpz_t d1, d2;
		mpz_init(d1);
		mpz_init(d2);
		mpz_t output1, output2;
		mpz_init(output1);
		mpz_init(output2);
		gmp_scanf("%Zd", a);
		//mpz_inp_str(a, stdin, 10);
		mpz_mod(d1, d, _p);
		mpz_powm(output1, a, d1, p);
		mpz_mod(d2, d, _q);
		mpz_powm(output2, a, d2, q);
		mpz_mul(output1, __q, output1);
		mpz_mul(output2, __p, output2);
		mpz_add(output, output1, output2);
		mpz_mod(output, output, n);
		gmp_printf("%Zd\n", output);
	}
	mpz_clear(output);
	mpz_clear(n);
	mpz_clear(_p);
	mpz_clear(_q);
	mpz_clear(t);
	mpz_clear(q);
	mpz_clear(p);
	mpz_clear(a);
	mpz_clear(d);
	mpz_clear(e);
	return 0;
}