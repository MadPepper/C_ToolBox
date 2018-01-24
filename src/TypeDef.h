/*
 * TypeDef.h
 * @brief	型の再宣言
 * @note	CO_TARGET_OS_TYPEを変更することで、対象OS上の型と互換性のある形で宣言する
 */

#ifndef TYPEDEF_H_
#define TYPEDEF_H_
/*------------------------------------------------*
 * Includes
 *------------------------------------------------*/

/*------------------------------------------------*
 * Defines/Macros
 *------------------------------------------------*/
#define D_OS_TYPE_32BIT			(0)
#define D_OS_TYPE_64BIT			(1)

#define TRUE					(1)
#define FALSE					(0)

#define CO_TARGET_OS_TYPE		(D_OS_TYPE_32BIT)

/*------------------------------------------------*
 * Type definitions
 *------------------------------------------------*/
typedef char					CHAR;		// 8bit signed integer
typedef unsigned char			BYTE;		// 8bit unsigned integer
typedef char					INT8;		// 8bit signed integer
typedef unsigned char			UINT8;		// 8bit unsigned integer
typedef signed short			SHORT;		// 16bit signed integer
typedef unsigned short			USHORT;		// 16bit unsigned integer
typedef signed short			INT16;		// 16bit signed integer
typedef unsigned short			UINT16;		// 16bit unsigned integer
#if (CO_TARGET_OS_TYPE == D_OS_TYPE_32BIT)
typedef signed int				LONG;		// 32bit signed integer
typedef unsigned int			ULONG;		// 32bit unsigned integer
#else
typedef signed long				LONG;		// 64bit signed integer
typedef unsigned long			ULONG;		// 64bit unsigned integer
#endif
typedef signed int				INT32;		// 32bit sigend integer
typedef unsigned int			UINT32;		// 32bit unsigned integer
typedef signed int				BOOL;		// 32bit signed integer
typedef float					FLOAT;		// 32bit floating point
typedef signed long long		LLONG;		// 64bit signed integer
typedef unsigned long long		ULLONG;		// 64bit unsigned integer
typedef double					DOUBLE;		// 64bit floating point

/*------------------------------------------------*
 * Function prototype
 *------------------------------------------------*/

#endif /* TYPEDEF_H_ */
