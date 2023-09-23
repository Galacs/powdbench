#include "motors.h"


MotorsClass::MotorsClass(int poudre_type, int poudre_dir, int poudre_step,
	int chariot_type, int chariot_dir, int chariot_step,
	int lit_type, int lit_dir, int lit_step) : m_poudre_step_mm(0), m_chariot_step_mm(0), m_lit_step_mm(0),
	m_poudre_motor(poudre_type, poudre_step, poudre_dir),
	m_chariot_motor(chariot_type, chariot_step, chariot_dir),
	m_lit_motor(lit_type, lit_step, lit_dir)
{
}

void MotorsClass::set_poudre_step_mm(int step_mm)
{
	m_poudre_step_mm = step_mm;
	/*Serial.print("poudre step: ");
	Serial.println(step_mm);*/
}

void MotorsClass::set_chariot_step_mm(int step_mm)
{
	m_chariot_step_mm = step_mm;
	/*Serial.print("chariot step: ");
	Serial.println(step_mm);*/

}

void MotorsClass::set_lit_step_mm(int step_mm)
{
	m_lit_step_mm = step_mm;
	/*Serial.print("lit step: ");
	Serial.println(step_mm);*/

}

void MotorsClass::set_poudre_position(int position)
{
	m_poudre_motor.moveTo(position * m_poudre_step_mm);
}

void MotorsClass::set_chariot_position(int position)
{
	m_chariot_motor.moveTo(position * m_chariot_step_mm);
}

void MotorsClass::set_lit_position(int position)
{
	m_lit_motor.moveTo(position * m_lit_step_mm);
}

void MotorsClass::move_poudre(float mm, bool absolute/* = false*/)
{
	if (!absolute) {
		m_poudre_motor.runToNewPosition(m_poudre_motor.currentPosition() + ((round(mm)) * m_poudre_step_mm));
	}
	else {
		m_poudre_motor.runToNewPosition(round(mm) * m_poudre_step_mm);
	}
}

void MotorsClass::move_chariot(float mm, bool absolute/* = false*/)
{
	if (!absolute) {
		m_chariot_motor.runToNewPosition(m_chariot_motor.currentPosition() + ((round(mm)) * m_chariot_step_mm));
	}
	else {
		m_chariot_motor.runToNewPosition(round(mm) * m_chariot_step_mm);
	}
}

void MotorsClass::move_lit(float mm, bool absolute/* = false*/)
{
	if (!absolute) {
		m_lit_motor.runToNewPosition(m_lit_motor.currentPosition() + ((round(mm) * m_lit_step_mm)));
	}
	else {
		m_lit_motor.runToNewPosition(round(mm) * m_lit_step_mm);
	}
}

void MotorsClass::set_poudre_speed(int speed)
{
	m_poudre_motor.setMaxSpeed(speed * m_poudre_step_mm);
	m_poudre_motor.setSpeed(speed * m_poudre_step_mm);
}

void MotorsClass::set_chariot_speed(int speed)
{
	m_chariot_motor.setMaxSpeed(speed * m_chariot_step_mm);
	m_chariot_motor.setSpeed(speed * m_chariot_step_mm);
}

void MotorsClass::set_lit_speed(int speed)
{
	m_lit_motor.setMaxSpeed(speed * m_lit_step_mm);
	m_lit_motor.setSpeed(speed * m_lit_step_mm);
	/*Serial.println("Speed total: " + String(speed * m_lit_step_mm));
	Serial.println("step per mm: " + String(m_lit_step_mm));
	Serial.println("Speed: " + String(speed));*/
}

void MotorsClass::set_poudre_acceleration(int acceleration)
{
	m_poudre_motor.setAcceleration(acceleration * m_poudre_step_mm);
}

void MotorsClass::set_chariot_acceleration(int acceleration)
{
	m_chariot_motor.setAcceleration(acceleration * m_chariot_step_mm);
}

void MotorsClass::set_lit_acceleration(int acceleration)
{
	m_lit_motor.setAcceleration(acceleration * m_lit_step_mm);
}

void MotorsClass::go_home()
{
	m_poudre_motor.runToNewPosition(0);
	m_chariot_motor.runToNewPosition(0);
	m_lit_motor.runToNewPosition(0);
}

int MotorsClass::get_poudre_position()
{
	return m_poudre_motor.currentPosition() / m_poudre_step_mm;
}

int MotorsClass::get_chariot_position()
{
	return m_chariot_motor.currentPosition() / m_chariot_step_mm;
}

int MotorsClass::get_lit_position()
{
	return m_lit_motor.currentPosition() / m_lit_step_mm;
}

bool MotorsClass::run()
{
	if (m_poudre_motor.distanceToGo() == 0 &&
		m_chariot_motor.distanceToGo() == 0 &&
		m_lit_motor.distanceToGo() == 0) return false;

	m_poudre_motor.run();
	m_chariot_motor.run();
	m_lit_motor.run();
	return true;
}