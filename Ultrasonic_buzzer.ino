#define trigPin 2
#define echoPin 3
const int bz = 8;

void setup() {
  
    pinMode(bz, OUTPUT);
  
  digitalWrite(bz, LOW);

Serial.begin (9600);

pinMode(trigPin, OUTPUT_FAST);
pinMode(echoPin, INPUT_FAST);
}

void loop() {
long duration, distance;
digitalWrite(trigPin, LOW); // Added this line
delayMicroseconds(2); // Added this line

digitalWrite(trigPin, HIGH);
// delayMicroseconds(1000); - Removed this line
delayMicroseconds(10); // Added this line
digitalWrite(trigPin, LOW);

duration = pulseIn2(echoPin, HIGH);
distance = (duration/2) / 29.1;
if (distance >= 1000000 || distance <= 0){
Serial.println("Out of range");
}
else {
Serial.print((distance*2)/100);

Serial.println(" cm");

if (((distance*2)/100)<200){
 digitalWrite(bz, HIGH);
}
else {
 digitalWrite(bz, LOW);
}

}
delay(500);
}

unsigned long pulseIn2(uint8_t pin, uint8_t state) {

    unsigned long pulseWidth = 0;
    unsigned long loopCount = 0;
    unsigned long loopMax = 5000000;

    // While the pin is *not* in the target state we make sure the timeout hasn't been reached.
    while ((digitalRead(pin)) != state) {
        if (loopCount++ == loopMax) {
            return 0;
        }
    }

    // When the pin *is* in the target state we bump the counter while still keeping track of the timeout.
    while ((digitalRead(pin)) == state) {
        if (loopCount++ == loopMax) {
            return 0;
        }
        pulseWidth++;
    }

    // Return the pulse time in microsecond!
    return pulseWidth * 50; // Calculated the pulseWidth //this is the value to be tweaked
}
