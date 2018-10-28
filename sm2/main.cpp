#include <iostream>
#include "sm2.h"
#include "common_test.h"
#include "typedef.h"
using namespace std;
extern ECC Ecc256;
int main()
{
	unsigned char msg[3] = { 0x61, 0x62, 0x63 };	//待签名数消息

	unsigned char Za[32];	//用户杂凑值Za, 此程序中Za在密钥生成时生成， 签名以及验证时不再另外生成
	unsigned char private_key[32] = { 0 };
	unsigned char pk_x[32] = { 0 };
	unsigned char pk_y[32] = { 0 };
	unsigned char sign_r[32] = { 0 };
	unsigned char sign_s[32] = { 0 };

	printf("Key generate...\n");
	key_generate(&Ecc256, private_key, pk_x, pk_y, Za);

	printf("\nSign...\n");
	sm2_sign(&Ecc256, msg, 3, Za, private_key, sign_r, sign_s);
	printf("sign_r:");
	BytePrint(sign_r, 32);
	printf("sign_s:");
	BytePrint(sign_s, 32);

	printf("\nVerify...\n");
	printf("%d\n", sm2_verify(&Ecc256, msg, 3, Za, sign_r, sign_s, pk_x, pk_y));
	return 0;
}
