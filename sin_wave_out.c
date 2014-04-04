#include <stdlib.h>  
#include <math.h>  
#include <fcntl.h>  
  
  
int main (int argc, const char* argv[])  
{  
          unsigned int num_samples = 1000;  
          unsigned char buf[4*num_samples];  
          unsigned int i, j;  
          unsigned short I, Q;  
          int fd;  
  
          for (i = 0; i < num_samples; i++)  
          {  
                    I = cos(2 * M_PI * i / 10) * 4000 + (1 << 15);   
                    Q = sin(2 * M_PI * i / 10) * 4000 + (1 << 15);  
  
                    j = i * 4;  
                    buf[j+0] = I & 0xff;  
                    buf[j+1] = I >> 8;  
                    buf[j+2] = Q & 0xff;  
                    buf[j+3] = Q >> 8;  
          }  
  
          fd = open("/dev/iio:device5", O_WRONLY);  
          if (fd < 0)  
                    exit(1);  
  
          write(fd, buf, 4 * num_samples);  
          close(fd);  
  
          return 0;  
}  