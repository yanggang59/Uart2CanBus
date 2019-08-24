#ifndef  _SERIAL_SEND_H
#define _SERIAL_SEND_H
 
 //串口相关的头文件  
#include<stdio.h>      /*标准输入输出定义*/  
#include<stdlib.h>     /*标准函数库定义*/  
#include<unistd.h>     /*Unix 标准函数定义*/  
#include<sys/types.h>   
#include<sys/stat.h>     
#include<fcntl.h>      /*文件控制定义*/  
#include<termios.h>    /*PPSIX 终端控制定义*/  
#include<errno.h>      /*错误号定义*/  
#include<string.h>  


//串口使用的宏定义  
#define FALSE  -1  
#define TRUE   0  


void serial_setup(int fd,struct termios *options);
int serial_send(int fd,unsigned char sendBuff[],int length);
int serial_recv(int fd,unsigned char readBuff[],int length);

#endif