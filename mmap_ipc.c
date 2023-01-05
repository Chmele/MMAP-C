#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/time.h>


int main() {
  char parent_message[1024000] = "hello";  
  char child_message[1024000] = "goodbye"; 
  void* shmem = mmap(NULL, 1024000, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

  memcpy(shmem, parent_message, sizeof(parent_message));

  int pid = fork();

  if (pid == 0) {
    struct timeval stop, start;
    gettimeofday(&start, NULL);
    memcpy(shmem, child_message, sizeof(child_message));
    gettimeofday(&stop, NULL);
    printf("\ntook %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec); 

  } else {
    printf("Parent read: %s\n", shmem);
    sleep(1);
    if (shmem == "goodbye"){
        printf("true");
    }
    printf("After 1s, parent read: %s\n", shmem);
  }
}