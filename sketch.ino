//declare pinout
int pinSensor = A0;
int pinPower = 8;
int pinRelay = 7;
int measured = 0;
int minMoisture = 100;
int maxMoisture = 400;
int waitTimeStopped = 3600000; //one hour
int waitTImeRunning = 5000; //five seconds

void setup() 
{
	Serial.begin(9600);
	pinMode(pinPower, OUTPUT);//set pinPower as OUTPUT
	pinMode(pinRelay, OUTPUT);//set pinRelay as OUTPUT
  digitalWrite(soilPower, LOW);//set pinPower to LOW in order to shutdown the sensor
	digitalWrite(pinRelay, LOW);//set pinRelay to low in order to shutdown the water pump
}

void loop() 
{
	readSensor();//read the moisture level
	if(measured <= minMoisture)//if it is lower than the requested start to irrigate
	{
		//while the moisture level is under the max level requested, it will start the pump, and check
		//each ten seconds, when the moisture is over the moisture requested it will stop the pump and
		//recheck each ten minutes
		digitalWrite(pinRelay, HIGH);
		while(measured < maxMoisture)
		{
			delay(waitTImeRunning)//wait ten seconds
			readSensor();//read the sensor value
		}
		digitalWrite(pinRelay, LOW);//stop the water pump
	}
	delay(waitTimeStopped)// wait ten minutes
}

void readSensor()
{
	digitalWrite(soilPower, HIGH);//turn on the sensor
	delay(10);//wait to the sensor becomes stable
	measured = analogRead(pinSensor);//store the data
	digitalWrite(soilPower, LOW);//turn off the sensor
	Serial.println(measured);
}
