int verbosity;
int getbaud(int fd); 
int readport(int fd, unsigned char *result);
int writeport(int fd, unsigned char *chars, int numBytes);
int initport(int fd);
int setupport(char* fdpath);


