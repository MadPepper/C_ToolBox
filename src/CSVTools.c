/**
 * CSVTools.c
 * @brief	CSV入出力
 * @note
 */


/*------------------------------------------------*
 * Includes
 *------------------------------------------------*/
#include <stdio.h>
#include "Typedef.h"
#include "FileTools.h"
#include "CSVTools.h"

/*------------------------------------------------*
 * Defines/Macros
 *------------------------------------------------*/

/*------------------------------------------------*
 * Type definitions
 *------------------------------------------------*/
typedef struct{
	ULONG ulColmun;	// 行
	ULONG ulRaw;	// 列
	ULONG ulLength;	// 長さ
	CHAR *pcAddres;	// バッファ上のアドレス
}T_CSV_CELL;

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
/**
 * @brief		CSV_parseCSV
 * @param[in]	CHAR *pcFilePath		展開するファイルのパス
 * @param[in]	CHAR cDelimiter			デリミタ文字
 * @param[out]	CHAR **ppcLoadBuffer	展開先のメモリアドレス
 * @param[out]	T_CSV_CELL **pptCell	アドレス上のセル情報
 * @return		LONG
 * @note		!!DANGER!! ppcLoadBufferとpptCellで取得したバッファは後で必ず開放すること
 */
LONG CSV_parseCSV(CHAR *pcFilePath, CHAR **ppcLoadBuffer, T_CSV_CELL **pptCell)
{
	LLONG llLength;
	CHAR *pBufPos;
	LLONG llBufCount;
	ULONG ulColmunLen = 0;
	ULONG ulColLenTmp = 0;
	ULONG ulRawLen = 0;
	
	llLength = FT_LoadFile(pcFilePath, ppcLoadBuffer);
	if (llLength < 0) {
		perror("Failed to file load");
		return -1;
	}
	pBufPos = *ppcLoadBuffer;
	
	for (llBufCount = 0; llBufCount < 100; ++llBufCount) {
		printf("%s", pBufPos);
		if (D_CSV_DELIMITER == *pBufPos) {
			for (; *(pBufPos) == *(pBufPos+1); ++pBufPos) {
//				Nothing to do
			}
			ulColLenTmp++;
			pBufPos++;
		} else if (memcmp(D_CSV_LINEFEED, pBufPos, 2) == 0) {
			ulRawLen++;
			if (ulColmunLen < ulColLenTmp) {
				ulColmunLen = ulColLenTmp;
			}
			ulColLenTmp = 0;
			pBufPos++;
#if 1	// 行頭のデリミタをすべてスキップ(行頭はデリミタ以外から始まる)
			for (; *(pBufPos) == *(pBufPos+1); ++pBufPos) {
//				Nothing to do
			}
#endif
		} else {
			pBufPos++;
		}
	}
	
	printf("%d, %d", ulColmunLen, ulRawLen);
//	*pptCell = (T_CSV_CELL *)malloc(ulColmunLen*ulRawLen);
	
	
	return 0;
}
