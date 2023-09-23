#include "SettingsManager.h"


SettingsManagerClass::SettingsManagerClass() : m_SDcard(nullptr), m_motors(nullptr)
{
}

void SettingsManagerClass::set_motors(MotorsClass* motors)
{
	m_motors = motors;
}

void SettingsManagerClass::set_SDcard(SDcardClass* SDcard)
{
	m_SDcard = SDcard;
}

void SettingsManagerClass::apply_steps_mm()
{
	std::vector<String> settings = m_SDcard->get_settings();

	m_motors->set_poudre_step_mm(settings[0].toInt());
	//Serial.println("Poudre step/mm: " + settings[0].toInt());
	/*Serial.println(settings[0]);
	Serial.println("3");*/

	m_motors->set_chariot_step_mm(settings[1].toInt());
	//Serial.println("Poudre step/mm: " + settings[1].toInt());
	/*Serial.println(settings[1]);
	Serial.println("4");*/

	m_motors->set_lit_step_mm(settings[2].toInt());
	//Serial.println("Poudre step/mm: " + settings[2].toInt());
	/*Serial.println(settings[2]);
	Serial.println("5");*/

}

void SettingsManagerClass::apply_motor_speeds()
{
	std::vector<String> settings = m_SDcard->get_settings();

	m_motors->set_poudre_speed(settings[3].toInt());
	m_motors->set_chariot_speed(settings[4].toInt());
	m_motors->set_lit_speed(settings[5].toInt());
}

void SettingsManagerClass::apply_motor_acceleration()
{
	std::vector<String> settings = m_SDcard->get_settings();

	m_motors->set_poudre_acceleration(settings[6].toInt());
	m_motors->set_chariot_acceleration(settings[7].toInt());
	m_motors->set_lit_acceleration(settings[8].toInt());
}

