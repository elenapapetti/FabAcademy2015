// Elena Papetti
// Fab Lab Frosinone
// Fab Academy 2015

import beads.*;
import java.util.Arrays; 
import processing.serial.*;
AudioContext ac;
Glide carrierFreq, modFreqRatio;
 Serial myPort;        // The serial port
 float inByte;
void setup() {
 println(Serial.list());
 // I know that the first port in the serial list on my mac
 // is always my  Arduino, so I open Serial.list()[0].
 // Open whatever port is the one you're using.
 myPort = new Serial(this, "COM12" ,115200);
 // don't generate a serialEvent() unless you get a newline character:
 myPort.bufferUntil('\n');

  size(500,500);
  ac = new AudioContext();
  /*
   * This is a copy of Lesson 3 with some mouse control.
   */
   //this time we use the Glide object because it smooths the mouse input.
  carrierFreq = new Glide(ac, 500);
  modFreqRatio = new Glide(ac, 1);
  Function modFreq = new Function(carrierFreq, modFreqRatio) {
    public float calculate() {
      // return x[0] * x[1] ;  // MODULAZIONE A2   DX SOPA SOTTO 
      return 0; // x[0] * x[1] ;  // MODULAZIONE A2   DX SOPA SOTTO 
    }
  };
  WavePlayer freqModulator = new WavePlayer(ac, modFreq, Buffer.SINE);
  Function carrierMod = new Function(freqModulator, carrierFreq) {
    public float calculate() {
      // return x[0] * inByte + x[1];  // MODULAZIONE A1   SX  DX SX
      return inByte;  // MODULAZIONE A1   SX  DX SX
    }
  };
  WavePlayer wp = new WavePlayer(ac, carrierMod, Buffer.SINE);
  Gain g = new Gain(ac, 1, 0.1);
  g.addInput(wp);
  ac.out.addInput(g);
  ac.start();
}

 void serialEvent (Serial myPort) {
 // get the ASCII string:
 String inString = myPort.readStringUntil('\n');
 
 if (inString != null) {
 // trim off any whitespace:
 inString = trim(inString);
 // convert to an int and map to the screen height:
 String[] list = split(inString, ',');
 
 inByte = float(list[0]) + float(list[1]) + float(list[2]) + float(list[3]);
 inByte = map(inByte, 0, 40, 100, 2500);
 
/*
 * The drawing code also has some mouse listening code now.
 */

 }}
 
 
/*
 * The drawing code also has some mouse listening code now.
 */
color fore = color(255, 102, 204);
color back = color(0,0,0);

/*
 * Just do the work straight into Processing's draw() method.
 */
void draw() {
  loadPixels();
  //set the background
  Arrays.fill(pixels, back);
  //scan across the pixels
  for(int i = 0; i < width; i++) {
    //for each pixel work out where in the current audio buffer we are
    int buffIndex = i * ac.getBufferSize() / width;
    //then work out the pixel height of the audio data at that point
    int vOffset = (int)((1 + ac.out.getValue(0, buffIndex)) * height / 2);
    //draw into Processing's convenient 1-D array of pixels
    vOffset = min(vOffset, height);
    pixels[vOffset * height + i] = fore;
  }
  updatePixels();
  //mouse listening code here
  carrierFreq.setValue((float)mouseX / width * 1000 + 50);
  modFreqRatio.setValue((1 - (float)mouseY / height) * 10 + 0.1);
}
