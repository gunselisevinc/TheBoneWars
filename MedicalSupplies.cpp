#include "MedicalSupplies.h"
#include "Archeologist.h"
MedicalSupplies::MedicalSupplies()
{
	claimed = false;
	size = 1;
	boardChar = 'M';
}

void MedicalSupplies::effect(Archeologist& player)
{
	player.setTrap(false);
}
