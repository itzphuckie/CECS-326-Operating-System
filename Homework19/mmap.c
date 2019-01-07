#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>


int main(){
    int fd;
    int position;
    char newLetter;
    char *filePtr;
    struct stat st;
    stat("mmap.txt",&st);
    // Open the text file
    fd = open("mmap.txt",O_RDWR);
    int size = st.st_size;
    // Memory maps the file 
    filePtr = mmap(0,size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    
    // Repeat 3 times 
    for(int i = 0;i<3;i++){
        printf("\nWhich position in the file do you like to change (0 - %d): ",size-1);
        scanf("%d",&position);
        if(position<0 || position>=size){
            printf("That is position is outside of the range of the file");
        }
        else{
            printf("\nWhat is the new letter for that position: ");
            scanf(" %c",&newLetter);
            filePtr[position] = newLetter;
        }
}
   // Un-mapping 
    munmap(filePtr,size);
    close(fd);
}
