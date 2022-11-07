#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include "gmp.h"

inline int primenumcheck(mpz_t p) {
	return mpz_probab_prime_p(p, 10);
}

void gcd(mpz_t g, mpz_t a, mpz_t b){
	mpz_init(g);
	mpz_init(a);
	mpz_init(b);
	while (1) {
		if (mpz_cmp(a, b) == 0) {
			mpz_set(g, a);
			return;
		}
		if (mpz_cmp(a, b) > 0) {
			mpz_sub(a, a, b);
		}
		else {
			mpz_sub(b, b, a);
		}
	}
}

int main() {
	int n;
	mpz_t p, q, e, d, _p, _q, t, tt, ttt;
	mpz_init(p);
	mpz_init(q);
	mpz_init(e);
	mpz_init(d);
	mpz_init(_p);
	mpz_init(_q);
	mpz_init(t);//t=(q-1)(p-1)
	mpz_init(tt);//tt=t%e
	mpz_init(ttt);//ttt=gcd(p-1.q-1)
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		gmp_scanf("%Zd %Zd %Zd", &e, &p, &q);
		mpz_sub_ui(_p, p, 1);//_p=p-1
		mpz_sub_ui(_q, q, 1);//_q=q-1
		mpz_mul(t, _p, _q);//t=(q-1)(p-1)
		mpz_mod(tt, t, e);//tt=t%e
		if (primenumcheck(p) && primenumcheck(q) && mpz_cmp_ui(tt, 0)) {//check p,q,tt,tt不再使用
			//printf("OK");
			mpz_sub(tt, p, q);//tt=p-q
			mpz_abs(tt, tt);
			if (mpz_cmp_ui(tt, 0xffffffffffffffff) < 0) {//确保p,q之差够大
				printf("ERROR\n");
				continue;
			}
			gcd(ttt, _p, _q);//ttt=gcd(p-1.q-1)
			if (mpz_cmp_ui(ttt, 0xff) > 0) {//确保ttt够小
				printf("ERROR\n");
				continue;
			}
			if (mpz_cmp_ui(p, 0xffffffffffffffff) < 0) {//确保p够大
				printf("ERROR\n");
				continue;
			}
			if (mpz_cmp_ui(q, 0xffffffffffffffff) < 0) {//确保q够大
				printf("ERROR\n");
				continue;
			}
			if (mpz_cmp_ui(e, 0xffff) < 0) {//确保e够大
				printf("ERROR\n");
				continue;
			}
			if (!mpz_probab_prime_p(e, 5)) {//确保e为素数
				printf("ERROR\n");
				continue;
			}
			mpz_invert(d, e, t);
			if (mpz_cmp_ui(d, 0xffffffffffffffff) < 0) {//确保d为够大
				printf("ERROR\n");
				continue;
			}
			gmp_printf("%Zd\n", d);
		}
		else
			printf("ERROR\n");
	}
	mpz_clear(q);
	mpz_clear(p);
	mpz_clear(e);
	mpz_clear(d);
	mpz_clear(_p);
	mpz_clear(_q);
	mpz_clear(t);
	mpz_clear(tt);
	mpz_clear(ttt);
	return 0;
}

