/* For the SN74HC485 latches*/
int DS = 13;
int SRCLK = 11;
int RCLK = 10; // Pulse only to store temporary results

/* For the EEPROM */
int WE = 12; // Write enable LOW to activate

int op[] = {2,3,4,5,6,7,8,9};

#define CLKINTERVAL 200

void setup() {

  Serial.begin(57600); // Takes up pin 0 and pin 1 for serial communication. cool.

  pinMode(DS, OUTPUT);
  pinMode(SRCLK, OUTPUT);
  pinMode(RCLK, OUTPUT);
  
  digitalWrite(SRCLK, HIGH);
  digitalWrite(RCLK, HIGH);
  digitalWrite(DS, LOW);

  digitalWrite(WE, HIGH);

  // VALUES TO SEND
  for (uint16_t pos = 0; pos < (1 << 4); pos++) {
    
  }

  // Signal done
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  
}
void setAddress(uint16_t address, bool outputEnable) {
  /* Set latch */
  shiftOut(DS, SRCLK, MSBFIRST, (address >> 8 | (outputEnable ? 0x00 : 0x80)));
  shiftOut(DS, SRCLK, MSBFIRST, address);
  
  digitalWrite(RCLK, LOW);
  digitalWrite(RCLK, HIGH);
  digitalWrite(RCLK, LOW);
    
}
void write(uint16_t address, uint8_t output) {

  setAddress(address, false);
  
  for(int q = 0; q < 8; q++) {
    //Serial.println(bitRead(output, q));
    pinMode(op[q], OUTPUT);
    delay(50);
    digitalWrite(op[q], bitRead(output, q));
  }
  
  digitalWrite(WE, LOW);
  delayMicroseconds(1);
  digitalWrite(WE, HIGH);
  delayMicroseconds(1);
  delay(10);
}

byte read(int address) {
  
  setAddress(address, true);
  byte accum = 0;
  for (int p = 0; p < 8; p++) {
    pinMode(op[q], INPUT);
 
    accum = (accum << 1) + digitalRead(op[p]);  
  }
  return accum;
}

void loop() {
   
}

