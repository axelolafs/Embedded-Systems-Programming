#include<iostream>
#include<unistd.h>

int main(){
    int i = 0;
    char buffer[10];
    while(true){
        sleep(1);
        i++;
        sprintf(buffer, "%d\n", i);
        std::cout << buffer;
        std::cout.flush();
    }
    return 0;
}