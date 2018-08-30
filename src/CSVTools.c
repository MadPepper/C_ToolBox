/**
 * CSVTools.c
 * @brief	CSV���o��
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
	ULONG ulColmun;	// �s
	ULONG ulRaw;	// ��
	ULONG ulLength;	// ����
	CHAR *pcAddres;	// �o�b�t�@��̃A�h���X
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
 * @param[in]	CHAR *pcFilePath		�W�J����t�@�C���̃p�X
 * @param[in]	CHAR cDelimiter			�f���~�^����
 * @param[out]	CHAR **ppcLoadBuffer	�W�J��̃������A�h���X
 * @param[out]	T_CSV_CELL **pptCell	�A�h���X��̃Z�����
 * @return		LONG
 * @note		!!DANGER!! ppcLoadBuffer��pptCell�Ŏ擾�����o�b�t�@�͌�ŕK���J�����邱��
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
#if 1	// �s���̃f���~�^�����ׂăX�L�b�v(�s���̓f���~�^�ȊO����n�܂�)
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
