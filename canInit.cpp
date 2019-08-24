#include "canInit.h"
#include "serialSend.h"

void InitCanBus(int fd)
{
	bool isBaudRateSet = false;
	bool isTransferSet = false;

	//设置波特率参数
	unsigned char setup_baudrate_send[8];
	setup_baudrate_send[0]=0x66;
	setup_baudrate_send[1]=0xCC;
	setup_baudrate_send[2]=0x00;
	setup_baudrate_send[3]=0x04;
	setup_baudrate_send[4]=0x12;
	setup_baudrate_send[5]=0x01;
	setup_baudrate_send[6]=0x32;
	setup_baudrate_send[7]=0x49;


	unsigned char setup_baudrate_recv[7];
	for(int i=0;i<7;i++)
	{
		setup_baudrate_recv[i] = 1;
	}


	//设置透传参数
	unsigned char setup_transfer_send[13];
	setup_transfer_send[0]=0x66;
	setup_transfer_send[1]=0xCC;
	setup_transfer_send[2]=0x00;
	setup_transfer_send[3]=0x09;
	setup_transfer_send[4]=0x16;
	setup_transfer_send[5]=0x02;
	setup_transfer_send[6]=0x18;
	setup_transfer_send[7]=0xFF;
	setup_transfer_send[8]=0x15;
	setup_transfer_send[9]=0x07;
	setup_transfer_send[10]=0x08;
	setup_transfer_send[11]=0x01;
	setup_transfer_send[12]=0x5D;

	unsigned char setup_transfer_recv[7];
	for(int i=0;i<7;i++)
	{
		setup_baudrate_recv[i] = 1;
	}

	while(true)
	{
		if(isTransferSet) break;
		//设置波特率
		while(true)
		{
			serial_send(fd,setup_baudrate_send,8);
			usleep(500000);
			if(0 == serial_recv(fd,setup_baudrate_recv,7))
			{
				printf("0: %2x \n",setup_baudrate_recv[0]);
				printf("1: %2x \n",setup_baudrate_recv[1]);
				printf("2: %2x \n",setup_baudrate_recv[2]);
				printf("3: %2x \n",setup_baudrate_recv[3]);
				printf("4: %2x \n",setup_baudrate_recv[4]);
				printf("5: %2x \n",setup_baudrate_recv[5]);
				printf("6: %2x \n",setup_baudrate_recv[6]);

				if(0 == setup_baudrate_recv[5])
				{
					cout<<"baud rate setup success,resp is "<<endl;
					isBaudRateSet = true;
					break;
				}
				else
					cout<<"baud rate setup fail"<<endl;

			}
			else 
				cout<<"rec fail"<<endl;
		}
		
		if(isBaudRateSet)
		{
			//设置透传参数
			while(true)
			{
				serial_send(fd,setup_transfer_send,13);
				usleep(500000);
				if(0 == serial_recv(fd,setup_transfer_recv,7))
				{
					printf("0: %2x \n",setup_transfer_recv[0]);
					printf("1: %2x \n",setup_transfer_recv[1]);
					printf("2: %2x \n",setup_transfer_recv[2]);
					printf("3: %2x \n",setup_transfer_recv[3]);
					printf("4: %2x \n",setup_transfer_recv[4]);
					printf("5: %2x \n",setup_transfer_recv[5]);
					printf("6: %2x \n",setup_transfer_recv[6]);

					if(0 == setup_transfer_recv[5])
					{
						cout<<"tranfer param setup success!!!"<<endl;
						isTransferSet = true;
						break;
					}
					else
						cout<<"transfer param setup fail"<<endl;
	
				}
				else 
					cout<<"rec fail"<<endl;
			}
		}
	
	}   

}
