#pragma once


#include "SDcard.h"
#include "motors.h"
#include "SettingsManager.h"

#include <vector>

//#include <Scheduler.h>

//void update_serial();

class SerialcomClass
{
public:
	SerialcomClass(SDcardClass& SDcard, MotorsClass& Motors, SettingsManagerClass& SettingsManager);
	bool update();
	bool send_settings(std::vector<String> settings, SDcardClass& SDcard);
	bool send_settings(std::vector<String> settings, char separator = ' ');
	//void start_update_scheduler(void(*update_function)(void));
	void set_SDcard(SDcardClass& SDcard);
	void set_motors(MotorsClass& Motors);
	//void set_update(void(&) (void));
	//void(&get_update()) (void);
	void setStartFunction(void(&) (void));
	bool stopped();
	
	bool is_running;
	SDcardClass& m_SDcard; // reference contenant SDcard
	MotorsClass& m_Motors;

	//void(*m_update_function)(void);

private:
	void(*m_start_function)(void);
	bool m_stopped;
	SerialcomClass* m_SerialCom;
	SettingsManagerClass& m_SettingsManager;
};

//extern SerialcomClass SerialCom;