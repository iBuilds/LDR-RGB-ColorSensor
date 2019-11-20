import processing.serial.*; 

String buff = "";
int val = 0;
int wRed, wGreen, wBlue;

Serial port; 

void setup() { 
  fullScreen();
  port = new Serial(this, "COM5", 9600);
} 

void draw() { 
  background(wRed, wGreen, wBlue);
  while (port.available() > 0) {
    serialEvent(port.read());
  }
} 

void serialEvent(int serial) { 

  if (serial != '\n') { 
    buff += char(serial);
  } else {
    int cRed = buff.indexOf("R");
    int cGreen = buff.indexOf("G");
    int cBlue = buff.indexOf("B");

    if (cRed >=0) {
      String val = buff.substring(cRed+3);
      wRed = Integer.parseInt(val.trim());
    }    
    if (cGreen >=0) {
      String val = buff.substring(cGreen+3);
      wGreen = Integer.parseInt(val.trim());
    }
    if (cBlue >=0) {
      String val = buff.substring(cBlue+3);
      wBlue = Integer.parseInt(val.trim());
    }

    buff = "";
  }
} 
