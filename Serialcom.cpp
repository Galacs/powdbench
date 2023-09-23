#include "Serialcom.h"

//void(*resetFunc) (void) = 0; //declare reset function @ address 0

SerialcomClass::SerialcomClass(SDcardClass& SDcard, MotorsClass& Motors, SettingsManagerClass& SettingsManager) : m_SDcard(SDcard), m_stopped(false),
				m_Motors(Motors), is_running(false), m_SerialCom(this),  m_SettingsManager(SettingsManager)
{
}


bool SerialcomClass::send_settings(std::vector<String> settings, SDcardClass& SDcard)
{
	if (!SDcard.is_initialized() || !SDcard.is_settings_loaded()) {
		return false;
	}
	Serial.print("par");
	for (String i : settings) {
		Serial.print(i + " ");
	}
	Serial.print('\n');
}

bool SerialcomClass::send_settings(std::vector<String> settings, char separator/* = ' '*/)
{

	if (!m_SDcard.is_initialized() || !m_SDcard.is_settings_loaded()) {
		Serial.println("2");
		return false;
	}

	Serial.print("par");
	for (String i : settings) {
		Serial.print(i + separator);
	}
	Serial.print('\n');
}

bool SerialcomClass::update()
{
	//update_serial();


	String raw;
	String data;
	String cmd_type;

	if (Serial.available())
	{
		raw = Serial.readStringUntil('\n');
		//Serial.println(raw);
		cmd_type = raw.substring(0, 3);
		data = raw.substring(3);
		//Serial.println(cmd_type);
		//Serial.println(data);

		// Si c'est une demande d'enregistrement
		if (cmd_type == "par") {
			std::vector<String> settings;
			String setting;
			for (char i : data) {
				if (i == ' ') {
					settings.push_back(setting);
					setting = "";
					continue;
				}
				setting += i;
			}
			settings.push_back(setting); // dernier car pas espace a la fin
			/*for (String i : settings) {
				Serial.println(i);
			}*/
			m_SDcard.set_settings(settings);
			m_SettingsManager.apply_steps_mm();
			m_SettingsManager.apply_motor_speeds();
			m_SettingsManager.apply_motor_acceleration();
		}

		else if (cmd_type == "apa") {
			send_settings(m_SDcard.get_settings(), ' ');
		}

		else if (cmd_type == "bbb"){
			auto settings = m_SDcard.get_settings();
			settings.pop_back();
			Serial.print("b01");
			Serial.println(settings[0]);

			Serial.print("b02");
			Serial.println(settings[1]);

			Serial.print("b03");
			Serial.println(settings[2]);

			Serial.print("b04");
			Serial.println(settings[3]);

			Serial.print("b05");
			Serial.println(settings[4]);

			Serial.print("b06");
			Serial.println(settings[5]);

			Serial.print("b07");
			Serial.println(settings[6]);

			Serial.print("b08");
			Serial.println(settings[7]);

			Serial.print("b09");
			Serial.println(settings[8]);

			Serial.print("b10");
			Serial.println(settings[9]);

			Serial.print("b11");
			Serial.println(settings[10]);

			Serial.print("b12");
			Serial.println(settings[11]);

			Serial.print("b13");
			Serial.println(settings[12]);

			Serial.print("b14");
			Serial.println(settings[13]);

			Serial.print("b15");
			Serial.println(settings[14]);

			Serial.print("b16");
			Serial.println(settings[15]);

			Serial.print("b17");
			Serial.println(settings[16]);

		}

		else if (cmd_type == "str") {
			Serial.println("inf04");
			m_start_function();
		}

		else if (cmd_type == "stp") {
			Serial.println("inf05");
			m_stopped = true;
		}

		else if (cmd_type == "mov") {
			std::vector<String> settings;
			String setting;
			for (char i : data) {
				if (i == ' ') {
					settings.push_back(setting);
					setting = "";
					continue;
				}
				setting += i;
			}
			settings.push_back(setting); // dernier car pas espace a la fin
			if (settings[0].toInt() == 1) {
				m_Motors.move_poudre(settings[1].toFloat(), false);
			}
			else if (settings[0].toInt() == 2) {
				m_Motors.move_chariot(settings[1].toFloat(), false);
			}
			else if (settings[0].toInt() == 3) {
				m_Motors.move_lit(settings[1].toFloat(), false);
			}
			Serial.print("mvd");
			Serial.println(settings[0]);
		}
		else if (cmd_type == "sep") {
			std::vector<String> settings;
			String setting;
			for (char i : data) {
				if (i == ' ') {
					settings.push_back(setting);
					setting = "";
					continue;
				}
				setting += i;
			}
			settings.push_back(setting); // dernier car pas espace a la fin
			m_Motors.move_poudre(settings[0].toFloat(), true);
			Serial.println("mvd1");

			m_Motors.move_chariot(settings[1].toFloat(), true);
			Serial.println("mvd2");

			m_Motors.move_lit(settings[2].toFloat(), true);

			Serial.println("mvd3");
		}
		else if (cmd_type == "pin") {
			Serial.println("pong!");
		}
		else if (cmd_type == "sta") {
			if (is_running == true) {
				Serial.println("run");
			}
			else if (is_running == false) {
				Serial.println("nru");
			}
		}
		else if (cmd_type == "hme") {
			m_Motors.go_home();
			Serial.println("inf06");
		}
		else if (cmd_type == "ctn") {
			Serial.println("inf07");
			return true;
		}
		else if (cmd_type == "pos") {
			Serial.print("pos");
			Serial.print(m_Motors.get_poudre_position());
			Serial.print(' ');
			Serial.print(m_Motors.get_chariot_position());
			Serial.print(' ');
			Serial.print(m_Motors.get_lit_position());
			Serial.println();
		}
		else if (cmd_type == "hm1") {
			m_Motors.move_poudre(0, true);
			Serial.println("mvd1");
		}
		else if (cmd_type == "hm2") {
			m_Motors.move_chariot(0, true);
			Serial.println("mvd2");
		}
		else if (cmd_type == "hm3") {
			m_Motors.move_lit(0, true);
			Serial.println("mvd3");
		}
		else if (cmd_type == "rst") {
			Serial.println("rst");
			delay(100);
			//resetFunc();
			ESP.restart();
			Serial.println("Reset!");
		}
	}
	return false;
}
/*void SerialcomClass::start_update_scheduler()
{
	Scheduler.startLoop(this->update());
}*/

void SerialcomClass::set_SDcard(SDcardClass& SDcard)
{
	m_SDcard = SDcard;
}

void SerialcomClass::set_motors(MotorsClass& Motors)
{
	m_Motors = Motors;
}

/*void(&SerialcomClass::get_update(void))(void)
{
	return *m_update;
}*/

void SerialcomClass::setStartFunction(void(& start_function)(void))
{
	m_start_function = start_function;
}

bool SerialcomClass::stopped()
{
	update();
	if (m_stopped) {
		m_stopped = false;
		return true;
	}
	else {
		return false;
	}
}

//extern SerialcomClass SerialCom;