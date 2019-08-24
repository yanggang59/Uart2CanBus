#include <fstream>
#include <string>
#include <sys/time.h>

//串口发送模块
#include "serialSend.h"

//can发送模块初始化
#include "canInit.h"




//保存的照片张数
int g_count;


//串口发送的消息
unsigned char send_buf[8];




int main(int argc, char* argv[])
{
	/*串口相关的设置*/
	int fd;                            //文件描述符
	int err;                           //返回调用函数的状态
	int len;

	struct termios options;

	/* 打开串口，返回文件描述符，在此之前必须先给串口写权限，或者直接将用户加入diaout用户组，否则会报错  */
	fd = open( "/dev/ttyUSB0", O_RDWR|O_NOCTTY|O_NDELAY);

	if(fd == -1)
	{
		perror("uart open failed!");
		return -1;
	}

	g_count = 0;

	serial_setup(fd,&options);

	InitCanBus(fd);
	
   
	while(true)
	{
		send_buf[0] = g_count%256;
		send_buf[1] = g_count/256;
		send_buf[2] = g_count%256;
		send_buf[3] = g_count/256;
		send_buf[4] = 0;
		send_buf[5] = 0;
		send_buf[6] = 0;
		send_buf[7] = 0;

		//透传模式下直接使用串口发送数据即可
		serial_send(fd,send_buf,8);

		//每隔1000ms发送一次
		sleep(1);

		g_count++;

		cout<<"------------------------------------"<<endl;
		cout<<"------------------In while----------------------- "<<endl;  
		cout<<"g_count is "<<g_count<<endl;     
	}


	return 0;
}
