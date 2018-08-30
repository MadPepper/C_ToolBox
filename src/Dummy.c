/**
 * Dummy.c
 * @brief	プロジェクトコンパイル用ダミーファイル
 * @note
 */


/*------------------------------------------------*
 * Includes
 *------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "FileTools.h"

/*------------------------------------------------*
 * Defines/Macros
 *------------------------------------------------*/

/*------------------------------------------------*
 * Type definitions
 *------------------------------------------------*/

/*------------------------------------------------*
 * Global Variables
 *------------------------------------------------*/

/*------------------------------------------------*
 * Function prototype
 *------------------------------------------------*/

/*------------------------------------------------*
 * Local Functions
 *------------------------------------------------*/

/*------------------------------------------------*
 * Global Functions
 *------------------------------------------------*/
int main(int argc, const char *argv[]){
	int count;
	CHAR *pcLoadBuffer, *pcTmp;
	LLONG llLength, llPos;
	FILE *fp;
	CHAR acTmpName[256] = {0};
	
	for (count = 1; count < argc; ++count) {
		strcpy(acTmpName, argv[count]);
		llLength = FT_LoadFile(acTmpName, &pcLoadBuffer);
		if (llLength < 0) {
			printf("Failed to load.");
			
			return -1;
		}
		
//		printf("%d",(LONG)llLength);
		for (llPos = 0; llPos < llLength; ++llPos) {
			if (memcmp("\n ", (const void*)(pcLoadBuffer+llPos), 2) == 0) {
				memcpy((void*)(pcLoadBuffer+llPos), "\n0", 2);
			}
		}
		
		pcTmp = strstr(acTmpName, ".dat");
		strcpy(pcTmp, ".csv");
		pcTmp = strstr(acTmpName, "588C_");
		strcpy(pcTmp, (const char*)(pcTmp+5));
		printf("%s\n", acTmpName);
		
		fp = fopen(acTmpName, "wb+");
		fwrite(pcLoadBuffer, sizeof(CHAR), llLength, fp);
		fclose(fp);
		
		free(pcLoadBuffer);
	}
	return 0;
}
