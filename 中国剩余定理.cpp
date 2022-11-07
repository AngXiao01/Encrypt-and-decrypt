#define _CRT_NO_SECURE_WARNINGS
#include<stdio.h>
#include<string.h>
#include "gmp.h"


int main() {
	int count;
	char exp[2048];
	mpz_t e, d, a, p, q, _p, _q, t, n, output;
	mpz_init(e);//a^ed = 1
	mpz_init(d);//a^d mod pq
	mpz_init(a);
	mpz_init(p);
	mpz_init(q);
	mpz_init(_p);//p-1
	mpz_init(_q);//q-1
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
	mpz_invert(_p, p, q);//_p=p^-1 mod q
	mpz_invert(_q, q, p);//_q=q^-1 mod p
	mpz_mul(_q, q, _q);
	mpz_mul(_p, p, _p);
	
	//gmp_printf("_p=%Zd _q=%Zd\n", _p, _q);
	mpz_mul(n, p, q);
	mpz_invert(d, e, t);
	//mpz_mod(d, d, t);//e=e mod p-1 q-1
	//mpz_get_str(exp, 2, d);//mpz_t e -> exp[2048](2)
	for (int i = 0; i < count; i++) {
		mpz_t output1, output2;
		mpz_init(output1);
		mpz_init(output2);
		//mpz_init_set_ui(output, 1);//set output=1
		gmp_scanf("%Zd", a);
		//mpz_inp_str(a, stdin, 10);
		mpz_powm(output1, a, d, p);
		mpz_powm(output2, a, d, q);
		mpz_mul(output1, _q, output1);
		mpz_mul(output2, _p, output2);
		mpz_add(output, output1, output2);
		mpz_mod(output, output, n);
		//gmp_printf("_p=%Zd _q=%Zd\n", _p,_q);
		//mpz_powm(output, a, d, n);
		/*{
			mpz_mod(a, a, n);
			for (int j = strlen(exp) - 1; j > -1; j--) {
				if (exp[j] == '1') {
					mpz_mul(output, output, a);//output=output*a
					mpz_mod(output, output, n);
				}
				mpz_mul(a, a, a);//a=a*a
				mpz_mod(a, a, n);
			}
		}*/
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