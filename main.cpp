#include "mbed.h"
#include "ISL29125.h"
#include <chrono>

#define BUFF_LENGTH  64

BufferedSerial pc(USBTX, USBRX, 115200);
int length;
char buffer[BUFF_LENGTH] = {0};

ISL29125 rgb(PB_9,PB_8);
uint16_t GRBdata[3];
bool data_present;


// main() runs in its own thread in the OS
int main()
{
    length = snprintf(buffer, BUFF_LENGTH, "\r\nISL29125 Test Starting...");
    pc.write(buffer, length);

    length = snprintf(buffer, BUFF_LENGTH, "\r\n[Mode] RGB mode: %02X\r\n", rgb.RGBmode());
    pc.write(buffer, length);
    while (true) {
        data_present = rgb.Read(ISL29125_RGB, GRBdata);
        if(data_present)
        {
            length = snprintf(buffer, BUFF_LENGTH, "\r\n[Data] RGB: %d-%d-%d\r\n", GRBdata[1], GRBdata[0], GRBdata[2]);
            pc.write(buffer, length);
        }
        ThisThread::sleep_for(chrono::seconds(1));
    }
}

