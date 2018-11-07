extern "C" {
#include "miracl.h"
#include "mirdef.h"
}

/******************************************************************************
定义椭圆曲线 y^2 = x^3 + ax + b
基点G(x,y), 其阶为n
******************************************************************************/
typedef struct {
	char *p;
	char *a;
	char *b;
	char *n;
	char *x;
	char *y;
}ECC;

/******************************************************************************
Function: key_generate
Description: Generate the private key and public key
Calls:
Called By: 
Input: ECC *ecc
Output: private_key[32], pk_x[32], pk_y[32], Za[256]
Return: null
Others: 
*******************************************************************************/
void key_generate(big p, big a, big b, big n, big x, big y, ECC* ecc, unsigned char* private_key, unsigned char* pk_x, unsigned char *pk_y, unsigned char *Za);


/******************************************************************************
Function: sm2_sign
Description: Sign the message
Calls:
Called By:
Input: ECC *ecc, msg, msg_len, Za, private_key[32]
Output: sign_r[32], sign_s[32]
Return: null
Others:
*******************************************************************************/
void sm2_sign(big p, big a, big b, big n, big x, big y, ECC* ecc, unsigned char *msg, int msg_len, unsigned char *Za, unsigned char* private_key, unsigned char *sign_r, unsigned char *sign_s);


/******************************************************************************
Function: sm2_verify
Description: Verify the signature
Calls:
Called By:
Input: ECC *ecc, msg, Za, sign_r[32], sign_s[32], pk_x[32], pk_y[32]
Output: null
Return: 1 if  pass, 0 else
Others:
*******************************************************************************/
int sm2_verify(big p, big a, big b, big n, big x, big y, ECC* ecc, unsigned char *msg, int msg_len, unsigned char *Za, unsigned char  *sign_r, unsigned char *sign_s, unsigned char *pk_x, unsigned char *pk_y);