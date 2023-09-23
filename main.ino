//#include <ArduinoSTL.h>

//#include <MultiStepper.h>

#include <AccelStepper.h>

//#include <ArduinoSTL.h>

#include "motors.h"
#include "Serialcom.h"
#include "SDcard.h"
#include "SettingsManager.h"


// Define pin connections1
const int dirPin1 = 30;
const int stepPin1 = 31;

// Define pin connections2
/*const int dirPin2 = 32;
const int stepPin2 = 33;

// Define pin connections3
const int dirPin3 = 34;
const int stepPin3 = 35;*/

// Define motor interface type
#define motorInterfaceType 1
//AccelStepper stepper1(motorInterfaceType, stepPin1, dirPin1);
/*AccelStepper stepper2(motorInterfaceType, stepPin2, dirPin2);
AccelStepper stepper3(motorInterfaceType, stepPin3, dirPin3);*/

SDcardClass SDcard(5);


/*MotorsClass Motors(1, 30, 31,
	1, 32, 33,
	1, 34, 35);*/


MotorsClass Motors(1, 17, 16,
	1, 21, 22,
	1, 25, 26);

SettingsManagerClass SettingsManager;

SerialcomClass SerialCom(SDcard, Motors, SettingsManager);

void setup() {
	Serial.begin(115200);

	SDcard.initialize();

	SerialCom.setStartFunction(program);
	//SerialCom.set_update(SerialCom.update);

	/*Serial.println(SDcard.get_settings()[0]);
	Serial.println(SDcard.get_settings()[1]);
	Serial.println(SDcard.get_settings()[2]);*/

	//SerialCom.send_settings(SDcard.get_settings(), SDcard);

	//SerialCom.start_update_scheduler(SerialCom.m_update_function);

	SettingsManager.set_motors(&Motors);
	SettingsManager.set_SDcard(&SDcard);

	SettingsManager.apply_steps_mm();
	SettingsManager.apply_motor_speeds();
	SettingsManager.apply_motor_acceleration();


	/*Motors.set_chariot_position(2000);
	Motors.set_lit_position(2000);
	Motors.set_poudre_position(2000);

	Motors.set_poudre_step_mm(100);
	Motors.set_chariot_step_mm(100);
	Motors.set_lit_step_mm(100);

	Motors.set_poudre_speed(10);
	Motors.set_chariot_speed(10);
	Motors.set_lit_speed(10);

	Motors.set_poudre_acceleration(10);
	Motors.set_chariot_acceleration(10);
	Motors.set_lit_acceleration(15);*/

	//Motors.move_poudre(1000);
	//program();


}

void loop() {
	SerialCom.update();
	//Motors.run();
	yield(); // bug crash
}


void program() {

	SerialCom.is_running = true;

	std::vector<String> settings = SDcard.get_settings();

	int deplacement_poudre(settings[9].toInt());
	int deplacement_chariot(settings[10].toInt());
	int deplacement_lit(settings[11].toInt());

	float first_layer_multiplicator(settings[12].toFloat());
	int first_layer_number_layers(settings[13].toInt());
	int total_number_of_layers(settings[14].toInt());

	float delay_m(round(settings[15].toFloat()*1000));
	float delay_all(round(settings[16].toFloat()*1000));
	int passes(0);

	Serial.println("mov" + String(passes));

	while (passes < total_number_of_layers) {

		if (passes < first_layer_number_layers) {
			// Monter poudre
			Motors.move_poudre(deplacement_poudre * first_layer_multiplicator);
			SerialCom.update();
			delay(delay_all);
			//Serial.println("poudre*");
			// racleur aller
			// Motors.move_chariot(deplacement_chariot * first_layer_multiplicator, true);
			Motors.move_chariot(deplacement_chariot, true);
			SerialCom.update();
			delay(delay_all);
			//Serial.println("chariot*");
			if (SerialCom.stopped()) return;
			// Monter racleur
			Motors.move_lit(deplacement_lit * first_layer_multiplicator);
			SerialCom.update();
			delay(delay_all);
			//Serial.println("lit*");
			// Racleur retour
			Motors.move_chariot(0, true);
			SerialCom.update();
			//Serial.println("chariot retour*");
		}
		else {
			// Monter poudre
			Motors.move_poudre(deplacement_poudre);
			SerialCom.update();
			delay(delay_all);
			//Serial.println("poudre");
			// racleur aller
			Motors.move_chariot(deplacement_chariot, true);
			SerialCom.update();
			delay(delay_all);
			//Serial.println("chariot");
			if (SerialCom.stopped()) return;
			// Monter racleur
			Motors.move_lit(deplacement_lit);
			SerialCom.update();
			delay(delay_all);
			//Serial.println("lit");
			// Racleur retour
			Motors.move_chariot(0, true);
			SerialCom.update();
			//Serial.println("chariot retour");
		}
		passes++;
		Serial.println("inf08");
		while (SerialCom.update() == false) {} // A tester lol (nice, c'est bon grace au {})
		Serial.print("pas");
		Serial.print(passes);
		Serial.print(" ");
		Serial.println(total_number_of_layers);
		/*Serial.println(passes);
		Serial.println(first_layer_number_layers);
		Serial.println(total_number_of_layers);
		Serial.println("Done\n");*/
		delay(delay_m);
		if (SerialCom.stopped()) return;
		//Serial.println(delay_m * 1000);
	}
	SerialCom.is_running = false;
	Serial.println("inf05");
}