#include <stdio.h>
#include <time.h>
#include <wiringPi.h>
#include <stdint.h>
#include <wiringPiI2C.h>
#include <math.h>

#define Interrupt_enable 0x01
#define Mode_configuration 0x06
#define SPO2_configuration 0x07
#define Led_configuration 0x09

int max301;
uint16_t a, b;
// int16_t read_sensor(unsigned char sensor)
// {
//     uint16_t high, low, data;
//     high = wiringPiI2CReadReg8(mpu,sensor);
//     low = wiringPiI2CReadReg8(mpu,sensor+1);
//     data = (high<<8) | low;
//     return data;
// }

void Init_30100()
{
    //Setup Interrupt Enable // khoi? xai` cung~ dc
    wiringPiI2CWriteReg8(max301,Interrupt_enable,0xF0);
    //Setup Mode Configuration
    wiringPiI2CWriteReg8(max301,Mode_configuration,0x0B);
    //Setup SPO2_Configuration
    wiringPiI2CWriteReg8(max301,SPO2_configuration,0x17);
    //Setup Led_Configuration
    wiringPiI2CWriteReg8(max301,Led_configuration,0x67);
}

int main(void)
{
    //Setup giao tiep I2C
    max301 = wiringPiI2CSetup(0x57);
    Init_30100();

    while(1)
    {
        
        //Read ADC
        // float data1 = wiringPiI2CReadReg8(max301,0x16);
        // float data2 = wiringPiI2CReadReg8(max301,0x17);
        // float data = data1 + data2*0.0625;
        // printf("Temp: %0.2f\n",data);
        // wiringPiI2CWriteReg8(max301,Mode_configuration,0x0B);

        //Read HR & SPO2
        uint16_t IR = wiringPiI2CReadReg16(max301,0x05);
        uint16_t RED = wiringPiI2CReadReg16(max301,0x05);
        //uint8_t c = wiringPiI2CReadReg8(max301,0x04);
        printf("SPO2: %d\n",IR);
        printf("HR: %d\n",RED);
        delay(500);
    }
    return 0;

}
