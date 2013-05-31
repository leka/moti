int  XYZ[6];

void setup() {
  Serial.begin(9600);
}

void loop() {
  randomize();
  sendJSON();
  delay(500);
}

void randomize(){
  for (int i = 0 ; i < 6 ; i++){
    XYZ[i] = random(0, 255);
  }
}

void sendJSON(){
	Serial.print("{");

		Serial.print("'accel' : ");

		Serial.print("{");

			Serial.print("'x' : '");
			Serial.print(XYZ[0]);
			Serial.print("', ");

			Serial.print("'y' : '");
			Serial.print(XYZ[1]);
			Serial.print("', ");

			Serial.print("'z' : '");
			Serial.print(XYZ[2]);
			Serial.print("'");

		Serial.print(" } ");

		Serial.print("'gyro' : ");

		Serial.print("{");

			Serial.print("'yaw' : '");
			Serial.print(XYZ[3]);
			Serial.print("', ");

			Serial.print("'pitch' : '");
			Serial.print(XYZ[4]);
			Serial.print("', ");

			Serial.print("'roll' : '");
			Serial.print(XYZ[5]);
			Serial.print("'");

		Serial.print(" } ");


	Serial.println("}");
}

