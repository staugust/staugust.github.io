/*
 * This code is used to mmap a file, and read fist 64 bytes. 
 */


#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <chrono>
#include <iostream>
#include <cstring>
#include <cerrno>

int main(int argc, char * argv[]){
  if(argc < 2){
    std::cout << "need dev file path"<<std::endl;
    return -1;
  }
  int f = open(argv[1], O_RDWR | O_SYNC);
  if (f == -1){
    std::cout << "cannot open " << argv[1]<<std::endl;
  }
  int res;
  int * p =  (int *)mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_SHARED | MAP_NORESERVE, f, 0);
  if (p != (int *)-1){
    for(int i = 0; i < 16; i++){
      printf("%x ", *p);
      if ((i + 1) % 4 == 0){
        printf("\n");
      }
      p++;
    } 
    goto cleanup;
  }
  std::cout << "cannot mmap " << argv[1] << std::endl;
  std::cout <<" now trying to read "<< std::endl;
  p = (int *)calloc(16, sizeof(int));
  res = read(f, p, 16*sizeof(int));
  if (res != 64){
    return errno;
  }
  for(int i = 0;i < 16; i++){
    printf("%x ", *p);
    if( (i+1)%4==0){
      printf("\n");
    }
  }
  
  
cleanup:
  close(f);
  return 0;
}


