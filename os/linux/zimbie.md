# A way to create zombie process & init process cannot recycle

```
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void thread_run(void){
  printf("begin thread...\n");
  sleep(1000);
  printf("end thread...\n");
}

int main(int argc, char * argv[]){
  pthread_t tid;
  int ret;
  daemon(0,0);
  printf("process begin...\n");
  ret = pthread_create(&tid, NULL, (void *)thread_run, NULL);
  if(ret != 0){
    printf("pthread error \n");
    exit(1);
  }
  sleep(10);
  printf("main thread ends\n");
  pthread_exit(0);
  printf("never exec\n");
}
```

While the main thread is quited, this process became a zombie process, because other thread is still running. 
