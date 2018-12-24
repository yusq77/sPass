/*  Copyright (C) 2018 * Ltd. All rights reserved.
 *      Create date : 2018-11-05 17:34:38
 *================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <time.h>

#include "common.h"
#include "unionenc.h"

void testSwitch()
{
    int n = 5;

    switch(n) {
        case 1: printf("1\n");break;
        case 5:
        case 6: printf("6\n"); break; //才退出
        default:
        printf("default\n");
    }
}

void getLocalTime()
{
    time_t timer;
    struct tm *tblock;

#if 0
    time(&timer);
    tblock = localtiem(&timer);
    printf ( "localtime: %s", asctime (tblock) );
#endif

    timer = time(NULL);
    tblock = localtime(&timer);
    printf("Hour is: %d  ,time: %ld\n",tblock->tm_hour,20000L/5);

    char date[255];
    strftime(date,255,"%Y%m%d\n",tblock);
    printf("date: %s\n",date);

}

int add_ok(int a, int b, int *sum)
{
    if( ((b > 0) && (a > (INT_MAX - b))) ||
        ((b < 0) && (a < (INT_MIN - b))))
    {
        printf("Handle error!");
        return -1;
    }
    *sum = a + b;
    printf("sum = %d\n", *sum);
    return 0;
}

int mul_ok(int a, int b, int *mul)
{
    if(a > 0)
    {
        if(b > 0)
        {
            if(a > (INT_MAX / b))
            {
                /* Handle error */
                printf("Handle error!");
                return -1;
            }
        }
        else
        {
            if(b < (INT_MIN / a))
            {
                /* Handle error */
                printf("Handle error!");
                return -1;
            }
        }
    }
    else
    {
        if(b > 0)
        {
            if(a < (INT_MIN / b))
            {
                /* Handle error */
                printf("Handle error!");
                return -1;
            }
        }
        else
        {
            if( (a != 0) && (b < (INT_MAX / a)))
            {
                /* Handle error */
                printf("Handle error!");
                return -1;
            }
        }
    }
    *mul = a * b;
    printf("mul = %d\n", *mul);
    return 0;
}

/* need_auto_su_passwd */
int Need_auto_Su_passwd(char *cmd_str,char *en_cmd, char **switchname)
{
   if (strlen(en_cmd) == 0)
   {
           return 1;
   }
   int ret_limit=0;
   int i;
   int prefix_len=0;
   char *p=strstr(cmd_str,en_cmd);
   printf("p[%s]\n", p);
   if(p)
   {
      prefix_len=p-cmd_str;
      printf("prefix_len[%d]\n", prefix_len);
     for(i=0;i<prefix_len;i++)
     {
       if(cmd_str[i]!=0x20 && i!=0)
       {
         ret_limit=1;
         break;
       }
     }
   }

   int suffix_cmd=prefix_len+strlen(en_cmd);
   printf("suffix_cmd[%d]\n", suffix_cmd);
   printf("cmd_str+prefix_len[%s]\n", cmd_str+prefix_len);
   printf("strcmp(cmd_str+prefix_len,en_cmd)[%d]\n", strcmp(cmd_str+prefix_len,en_cmd));
   if(!ret_limit&&p && (cmd_str[suffix_cmd]==0x20||!strcmp(cmd_str+prefix_len,en_cmd)))
   {
           if (switchname)
           {
                   if (*switchname)
                   {
                           free(*switchname);
                           *switchname = NULL;
                   }
                   printf("strcmp(en_cmd,sudo)[%d]n", strcmp(en_cmd,"sudo"));
                   if(strstr(cmd_str,"sudo"))
                   {
                     *switchname = "yusq";
                     return 0;
                   }
                   //get the name of switchname and input
                   p += strlen(en_cmd);
                   printf("p[%s]\n", p);
                   //skip space
                   for (; *p != 0 ; ++p)
                   {
                           if (*p != ' ')
                           {
                                   break;
                           }
                   }
                   if (strlen(p))
                   {
                           //skip space and '-'
                           for (; *p != '\0'; ++p)
                           {
                                   if (*p == ' ' || *p == '-')
                                   {
                                   }
                                   else
                                   {
                                           break;
                                   }
                           }
                          *switchname = strdup(p);
                          printf("switchname_before_cancel_space[%s]\n", *switchname);
                          //abandon newline and space
                          char *p = *switchname;
                           for (i = 0; *p != '\0';p++)
                            {
                                    if (*p == ' ' || *p == '\r' || *p == '\n')
                                    {
                                            *p = 0;
                                            break;
                                    }
                            }
                            printf("switchname[%s]\n", *switchname);
                    }
            }
            return 0;
    }
    return 1;
}


char* ReadSpeacialLine(const char* filename, int whichLine)
{
    if (whichLine < 0 || NULL == filename)
    {
        return NULL;
    }
    FILE *fp = fopen(filename, "r");
    if (NULL == fp) {
        return NULL;
    }
    int reachWhichLine = 0;
    int curLine = 1;
#define LINE_SIZE 256
    char *data = NULL;
    data = (char*) malloc(LINE_SIZE);
    while (!feof(fp))
    {
        memset(data, 0, LINE_SIZE);
        fgets(data, LINE_SIZE - 1, fp);
        curLine++;
        if (curLine > whichLine)
        {
            reachWhichLine = 1; //already read whichLine
            break;
        }
    }
    fclose(fp);

    return 0 == reachWhichLine ? NULL : data;
}

void GetLocalIP(char *IP)
{
    char *ip = (char *)calloc(1, 50);
    char *cmd = (char *)calloc(1,128);
    strcpy(cmd, "ip addr | grep inet | awk '{ print $2; }' | sed 's/\\/.*$//' >> ip.txt");
    system(cmd);
    strcpy(ip, ReadSpeacialLine("ip.txt", 3));
    snprintf(IP, strlen(ip), "%s", ip); //Remove the newline characters at the end of IP.
    system("rm -f ip.txt");
    free(cmd);
    free(ip);
}

void encrypt(unsigned char *pwd)
{
    /*password encrypt*/
    int OutLen=128, len;
    unsigned char EncryptedData[128] = {0};

    UnionPswdEncrypt((unsigned char*)pwd, strlen(pwd), EncryptedData, OutLen, &len);
    printf("[EncPwd]: %s\n", EncryptedData);
}

void decrypt(unsigned char *pwd)
{
    //password decrypt
    unsigned char clearpwd[100] = {0};
    int pwdlen = 0;

    UnionPswdDecrypt(pwd, strlen(pwd), clearpwd, 1000, &pwdlen);
    printf("[ClearPwd]: %s\n", clearpwd);
}


