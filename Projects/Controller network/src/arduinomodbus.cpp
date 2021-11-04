/* Arduino Serial Command Processor */
#include <Arduino.h>

uint16_t ModRTU_CRC(uint8_t buf[], int len);
void ModRTU_write(char *buf);
void ModRTU_read(char *buf);
void printBuffer(char buf[], int len);

const unsigned char ADDR = 0x01;
const unsigned char READ_FUNC = 0x03;
const unsigned char WRITE_FUNC = 0x06;
uint8_t* reg;

void setup()
{ // called once on start up
    // A baud rate of 115200 (8-bit with No parity and 1 stop bit)
    Serial.begin(115200, SERIAL_8N1);
}


void loop()
{ // loops forever
    const int len = 8;
    char buf[len];
    char msg[len-2];
    uint16_t crc;
    uint16_t check;
    if (Serial.available() > 0){
        Serial.readBytes(buf, len);
        // printBuffer(buf, len);
        /*
        for(int i = 0; i < len-2; i++){
            msg[i] = buf[i];
        }
        check = (buf[6] << 8) + buf[7];
        crc = ModRTU_CRC(msg, len-2);
        */
        if(true){
            if (buf[0] == ADDR){
                switch (buf[1]){
                    case READ_FUNC:
                        ModRTU_read(buf);
                        break;
                    case WRITE_FUNC:
                        ModRTU_write(buf);
                        break;
                    default:
                        break;
                }
            }
        }
    } 
}

uint16_t ModRTU_CRC(uint8_t buf[], int len){
    uint16_t crc=0xFFFF;

    for(int pos = 0; pos < len; pos++){
        crc ^= (uint16_t)buf[pos];      //XOR byte into least sig. byte of crc
        for(int i = 8; i != 0; i--){    //Loop over each bit
            if((crc&0x0001)!=0){        //If the LSB is set
                crc >>= 1;              //Shift right and XOR 0xA001
                crc ^= 0xA001;
            }
            else                        //Else LSB is not set
                crc >>= 1;              //Just shift right
            }
        }                               //Note, this number has low and high bytes swapped, souse it accordingly(or swap bytes)
    return crc;
}

void ModRTU_write(char *buf){
    // uint8_t msbyte = atoi(buf[4]);
    // uint8_t lsbyte = atoi(buf[5]);
    uint8_t regIndex = buf[3];
    // reg[int()] = 255;
    reg[regIndex] = (buf[4] << 8) + buf[5];
    printBuffer(buf, 8);
    // for(int i = 0; i < 8; i++){
        // Serial.print(buf[i]);
    // }
}

void ModRTU_read(char *buf){
    uint8_t regIndex = buf[3];
    Serial.print(buf[0]);
    Serial.print(buf[1]);
    Serial.print(buf[5]);
    Serial.print(char((reg[regIndex]) >> 8));
    Serial.print(char(reg[regIndex]));

    printBuffer(buf, 8);
}

void printBuffer(char buf[], int len){
    for (int i = 0; i < len; i++){
        Serial.print(buf[i]);
    }
}