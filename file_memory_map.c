#include <fcntl.h>    // open
#include <stdio.h>    // printf
#include <sys/mman.h> // mmap, munmap
#include <sys/stat.h> // fstat
#include <unistd.h>   // close

int main(int argc, char **argv)
{char filename[256];
 if (argc>1)
    sprintf(filename,argv[1]);
 else sprintf(filename,"file.bin");
 int fd;
 struct stat st;
 unsigned char *addr;
 fd = open(filename, O_RDWR);
 fstat(fd, &st); // file size st.st_size
 addr=mmap(NULL,st.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
 printf("content: 0x%02x 0x%02x\n", addr[0],addr[1]);
 munmap(addr, st.st_size);close(fd);
}

