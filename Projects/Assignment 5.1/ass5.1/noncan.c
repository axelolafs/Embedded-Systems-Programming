
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<termios.h>   // using the termios.h library
#include<pthread.h>

struct termios options;       // the termios structure is vital
int file, count;
char c;
unsigned char recv;

void *write_thread(void *param){
    while(1){
        usleep(100000);
        c = getchar();
        if ((count = write(file, &c, 1))<0){         // transmit
            perror("Failed to write to the output\n");
            // return -1;
        }
    }
}

void *read_thread(void *param){
    while(1){
        usleep(100000);
        if ((read(file, &recv, 1))<0){   //receive data
            perror("Failed to read from the input\n");
            // return -1;
        }
        printf("%c", recv);
    }
}

int main(void){
   
   if ((file = open("/dev/ttyS0", O_RDWR | O_NOCTTY))<0){
      perror("UART: Failed to open the file.\n");
      return -1;
   }

   struct termios stdOpt, initStdOpt;
   tcgetattr(file, &options);    // sets the parameters for the file
   tcgetattr(STDIN_FILENO, &initStdOpt);
   // Set up the communications options:
   // 115200 baud, 8-bit, enable receiver, no modem control lines
   struct termios initOptions = options;
   stdOpt = initStdOpt;
   stdOpt.c_lflag &= ~ICANON;
   options.c_cflag |= B57600 | CS8 | CREAD | CLOCAL;
   options.c_iflag |= IGNPAR | ICRNL;   // ignore partity errors
   options.c_cflag |= CSTOPB | PARENB; // 2 stop bits and enable parity check
   options.c_lflag &= ~(ICANON);         // non canonical mode
   options.c_cc[VTIME] = 0;            // blocking
   options.c_cc[VMIN] = 1;             // wait for 1 byte
   tcflush(file, TCIFLUSH);            // discard file information
   tcsetattr(file, TCSANOW, &options); // changes occur immmediately
   tcsetattr(STDIN_FILENO, TCSANOW, &stdOpt);

    pthread_t write, read;
    pthread_create(&write, NULL, write_thread, NULL);
    pthread_create(&read, NULL, read_thread, NULL);
    pthread_join(write, NULL);
    pthread_join(read, NULL);

    tcsetattr(file, TCSANOW, &initOptions);
    tcsetattr(STDIN_FILENO, TCSANOW, &initStdOpt);
    close(file);
   return 0;
}


