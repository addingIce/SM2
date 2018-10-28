#include "common_test.h"

void BytePrint(U8* pBytebuff, S32 bytelen)
{
	int i;
	for (i = 0; i < bytelen; i++)
	{
		if (i%32 ==0)
		{
			printf("\n");
		}
	    printf("%02X", pBytebuff[i]);
	}
	printf("\n");
}

