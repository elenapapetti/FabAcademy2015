//Elena Papetti
//Fab Lab Frosinone
//Fab Academy 2015


// set pin numbers:
const int buttonPin = 3;     // the number of the pushbutton pin
const int ledPin =  7;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);     
}



void loop() {

  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == LOW) {     
    // turn LED on:    
    digitalWrite(ledPin, HIGH);  
  } 
  else {
    // blink
    digitalWrite(ledPin, HIGH); 
    delay(500);
    digitalWrite(ledPin, LOW); 
    delay(500);
  }
}
