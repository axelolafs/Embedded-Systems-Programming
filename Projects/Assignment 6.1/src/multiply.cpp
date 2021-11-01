#include <iostream>
#include <unistd.h>

int main(int argc, char *argv[]){
    char buffer[10];
    int i;
    int c;
    if (argc == 2){
        c = atoi(argv[1]);
    }
    else{
        c = 1;
    }

    while(true){
        std::cin >> buffer;
        i = atoi(buffer);
        i *= c;
        sprintf(buffer, "%d\n", i);
        std::cout << buffer;
    }

    return 0;
}