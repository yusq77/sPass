#ifndef UNION_ENC_H
#define UNION_ENC_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <openssl/evp.h>

enum {                       //加密模式
	UNION_ENCMODE_NORMAL = 0,
	UNION_ENCMODE_HWINFO,
	UNION_ENCMODE_LICENSE,
	UNION_ENCMODE_USER_TOKEN,
	UNION_ENCMODE_PATCH_FILE,
	UNION_ENCMODE_ACC_PSWD,	
	UNION_ENCMODE_ACC_PSWD_FILE,
	UNION_ENCMODE_HACTOKEN
};

enum {                       //pwd转换成加解密key,iv的模式(包括补位、转换)
	UNION_KEY_TRANS_NORMAL = 1,
	UNION_KEY_TRANS_PSWDFILE_EXPORT
};
#ifdef __cplusplus
extern "C" {
#endif

void HexPrint( unsigned char *data, int InputLen );
//int UnionPrintHex( char *data, int len, char *HexData );
void B64Encode( unsigned char *ClearData, int InputLen,
	unsigned char *B64Data, int *B64DataLen );
void B64Decode( unsigned char *B64Data, int InputLen,
	unsigned char *ClearData, int *ClearDataLen );
int UnionNormalDecrypt( unsigned char *EncryptedData, int InputLen,
	unsigned char *ClearData, int MaxOutputLen, int *ClearDataLen );
int UnionNormalEncrypt( unsigned char *ClearData, int InputLen,\
	unsigned char *EncryptedData, int MaxOutputLen,\
	int *EncryptedDataLen );
int UnionTokenEncrypt( unsigned char *ClearData, int InputLen, 
		        unsigned char *EncryptedData, int MaxOutputLen, int *EncryptedDataLen );
int UnionTokenDecrypt( unsigned char *EncryptedData, int InputLen, 
		        unsigned char *ClearData, int MaxOutputLen, int *ClearDataLen );
int UnionHWInfoEncrypt( unsigned char *ClearData, int InputLen, 
		        unsigned char *EncryptedData, int MaxOutputLen, int *EncryptedDataLen );
int UnionHWInfoDecrypt( unsigned char *EncryptedData, int InputLen, 
		        unsigned char *ClearData, int MaxOutputLen, int *ClearDataLen );
int UnionPatchEncrypt( char *InFile, char *OutFile, unsigned char enckey[64] );
int UnionPatchDecrypt( char *InFile, char *OutFile, unsigned char deckey[64] ); 
int UnionPwdEptFileEncrypt( char *InFile, char *OutFile, unsigned char enckey[16] );
int UnionPwdEptFileDecrypt( char *InFile, char *OutFile, unsigned char deckey[16] ); 
int UnionPswdEncrypt( unsigned char *ClearData, int InputLen, 
		unsigned char *EncryptedData, int MaxOutputLen, int *EncryptedDataLen );
int UnionPswdDecrypt( unsigned char *EncryptedData, int InputLen, 
		unsigned char *ClearData, int MaxOutputLen, int *ClearDataLen );
int UnionGetKeyByPwd( unsigned char *pwd, int TransMode, 
		unsigned char key[24], unsigned char iv[16] );
int UnionDataEncSM4( unsigned char *input, int len, unsigned char *output,
		unsigned char key[16], unsigned char iv[16] );
int UnionDataDecSM4( unsigned char *input, int len, unsigned char *output,
		unsigned char key[16], unsigned char iv[16] );
int UnionHTokenEncrypt( unsigned char *ClearData, int InputLen, 
		unsigned char *EncryptedData, int MaxOutputLen, int *EncryptedDataLen );
int UnionHTokenDecrypt( unsigned char *EncryptedData, int InputLen, 
		unsigned char *ClearData, int MaxOutputLen, int *ClearDataLen );
int UnionSM4PaddingLen( int len );

#ifdef __cplusplus
}
#endif

#endif
