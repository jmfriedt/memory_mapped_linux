#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/mman.h> // mmap
#include <unistd.h>   // sysconf 

#define BUFFER_SIZE 1024

int main(int argc, char **argv)
{int fd;
 long page_size;
 char *addr;
 char buf[BUFFER_SIZE];
 uintptr_t paddr;
 if (argc < 2) {printf("Usage: %s <mmap_file>\n", argv[0]);return EXIT_FAILURE;}
 page_size = sysconf(_SC_PAGE_SIZE);
 fd = open(argv[1], O_RDWR | O_SYNC); if (fd < 0) perror("open");
 addr=mmap(NULL, page_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
 if (addr==MAP_FAILED) perror("mmap");
 printf("%s",addr); // print the content of memory
 if (munmap(addr, page_size)) perror("munmap");
 close(fd);
 return EXIT_SUCCESS;
}
