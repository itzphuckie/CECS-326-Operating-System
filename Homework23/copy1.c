#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
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
  //dest_fd = open(argv[2],O_WRONLY | O_CREAT, sizeof(filebuf));
  if(access(argv[2], F_OK) != -1){
	printf("The destination file already exists!!!");
	return 0;
  }else{
  //Open dest file
		dest_fd = open(argv[2], O_CREAT|O_WRONLY, sizeof(filebuf));
  }
  
  // Another check to make sure these open ^ aren't failling
  if(dest_fd < 0){
	printf("The destination file couldn't be opended\n");
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
  //Computing  md5 hash	
  execlp("md5sum", "md5sum", argv[1], argv[2],  NULL);
  return 0;
}
