#include "SDcard.h"

SDcardClass::SDcardClass(int spi_pin) : m_spi_pin(spi_pin)
{

}

bool SDcardClass::initialize()
{
    pinMode(m_spi_pin, OUTPUT);
    //Serial.print("Initializing SD card...");
    if (!SD.begin(5)) {
        //Serial.println("initialization failed!");
        Serial.println("err01");
        //delay(10000000);
        return false;
    }
    //Serial.println("initialization done.");
    Serial.println("inf01");
    m_initialized = true;
    return true;
}

bool SDcardClass::is_initialized()
{
    if (SD.begin(4) && m_initialized) {
        return true;
    }
}

int SDcardClass::get_spi_pin()
{
    return m_spi_pin;
}

void SDcardClass::set_spi_pin(int spi_pin)
{
    pinMode(m_spi_pin, INPUT);
    pinMode(spi_pin, OUTPUT);
    m_spi_pin = spi_pin;
}

bool SDcardClass::is_settings_loaded()
{
    return m_settingsLoaded;
}

std::vector<String> SDcardClass::get_settings()
{

    File settingsFile = SD.open("/settings.txt");

    std::vector<String> settings;
    std::string raw_settings;
    std::string setting;

    if (!settingsFile && !settingsFile.available()) {
        Serial.println("err02");
        return std::vector<String>({});
    }
    else {
        raw_settings += '\n';
        while (settingsFile.available()) {
            raw_settings += settingsFile.read();
        }
        settingsFile.close();
        for (char i : raw_settings) {
            //Serial.print(i);
            if (i == 10) { // 10 = newline
                settings.push_back(setting.c_str());
                setting = "";
            }
            setting += i;
        }
        settings.push_back(setting.c_str()); // a la fin du fichier y'a pas de newline
        settings.erase(settings.begin() + 0);
        settings[0] = settings[0].substring(1);
        setting = "";
        for (String& i : settings) {
            setting = i.c_str();
            setting.erase(std::remove(setting.begin(), setting.end(), '\n'), setting.end());
            i = setting.c_str();
        }

        //settings.pop_back();

        /*for (auto i : settings) {
            Serial.println("lecture: " + i);
        }*/

        m_settingsLoaded = true;
        Serial.println("inf02");

        return settings;
    }

}

bool SDcardClass::set_settings(std::vector<String> new_settings)
{
    m_settingsLoaded = true;
    if (!m_settingsLoaded) {
        return false;
    }
    SD.remove("/settings.txt");
    File settingsFile = SD.open("/settings.txt", FILE_WRITE);

    if (!settingsFile && !settingsFile.available()) {
        Serial.println("err03");
        return false;
    }
    else {
        for (String i : new_settings) {
            settingsFile.println(i);
            Serial.println("saving: " + i);
        }
        settingsFile.close();
        Serial.println("inf03");

    }
}
