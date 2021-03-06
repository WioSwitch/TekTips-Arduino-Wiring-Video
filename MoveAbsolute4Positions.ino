/*
  TekTips1 - program to highlight Arduino wiring to a Teknic ClearPath integrated servo motor
  Author is Abe Amirana, 7/10/2017    
  Program uses a "MCVC" (Motion Control Velocity Control) ClearPath servo motor 
  Operating Mode is the "Ramp Up/Down to Selected Velocity" (uses 2 input bits to control 4 velocities)
  - View operational mode video for further information on this specific Operational Mode:
  https://www.teknic.com/watch-video/#Opmode5
      
  TekTips Video: Wiring a ClearPath motor to an Arduino micro controller
  www.youtube.com/blahblahblah
*/

//Wire colors refer to a standard Teknic ClearPath controller cable 
const int Enable = 6; // ClearPath ~enable input; +enable = BLU wire; -enable = ORN wire
const int InputA = 8; // ClearPath Input A; +InputA = WHT wire; -InputA is BRN wire
const int InputB = 9; // ClearPath Input B; +InputB = BLK wire; -InputB = YEL wire
const int HLFB = 4; // ClearPath HLFB Output; +HLFB = GRN wire; -HLFB = RED wire
const int myLED = 13; // Arduino on-board LED

int DwellTime = 500; // desired time for ramp and constant velocity

// ============================================================================================
// put your setup code here, to run once:
void setup() 
{
  pinMode(Enable, OUTPUT);
  pinMode(InputA, OUTPUT);
  pinMode(InputB, OUTPUT);
  //pinMode(HLFB, INPUT_PULLUP);
  pinMode(HLFB, INPUT);
  pinMode(myLED, OUTPUT);

  // start off by ensuring thet the motor is disabled before proceeding
  digitalWrite(Enable, LOW);
  delay(10);

  // set the two outputs to their initial states
  digitalWrite(InputA, LOW);
  digitalWrite(InputB, LOW);
  digitalWrite(myLED, LOW);
  
  // toggle ~enable, read HLFB & set on-board LEDs - this clears any safety shutdowns & activates motor's power stage
  digitalWrite(Enable, HIGH);
  delay(15);
  while(digitalRead(HLFB) == !LOW) {
    delay(20);
  }
  if (digitalRead(HLFB) == LOW) {
    digitalWrite(myLED, HIGH);
    delay(200);
  }
}
// end of setup code

// put your main code here, to loops indefinitely:
void loop()
{
  for (int i = 0; i<3; i++) {
    // command to the first velocity setting
    digitalWrite(InputA, HIGH);
    digitalWrite(InputB, LOW);
    while(digitalRead(HLFB) == LOW) {   // wait for HLFB to go false (move has started)
    }
    while(digitalRead(HLFB) == !LOW) {  // wait for HLFB to go true (Move Done = true)
    }
    delay(DwellTime);

    // command to the second velocity setting
    digitalWrite(InputA, LOW);
    digitalWrite(InputB, HIGH);
    while(digitalRead(HLFB) == LOW) {
    }
    while(digitalRead(HLFB) == !LOW) {
    }
    delay(DwellTime);
  
    // command to the third velocity setting
    digitalWrite(InputA, HIGH);
    digitalWrite(InputB, HIGH);
    while(digitalRead(HLFB) == LOW) {
    }
    while(digitalRead(HLFB) == !LOW) {
    }
    delay(DwellTime);
  
    // command to the forth and final velocity setting (back to zero velocity)
    digitalWrite(InputA, LOW);
    digitalWrite(InputB, LOW);
    while(digitalRead(HLFB) == LOW) {
    }
    while(digitalRead(HLFB) == !LOW) {
    }
    delay(DwellTime);

    DwellTime = DwellTime - 250;
    //delay(50);
  }
  DwellTime = 500;  
  delay(DwellTime);
}
// end of main code, will loop indefinitely:

