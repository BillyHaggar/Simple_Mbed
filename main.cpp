//Includes
#include "mbed.h"


//Global objects


//Ticker for precise measurements
Ticker t;


DigitalOut GreenLED(D5);
DigitalOut RedLED(D7);
DigitalIn SW(D4);
AnalogIn aPOT(A0);
AnalogIn aLDR(A1);
float fPOTVin = 0.0;
float fLDRVin = 0.0;
bool paused = false;
int refreshRate = 1;
float milliseconds;

//Serial interface
Serial pc(SERIAL_TX, SERIAL_RX);

void TakeSample(){
	if(paused == false) {
		RedLED = 0; // RED LED shouldnt be on
		GreenLED = !GreenLED; // the green LED will flip for every sample taken
		//Read ADC         
  fPOTVin = aPOT;
	fLDRVin = aLDR;
  //Write to terminal
  printf("Potentiometer Input = %6.3f, |||||||  LDR Input = %6.3f\n\r", fPOTVin, fLDRVin ); 
	}else{
	GreenLED = 0; // turn on the RED led while input is being made
	RedLED = 1;
	}
	
}//End TakeSample()

void GetRefreshRate(){
	printf("PLEASE ENTER A NEW REFRESH RATE: ");
	scanf("%d", &refreshRate);
	printf("THE NEW REFRESH RATE IS: %d HZ \n\r", refreshRate);
	
}
//Main function
int main() {
	//Initialize components
	 pc.baud(9600);
	//attach sample taking to happen at a precise rate
	 milliseconds = 1 / refreshRate;
   t.attach(&TakeSample, milliseconds);
    
	//wait until the buttons push then pause software
	while(1) {   
	if (SW == 1){
		paused = !paused;
		wait(0.5);
		
		GetRefreshRate();
		
		
		
		t.detach();
		milliseconds = 1 / refreshRate;
		t.attach(&TakeSample, milliseconds);
		paused = !paused;	
		}
  } //end while(1)
	
	

} //end main

