/* 
 * 复现ptrace造成僵尸进程的代码
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <errno.h>
#include <string.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define STACK_SIZE 65536

int child1(void* arg);
int child2(void* arg);

int main(int argc, char **argv)
{
  int child_pid;
  char* child_stack = malloc(STACK_SIZE);
  char* stack_top = child_stack + STACK_SIZE;
  char command[256];
  char line[256];
  int fd;
  int idx  = 0;
  char c;
  child_pid = clone(&child1, stack_top, CLONE_NEWPID, NULL);
  if (child_pid == -1) {
    printf("parent: clone failed: %s\n", strerror(errno));
    return EXIT_FAILURE;
  }
  printf("parent: child1_pid: %d\n", child_pid);

  sleep(1);
  printf("child state, if it's D (disk sleep), the child process is hung\n");
  sprintf(command, "cat /proc/%d/status | grep State:", child_pid);
  system(command);
  memset(command, 0, 256);
  sprintf(command, "/proc/%d/status", child_pid);
  fd = open(command, O_RDONLY);
  if (fd <= 0 ){
    printf("cannot open file /proc/%d/status with error %d\n", child_pid, errno);
  }

  do{
    idx = 0;
    for (;;) {
      read(fd, &c, 1);
      line[idx++] = c;
      if (c == '\n') {
        break;
      }
    }
    line[idx] = 0;
    if (line[0] == 'S') {
      printf("%s\n", line);
      break;
    }
  }while(1);
  printf("%c\n", line[8]);
  if (line[7] == 'S') {

    return 0;
  }

  sleep(3600);
  return EXIT_SUCCESS;
}

int child1(void* arg)
{
  int flags = CLONE_FILES | CLONE_FS | CLONE_VM | CLONE_SIGHAND | CLONE_THREAD;
  char* child_stack = malloc(STACK_SIZE);
  char* stack_top = child_stack + STACK_SIZE;
  long ret;

  ret = ptrace(PTRACE_TRACEME, 0, NULL, NULL);
  if (ret == -1) {
    printf("child1: ptrace failed: %s\n", strerror(errno));
    return EXIT_FAILURE;
  }

  ret = clone(&child2, stack_top, flags, NULL);
  if (ret == -1) {
    printf("child1: clone failed: %s\n", strerror(errno));
    return EXIT_FAILURE;
  }
  printf("child1: child2 pid: %ld\n", ret);

  sleep(1);
  printf("child1: end\n");
  return EXIT_SUCCESS;
}

int child2(void* arg)
{
  long ret = ptrace(PTRACE_TRACEME, 0, NULL, NULL);
  if (ret == -1) {
    printf("child2: ptrace failed: %s\n", strerror(errno));
    return EXIT_FAILURE;
  }

  printf("child2: end\n");
  return EXIT_SUCCESS;
}

