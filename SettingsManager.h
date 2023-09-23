#pragma once

#include <vector>

#include "SDcard.h"
#include "motors.h"

class SettingsManagerClass
{
public:
	SettingsManagerClass();
	void set_motors(MotorsClass*);
	void set_SDcard(SDcardClass*);
	void apply_steps_mm();
	void apply_motor_speeds();
	void apply_motor_acceleration();
private:
	SDcardClass* m_SDcard; // pointer sdcard
	MotorsClass* m_motors; // reference motors

};