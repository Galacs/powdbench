#pragma once
#include <AccelStepper.h>


class MotorsClass
{
public:
	MotorsClass(int poudre_type, int poudre_dir, int poudre_step,
		int chariot_type, int chariot_dir, int chariot_step,
		int lit_type, int lit_dir, int lit_step);

	void set_poudre_step_mm(int step_mm);
	void set_chariot_step_mm(int step_mm);
	void set_lit_step_mm(int step_mm);


	void set_poudre_position(int position);
	void set_chariot_position(int position);
	void set_lit_position(int position);

	void move_poudre(float mm, bool absolute = false);
	void move_chariot(float mm, bool absolute = false);
	void move_lit(float mm, bool absolute = false);

	void set_poudre_speed(int speed);
	void set_chariot_speed(int speed);
	void set_lit_speed(int speed);

	void set_poudre_acceleration(int acceleration);
	void set_chariot_acceleration(int acceleration);
	void set_lit_acceleration(int acceleration);

	void go_home();

	int get_poudre_position();
	int get_chariot_position();
	int get_lit_position();


	bool run();


private:

	AccelStepper m_poudre_motor;
	AccelStepper m_chariot_motor;
	AccelStepper m_lit_motor;

	int m_poudre_step_mm;
	int m_chariot_step_mm;
	int m_lit_step_mm;

};