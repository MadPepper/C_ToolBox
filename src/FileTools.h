/**
 * FileTools.h
 * @brief	ファイル入出力とかディレクトリ操作とか
 * @note
 */

#ifndef FILETOOLS_H_
#define FILETOOLS_H_
/*------------------------------------------------*
 * Includes
 *------------------------------------------------*/
#include <stdio.h>

#include "TypeDef.h"

/*------------------------------------------------*
 * Defines/Macros
 *------------------------------------------------*/
#define D_FT_MAX_ENT_NUM (1024)    /// フォルダ内の最大エントリ数（これ以上は扱わない）
#define D_FT_MAX_FILE_PATH_LEN (512 + FILENAME_MAX)    /// ファイルパスの最大長（これ以上は扱わない）
#define D_FT_DELIMITER ('\\')                          /// Windowsのパスのデリミタ

/*------------------------------------------------*
 * Type definitions
 *------------------------------------------------*/
/**
 * @brief	ディレクトリ内容を格納するための構造体
 * @note
 */
typedef struct {
    ULONG ulCount;                                                      /// エントリ数
    CHAR  aascFileStr[D_FT_MAX_ENT_NUM][FILENAME_MAX];                  /// ディレクトリ名orファイル名
    CHAR  aascFilePathStr[D_FT_MAX_ENT_NUM][D_FT_MAX_FILE_PATH_LEN];    /// パス
} T_FT_FILES_ARRAY;                                                     ///

/*------------------------------------------------*
 * Function prototype
 *------------------------------------------------*/
LLONG FT_LoadFile(CHAR *pcFilePath, CHAR **pcLoadBuffer);
LONG  FT_CompareFile(CHAR *pcFilePath1, CHAR *pcFilePath2);
LONG  FT_GetDirectoryPath(CHAR *pcInputPath, CHAR *pcOutputPath);
LONG  FT_GetEntriesInDirectory(CHAR *pcDirectoryPath, T_FT_FILES_ARRAY *ptEntryArray);

#endif /* FILETOOLS_H_ */
