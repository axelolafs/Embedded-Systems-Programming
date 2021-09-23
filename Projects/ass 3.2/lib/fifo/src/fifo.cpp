#include "fifo.h"

Fifo::Fifo(){

}

int Fifo::get(){

    int front = buffer[0];
    tail--;
    for (int i = 0; i < tail - head; i++){
        buffer[i] = buffer[i + 1];
    }
    

    return front;
}

void Fifo::put(int item){
    int pos = tail - head;
    tail++;
    buffer[pos] = item;
}

bool Fifo::is_empty(){
    return head == tail;
}

bool Fifo::is_full(){
    return tail >= head + FIFO_SIZE - 1;
}

void Fifo::reset(){
    tail = head;
}