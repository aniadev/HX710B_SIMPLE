#ifndef _HX710B_SIMPLE_H_
#define _HX710B_SIMPLE_H_

#include "Arduino.h"
#include "stdlib.h"
#include "stdio.h"


#define HX710B_DIFF1    25      // data rate 10Hz
#define HX710B_TEMP     26      // data rate 40Hz
#define HX710B_DIFF2    27      // data rate 40Hz

#define HX710B_DEFAULT_MODE     HX710B_DIFF2


#define UNDEF_PIN      255
/* Status Reply */

#define HX710B_SUCCESS      0x01
#define HX710B_ERROR        0x00
#define HX710B_BUSY         0x02
#define HX710B_TIMEOUT      0x03

class HX710B_SIMPLE{

    private :
        uint8_t SCK_pin = UNDEF_PIN,
                DO_pin  = UNDEF_PIN;
        uint8_t mode;
        float voltageRef = 5.0;
        uint32_t calib = 0x00;
    public :

        HX710B_SIMPLE(uint8_t sck_pin = UNDEF_PIN, uint8_t do_pin = UNDEF_PIN, uint8_t mode = HX710B_DEFAULT_MODE);
        ~HX710B_SIMPLE();
        uint8_t init(void);
        void setReference(float _vref = 5.0);
        uint8_t setMode(uint8_t mode_);
        uint32_t read();
        float readVoltage();
};

#endif