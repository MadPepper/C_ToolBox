/**
 * FileTools.c
 * @brief	ファイル入出力とかディレクトリ操作とか
 * @note
 */

/*------------------------------------------------*
 * Includes
 *------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

#include "Typedef.h"
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
/**
 * @brief	デリミタ文字をStrcatなどで使えるようにヌル文字を足したもの
 */
static const CHAR gacDelimiter[2] = { D_FT_DELIMITER, 0 };

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
 * @brief		ファイル全体をメモリに展開する
 * @brief		ファイルオープン→ファイルサイズ分のバッファをMalloc→バッファにファイル内容を読み出す
 * @param[in]	CHAR *pcFilePath	展開するファイルのパス
 * @param[out]	CHAR **pcLoadBuffer	展開先のメモリアドレス
 * @return		LLONG, 正の値; 読み出したサイズ, 負の値; エラーコード
 * @note		!!DANGER!! pcLoadBufferで取得したバッファは後で必ず開放すること
 */
LLONG FT_LoadFile(CHAR *pcFilePath, CHAR **ppcLoadBuffer) {
	LLONG llRet = 0;
	LONG slErr, slLength;
	FILE *pFile;
	fpos_t llPos;

	pFile = fopen(pcFilePath, "rb");		// Read as binary
	if (pFile == NULL) {
		printf("Cannot open file %s\n", pcFilePath);
		return -1;
	}
	slErr = fseek(pFile, 0, SEEK_END);
	if (slErr) {
		printf("Error occurs in file seek.(%d)\n", slErr);
		llRet = -2;
		goto FILE_CLOSE;
	}
	slErr = fgetpos(pFile, &llPos);
	if (slErr) {
		printf("Error occurs in getting file pos.(%d)\n", slErr);
		llRet = -3;
		goto FILE_CLOSE;
	}
	*ppcLoadBuffer = (char*) malloc(llPos);
	if (*ppcLoadBuffer == NULL) {
		perror("Memory allocation failed.\n");
		llRet = -4;
		goto FILE_CLOSE;
	}
	slErr = fseek(pFile, 0, SEEK_SET);
	if (slErr) {
		printf("Error occurs in file seek(2).(%d)\n", slErr);
		llRet = -5;
		free(*ppcLoadBuffer);
		goto FILE_CLOSE;
	}
	slLength = fread(*ppcLoadBuffer, 1, llPos, pFile);
	if (slLength != llPos) {
		printf("Error occurs in read file.(cannot read all %d/%lld)\n", slLength, llPos);
		llRet = -6;
		free(*ppcLoadBuffer);
		goto FILE_CLOSE;
	}
	llRet = llPos;

FILE_CLOSE:
	slErr = fclose(pFile);
	if (slErr) {
		printf("Error occurs in file close.(%d)\n", slErr);
		llRet = -3;
	}

	return llRet;
}

/**
 * @brief		2つのファイルを単純比較する
 * @param[in]	CHAR *pcFilePath1	1つ目のファイルパス
 * @param[in]	CHAR *pcFilePath2	2つ目のファイルパス
 * @return		LONG, エラーコード
 * @note
 */
LONG FT_CompareFile(CHAR *pcFilePath1, CHAR *pcFilePath2) {
	CHAR *pcAnswerBuff, *pcTestBuff;
	LLONG llSize1, llSize2;
	LONG slRet = 0;

	llSize1 = FT_LoadFile(pcFilePath1, &pcTestBuff);
	if (llSize1 < 0) {
		printf("Cannot read file1.(%s)\n", pcFilePath1);
		slRet = -1;
		goto EXIT;
	}
	llSize2 = FT_LoadFile(pcFilePath2, &pcAnswerBuff);
	if (llSize2 < 0) {
		printf("Cannot read file2.(%s)\n", pcFilePath2);
		slRet = -2;
		goto EXIT;
	}

	if(llSize1 != llSize2){
		printf("File size is not matched. XP\n(%s)\n(%s)\n", pcFilePath1, pcFilePath2);
		slRet = -3;
		goto EXIT;
	}

	slRet = memcmp(pcTestBuff, pcAnswerBuff, llSize1);
	if (slRet != 0) {
		printf("%s\nand\n%s\nFiles are not matched. XP\n\n", pcFilePath1, pcFilePath2);
		slRet = -3;
		goto EXIT;
	}

//	printf("%s\nand\n%s\nare matched. ;)\n\n", pcFilePath1, pcFilePath2);

EXIT:
	free(pcAnswerBuff);
	free(pcTestBuff);

	return slRet;
}

/**
 * @brief		引数のディレクトリパスを取得する[ファイルパスが引数の場合は親ディレクトリのパスを取得する]
 * @param[in]	CHAR *pcInputPath	元のパス
 * @param[out]	CHAR *pcOutputPath	探索後のパス（領域は自動確保ではない）
 * @return		LONG, エラーコード
 * 					return -1;	ディレクトリ探索に失敗
 * 					return 1;	親ディレクトリを発見
 * 					return 0;	引数はすでにディレクトリ
 * @note		ファイルパス文字列の最大長は(D_FT_MAX_FILE_PATH_LEN)
 * @note		パスのデリミタは(D_FT_DELIMITER)
 * @note		todo 文字列が最大長を超えた場合の処理
 */
LONG FT_GetDirectoryPath(CHAR *pcInputPath, CHAR *pcOutputPath) {
	DIR *ptDirectory;
	CHAR acTmpPath[D_FT_MAX_FILE_PATH_LEN] = { 0 };
	CHAR *pcStrPos;

	strcpy(acTmpPath, pcInputPath);

	ptDirectory = opendir(acTmpPath);
	if (ptDirectory == NULL) {
		pcStrPos = strrchr(acTmpPath, gacDelimiter[0]);	// Search delimiter
		*pcStrPos = 0;		// Write null character, cut off string.
		pcStrPos = strrchr(acTmpPath, gacDelimiter[0]);	// Search delimiter again
		if (pcStrPos == NULL) {	// Check root directory
			strcat(acTmpPath, gacDelimiter);	// Concatenate delimiter
		}

		ptDirectory = opendir(acTmpPath);
		if (ptDirectory == NULL) {
			printf("Something wrong with path %s.\n", acTmpPath);
			return -1;
		}
		closedir(ptDirectory);

		strcpy(pcOutputPath, acTmpPath);

		return 1;
	} else {
		strcpy(pcOutputPath, acTmpPath);
	}
	closedir(ptDirectory);

	return 0;
}

/**
 * @brief		ディレクトリの内容を読み出す
 * @param[in]	CHAR *pcDirectoryPath			ディレクトリパス
 * @param[out]	T_DIR_ENT_ARRAY *ptEntryArray	ディレクトリ内容を格納する構造体(領域は自動確保ではない)
 * @return		LONG, エラーコード
 * @note		読み出すエントリ数の最大値は(D_FT_MAX_ENT_NUM)
 * @note		ファイル名の最大長は(FILENAME_MAX) これはGccに依存
 * @note		ファイルパスの最大長は(D_FT_MAX_FILE_PATH_LEN)
 * @note		ファイルパスのデリミタは(D_FT_DELIMITER)
 * @note		todo Sort by FileName, Size
 * @note		todo 文字列が最大長を超えた場合の処理
 */
LONG FT_GetEntriesInDirectory(CHAR *pcDirectoryPath, T_FT_FILES_ARRAY *ptEntryArray) {
	DIR *ptDirectory;
	struct dirent *ptDirEnt;
	LONG slDelimiterFlg = 1, slStrLen;

	ptDirectory = opendir(pcDirectoryPath);
	if (ptDirectory == NULL) {
		printf("Cannot open directory:%s\n", pcDirectoryPath);
		return -1;
	}

	ptEntryArray->ulCount = 0;
	memset(ptEntryArray->aascFileStr, 0, sizeof(ptEntryArray->aascFileStr));
	memset(ptEntryArray->aascFilePathStr, 0, sizeof(ptEntryArray->aascFilePathStr));
	slStrLen = strlen(pcDirectoryPath);
	if (pcDirectoryPath[slStrLen - 1] == gacDelimiter[0]) {	// Check root directory
		slDelimiterFlg = 0;
	}

	for (ptDirEnt = readdir(ptDirectory); ptDirEnt != NULL; ptDirEnt = readdir(ptDirectory)) {
		if (strcmp(ptDirEnt->d_name, ".") == 0 || strcmp(ptDirEnt->d_name, "..") == 0) {
			continue;
		}
		strcpy(ptEntryArray->aascFileStr[ptEntryArray->ulCount], ptDirEnt->d_name);
		strcpy(ptEntryArray->aascFilePathStr[ptEntryArray->ulCount], pcDirectoryPath);
		if (slDelimiterFlg) {
			strcat(ptEntryArray->aascFilePathStr[ptEntryArray->ulCount], gacDelimiter);
		}
		strcat(ptEntryArray->aascFilePathStr[ptEntryArray->ulCount], ptDirEnt->d_name);
		if (ptEntryArray->ulCount >= (D_FT_MAX_ENT_NUM - 1)) {
			printf("Too many files are in this folder.(%s)\n", pcDirectoryPath);
		} else {
			ptEntryArray->ulCount++;
		}
	}

	closedir(ptDirectory);

	return 0;
}
