#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main () {
 
  //for(int i =0; i<5; i++){
  int result;
  int fd_out, fd_in;
  
  mkfifo("fifo.pipe",0600);
  fd_in = open("fifo.pipe",O_RDONLY);

  mkfifo("fifor.pipe",0600);
  fd_out = open("fifor.pipe",O_WRONLY);
  
  fflush(stdout);
//ans = open("fifo.pipe",O_WRONLY);
  for(int i = 0; i<5; i++){
  int multiplier;
  int multiplicand;
  int answer;
  // Reading the multipliAnd from the pipe
  read(fd_in, &multiplicand, sizeof(multiplicand));
  // Reading the multiplier from the pipe
  read(fd_in, &multiplier, sizeof(multiplier));
  // Method to multiply
  printf("Multiplicand is: %d\n", multiplicand);
  printf("Multiplier is %d\n", multiplier);

  answer = multiplicand * multiplier;

  printf("Answer is: %d\n\n", answer);
  // Write the result to the "result" pipe
  write(fd_out,&answer,sizeof(answer));
  //read(fd,buf,sizeof(buf));
  }
  return 0;

};
