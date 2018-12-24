#ifndef __COMMON_H__
#define __COMMON_H__

#ifdef __cplusplus
extern "C" {
#endif

void testSwitch();
void getLocalTime();
int add_ok(int a, int b, int *sum);
int mul_ok(int a, int b, int *mul);

int Need_auto_Su_passwd(char *cmd_str,char *en_cmd, char **switchname);
void GetLocalIP(char *IP);

void decrypt(unsigned char *pwd);
void encrypt(unsigned char *pwd);


#ifdef __cplusplus
extern "C" {
#endif

#endif
