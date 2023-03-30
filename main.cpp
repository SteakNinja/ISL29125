#include "mbed.h"
#include "ISL29125.h"
#include <chrono>

#define BUFF_LENGTH  64

BufferedSerial pc(USBTX, USBRX, 115200);
int length;
char buffer[BUFF_LENGTH] = {0};

ISL29125 rgb(PB_9,PB_8);                    //Main sensor object
uint16_t GRBdata[3];                        //Returned data holder
bool data_present;                          //Boolean data check


// main() runs in its own thread in the OS
int main()
{
    length = snprintf(buffer, BUFF_LENGTH, "\r\nISL29125 Test Starting...");                                                //Startup message
    pc.write(buffer, length);

    length = snprintf(buffer, BUFF_LENGTH, "\r\n[Mode] RGB mode: %02X\r\n", rgb.RGBmode());                                 //Print sensor mode (5 = GRB)
    pc.write(buffer, length);
    while (true) {
        data_present = rgb.Read(ISL29125_RGB, GRBdata);                                                                     //Read from sensor - returns true if data available
        if(data_present)                                                                                                    //If returned true, do something
        {
            length = snprintf(buffer, BUFF_LENGTH, "\r\n[Data] RGB: %d-%d-%d\r\n", GRBdata[1], GRBdata[0], GRBdata[2]);     //Print out returned data as RGB (from GRB)
            pc.write(buffer, length);
        }
        ThisThread::sleep_for(chrono::seconds(1));
    }
}

