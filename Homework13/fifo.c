#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main () {
  
  int fd_out, fd_in;
  int result;
  

  mkfifo("fifo.pipe",0600);
  fd_out = open("fifo.pipe",O_WRONLY);

  mkfifo("fifor.pipe",0600);
  fd_in = open("fifor.pipe", O_RDONLY);

  for(int i =0; i<5; i++){
  
  int multiplicand;
  int multiplier;
  int answer;
  printf("Multiplicand: ");
  scanf("%d", &multiplicand);// scan ithe user input into multiplicand

  //Take in the multiplier
  printf("Multiplier: ");
  // scan the user input into multiplier
  scanf("%d", &multiplier);

  //Write the multiplicand to the pipe - child
  write(fd_out, &multiplicand, sizeof(multiplicand));

  //Write the multiplier to the server pipe 
  write(fd_out, &multiplier, sizeof(multiplier));
  //Read back the answer from the other pipe (result)
  read(fd_in,&answer,sizeof(answer));
  //Display the result
  printf("Result: %d\n\n", answer);
 // write(fd,"Hello",6);
 // close(fd);
 } 
return 0;
  
};
