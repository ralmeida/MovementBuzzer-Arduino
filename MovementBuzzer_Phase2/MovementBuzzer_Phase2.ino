//PIN of our sensor
int speakerPin = 3;

//--BEGIN NEW CODE--//

//PIN for x
int xPin = A0;

//PIN for y
int yPin = A1;

//PIN for z
int zPin = A2;

//Vars to hold the current x,y,z
int x, y, z;

//--END NEW CODE--//

//Hold the current volume
int volume = 5;

//--BEGIN NEW CODE--//

//Did We Move Toggle
bool didMove = false;

/*
 * Setting for movement check
 * if 
 *  - false then buzz when not moving
 *  - true then buzz when moving
 */
bool toggle = false;

//--END NEW CODE--//

// the setup routine runs once when you press reset:
void setup() {
  //set the pinMode for our Speaker to an Output
  pinMode (speakerPin, OUTPUT);

  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  
    /* --OLD CODE--
    //play buzzer @ 'volume'
    analogWrite (speakerPin, volume); 
    //pause for 50 miliseconds 
    delay (50);
    //stop the tone
    analogWrite (speakerPin, 0);
    //pause for 10 miliseconds 
    delay (10);*/  
  
  /*
   * if our toggle is false and we haven't moved
   * OR
   * if our toggle is true and we have moved
  */
  if((!toggle && !didMove) || (toggle && didMove)) {

    //play buzzer @ 'volume'
    analogWrite (speakerPin, volume);
    //pause for 50 miliseconds 
    delay (50);
    //stop the tone
    analogWrite (speakerPin, 0);
  }

  //read sensor x,y,z
  int newX = analogRead(xPin); // read analog input xPin
  int newY = analogRead(yPin); // read analog input yPin
  int newZ = analogRead(zPin); // read analog input zPin

  
  //if(newX != 1) {
  Serial.println(newX);
  Serial.println(newY);
  //}
  
  //hold our difference form what we just read to our last
  int xDiff = newX-x;
  int yDiff = newY-y;
  int zDiff = newZ-z;

  //local flag for movement checking
  bool didItMove = false;

  //check for differences allowing for a +/-1 variance
  if(xDiff != 0 || yDiff != 0 || zDiff != 0) {
  
    if(xDiff > 1 || xDiff < -1) {
      //Serial.print("xDiff");
      didItMove = true;
    }
    if(yDiff > 1 || yDiff < -1) {
      //Serial.print("yDiff");
      didItMove = true;
    }
    if(zDiff > 1 || zDiff < -1) {
      //Serial.print("zDiff");
      didItMove = true;
    }
        
    /*REMOVE THIS IF NOT USING SIM*/
    //didItMove=true;
  }

  //Set our current vals to the readings
  x=newX, y=newY, z=newZ;

  //Set if we moded or not
  didMove = didItMove;
  
  delay(75); 
}
