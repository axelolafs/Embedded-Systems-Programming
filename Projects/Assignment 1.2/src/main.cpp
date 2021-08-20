#include <stdint.h>

int main(){

  int* arr = new int[1000];
  
  // for (int i = 0; i < 1000; i++){
  //   arr[i] = 0;
  // }
  delete arr;
  return 0;
}