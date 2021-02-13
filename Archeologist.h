#pragma once
#pragma warning(disable:4996)
#include <vector>
#include "Resources.h"
class Archeologist
{
	char name[6];
	size_t score;
	double energy;
	std::vector<Resources*> inventory;
	bool trap;

public:
	//Constructors
	Archeologist(const char nameInput[]);

	//Setters & Getters
	void setEnergy(double energyInput);
	void setTrap(bool trapInput);

	size_t getScore() const;
	double getEnergy() const;
	std::vector<Resources*>& getInventory();
	bool getTrap();

	//Other Methods
	void modifyEnergy(double change);
	void modifyScore(size_t change);
	void addResource(Resources* resourceInput);
};
