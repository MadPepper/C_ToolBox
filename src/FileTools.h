/**
 * FileTools.h
 * @brief	�t�@�C�����o�͂Ƃ��f�B���N�g������Ƃ�
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
#define D_FT_MAX_ENT_NUM (1024)    /// �t�H���_���̍ő�G���g�����i����ȏ�͈���Ȃ��j
#define D_FT_MAX_FILE_PATH_LEN (512 + FILENAME_MAX)    /// �t�@�C���p�X�̍ő咷�i����ȏ�͈���Ȃ��j
#define D_FT_DELIMITER ('\\')                          /// Windows�̃p�X�̃f���~�^

/*------------------------------------------------*
 * Type definitions
 *------------------------------------------------*/
/**
 * @brief	�f�B���N�g�����e���i�[���邽�߂̍\����
 * @note
 */
typedef struct {
    ULONG ulCount;                                                      /// �G���g����
    CHAR  aascFileStr[D_FT_MAX_ENT_NUM][FILENAME_MAX];                  /// �f�B���N�g����or�t�@�C����
    CHAR  aascFilePathStr[D_FT_MAX_ENT_NUM][D_FT_MAX_FILE_PATH_LEN];    /// �p�X
} T_FT_FILES_ARRAY;                                                     ///

/*------------------------------------------------*
 * Function prototype
 *------------------------------------------------*/
LLONG FT_LoadFile(CHAR *pcFilePath, CHAR **pcLoadBuffer);
LONG  FT_CompareFile(CHAR *pcFilePath1, CHAR *pcFilePath2);
LONG  FT_GetDirectoryPath(CHAR *pcInputPath, CHAR *pcOutputPath);
LONG  FT_GetEntriesInDirectory(CHAR *pcDirectoryPath, T_FT_FILES_ARRAY *ptEntryArray);

#endif /* FILETOOLS_H_ */
