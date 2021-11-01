#include<iostream>
#include<unistd.h>

int main(){
    int i = 0;
    char buffer[10];
    while(true){
        i++;
        sprintf(buffer, "%d\n", i);
        std::cout << buffer;
        sleep(1);
    }
    return 0;
}