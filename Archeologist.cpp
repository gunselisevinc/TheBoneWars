#include "Archeologist.h"

Archeologist::Archeologist(const char nameInput[])
	:score{0}, energy{0}, trap{false}
{
	strcpy(name, nameInput);
}

void Archeologist::setEnergy(double energyInput)
{
	energy = energyInput;
}

void Archeologist::setTrap(bool trapInput)
{
	trap = trapInput;
}

size_t Archeologist::getScore() const
{
	return score;
}

double Archeologist::getEnergy() const
{
	return energy;
}

std::vector<Resources*>& Archeologist::getInventory()
{
	return inventory;
}

bool Archeologist::getTrap()
{
	return trap;
}

void Archeologist::modifyEnergy(double change)
{
	energy += change;
}

void Archeologist::modifyScore(size_t change)
{
	score += change;
}

void Archeologist::addResource(Resources* resourceInput)
{
	inventory.push_back(resourceInput);
	resourceInput->effect(*this);
	resourceInput->setClaimed(true);
}
