#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
int main (int argc, char* argv[]) {
 // decaring variables 
  int src_fd, dest_fd;
  char filebuf[256]; /* a small buffer used to copy the file */
  ssize_t readSizeSrc, readSizeDest;

  src_fd = open(argv[1],O_RDONLY);
  // cathing
  if(src_fd == -1){
	printf("The source file is not opening !!!");
	return 0;
	}
  // open dest
  dest_fd = open(argv[2],O_WRONLY | O_CREAT, sizeof(filebuf));
  if(dest_fd == -1){
	printf("The destination file already exists!!!");
	return 0;
	}
  while (( readSizeSrc = read(src_fd, filebuf, sizeof(filebuf)-1)) > 0)
  {
    // I turn it into a string only because I'm using printf;
    // making a copy using "write" would not need this.
    readSizeDest = write(dest_fd, filebuf, (ssize_t)readSizeSrc); 
   // filebuf[readSize] = '\0';
   // printf("%s",filebuf);
    if(readSizeDest != readSizeSrc){
	printf("Could not copy from the source file to the destination file");
	return 0;
    }
  }
  close(src_fd);
  close(dest_fd);
  return 0;
}
