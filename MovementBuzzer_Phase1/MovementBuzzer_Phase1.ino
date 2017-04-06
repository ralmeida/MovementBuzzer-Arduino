//PIN of our sensor
int speakerPin = 3;

//Hold the current volume
int volume = 5;

// the setup routine runs once when you press reset:
void setup() {
  //set the pinMode for our Speaker to an Output
  pinMode (speakerPin, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
    //play buzzer @ 'volume'
    //uncomment the line below for a random volume
    volume = random(0,255);
    analogWrite (speakerPin, volume); 
    //pause for 50 miliseconds 
    delay (50);
    //stop the tone
    analogWrite (speakerPin, 0);
    //pause for 10 miliseconds 
    delay (10);
}
