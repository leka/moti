
//###########//
// LIBRARIES //
//###########//

#include <Arduino.h>
#include <Serial.h>
#include <Wire.h>
#include <CommunicationUtils.h>
#include <DebugUtils.h>
#include <FIMU_ADXL345.h>
#include <FIMU_ITG3200.h>
#include <FreeSixIMU.h>

// Include all the classes needed to beautifully develop your robot.
#include <Led.h>

//	Tests
#include <Test_Led.h>

// Then create instances of every classes
Led led = Led(11, 12, 13);
Led led1 = Led(8, 9, 10);
TEST_LED test;


//#######//
// SETUP //
//#######//

void setup() {
	led.open();	
	led1.open();
	delay(1000);
	Serial.begin(115200);
	Serial.println();

	delay(1000);
	// // TEST CONSTANTS
	// test.test_constant_set_get(led);

	// // TEST LED
	// test.test_led_set_get(led);

	// // TEST OUTPUT
	// delay(1000);
	// test.test_led_output(led);
}



//######//
// LOOP //
//######//

void loop() {

	while(millis() < 10000){
		test.test_led_blink(led);
		test.test_led_blink(led1);
	}
	while(millis() < 15000){
		led.turnOff();
		led1.turnOff();
	}

	while(millis() < 25000){
		test.test_led_blink(led);
		test.test_led_blink(led1);
	}
	led.turnOff();
	led1.turnOff();
}