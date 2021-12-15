#include <Wire.h>
#include <HCSR04.h>

#define TrigPin 1
#define EchoPin 3
#define LED 4

UltraSonicDistanceSensor distanceSensor(TrigPin, EchoPin);

byte SlaveAddr = 0x27;
byte Addr;
byte REGS[] = {0,1};
byte RegIndx;
bool trig = false;

void setup()
{
    pinMode(LED, OUTPUT);
    Wire.begin(SlaveAddr);
    Wire.onReceive(receiveEvent);
    Wire.onRequest(sendEvent);
}

void loop()
{
    digitalWrite(LED, LOW);
    delay(200);
}

void receiveEvent()
{
    LEDBlink(1);
    while (Wire.available() > 0)
    {
        RegIndx = Wire.read();
    }
}

void LEDBlink(byte count)
{
    for (int i = 0; i < count; i++)
    {
        digitalWrite(LED, HIGH);
        delay(100);
        digitalWrite(LED, LOW);
        delay(100);
    }
}

void sendEvent()
{
    LEDBlink(2);
    DistToRegs();
    Wire.write(REGS[0]);
    Wire.write(REGS[1]);
}

void DistToRegs(){
    int dist=int(distanceSensor.measureDistanceCm());
    REGS[0] = (dist >> 8)&0xFF;
    REGS[1] = (dist >> 0)&0xFF;
}
