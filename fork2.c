//fork2.c: creación de procesos (hilos) con fork y archivos
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/times.h>
#include <sys/stat.h>
#include <sys/wait.h>

// Write a NUL terminated string to an fd.
void writestr(int fd, char *buf)
 {
   int r = write(fd, buf, strlen(buf));
   if (r == -1)
    perror(buf);
 }

// Simple busy-wait loop to throw off our timing.
 void busywait(void)
 {
 clock_t t1 = times(NULL);
 while (times(NULL) - t1 < 2);
 }

 int main(int argc, char *argv[])
 {
 int fd = open("thefile.txt", 
  O_CREAT | O_TRUNC | O_RDWR,
 S_IRWXU | S_IRWXG | S_IRWXO);

 assert(fd != -1);

 writestr(fd, "This is the parent.\n");
 
 pid_t pid = fork();
 
 // Both parent and child do a busywait,  // which should throw off our timing.
 //busywait();

 if (pid == 0) {
 // Child process
  printf("El hijo escribe a archivo\n");	
  writestr(fd, "Child write\n");
 }
 else {
 // parent process writes one line and  // waits for the child
  printf("El padre escribe y espera...\n");	
  writestr(fd, "Hi it's me. I'm back.\n");

  int status;
  waitpid(pid, &status, 0);
 }
 close(fd);
 return 0;
 }
 

