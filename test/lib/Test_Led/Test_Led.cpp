#include <Arduino.h>
#include <Test_Led.h>

TEST_LED::TEST_LED(){
}

void TEST_LED::test_constant_set_get(Led& led){
	Serial.println(F("CONSTANT TESTS"));
	delay(1000);
	int test_brightness;

	Serial.println(F("setMaxBrightness Test"));
	delay(500);
	for (test_brightness = -1000 ; test_brightness < 1001 ; test_brightness = test_brightness + 100 ){
		led.setMaxBrightness(test_brightness);
		if(led.getMaxBrightness() == constrain(test_brightness, 0, 255)){
			Serial.println(F("setMaxBrightness Test --> OK"));
		}
		else{
			Serial.println(F("setMaxBrightness Test --> FAILED"));	
		}
	}

	delay(1000);
	Serial.println(F("setRedMaxBrightness Test"));
	delay(500);
	for (test_brightness = -1000 ; test_brightness < 1001 ; test_brightness = test_brightness + 100 ){
		led.setRedMaxBrightness(test_brightness);
		if(led.getRedMaxBrightness() == constrain(test_brightness, 0, 255)){
			Serial.println(F("setRedMaxBrightness Test --> OK"));
		}
		else{
			Serial.println(F("setRedMaxBrightness Test --> FAILED"));	
		}
	}

	delay(1000);
	Serial.println(F("setGreenMaxBrightness Test"));
	delay(500);
	for (test_brightness = -1000 ; test_brightness < 1001 ; test_brightness = test_brightness + 100 ){
		led.setGreenMaxBrightness(test_brightness);
		if(led.getGreenMaxBrightness() == constrain(test_brightness, 0, 255)){
			Serial.println(F("setGreenMaxBrightness Test --> OK"));
		}
		else{
			Serial.println(F("setGreenMaxBrightness Test --> FAILED"));	
		}
	}

	delay(1000);
	Serial.println(F("setBlueMaxBrightness Test"));
	delay(500);
	for (test_brightness = -1000 ; test_brightness < 1001 ; test_brightness = test_brightness + 100 ){
		led.setBlueMaxBrightness(test_brightness);
		if(led.getBlueMaxBrightness() == constrain(test_brightness, 0, 255)){
			Serial.println(F("setBlueMaxBrightness Test --> OK"));
		}
		else{
			Serial.println(F("setBlueMaxBrightness Test --> FAILED"));	
		}
	}
}

void TEST_LED::test_led_set_get(Led& led){
	Serial.println(F("LED TESTS"));
	delay(1000);
	int test_brightness;
	String test_name;

	//	TEST 1
	delay(1000);

	test_name = "setRgb(index, value) and getRgb(index)";

	Serial.print(test_name);
	Serial.println(F(" Test"));
	delay(500);

	for (test_brightness = -1000 ; test_brightness < 1001 ; test_brightness = test_brightness + 100 ){
		for (int i = 0; i < 3; i++) {
			led.setRgb(i, test_brightness);
			if (led.getRgb(i) == constrain(test_brightness, 0, 255)) {
				Serial.print(test_name);
				Serial.println(F(" --> OK"));
			}
			else{
				Serial.print(test_name);
				Serial.println(F(" --> FAILED"));
			}
		}
	}

	//	TEST 2
	delay(1000);

	test_name = "setRgb(red, green, blue) and getRgb(index)";

	Serial.print(test_name);
	Serial.println(F(" Test"));
	delay(500);

	for (test_brightness = -1000 ; test_brightness < 1001 ; test_brightness = test_brightness + 100 ){
		led.setRgb(test_brightness, test_brightness, test_brightness);
		for (int i = 0; i < 3; i++) {
			if (led.getRgb(i) == constrain(test_brightness, 0, 255)) {
				Serial.print(test_name);
				Serial.println(F(" --> OK"));
			}
			else{
				Serial.print(test_name);
				Serial.println(F(" --> FAILED"));
			}
		}
	}

	//	TEST 3
	delay(1000);

	test_name = "setRed(red) & getRed()";

	Serial.print(test_name);
	Serial.println(F(" Test"));
	delay(500);

	for (test_brightness = -1000 ; test_brightness < 1001 ; test_brightness = test_brightness + 100 ){
		led.setRed(test_brightness);
	
		if (led.getRed() == constrain(test_brightness, 0, 255)) {
			Serial.print(test_name);
			Serial.println(F(" --> OK"));
		}
		else{
			Serial.print(test_name);
			Serial.println(F(" --> FAILED"));
		}
	}

	//	TEST 4
	delay(1000);

	test_name = "setGreen(Green) & getGreen()";

	Serial.print(test_name);
	Serial.println(F(" Test"));
	delay(500);

	for (test_brightness = -1000 ; test_brightness < 1001 ; test_brightness = test_brightness + 100 ){
		led.setGreen(test_brightness);
	
		if (led.getGreen() == constrain(test_brightness, 0, 255)) {
			Serial.print(test_name);
			Serial.println(F(" --> OK"));
		}
		else{
			Serial.print(test_name);
			Serial.println(F(" --> FAILED"));
		}
	}

	//	TEST 5
	delay(1000);

	test_name = "setBlue(Blue) & getBlue()";

	Serial.print(test_name);
	Serial.println(F(" Test"));
	delay(500);

	for (test_brightness = -1000 ; test_brightness < 1001 ; test_brightness = test_brightness + 100 ){
		led.setBlue(test_brightness);
	
		if (led.getBlue() == constrain(test_brightness, 0, 255)) {
			Serial.print(test_name);
			Serial.println(F(" --> OK"));
		}
		else{
			Serial.print(test_name);
			Serial.println(F(" --> FAILED"));
		}
	}
}

void TEST_LED::test_led_output(Led& led){

	Serial.println(F("LED TESTS OUTPUT"));
	delay(1000);
	int test_brightness;
	String test_name;

	//	TEST 1
	delay(1000);

	test_name = "setRgb(red, green, blue) and writeRgb()";

	Serial.print(test_name);
	Serial.println(F(" Test"));
	delay(500);

	for (test_brightness = -300 ; test_brightness < 301 ; test_brightness = test_brightness + 5 ){
		led.setRgb(test_brightness, test_brightness, test_brightness);
		Serial.println(test_brightness);
		for (int i = 0; i < 3; i++) {
			if (led.getRgb(i) == constrain(test_brightness, 0, 255)) {
				Serial.print(test_name);
				Serial.println(F(" --> OK"));
			}
			else{
				Serial.print(test_name);
				Serial.println(F(" --> FAILED"));
			}
		}
		led.writeRgb();
		Serial.println(led.getBlue());
		for (int i = 0; i < 3; i++) {
			if (led.getRgb(i) == constrain(test_brightness, 0, 255)) {
				Serial.print(test_name);
				Serial.println(F(" --> OK"));
			}
			else{
				Serial.print(test_name);
				Serial.println(F(" --> FAILED"));
			}
		}
	}

	led.setRgb(0, 0, 0);
	led.writeRgb();

	//	TEST 2
	delay(1000);

	test_name = "setRgb(index, value) and writeRgb(r, g, b)";

	Serial.print(test_name);
	Serial.println(F(" Test"));
	delay(500);

	for (int i = 0; i < 3; i++) {

		for (test_brightness = -300 ; test_brightness < 301 ; test_brightness = test_brightness + 2 ){
			
			led.setRgb(i, test_brightness);
			if(i == 0){
				led.setGreen(0);
				led.setBlue(0);
			}
			if(i == 1){
				led.setRed(0);
				led.setBlue(0);
			}
			if(i == 2){
				led.setRed(0);
				led.setGreen(0);
			}

			led.writeRgb();
			if (led.getRgb(i) == constrain(test_brightness, 0, 255)) {
				Serial.print(test_name);
				Serial.println(F(" --> OK"));
			}
			else{
				Serial.print(test_name);
				Serial.println(F(" --> FAILED"));
			}
		}
	}

	led.setRgb(0, 0, 0);
	led.writeRgb();

	//	TEST 3
	delay(1000);

	test_name = "writeRgb(r, g, b)";

	Serial.print(test_name);
	Serial.println(F(" Test"));
	delay(500);

	for (test_brightness = -300 ; test_brightness < 301 ; test_brightness = test_brightness + 5 ){
		led.setRgb(test_brightness, test_brightness, test_brightness);
		Serial.println(test_brightness);

		led.writeRgb(test_brightness, test_brightness, test_brightness);

		for (int i = 0; i < 3; i++) {
			if (led.getRgb(i) == constrain(test_brightness, 0, 255)) {
				Serial.print(test_name);
				Serial.println(F(" --> OK"));
			}
			else{
				Serial.print(test_name);
				Serial.println(F(" --> FAILED"));
			}
		}
	}

	led.setRgb(0, 0, 0);
	led.writeRgb();
}

void TEST_LED::test_led_blink(Led& led){

	led.blinkSync(RAND, random(200, 4000));

}