int sensorPin = 0;
int ledPin = 13;
int sensorValue = 1001;



void setup() {
  // put your setup code here, to run once:
    pinMode(sensorPin, INPUT);
    pinMode(ledPin, OUTPUT);
    Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly: 
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
delay(50);
}
