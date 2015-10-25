/*
    Home Monitoring
    Author: tgoetheyn
    
    Changelog:
    2015-10-18  Initial script
    2015-10-24  Add enviroment sensor living room
*/
#include <SPI.h>
#include <Ethernet.h>
#include <Nagduino.h>
#include <DHT.h>

#define DHT1TYPE DHT11

/* INITIAL CONFIG */
    // Pin Configuration- DIGITAL
    int PinGarageMotion = 5; //Garage
    #define DHT1PIN 2 // Living Room - enviroment
    
    // Pin Configuration- ANALOG
          
    // Variables
    int GarageMotion = 0;
    int MotionSent = 0;
    int loopcount = 0;
    
    // Nagios Server Config
    
    byte mac[6]    = { 0x4E, 0x61, 0x67, 0x69, 0x6F, 0x73 };
    byte ip[4]     = { 192,168,1,66 };	// Arduino IP
    byte nagios[4] = { 192,168,1,55 };	// Nagios IP
    char token[]   = "DummyNrdpToken";	// NRDP token
    Nagduino nagduino;     // Nagduino object for sending NRDP
    
    // create objects
    DHT dht1(DHT1PIN, DHT1TYPE);

/* START PROGRAM */
void setup()
{
    Serial.begin(9600);
    pinMode(PinGarageMotion, INPUT);
    dht1.begin();
}

void loop()
{
    //check Garage
    GarageMotion = digitalRead(PinGarageMotion);
    if (GarageMotion) {
        if (!MotionSent) {
            MotionSent = 120;
            //Serial.println("Motion alert sent");
            nagduino.sendNRDP("Nagduino", "Garage - Motion", 1, "Motion detected! | Motion=1");     
        }
    } else {
        if (!MotionSent) {
            nagduino.sendNRDP("Nagduino", "Garage - Motion", 0, "OK | Motion=0");  
        }
    }
    if (MotionSent) {
        MotionSent = MotionSent - 1;
    }
    
    //send enviromental sensor data every 60 seconds
    if (loopcount > 59) {
        int h1 = dht1.readHumidity();
        int t1 = dht1.readTemperature();
        char charLiving[100];
        char EnvStrT[] = "Temperature=";
        char EnvStrH[] = ", Humidity=";
        char Sep[] = "|";
        sprintf(charLiving,"%s %i%s %i %s %s%i%s%i",EnvStrT,t1,EnvStrH,h1,Sep,EnvStrT,t1,EnvStrH,h1);
        delay(500);
        nagduino.sendNRDP("Nagduino", "Living - Enviroment", 0, charLiving);
        Serial.println(charLiving);
        loopcount = 0;
    } else {
        loopcount = loopcount +1;
    }
    delay(1000);
}
