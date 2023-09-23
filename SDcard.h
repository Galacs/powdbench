#pragma once
#include <SD.h>
#include <SPI.h>
#include <string>
#include <vector>



class SDcardClass
{
public:
	// Spi pin
	SDcardClass(int spi_pin = 5); // Contructeur
	bool initialize(); // initialize la connection sd
	bool is_initialized(); // check si la carte sd est initilisé
	int get_spi_pin(); // methode pour avoir le spi pin actuel
	void set_spi_pin(int spi_pin); // changer le spi pin
	bool is_settings_loaded(); // es ce que les settings sont loede
	std::vector<String> get_settings(); // donne les settings
	bool set_settings(std::vector<String>); // set les settings

	std::vector<String> m_settings; // map des parametres


private:
	// Spi pin
	int m_spi_pin; // variable contenant le pin du spi
	bool m_initialized = false; // variable contenant l'etat d'initilisation de la carte sd
	bool m_settingsLoaded; // es ce que les settings sont loede
};