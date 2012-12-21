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

#define BUFLEN		16  //the length the buffer should be
#define TRUE 1
#define false 0


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
  /*
  i=0;

    while(1) {
  for (i=0; i < strlen(text); i++) {
  memset(output, ' ', BUFLEN);
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
    }*/
  
    int times = strlen(text) / displaylen;		//The number of complete 16 char blocks
    int llength = strlen(text) % displaylen;	//The leftover number of charecters
    int full16 = strlen(text)/ displaylen * displaylen; 	//The char position after the complete 16 char blocks are finished
    printf("Times: %d llength: %d Full16: %d STRLEN: %d\n", times, llength, full16, strlen(text));
	
    while (times > 0)
    {
    int s = (strlen(text) / displaylen - times) * displaylen;
    printf("Output: [%s] pos: %d\n", substring(text,s,displaylen), s);
    writeport(fd, showmode1, 4);
    writeport(fd, substring(text,s,displaylen), 16);
    times--;
    sleep(2);
    }
    
  
    if (llength > 0) {
    char ss[17]; 
 
    printf("Leftover: %s\n",substring(text, full16, strlen(text) - full16));
    strcpy(ss,substring(text, full16, strlen(text) - full16)); 
    for (i = 0; i < 16 - llength; i++)
    {
    strcat(ss, " ");
    }
    printf("Output: [%s] pos: %d\n", ss, full16);
    writeport(fd, showmode1, 4);
    writeport(fd, ss, 16);
  
    sleep(2);
    }



  fcntl(fd, F_SETFL, 0);

  
  close(fd);
  return 0;
}
