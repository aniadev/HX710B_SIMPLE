#define SCK 3
#define SDI 4 //DOUT on module
#include <HX710B_SIMPLE.h>
HX710B_SIMPLE airPressureSensor(SCK, SDI);

void setup() {
  airPressureSensor.init();
  delay(100);
  Serial.begin(9600);
}

void loop() {
  float voltage = airPressureSensor.readVoltage();
  uint32_t raw  = airPressureSensor.read();
  Serial.print("Raw: "); Serial.print(raw, DEC);
  Serial.print(", Voltage: "); Serial.print(voltage);
  Serial.println();
  delay(1000);
}
