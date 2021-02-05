
/*Swerve Source code adapted from Howard E. Bartlett IV's Pixy swerve development project. 
All IP and programming in this development project is hereby being granted permanent unlimited 
licensing to the Kettering University Combat Team, meaning that it can be modified and used in any way desired by the team.*/


/*This program is currently only useful as a speed test to act as a benchmark 
to compare the speeds of different microcontrollers for processing swerve drive code. 
This is not readily-deployable code and will need some overhaul to be made ready for use.*/


/* Written by Howard E. Bartlett IV on 4/20/2020
 *  Update 1 written by Howard E. Bartlett IV on 4/21/2020
 *  Update 2 written by Howard E. Bartlett IV on 4/22/2020
 *  Update 3 written by Howard E. Bartlett IV on 4/25/2020
 *  Update 4 written by Howard E. Bartlett IV on 4/28/2020
 */


#include <SPI.h> // Adding all necessary libraries
#include <Wire>
#include <RF24.h>
#include <math.h> 


//Define I2C adresses for slave devices


int FRdrive = 1;
int FLdrive = 2;
int RRdrive = 3;
int RLdrive = 4;
int Weaponcontroller = 5;


//Define comm variables
int GoodTrans = 0;
int Timeout = 20;

// define swerve movement vectors
int FRVect[] = {0, 0};
int FLVect[] = {0, 0};
int RRVect[] = {0, 0};
int RLVect[] = {0, 0};

//define global Utan vectors
int UtanFR[];
int UtanFL[];
int UtanRR[];
int UtanRL[];


// define wheel positions around COR (X,Y)
int FRP[] = {12, 24};
int FLP[] = {-12, 24};
int FRP[] = {12, -24};
int FRP[] = {-12, -24};


//weapon safety and control variables. Initialized in safe mode to prevent accidental firing or pressurization.
bool WeaponArmed = false; 
bool WeaponCharging = false;
bool WeaponTrigger = false;
bool WeaponVent = true; // Weapon tank initializes in vent mode until close signal is recieved. This value doesn't immediately return to vent mode if connection is lost. The valve will automatically vent if connection is lost for 20 seconds, since we would have been counted out by then, and we don't want to touch the bot with a pressurized tank.


/* Open communication tunnel and set up data transfer to transponder.
 *  MOSI is attached to pin 11
 *  MISO is attached to pin 12
 *  Clock is attached to ppin 13
 *  Vcc MUST be regulated to 3.3v
 */


RF24 radio(10, 9);   // (CE, CSN) These can be exchanged for any other DIO pins
const byte address[6] = "00001";
unsigned long lastReceiveTime = 0; //Timer Circuit variables. (Safety cutoff measure)
unsigned long currentTime = 0;
// Max size of this struct is 32 bytes. Warning, values can only be read in 8 bit integers.
struct Command_line {
  byte DriveX;
  byte DriveY;
  byte DriveZ;
  byte WeaponCharge;
  byte WeaponTrigger;
  byte WeaponArmed;
  byte WeaponVent;
 

};
void setup() { 
  Wire.begin(); //begin running I2C protocol as master
  Serial.begin(9600); // Open debugging command line
  radio.begin(); // begin reading radio communications
  radio.openReadingPipe(0, address); // open default signal line
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening(); //  Set the module as receiver

  int UtanFR[] = ;
  int UtanFL[] = ;
  int UtanRR[] = ;
  int UtanRL[] = ;
  

}

void loop() {
   if (radio.available()) //poll radio for data
   {
    radio.read(&data, sizeof(Command_line)); // Read data and store in structure
    GoodTrans = 0; // set communication monitor to 0
    }
    else
    {GoodTrans = constrain(GoodTrans + 1, 0, Timeout);} //compile transmission errors until timeout value


    if {GoodTrans == Timeout)
    { SafeMode();)} //put robot in safe mode if communication errors reach timeout. Continue scanning for communication recovery.
    else{
      Runasnormal(); // Run as normal if communication is active
    }

      SendI2C();
 
}
void SafeMode(){ // Automatically resets all control outputs to safe holding values, these values will be over written in the case that communication is re-established

FRVect[] = {0, 0};
FLVect[] = {0, 0};
RRVect[] = {0, 0};
RLVect[] = {0, 0};

WeaponArmed = false; 
WeaponCharging = false;
WeaponTrigger = false;

}
void Runasnormal(){

FRVect[] = {SwAngle(DriveX, DriveY, ), 0};

  byte DriveX;
  byte DriveY;
  byte DriveZ;

  
}

int SwAngle(X, Y, UtanX, UtanY, Rot)
{
 int RotV[] = {UtanX * Rot, UtanY * Rot};
 int ReVect[] = {X + RotV[0], Y + RotV[1]};
 float DriveAngle = (degrees(atan2(ReVect[0], ReVect[1])) + 90);


  return DriveAngle;
}

int SSpeed(X, Y, UtanX, UtanY, Rot)
{
 int RotV[] = {UtanX * Rot, UtanY * Rot};
 int ReVect[] = {X + RotV[0], Y + RotV[1]};
 int DriveSpeed = (sqrt((ReVect[0]*ReVect[0]) + (ReVect[1] * ReVect[1]));
 
 
  return DriveSpeed;
}
