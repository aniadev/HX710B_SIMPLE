#include "HX710B_SIMPLE.h"

HX710B_SIMPLE::HX710B_SIMPLE(uint8_t sck_pin , uint8_t do_pin, uint8_t mode)
{
    this->SCK_pin = sck_pin;
    this->DO_pin = do_pin;
    this->mode = mode;
}

HX710B_SIMPLE::~HX710B_SIMPLE(){}

uint8_t HX710B_SIMPLE::init(void)
{

    if (this->SCK_pin == UNDEF_PIN ||
        this->DO_pin == UNDEF_PIN )
        return HX710B_ERROR;
    pinMode(this->DO_pin, INPUT_PULLUP);    digitalWrite(this->DO_pin, HIGH);
    pinMode(this->SCK_pin, OUTPUT);         digitalWrite(this->SCK_pin, HIGH);
    uint32_t _test = this->read();
    if (_test){
        return HX710B_SUCCESS;
    }
    digitalWrite(this->SCK_pin, LOW);
    delay(1);
}

void HX710B_SIMPLE::setReference(float _vref = 5.0) {
    this->voltageRef = _vref;
}

uint8_t HX710B_SIMPLE::setMode(uint8_t mode_)
{
    if (mode_ == HX710B_DIFF1 || mode_ == HX710B_TEMP || mode_ == HX710B_DIFF2) {
        this->mode = mode_;
        return HX710B_SUCCESS;
    } else {
        return HX710B_ERROR;
    }
    
}

uint32_t HX710B_SIMPLE::read()
{
    // exit sleep mode
    digitalWrite(this->SCK_pin, LOW);
    uint8_t i = 0;
    uint32_t raw = 0;
    for (i = 0; i < this->mode; i++)
    {
        delayMicroseconds(1);
        digitalWrite(this->SCK_pin, HIGH);
        delayMicroseconds(1);
        digitalWrite(this->SCK_pin, LOW);
        if (i < 24)
        {
            raw = raw << 1;
            if (digitalRead(this->DO_pin))
                raw = raw | 0x01;
        }
    }
    return raw;
}

float HX710B_SIMPLE::readVoltage() {
    uint32_t rawData = this->read();
    float voltage = double(rawData) / double(0xffffff) * this->voltageRef;
    return voltage;
}
