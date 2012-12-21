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
#include "common.h"


static const char *optString = "dl:v::";

static const struct option longOpts[] = {
  { "dev", required_argument, NULL, 'd' },
  { "displaylen", required_argument, NULL, 'l' },
  { "verbose", optional_argument, NULL, 'v' }
};



void startup(int argc, char **argv) {
int opt=0;
int longIndex=0;
 int i;


verbosity=0;
displaylen=16;
dev="/dev/ttyUSB0";

  opt = getopt_long( argc, argv, optString, longOpts, &longIndex);
  while (opt != -1) {
    switch ( opt ) {
    case 'd':
      dev = optarg;
      break;
    case 'l':
      displaylen = *optarg;
      break;
    case 'v':
      verbosity++;
      break;
    case '?':
      display_usage();
      break;
    };
    opt = getopt_long( argc, argv, optString, longOpts, &longIndex);
  }

	
  if (optind < argc) {

    strcpy(text, argv[optind]);
  } else {
    printf("Enter text to display: ");
    fgets(text, sizeof(text), stdin);
  }	  

  //If the text is less than the display len, fill it with spaces
  if (strlen(text) < displaylen) {
 
    for (i = strlen(text); i < displaylen; i++) {
      text[i] = ' ';
    }
    text[displaylen + 1] = '\0'; // end the string
  }

  if (verbosity) {
    printf("The text is: %s Length: %lu\n",text,strlen(text));
  }

  fd = setupport(dev);  
  initport(fd);
  if (verbosity) {
    printf("baud=%d\n", getbaud(fd));
  }



}


char *substring(char *string, int position, int length) 
{
   char *pointer;
   int c;
 
   pointer = malloc(length+1);
 
   if (pointer == NULL)
   {
      printf("Unable to allocate memory.\n");
      exit(EXIT_FAILURE);
   }
 
   for (c = 0 ; c < position ; c++) 
      string++; 
 
   for (c = 0 ; c < length ; c++)
   {
      *(pointer+c) = *string;      
      string++;   
   }
 
   *(pointer+c) = '\0';
 
   return pointer;
}


int __nsleep(const struct timespec *req, struct timespec *rem)
{
  struct timespec temp_rem;
  if(nanosleep(req,rem)==-1)
    __nsleep(rem,&temp_rem);
  else
    return 1;
}
int msleep(unsigned long milisec)
{
  struct timespec req={0},rem={0};
  time_t sec=(int)(milisec/1000);
  milisec=milisec-(sec*1000);
  req.tv_sec=sec;
  req.tv_nsec=milisec*1000000L;
  __nsleep(&req,&rem);
  return 1;
}

