#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include "cmos_rtc.h"

#define SUCCESS 0
#define FAILURE -1

#define DEVICE_FILE_NAME "/dev/rtcDevice"

rtc_t rdbuff;
rtc_t wrbuff;

int main(void)
{
  int fd,retval;
  
  fd = open(DEVICE_FILE_NAME,O_RDWR);
  if(fd < 0)
  {
    perror("Open Failed : ");
    return FAILURE;
  }
  printf("File Open Success\n");
  getchar();
  
  retval = read(fd, &rdbuff, sizeof(rdbuff));
  if(retval < 0)
  {
    perror("Read Failed : ");
    return FAILURE;
  }
  printf("File Read Success\n");

  printf("%02x:%02x:%02x, %02x/%02x/%02x\n", rdbuff.hour, rdbuff.minute, 
    rdbuff.second, rdbuff.day, rdbuff.month, rdbuff.year);
  getchar();
/*
  wrbuff.second = 0x01;
  wrbuff.minute = 0x01;
  wrbuff.hour   = 0x01;
  wrbuff.day    = 0x01;
  wrbuff.month  = 0x01;
  wrbuff.year   = 0x01;

  retval = write(fd, &wrbuff, sizeof(wrbuff));
  if(retval < 0)
  {
    perror("Write Failed : ");
    return FAILURE;
  }
  printf("File Write Success\n");
  getchar();
*/
  retval = close(fd);
  if(retval < 0)
  {
    perror("Close Failed : ");
    return FAILURE;
  }
  printf("File Close Success\n");
  return SUCCESS;
}
