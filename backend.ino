
int leftPin = D5; 
int middlePin = D6;
int rightPin = D7;

int pos = 0;

int dutyCycleDelay = 10;

void setup() {

  pinMode(leftPin, OUTPUT);
  pinMode(middlePin, OUTPUT);
  pinMode(rightPin, OUTPUT);
  
  Spark.function("setpos", setPosition);
  Spark.function("getpos", getPosition);
  Spark.function("right", rightDummy);
  Spark.function("left", leftDummy);

}

// Next we have the loop function, the other essential part of a microcontroller program.
// This routine gets repeated over and over, as quickly as possible and as many times as possible, after the setup function is called.
// Note: Code that blocks for too long (like more than 5 seconds), can make weird things happen (like dropping the network connection).  The built-in delay function shown below safely interleaves required background activity, so arbitrarily long delays can safely be done if you need them.

int resetPins() {
    digitalWrite(leftPin, LOW);
    digitalWrite(middlePin, LOW);
    digitalWrite(rightPin, LOW);
    return 0;
    
}


void pinBlink(int pin) {
    resetPins();
    digitalWrite(pin, HIGH);
}
void right() { 
    pinBlink(leftPin);
}

int rightDummy(String dummy) {
    right();
    return 1;
}

int leftDummy(String dummy) {
    left();
    return 1;
}

void left() {
    pinBlink(rightPin);
}
void forward() {
    digitalWrite(rightPin, LOW);
    digitalWrite(leftPin, LOW);
    digitalWrite(middlePin, HIGH);
}


int setPosition(String posValue) {
    pos = posValue.toInt();
    return pos;
    
}



int getPosition(String dummy) {
    return pos;
}

void loop() {
  // Pos goes from 0 to 100, meaning that 50 is middle so we...
  
  int newpos = pos - 50;
  
  // now -50 is full on left, 50 is full on right, 0 is straight ahead. we need to have a way of "blinking" the sensor on on a duty cycle. 
  
  // We'll use a stochastic duty cycle for smoothness -
  // by that what I mean is that we generate a random number between 1-50, if it's below abs(pos) then we blink the pin high for 10ms, if it's above we keep it low
  
   for (int i=0; i<50; i++) {
        if ( random(50)<abs(newpos)) {
             if (newpos > 0) left();
             if (newpos < 0) right();
             if (newpos == 0) 
             { 
                 forward();
             }
        }
        else { 
               forward();
        }
        delay(dutyCycleDelay);
    }
  // And repeat!
}

