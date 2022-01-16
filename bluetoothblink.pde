import processing.serial.*;  //imports library used for wireless comm with the HC-05
Serial myPort;               // declares Serial Port object from library
String Status= "OFF";        // matches inital state of LED

void setup()
{
 size(900,1000);                         // create window of this size
 myPort=new Serial(this, "COM3", 9600);  //my port was COM6 but yours may be different, recall when you connected it to your computer
 myPort.bufferUntil('\n');               //delays calling serialEvent unitl reaching '\n'
}

void serialEvent( Serial myPort){        //serialEvent is called whenever data is available
  Status=myPort.readStringUntil('\n');   //reads Serial.println() from Arduino
}

int state=0;
void draw()
{


  background(237,240,241);        // sets background to a color, parameters correspond to an RGB code
  fill(20,160,133);               // sets color we will use to fill shapes
  stroke(33);                     // sets color used for border around shapes
  strokeWeight(1);                // sets width of stroke when drawing shapes

  rect(50,300,150,50,10);        //creates rectangle with the given parameters
  rect(380,300,150,50,10);   
  rect(700,300,150,50,10);   
 


  fill(255);
  textSize(32);                   // sets size of text

  text("DIM", 425, 335);          //places "DIM" at coordinates
   text("OFF", 95, 335);
  text("BRIGHT", 725, 335);


  textSize(24);
  fill(33);
  text("Status:", 335, 735);
  textSize(30);
  text(Status, 420 , 735);        // Status is obtained from serialEvent, which happens whenver we write something. Status is the string being printed by Arduino



  if(mousePressed && mouseX>380 && mouseX<528 && mouseY>300 && mouseY<375)
  {
   state=1;

  }//dim
    if(mousePressed && mouseX>50 && mouseX<300&& mouseY>300 && mouseY<375)
  {
   state=0;

  }//dim
     if(mousePressed && mouseX>700 &&mouseY>300 && mouseY<375)
  {
   state=2;

  }//dim









  if(state>-1)
  {
   myPort.write(state);
  }

}
