#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <getopt.h>
#include "serprt.h"
#include "helper.h"
#include "common.h"




int displaylen;
char *dev;
int verbosity;
char text[100];

int fd;


void display_usage( void ) {
  puts( "LED Scroll - Scrolls a message a sinlge time across a message board");
  puts( "Options:" );
  puts( " -d, --dev         Path to the USB dev for the board, default: /dev/ttyUSB0" );
  puts( " -l, --displaylen  The number of charecters in the display, default: 16");
  puts( " -v, --verbose     Will print out lots of info, default: off");
  puts( " -vv               Extra bonus info");
}

int main(int argc, char **argv) {

  startup( argc, argv);


  unsigned char showmode1[4] = { -2, 71, 1, 1}; 
  unsigned char sResult[17];
  char output[BUFLEN+1];
  int i,copyn;

  output[BUFLEN] = '\0';


    while(1) {
  for (i=0; i < strlen(text); i++) {
    memset(output, ' ', displaylen);
  if (strlen(text)-i < displaylen) {
    copyn = strlen(text) - i;

    strncpy(output, text+i, copyn);
    strncpy(output+copyn+1, text, displaylen-copyn-1);	  
  }else{

    copyn = displaylen;
    strncpy(output, text+i, copyn);
  }

  if (verbosity) {
    printf("output: [%s]\n",output);
  }
  writeport(fd, showmode1, 4);
  writeport(fd, output, 16);

  msleep(250);
    }
  }

  fcntl(fd, F_SETFL, 0);
  
  close(fd);
  return 0;
}
