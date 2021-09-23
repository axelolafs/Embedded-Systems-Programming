#include "fifo.h"

Fifo::Fifo(){

}

int Fifo::get(){

    int front = *head;
    head++;
    bufferLength--;
    return front;
}

void Fifo::put(int item){
    *tail = item;
    tail++;
    if (tail == &buffer[0] + FIFO_SIZE){
        tail = &buffer[0];
    }
    if (bufferLength < FIFO_SIZE){
        bufferLength++;
    }
}

bool Fifo::is_empty(){
    return bufferLength == 0;
}

bool Fifo::is_full(){
    return bufferLength >= FIFO_SIZE;
}

void Fifo::reset(){
    tail = head;
    bufferLength = 0;
}