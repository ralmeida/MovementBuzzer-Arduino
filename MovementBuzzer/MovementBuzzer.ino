//PIN of our sensor
int speakerPin = 3;

//PIN of our toggle
int togglePin = 2;

//PIN to read our Volume value
int volumePin = A3;

//PIN for x
int xPin = A0;

//PIN for y
int yPin = A1;

//PIN for z
int zPin = A2;

//Vars to hold the current x,y,z
int x, y, z;

//Hold the current volume
int volume = 5;

//Volume min value
const int volumeMIN = 5;

//Volumne max value
const int volumeMAX = 250;

//Did We Move Toggle
bool didMove = false;

//Set a Variance (Buzz when Moving)
int move_variance = 1;
//Set a Variance (Buss when Still)
int still_variance = 3;

/*
 * Setting for movement check
 * if 
 *  - false then buzz when not moving
 *  - true then buzz when moving
 */
bool toggle = true;

void setup () {
  Serial.begin(9600);
  pinMode (speakerPin, OUTPUT);
  pinMode (togglePin, INPUT);
}

void loop () {

  //Read the current value from the volume knob
  volume = analogRead(volumePin);
  
  //make sure the volume is within range (shorthand)
  //volume = (volume < volumeMIN) ? volumeMin : (volume > volumeMAX) ? volumeMax : volume;
  
  //make sure the volume is within range (full)
  if(volume < volumeMIN) {
    volume = volumeMIN;
  } else if(volume > volumeMAX) {
    volume = volumeMAX;
  }

  //read the toggle value from the switch
  toggle = digitalRead(togglePin);
  //Serial.println(toggle);
  
  /*
   * if our toggle is false and we haven't moved
   * OR
   * if our toggle is true and we have moved
  */
  if((!toggle && !didMove) || (toggle && didMove)) {

    //play a random note from 0,255
    //analogWrite (speakerPin, random(0, 255));
    //play a note at the given volume
    analogWrite (speakerPin, volume); 
    delay (50);
    //stop the tone
    analogWrite (speakerPin, 0);
    delay (10);
  }

  //read sensor x,y,z
  int newX = analogRead(xPin); // read analog input xPin
  int newY = analogRead(yPin); // read analog input yPin
  int newZ = analogRead(zPin); // read analog input zPin

  //hold our difference form what we just read to our last
  int xDiff = newX-x;
  int yDiff = newY-y;
  int zDiff = newZ-z;

  //local flag for movement checking
  bool didItMove = false;

  int variance = (toggle) ? still_variance : move_variance;
  
  //check for differences allowing for a +/-variance
  if(xDiff != 0 || yDiff != 0 || zDiff != 0) {
    if(xDiff > variance || xDiff < -variance) {
      //Serial.print("xDiff: ");
      //Serial.println(xDiff);
      didItMove = true;
    }
    if(yDiff > variance || yDiff < -variance) {
      //Serial.print("yDiff: ");
      //Serial.println(yDiff);
      didItMove = true;
    }
    if(zDiff > variance || zDiff < -variance) {
      //Serial.print("zDiff: ");
      //Serial.println(zDiff);
      didItMove = true;
    }
  }

  //Set our current vals to the readings
  x=newX, y=newY, z=newZ;

  //Set if we moded or not
  didMove = didItMove;
  
  delay(25);
}
