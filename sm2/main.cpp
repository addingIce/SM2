#include <stdio.h>
#include <iostream>
#include "sm2.h"
#include "common_test.h"
#include "typedef.h"
extern "C" {
#include "miracl.h"
#include "mirdef.h"
}

int main()
{
	//椭圆曲线参数，依次为p,a,b,n,x,y
	ECC Ecc256 = {
		"FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFF",
		"FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFC",
		"28E9FA9E9D9F5E344D5A9E4BCF6509A7F39789F515AB8F92DDBCBD414D940E93",
		"FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFF7203DF6B21C6052B53BBF40939D54123",
		"32C4AE2C1F1981195F9904466A39C9948FE30BBFF2660BE1715A4589334C74C7",
		"BC3736A2F4F6779C59BDCEE36B692153D0A9877CC62A474002DF32E52139F0A0"
	};

	unsigned char msg[3] = { 0x61, 0x62, 0x63 };	//待签名数消息

	unsigned char Za[32];	//用户杂凑值Za, 此程序中Za在密钥生成时生成， 签名以及验证时不再另外生成
	unsigned char private_key[32] = { 0 };
	unsigned char pk_x[32] = { 0 };
	unsigned char pk_y[32] = { 0 };
	unsigned char sign_r[32] = { 0 };
	unsigned char sign_s[32] = { 0 };

	//初始化椭圆曲线参数
	big p, a, b, n, x, y;
	miracl *mip = mirsys(300, 0);
	p = mirvar(0);
	a = mirvar(0);
	b = mirvar(0);
	n = mirvar(0);
	x = mirvar(0);
	y = mirvar(0);
	mip->IOBASE = 16;
	cinstr(p, Ecc256.p);
	cinstr(a, Ecc256.a);
	cinstr(b, Ecc256.b);
	cinstr(n, Ecc256.n);
	cinstr(x, Ecc256.x);
	cinstr(y, Ecc256.y);

	//椭圆曲线公私钥生成
	printf("Key generate...\n");
	key_generate(p, a, b, n, x, y, &Ecc256, private_key, pk_x, pk_y, Za);

	//签名
	printf("\nSign...\n");
	sm2_sign(p, a, b, n, x, y, &Ecc256, msg, 3, Za, private_key, sign_r, sign_s);
	printf("sign_r:");
	BytePrint(sign_r, 32);
	printf("sign_s:");
	BytePrint(sign_s, 32);

	//验证签名
	printf("\nVerify...\n");
	printf("%d\n", sm2_verify(p, a, b, n, x, y, &Ecc256, msg, 3, Za, sign_r, sign_s, pk_x, pk_y));

	mirkill(p);
	mirkill(a);
	mirkill(b);
	mirkill(n);
	mirkill(x);
	mirkill(y);
	mirexit();

	return 0;
}
