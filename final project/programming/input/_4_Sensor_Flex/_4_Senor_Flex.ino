
// #Elena Papetti 
// #Fablab Frosinone
// #Giugno 2015

#define sensElbowSx A0 // Gomito SX
#define sensShoulderSx A1 // Spalla SX
#define sensElbowDx A2  // Gomito DX
#define sensShoulderDx A3 // Spalla DX

// Reset Vars
int valueElbowSx = 0;
int valueShoulderSx = 0;
int valueElbowDx = 0;
int valueShoulderDx = 0;

static int valuePrevSens = 0;
static int valueActSens = 0;
const int diffTrigger = 3;  // SensibilitÃ 

// Sensor Calibration Value
// A0
int minSensValElbowSx = 30; // This value for flat position
int maxSensValElbowSx = 90; // This value for +90 degrees
// A1
int minSensValShoulderSx = 10; // This value for flat position
int maxSensValShoulderSx = 33; // This value for +90 degrees
// A2
int minSensValElbowDx = 52; // This value for flat position
int maxSensValElbowDx = 102; // This value for +90 degrees
// A3
int minSensValShoulderDx = 11; // This value for flat position
int maxSensValShoulderDx = 33; // This value for +90 degrees
//
byte const splitPositions = 10;
void setup() {
  Serial.begin(115200);
  pinMode( sensElbowSx,INPUT );
  pinMode( sensShoulderSx,INPUT );
  pinMode( sensElbowDx,INPUT );
  pinMode( sensShoulderDx,INPUT );
 
} 
void loop() {
  valueElbowSx = analogRead( sensElbowSx );
  valueShoulderSx  = analogRead( sensShoulderSx );
  valueElbowDx   = analogRead( sensElbowDx );
  valueShoulderDx = analogRead( sensShoulderDx ); 
  int posElbowSx = map(valueElbowSx, minSensValElbowSx, maxSensValElbowSx, splitPositions, 0 );
  int posShoulderSx = map(valueShoulderSx, minSensValShoulderSx, maxSensValShoulderSx, splitPositions, 0);
  int posElbowDx = map(valueElbowDx, minSensValElbowDx, maxSensValElbowDx, splitPositions, 0);
  int posShoulderDx = map(valueShoulderDx, minSensValShoulderDx, maxSensValShoulderDx, splitPositions, 0);
 
  /*
  
  Serial.print( valueElbowSx );
  Serial.print( " P: " );
  Serial.print( posElbowSx );
  Serial.print( " - " );
  
  Serial.print( valueElbowDx );
  Serial.print( " P: " );
  Serial.print( posElbowSx );
  Serial.print( " - " );

  Serial.print( valueShoulderSx );
  Serial.print( " P: " );
  Serial.print( posShoulderSx );
  Serial.print( " - " );
  
  Serial.print( valueShoulderDx );
  Serial.print( " P: " );
  Serial.print( posShoulderDx  );
  Serial.print( "\n" );
  
  delay( 1000 );
  
  */
  String outString = String(posElbowSx);
  outString += ",";
  outString += String(posShoulderSx);
  outString += ",";
  outString += String(posElbowDx);
  outString += ",";
  outString += String(posShoulderDx);
  
  boolean senddata = diff(posElbowSx + posShoulderSx + posElbowDx + posShoulderDx);
  if (senddata == true) 
  {
    // Serial.println(send);
    Serial.println(outString);    // Ritardo suono successivo
    delay(500);        // delay in between reads for stability
  }
    else
  {
    // Serial.println(send);
    Serial.println("0,0,0,0");
    delay(50);        // delay in between reads for stability
  }

}

boolean diff(int ActValue) {
    if (abs(valuePrevSens - ActValue) >= diffTrigger) {
        valuePrevSens = ActValue;
    return true;
  } 
  else 
  {
    return false;
  } 
} 



