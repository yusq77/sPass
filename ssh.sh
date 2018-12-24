#!/usr/bin/expect 
set timeout 10
# 参数是从0开始的
set PORT 22
set SRCFILE libmyso.so
set USERNAME root
set IP 10.10.3.128
set TARPATH /home/spv/bin
set PASSWORD 62960909

spawn scp -P ${PORT}  ${SRCFILE} ${USERNAME}@${IP}:${TARPATH}
# 输入脚本模板,expect { 必须在同一行
expect {
  "(yes/no)?"
  {
    send -- "yes\r";
  }
  "*assword:"
  {
    send -- "$PASSWORD\r"
  }
}

expect "100%"
interact
