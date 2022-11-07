//#pragma comment(lib, "ws2_32.lib")
#include <stdio.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/pkcs7.h>
#include <openssl/x509.h>
#include <openssl/sm2.h>
#include <openssl/rand.h>
#include <openssl/objects.h>
#include <openssl/x509v3.h>
#include <openssl/x509_vfy.h>
#include<openssl/applink.c>
#define POINT_BIN_LENGTH 65

const char cacert[] = "\
-----BEGIN CERTIFICATE----- \n\
MIIB/zCCAaagAwIBAgIJAKKa0PAt9M1FMAoGCCqBHM9VAYN1MFsxCzAJBgNVBAYT \n\
AkNOMQ4wDAYDVQQIDAVIdUJlaTEOMAwGA1UEBwwFV3VIYW4xDTALBgNVBAoMBEhV \n\
U1QxDDAKBgNVBAsMA0NTRTEPMA0GA1UEAwwGY2Fyb290MB4XDTIwMDkyMDIwNTkx \n\
OVoXDTMwMDkxODIwNTkxOVowWzELMAkGA1UEBhMCQ04xDjAMBgNVBAgMBUh1QmVp \n\
MQ4wDAYDVQQHDAVXdUhhbjENMAsGA1UECgwESFVTVDEMMAoGA1UECwwDQ1NFMQ8w \n\
DQYDVQQDDAZjYXJvb3QwWTATBgcqhkjOPQIBBggqgRzPVQGCLQNCAASJ8mm28JJR \n\
bZKLr6DCo1+KWimpKEsiTfZM19Zi5ao7Au6YLosyN71256MWmjwkwXxJeLa0lCfm \n\
kF/YWCX6qGQ0o1MwUTAdBgNVHQ4EFgQUAL5hW3RUzqvsiTzIc1gUHeK5uzQwHwYD \n\
VR0jBBgwFoAUAL5hW3RUzqvsiTzIc1gUHeK5uzQwDwYDVR0TAQH/BAUwAwEB/zAK \n\
BggqgRzPVQGDdQNHADBEAiAaZMmvE5zzXHx/TBgdUhjtpRH3Jpd6OZ+SOAfMtKxD \n\
LAIgdKq/v2Jkmn37Y9U8FHYDfFqk5I0qlQOAmuvbVUi3yvM= \n\
-----END CERTIFICATE----- \n\
";//根CA的公钥证书

const char certB[] = "\
-----BEGIN CERTIFICATE----- \n\
MIICHDCCAcKgAwIBAgIBAzAKBggqgRzPVQGDdTBbMQswCQYDVQQGEwJDTjEOMAwG \n\
A1UECAwFSHVCZWkxDjAMBgNVBAcMBVd1SGFuMQ0wCwYDVQQKDARIVVNUMQwwCgYD \n\
VQQLDANDU0UxDzANBgNVBAMMBmNhcm9vdDAeFw0yMDA5MjAyMTIxMDNaFw0zMDA5 \n\
MTgyMTIxMDNaMEoxCzAJBgNVBAYTAkNOMQ4wDAYDVQQIDAVIdUJlaTENMAsGA1UE \n\
CgwESFVTVDEMMAoGA1UECwwDQ1NFMQ4wDAYDVQQDDAVVc2VyQjBZMBMGByqGSM49 \n\
AgEGCCqBHM9VAYItA0IABB+6yy4hQEnt0lkrBm8RVLXz2P/6V6i74DOkTsomIS5D \n\
8RLpcK03vJL+UfPzQO5Ekr3LBiEPRD1oa+h5wlC6ZJejgYcwgYQwCQYDVR0TBAIw \n\
ADALBgNVHQ8EBAMCBSAwKgYJYIZIAYb4QgENBB0WG0dtU1NMIEdlbmVyYXRlZCBD \n\
ZXJ0aWZpY2F0ZTAdBgNVHQ4EFgQUAhr5rk22vn/vEACBoMYN1FMPmGAwHwYDVR0j \n\
BBgwFoAUAL5hW3RUzqvsiTzIc1gUHeK5uzQwCgYIKoEcz1UBg3UDSAAwRQIhANkY \n\
3oWdgG8jriJXuRhX5le4QjE19EnKB4rWCQcKvORfAiAR4hnLYT+dXgFCxVgPkjGO \n\
PDXj9mXJk6crvhRRxZfWNg== \n\
-----END CERTIFICATE----- \n\
";

const char pkeyB[] = "\
-----BEGIN EC PARAMETERS----- \n\
BggqgRzPVQGCLQ== \n\
-----END EC PARAMETERS----- \n\
-----BEGIN EC PRIVATE KEY----- \n\
MHcCAQEEINQhCKslrI3tKt6cK4Kxkor/LBvM8PSv699Xea7kTXTToAoGCCqBHM9V \n\
AYItoUQDQgAEH7rLLiFASe3SWSsGbxFUtfPY//pXqLvgM6ROyiYhLkPxEulwrTe8 \n\
kv5R8/NA7kSSvcsGIQ9EPWhr6HnCULpklw== \n\
-----END EC PRIVATE KEY----- \n\
";//消息接收者用户B的私钥

X509* getX509(const char* cert)
{
	BIO* bio;
	bio = BIO_new(BIO_s_mem());
	BIO_puts(bio, cert);
	return  PEM_read_bio_X509(bio, NULL, NULL, NULL);
}
EVP_PKEY* getpkey(const char* private_key)
{
	BIO* bio_pkey = BIO_new_mem_buf((char*)private_key, strlen(private_key));
	if (bio_pkey == NULL)
		return NULL;
	return  PEM_read_bio_PrivateKey(bio_pkey, NULL, NULL, NULL);
}

void decrypt()
{
	char* message;
	message = (char*)malloc(sizeof(char) * 10000);
	BIO* b;
	PKCS7* p7;
	EVP_PKEY* pB = getpkey(pkeyB);
	X509* cB = getX509(certB);
	b = BIO_new_fp(stdin, 1);
	p7 = PEM_read_bio_PKCS7(b, NULL, NULL, NULL);
	if (p7 == NULL)
	{
		printf("ERROR\n");
		return;
	}

	BIO* mess = PKCS7_dataDecode(p7, pB, NULL, cB);
	int len = BIO_read(mess, message, 9999);
	message[len] = 0;
	//解密完成message
	//验证
	STACK_OF(X509)* certs = NULL;
	X509_STORE* store = X509_STORE_new();
	X509_STORE_add_cert(store, getX509(cacert));

	//certs
	certs = p7->d.signed_and_enveloped->cert;
	if (certs == NULL)
	{
		printf("ERROR\n");
		return;
	}
	sk_X509_push(certs, getX509(cacert));

	//ctx
	STACK_OF(PKCS7_SIGNER_INFO)* mysign = PKCS7_get_signer_info(p7);
	int count = sk_PKCS7_SIGNER_INFO_num(mysign);
	for (int i = 0; i < count; i++) {
		PKCS7_SIGNER_INFO* signerinfo = sk_PKCS7_SIGNER_INFO_value(mysign, i);
		if (signerinfo == NULL)
		{
			printf("ERROR\n");
			return;
		}

		X509* cert = PKCS7_cert_from_signer_info(p7, signerinfo);
		X509_STORE_CTX* ctx = X509_STORE_CTX_new();
		X509_STORE_CTX_init(ctx, store, cert, certs);
		if (ctx == NULL)
		{
			printf("ERROR\n");
			return;
		}

		if (X509_verify_cert(ctx) == 0)
		{
			printf("ERROR\n");
			return;
		}

		if (PKCS7_dataVerify(store, ctx, mess, p7, signerinfo) == 0)
		{
			printf("ERROR\n");
			return;
		}
		X509_free(cert);
		X509_STORE_CTX_cleanup(ctx);
		X509_STORE_CTX_free(ctx);
	}
	printf("%s", message);
}

int main(int argc, char** argv) {
	ERR_load_crypto_strings();
	OpenSSL_add_all_algorithms();
	decrypt();

	return 0;
}
