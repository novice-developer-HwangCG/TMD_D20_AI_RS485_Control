#ifndef RS485_H
#define RS485_H

int InitRS485();
void SendRS485(int fd, unsigned char *data, int size);
int ReceiveRS485(int fd, unsigned char *buffer, int size);
unsigned short CalculateCRC16(unsigned char *buf, int len);

#endif
