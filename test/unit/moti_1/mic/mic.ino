const int pinMic = A3; //analog input connected to mic AUD

const int pinLED0 = 8; //digital output connected to LED 0
const int pinLED1 = 9; //digital output connected to LED 1
const int pinLED2 = 10; //digital output connected to LED 2


//baseline level for my mic in a fairly quiet room
//determined by watching serial monitor on first run
const int valBaseline = 330;
int valMic;

void setup() {
    Serial.begin(9600);

    pinMode(pinLED0, OUTPUT);
    pinMode(pinLED1, OUTPUT);
    pinMode(pinLED2, OUTPUT);

}

void loop() {


    sound();

}

void sound(){
      int valMic = analogRead(pinMic);

    Serial.println(valMic);
    if (valMic > valBaseline + 10) digitalWrite(pinLED0, HIGH);
    else digitalWrite(pinLED0, LOW);

    if (valMic > valBaseline + 35) digitalWrite(pinLED1, HIGH);
    else digitalWrite(pinLED1, LOW);

    if (valMic > valBaseline + 55) digitalWrite(pinLED2, HIGH);
    else digitalWrite(pinLED2, LOW);

}
